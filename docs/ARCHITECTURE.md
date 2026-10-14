# Architecture contract

The retail executable targets the Nintendo 64's big-endian MIPS III R4300 with
the 32-bit o32 ABI. Binary matching must retain instruction ordering, delay-slot
behavior, alignment, and exact big-endian layouts.

A future PS Vita target is little-endian ARMv7-A (Cortex-A9), using 32-bit
ARM/Thumb and ILP32. It is not AArch64. Vita builds must inspect compiler
identity and ELF attributes for consistent floating-point ABI across every
object and dependency; CPU floating-point capability does not determine ABI.

Development hosts differ: Linux/WSL x86-64 normally uses LP64 and Windows x64
uses LLP64. Portable code must use fixed-width integers and endian-aware access
for persisted structures, wire formats, checksums, and emulated pointer tokens.
It must not globally pack structs or truncate real host pointers. Host tests
need compile-time layout assertions where they model original structures, but
host/emulator success never proves physical Vita correctness.
