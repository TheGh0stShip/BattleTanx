# Completion verification

BattleTanx USA Rev 0 is a 100% matching decompilation. The figures below were
regenerated and verified on 2026-10-16; they are also enforced by the project
tests and the report generated in CI.

## Retail ROM identity

The reference ROM is not included in the repository. Verification used a
legally obtained, big-endian 8 MiB dump with this identity:

| Property | Expected and verified value |
|---|---|
| Title | `BATTLETANX` |
| Serial | `NBXE` |
| Region/revision | USA, Rev 0 |
| Size | 8,388,608 bytes |
| SHA-1 | `535860d941738ac1210c20a9b80114fea0e0ff17` |
| SHA-256 | `c5b7cf3523de025e3f18e2c8df2deb0eced5613e7c46cb8c6c5a4f22644ead3f` |

These values are the repository's ROM contract. Tools that consume the ROM
reject an input that does not match it.

## Completion evidence

`make report` generated the following audited totals:

| Measure | Matched | Total | Progress |
|---|---:|---:|---:|
| Code | 703,452 bytes | 703,452 bytes | 100% |
| Functions | 1,738 | 1,738 | 100% |
| Initialized data | 153,924 bytes | 153,924 bytes | 100% |
| Asset region | 7,335,936 bytes | 7,335,936 bytes | 100% |

The full ROM-backed verifier accepted all 1,563 matching source units. Its
manifest total is 704,012 verified code bytes because it also includes the
authentic boot and low-level assembly ranges outside the report's canonical
function-code denominator. It additionally verified all 153,924 initialized
data bytes.

The canonical generated split contains no remaining function `asm` segments.
Every catalogued function maps to a verified C or authentic source-assembly
unit.

## Reproducing the checks

Place the verified ROM at `baseroms/us/baserom.z64`, then run:

```sh
sha1sum baseroms/us/baserom.z64
sha256sum baseroms/us/baserom.z64
python3 tools/verify_matching_units.py
make check
make report
git diff --check
```

The completion gate requires:

- every compiled or assembled unit to match its complete relocated retail byte
  range;
- all initialized-data manifest ranges to match the corresponding ROM bytes;
- the generated report to remain at 100% code, functions, and initialized
  data;
- the asset ledger to cover its entire region without gaps, overlaps, or
  unknown ranges;
- repository safety and metadata tests to pass.

Compiler and assembler compatibility rules are function-scoped, fail closed on
source drift, and have negative tests proving that they do not alter unrelated
translation units. They preserve the original code semantics while reproducing
the retail KMC/SN toolchain's allocation, scheduling, and assembly behavior.
