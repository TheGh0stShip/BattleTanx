# Third-party notices

Unless stated otherwise below, the source and documentation in this repository
are licensed under GNU GPL version 3 only, as provided in `COPYING`.

## Research incorporated under GPL-3.0

- Function-boundary research in `config/us/recomp_function_boundaries.toml`
  derives from `bdragoncore/battle-tanx-recomp` and its contributors.
- Byte-identical source candidates and comparative research were obtained from
  the VitaTanx/Global Assault matching decompilation. Every imported candidate
  was independently rebuilt and checked against BattleTanx before acceptance.

These GPL-derived portions remain covered by GPL-3.0. More detailed provenance
is recorded in `docs/PROVENANCE.md`.

## Separately licensed tooling

- `tools/modern_asn64.py` derives from RocketRet's `modern_asn64`, distributed
  under the Unlicense. BattleTanx-specific compatibility rules and surrounding
  project integration are distributed under GPL-3.0.
- Splat is installed as an external, pinned dependency and retains its own
  upstream license. It is not vendored into this repository.

## Excluded proprietary material

BattleTanx, its ROM, executable, artwork, audio, levels, and other game data
remain the property of their respective rights holders. None is licensed by
this repository, and none is included. Users must supply a legally obtained
USA Rev 0 ROM for verification and local reconstruction.
