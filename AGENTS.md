# Project instructions

This is a matching decompilation of BattleTanx (N64, USA Rev 0) and the source
foundation for later native ports. Keep matching work distinct from portability
changes. Never commit ROMs, ROM-extracted assets, generated assembly, binaries,
crash dumps, or private hardware evidence.

## Architectures

- Original game: big-endian MIPS III/R4300, 32-bit o32 ABI. Preserve N64 widths,
  alignment, delay slots, and big-endian ROM/data layouts while matching.
- PS Vita: little-endian ARMv7-A Cortex-A9, 32-bit ARM/Thumb, ILP32 (`int`,
  `long`, pointers, and `size_t` are 32-bit). It is not AArch64.
- Linux/WSL x86-64 is normally LP64; Windows x64 is LLP64. Host probes must use
  explicit widths and endian-safe access at ROM, disk, wire, checksum, and
  pointer-token boundaries. Never globally pack structs or truncate live host
  pointers.
- Before accepting Vita output, inspect the compiler and dependency ELF
  attributes for hard-float/softfp consistency. CPU capability does not prove
  the ABI. Check ARM alignment and calling conventions.

Host or emulator success is not physical-Vita evidence. A Vita release gate
requires a clean cross-build plus supervised physical-hardware testing.

## Workflow gates

1. Verify the base ROM before extraction or comparison.
2. Keep generated `asm/`, extracted assets, and build products untracked.
3. Support matching claims with an object/ROM byte comparison.
4. Preserve original 32-bit semantics in portability work and add host layout
   assertions at relevant boundaries.
5. Do not deploy to hardware without an explicitly supervised test request.
