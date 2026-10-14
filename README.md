# BattleTanx — matching decompilation

This repository bootstraps a matching decompilation of **BattleTanx** for
Nintendo 64 (USA Rev 0). It currently provides a verified ROM contract and a
1,685-entry function catalogue covering the game's loaded 1 MiB program region.
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
make check
```

`make setup` creates a local virtual environment with pinned dependencies and
regenerates the splat configuration from the reviewed catalogue. `make split`
produces ignored assembly for analysis. `make check` runs ROM-independent
metadata, architecture, and repository-safety tests.

## Status and provenance

The catalogue is derived from the GPL-3.0 BattleTanx static-recompilation
symbol table by bdragoncore and contributors, with its comments and known
caveats retained in `config/us/recomp_function_boundaries.toml`. It is valuable
boundary research, not proof that the functions are decompiled or matching.
The generator rejects out-of-range, unaligned, or overlapping canonical
function ranges. Aliases contained inside another function remain in the
catalogue but are not emitted as duplicate splat segments.

The initial split accounts for the full 8 MiB ROM: 1,568 non-overlapping
function ranges produce about 701 KiB of generated assembly, while gaps and the
resource area remain explicit binary regions. Two hundred eighty-five reviewed C source units
now reconstruct 18,628 retail bytes. The 45 libultra units include the
ten-function 64-bit
arithmetic runtime, controller CRC routines, heap routines, byte copy, and
string primitives, audio bus/save processing, and low-level AI/SI/SP accessors.
`make verify-matching`
compiles every manifest entry with pinned IDO 5.3 and compares every emitted
byte directly with the supported ROM.

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

Two authentic source-assembly units additionally reconstruct the contiguous
80-byte cache-maintenance and CP0-status block at ROM `0x71BC-0x720C`. These
remain assembly because they directly use `cache`, `mfc0`, and `mtc0`; rewriting
them as ordinary C would misrepresent the original low-level implementation.

See `docs/ARCHITECTURE.md` and `docs/PROVENANCE.md` before contributing.

## License

Project-authored code and imported GPL research are GPL-3.0; see `COPYING`.
BattleTanx and its game data remain the property of their respective holders.
