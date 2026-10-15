#!/usr/bin/env python3
"""Parse and validate BattleTanx (US Rev 0) libaudio banks and MIDI sequences.

Consumers:
  load_audio_banks 0x8007A004: DMA ctl 0x215620..0x217EC0, alBnkfNew(ctl, PI 0xB0100000);
                               DMA ctl 0x298D60..0x29A710, alBnkfNew(ctl, PI 0xB0217EC0);
                               scans PI table 0x80125714 (20 words) for the largest sequence.
  apply_audio_sequence 0x80079C20: DMA table[i-1]..table[i] then alSeqNew 0x80119A78
                               (checks 'MThd'/'MTrk').
Usage: audio_banks.py REPO OUTDIR
"""
import hashlib, struct, sys
from pathlib import Path

ROM_SHA1 = "535860d941738ac1210c20a9b80114fea0e0ff17"
BANKS = (("sfx", 0x215620, 0x217EC0, 0x100000, 0x215620),
         ("music", 0x298D60, 0x29A710, 0x217EC0, 0x298D60))
SEQ_TABLE_ROM = 0x80125714 - 0x80070000
SEQ_COUNT = 19
LEDGER_START = 0x100000  # splat main segment nominally ends at 0x101000; sfx tbl base is 0x100000


class Fail(Exception):
    pass


def u32(b, o): return struct.unpack_from(">I", b, o)[0]
def s16(b, o): return struct.unpack_from(">h", b, o)[0]


def parse_bank(rom, name, cs, ce, ts, te):
    ctl = rom[cs:ce]
    structs = {}  # offset -> (kind, size, detail)

    def add(off, kind, size, detail=""):
        if off in structs:
            if tuple(structs[off][:2]) != (kind, size):
                raise Fail(f"{name}: conflicting structs at 0x{off:X}")
            structs[off][3] += 1
            return False
        if off <= 0 or off + size > len(ctl):
            raise Fail(f"{name}: {kind} 0x{off:X} out of range")
        structs[off] = [kind, size, detail, 1]
        return True

    rev, nb = struct.unpack_from(">Hh", ctl, 0)
    if rev != 0x4231:
        raise Fail(f"{name}: bad revision")
    structs[0] = ["ALBankFile", 4 + 4 * nb, f"rev=B1 banks={nb}", 1]
    waves = {}
    for bi in range(nb):
        b = u32(ctl, 4 + 4 * bi)
        ni = s16(ctl, b)
        flags, rate, perc = ctl[b + 2], u32(ctl, b + 4), u32(ctl, b + 8)
        add(b, "ALBank", 12 + 4 * ni, f"bank={bi} insts={ni} flags={flags} rate={rate} perc=0x{perc:X}")
        insts = [u32(ctl, b + 12 + 4 * i) for i in range(ni)] + ([perc] if perc else [])
        for ii in insts:
            if not ii:
                continue
            ns = s16(ctl, ii + 14)
            if not add(ii, "ALInstrument", 16 + 4 * ns, f"vol={ctl[ii]} pan={ctl[ii+1]} prio={ctl[ii+2]} sounds={ns}"):
                continue
            for si in range(ns):
                s = u32(ctl, ii + 16 + 4 * si)
                env, km, wt = u32(ctl, s), u32(ctl, s + 4), u32(ctl, s + 8)
                if not add(s, "ALSound", 16, f"pan={ctl[s+12]} vol={ctl[s+13]} flags={ctl[s+14]}"):
                    continue
                at, dt, rt = struct.unpack_from(">iii", ctl, env)
                add(env, "ALEnvelope", 16, f"atk={at} dec={dt} rel={rt} av={ctl[env+12]} dv={ctl[env+13]}")
                add(km, "ALKeyMap", 6, "vel={}-{} key={}-{} base={} detune={}".format(*ctl[km:km + 6]))
                base, length = u32(ctl, wt), u32(ctl, wt + 4)
                wtype, wflags = ctl[wt + 8], ctl[wt + 9]
                loop, book = u32(ctl, wt + 12), u32(ctl, wt + 16)
                if wtype != 0:
                    raise Fail(f"{name}: non-ADPCM wave 0x{wt:X}")
                if add(wt, "ALWaveTable", 20, f"base=0x{base:X} len=0x{length:X} type=ADPCM loop=0x{loop:X} book=0x{book:X}"):
                    waves.setdefault((base, length), []).append(wt)
                if loop:
                    st, en, cnt = u32(ctl, loop), u32(ctl, loop + 4), u32(ctl, loop + 8)
                    add(loop, "ALADPCMloop", 44, f"start={st} end={en} count={cnt if cnt < 0x80000000 else cnt - (1 << 32)}")
                order, npred = struct.unpack_from(">ii", ctl, book)
                if not (1 <= order <= 8 and 1 <= npred <= 16):
                    raise Fail(f"{name}: bad book 0x{book:X}")
                add(book, "ALADPCMBook", 8 + 16 * order * npred, f"order={order} npredictors={npred}")
    # coverage of ctl
    rows, pos = [], 0
    for off in sorted(structs):
        kind, size, detail, refs = structs[off]
        if off < pos:
            raise Fail(f"{name}: overlap at 0x{off:X}")
        if off > pos:
            gap = ctl[pos:off]
            if any(gap):
                raise Fail(f"{name}: unexplained ctl gap 0x{pos:X}..0x{off:X} {gap.hex()}")
            rows.append((name, "ctl", "padding", cs + pos, cs + off, pos, off, f"fill=00 align", 0))
        rows.append((name, "ctl", kind, cs + off, cs + off + size, off, off + size, detail, refs))
        pos = off + size
    if pos != len(ctl):
        tail = ctl[pos:]
        if any(tail):
            raise Fail(f"{name}: ctl tail 0x{pos:X} {tail[:32].hex()}")
        rows.append((name, "ctl", "padding", cs + pos, ce, pos, len(ctl), "fill=00 tail", 0))
    # tbl coverage
    tpos = 0
    tlen = te - ts
    for (base, length) in sorted(waves):
        refs = waves[(base, length)]
        if base < tpos:
            raise Fail(f"{name}: wave 0x{base:X} overlaps previous / precedes region")
        if base > tpos:
            gap = rom[ts + tpos:ts + base]
            fill = set(gap)
            rows.append((name, "tbl", "padding" if fill <= {0} else "gap_nonzero", ts + tpos, ts + base, tpos, base,
                         "fill=00" if fill <= {0} else f"nonzero bytes={sum(1 for x in gap if x)}", 0))
        rows.append((name, "tbl", "adpcm_wave", ts + base, ts + base + length, base, base + length,
                     f"frames9={length // 9} rem={length % 9} wavetables=" + ",".join(f"0x{w:X}" for w in refs), len(refs)))
        tpos = base + length
    if tpos > tlen:
        raise Fail(f"{name}: tbl overrun")
    if tpos < tlen:
        gap = rom[ts + tpos:te]
        rows.append((name, "tbl", "padding" if not any(gap) else "gap_nonzero", ts + tpos, te, tpos, tlen,
                     "fill=00 tail" if not any(gap) else f"nonzero bytes={sum(1 for x in gap if x)}", 0))
    return rows, structs, waves


def read_vlq(d, o):
    v = 0
    for _ in range(4):
        c = d[o]; o += 1
        v = (v << 7) | (c & 0x7F)
        if not c & 0x80:
            return v, o
    raise Fail("bad VLQ")


def parse_track(d, o, end):
    running, events = None, 0
    while o < end:
        _, o = read_vlq(d, o)
        st = d[o]
        if st == 0xFF:
            typ = d[o + 1]
            ln, o = read_vlq(d, o + 2)
            o += ln; events += 1
            if typ == 0x2F:
                if ln != 0:
                    raise Fail("EOT length")
                return o, events
            continue
        if st in (0xF0, 0xF7):
            ln, o = read_vlq(d, o + 1); o += ln; events += 1; continue
        if st & 0x80:
            running = st; o += 1
        elif running is None:
            raise Fail("data byte without running status")
        n = 1 if (running & 0xF0) in (0xC0, 0xD0) else 2
        if any(x & 0x80 for x in d[o:o + n]):
            raise Fail("bad data byte")
        o += n; events += 1
    raise Fail("no end-of-track")


def parse_midi(rom, idx, s, e):
    d = rom[s:e]
    if d[:4] != b"MThd" or u32(d, 4) != 6:
        raise Fail(f"seq {idx}: MThd")
    fmt, ntr, div = struct.unpack_from(">HHH", d, 8)
    o, evs = 14, 0
    for t in range(ntr):
        if d[o:o + 4] != b"MTrk":
            raise Fail(f"seq {idx}: MTrk")
        ln = u32(d, o + 4)
        end, n = parse_track(d, o + 8, o + 8 + ln)
        if end != o + 8 + ln:
            raise Fail(f"seq {idx}: EOT at 0x{end:X} != chunk end 0x{o+8+ln:X}")
        evs += n; o = end
    pad = d[o:]
    if any(pad):
        raise Fail(f"seq {idx}: nonzero padding")
    return dict(index=idx, rom_start=s, rom_end=e, midi_end=s + o, format=fmt, tracks=ntr, division=div,
                track_len=ln, events=evs, pad=len(pad), sha1=hashlib.sha1(d[:o]).hexdigest())


def main():
    rom = (Path(sys.argv[1]) / "baseroms/us/baserom.z64").read_bytes()
    if hashlib.sha1(rom).hexdigest() != ROM_SHA1:
        sys.exit("ROM SHA-1 mismatch")
    out = Path(sys.argv[2]); out.mkdir(parents=True, exist_ok=True)
    all_rows, summary = [], {}
    for b in BANKS:
        rows, structs, waves = parse_bank(rom, *b)
        all_rows += rows
        kinds = {}
        for k, sz, _, refs in structs.values():
            kinds.setdefault(k, [0, 0, 0]); kinds[k][0] += 1; kinds[k][1] += sz; kinds[k][2] += refs
        summary[b[0]] = (kinds, waves)
    with open(out / "audio_banks.tsv", "w") as f:
        f.write("bank\tfile\tkind\trom_start\trom_end\tfile_start\tfile_end\tsize\tdetail\trefs\n")
        for r in all_rows:
            f.write(f"{r[0]}\t{r[1]}\t{r[2]}\t0x{r[3]:06X}\t0x{r[4]:06X}\t0x{r[5]:X}\t0x{r[6]:X}\t{r[4]-r[3]}\t{r[7]}\t{r[8]}\n")
    table = struct.unpack_from(">20I", rom, SEQ_TABLE_ROM)
    seqs = [parse_midi(rom, i, table[i] - 0xB0000000, table[i + 1] - 0xB0000000) for i in range(SEQ_COUNT)]
    with open(out / "midi_sequences.tsv", "w") as f:
        f.write("index\trom_start\trom_end\tmidi_end\tformat\ttracks\tdivision\ttrack_len\tevents\tpad_bytes_fill00\tsha1\n")
        for q in seqs:
            f.write(f"{q['index']}\t0x{q['rom_start']:06X}\t0x{q['rom_end']:06X}\t0x{q['midi_end']:06X}\t{q['format']}\t"
                    f"{q['tracks']}\t{q['division']}\t{q['track_len']}\t{q['events']}\t{q['pad']}\t{q['sha1']}\n")
    # ledger
    led = [(r[3], r[4], f"{r[0]}_{r[1]}", r[2], r[7]) for r in all_rows]
    for q in seqs:
        led.append((q["rom_start"], q["midi_end"], "midi", "midi_sequence", f"seq {q['index']}"))
        if q["pad"]:
            led.append((q["midi_end"], q["rom_end"], "midi", "padding", "fill=00"))
    led.sort()
    pos = LEDGER_START
    for s, e, *_ in led:
        if s != pos:
            raise Fail(f"ledger gap/overlap at 0x{pos:X} vs 0x{s:X}")
        pos = e
    if pos != table[-1] - 0xB0000000:
        raise Fail("ledger end")
    with open(out / "ledger.tsv", "w") as f:
        f.write("rom_start\trom_end\tsize\tgroup\tkind\tdetail\n")
        for s, e, g, k, d in led:
            f.write(f"0x{s:06X}\t0x{e:06X}\t{e-s}\t{g}\t{k}\t{d}\n")
    tot = {}
    for s, e, g, k, d in led:
        tot[(g, k)] = tot.get((g, k), 0) + e - s
    for k, v in sorted(tot.items()):
        print(f"{k[0]:10s} {k[1]:14s} {v}")
    for n, (kinds, waves) in summary.items():
        print(n, {k: v for k, v in kinds.items()}, "unique waves", len(waves))
    print("ledger OK 0x%X..0x%X" % (LEDGER_START, pos))


if __name__ == "__main__":
    main()
