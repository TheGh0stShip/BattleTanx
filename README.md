# BattleTanx decompilation

This repository contains the decompilation of **BattleTanx** for
Nintendo 64 (USA Rev 0). It currently provides a verified ROM contract and a
1,700-entry function catalogue covering the game's loaded 1 MiB program region.
Generated disassembly is deliberately untracked; reviewed C and authentic
source assembly will replace it incrementally.

No ROM or ROM-derived assets are included. Supply your own legally obtained
dump.

## Supported ROM

- Title: `BATTLETANX`
- Region/revision: USA, Rev 0 (`NBXE`)
- Format: big-endian `.z64`
- Size: 8 MiB
- SHA-1: `535860d941738ac1210c20a9b80114fea0e0ff17`
- SHA-256: `c5b7cf3523de025e3f18e2c8df2deb0eced5613e7c46cb8c6c5a4f22644ead3f`

## Quick start

```sh
python3 tools/prepare_rom.py --input /absolute/path/to/BattleTanx.z64 \
  --output baseroms/us/baserom.z64
make setup
make split
make verify-matching
make report
make asset-catalogue
make data-survey
make check
```

`make setup` creates a local virtual environment with pinned dependencies and
regenerates the splat configuration from the reviewed catalogue. `make split`
produces ignored assembly for analysis. `make check` runs ROM-independent
metadata, architecture, and repository-safety tests.

`make verify-matching` installs the hash-pinned IDO, KMC GCC, and SN Systems
GCC matching toolchains under ignored `.toolchain/` paths. The SN lane builds
the GCC 2.8.0 runtime sources through Wibo and converts its Psy-Q objects to
big-endian ELF before the same relocation-aware ROM comparison used elsewhere.

`make asset-catalogue` validates and decodes the currently identified retail
resource bundles into an ignored JSON catalogue under `build/us/assets/`.
`make data-survey` produces ignored JSON and Markdown maps of the initialized
program image. Both commands verify the USA Rev 0 ROM before reading it. To
materialize individual bundle entries for local editor work, run
`python3 tools/battletanx_assets.py extract`; extracted binaries remain under
ignored `build/` paths and must never be committed.

## Status and provenance

The catalogue is derived from the GPL-3.0 BattleTanx static-recompilation
symbol table by bdragoncore and contributors, with its comments and known
caveats retained in `config/us/recomp_function_boundaries.toml`. It is valuable
boundary research, not proof that the functions are decompiled or matching.
The generator rejects out-of-range, unaligned, or overlapping canonical
function ranges. Aliases contained inside another function remain in the
catalogue but are not emitted as duplicate splat segments.

The initial split accounts for the full 8 MiB ROM: 1,739 non-overlapping
function ranges produce 703,444 bytes of generated assembly, while gaps and the
resource area remain explicit binary regions. The 1,457 compiler-built source
units now reconstruct 449,616 retail code bytes. Together with 17 authentic
source-assembly units, 1,474 matching units reconstruct 450,964 code bytes.
Eighty-three of the compiler-built units are data-only translation units whose initialized sections are verified
independently. The
168 libultra and compiler-runtime units include the
ten-function 64-bit
arithmetic runtime, controller CRC routines, heap routines, byte copy, and
string primitives, audio synthesis and effects processing, timer services, VI
management, audio bus/save processing, low-level AI/SI/SP accessors, controller
polling, Controller Pak file operations, and motor support.
`make verify-matching`
compiles every manifest entry with pinned IDO 5.3 and compares every emitted
byte directly with the supported ROM.

The project is listed through the root [`.recomp.json`](.recomp.json) manifest.
Every CI run on the default branch publishes an objdiff v2 progress artifact
named `NBXE_report`, with `report.json` generated from the reviewed function
catalogue and the four byte-verified matching manifests. This is the artifact
contract consumed by [recomp.fyi](https://recomp.fyi/); locally, `make report`
writes the same ignored report under
`build/` without requiring a ROM. Report policy and strict manifest validation
are provided by [Decompkit](docs/DECOMPKIT.md) through
`config/decompkit.toml`. Code and data are reported separately. Data progress
advances only when reviewed `.data`, `.rodata`, or `.rdata` ranges are added to
the section-aware matching-data manifest. All 153,924 initialized-data bytes are
currently verified. Uncatalogued instructions, linker padding, and ranges
reserved for separate code/library work are audited independently and are not
misreported as data. This includes effect scripts, HUD and level-map metadata, briefing text,
image descriptors, opponent-wave configuration, and the remaining typed constant
and initialized-data ranges. Unknown non-function bytes are never credited as
reconstructed data.
Asset identification is tracked separately over the ROM's asset region. A byte
is classified only when its boundaries and encoding are supported by recovered
code and validated against the retail ROM. The canonical ledger covers every
asset-region byte exactly once, distinguishing payloads and containers from
padding and parsed-but-unreferenced data. Some bundle entries remain semantically
unidentified even though their enclosing format and byte range are proven.

```text
code       [█████████████░░░░░░░]  64.03%    450,404 / 703,444 bytes
data       [████████████████████] 100.00%    153,924 / 153,924 bytes
functions  [███████████████████░]  94.59%       1,645 / 1,739
assets     [████████████████████] 100.00%  7,335,936 / 7,335,936 bytes
```

The game-owned KMC GCC units cover string and list helpers, state initialization
and predicates, vector copying, matrix state setup, two matrix multiplication
routines, a byte-sum helper, and a 16-bit angular-distance helper. Their
target-address names were corrected for BattleTanx rather than retaining Global
Assault addresses.
Twelve additional leaf routines were recovered directly from the BattleTanx
split, including ten no-op callbacks, a field setter, and a pointer-offset
helper.
The adjacent object-accessor cluster adds three typed field reads, a field
initializer, a boolean presence check, and a constant-zero leaf.

The opening narrative sequence is reconstructed as one original translation
unit: 28,652 bytes of state-machine and display-list code plus its 420-byte
literal pool. Its raw KMC output requires the opt-in ASN64 compatibility lane;
both sections are still compared byte-for-byte at their retail addresses.

Two authentic source-assembly units additionally reconstruct the contiguous
80-byte cache-maintenance and CP0-status block at ROM `0x71BC-0x720C`. These
remain assembly because they directly use `cache`, `mfc0`, and `mtc0`; rewriting
them as ordinary C would misrepresent the original low-level implementation.

See `docs/ARCHITECTURE.md` and `docs/PROVENANCE.md` before contributing.

## License

Project-authored code and imported GPL research are GPL-3.0; see `COPYING`.
BattleTanx and its game data remain the property of their respective holders.
