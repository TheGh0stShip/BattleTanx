# Global Assault cross-project reuse audit

The completed [BattleTanx: Global Assault matching decompilation](https://github.com/TheGh0stShip/BattleTanx-Global-Assault)
is a useful comparative corpus for this project. This audit was made against
Global Assault commit `63595f4dbcd2c4b64aa32bf90d4da2e2f86d60c1` on 2026-10-14.
Nothing from that project establishes a BattleTanx match by itself: every
candidate must still compile against the pinned BattleTanx toolchain and match
the verified USA Rev 0 ROM bytes.

## Immediately reusable

| Area | Global Assault material | BattleTanx use |
| --- | --- | --- |
| Matching infrastructure | `tools/decompkit/`, especially `units`, `tables`, `rewrite`, `registers`, and `gcc_alloc` | Decompkit configuration and strict manifest parsing now drive the production progress report. Replace the remaining title-specific verification internals incrementally while keeping the existing byte verifier operational during adapter introduction. |
| Candidate analysis | `decomp_compile.py`, `decomp_context.py`, `decomp_score.py`, `decomp_register_atlas.py`, and the bounded batch/beam/permuter tools | Diagnose structural, scheduling, and register-allocation differences without weakening the final byte comparison. Paths, ROM mapping, and manifests need BattleTanx adapters. |
| Reporting and safety | `decompkit.report`, `decompkit.assembly`, `audit_assembly_segments.py`, `audit_source_names.py`, and their synthetic tests | Generate reproducible progress reports, distinguish generated code from data or authentic assembly, and enforce address-traceable semantic names. |
| Compiler research | `docs/COMPILER.md`, `docs/MATCHING_RESEARCH.md`, the diagnostic GCC 2.7.2 scripts, and `decompkit.gcc_alloc` | The same KMC GCC family makes the documented scheduling/allocation diagnostics directly relevant. Function-specific normalizer rules must not be copied without new local evidence. |
| ASN64 compatibility | `tools/modern_asn64.py` and its conformance tests | Use the opt-in `--assembler=asn64` matching-manifest flag for translation units whose raw KMC assembly requires the historical assembler's scheduling and hazard behavior. The ordinary normalizer remains the default. |
| Source organization | `docs/SOURCE_MATURITY.md` and `config/source_layout.tsv` | Adopt its evidence levels and address-to-name ledger as this repository grows. Directory placement should follow proven ownership or translation-unit evidence rather than surface similarity. |
| SDK code | matching `src/libultra` implementations and library fingerprints | Twenty-four current BattleTanx libultra source/header files are byte-for-byte identical to files in the audited tree. Continue testing whole objects locally and use the library fingerprint research to choose SDK releases and flags. |

## Reusable after title-specific adaptation

- The `decompkit` package deliberately injects compiler and reference-image
  adapters. BattleTanx needs its own configuration, catalogue parser, VRAM/ROM
  mapping, and KMC build adapter before adopting it.
- The LZARI codec, N64 texture helpers, whole-image verifier, resource-region
  engine, and inventory/repack patterns are technically portable. Their Global
  Assault table addresses and asset manifests are not. They become valuable
  when BattleTanx asset work begins and should first be exercised against
  synthetic fixtures and then a verified local ROM.
- Global Assault gameplay source is useful for fuzzy matching shared engine
  idioms, structures, call shapes, and subsystem boundaries. Similarity is
  naming evidence only when BattleTanx callers and data flow support the same
  behavior; exact local object/ROM comparison remains mandatory.
- The RSP, N_audio, libmus, libgcc, and libultra catalogues are strong leads for
  library identification. Versions, object boundaries, flags, and any altered
  source must be independently established for BattleTanx.

## Not directly portable

- Global Assault ROM hashes, addresses, symbol tables, linker layout, function
  boundaries, rodata/data ownership, and resource-region manifests.
- Address-gated normalizer rewrites and source forms that only match a Global
  Assault translation unit.
- Game-specific world, script, image, audio-bank, and O2R manifests. The codec
  and validation architecture can be reused, but the extracted facts cannot.
- Completion totals or matching claims. They describe a different executable.

## Recommended integration order

1. The portable configuration and table parser are now behind the existing
   BattleTanx manifests and report. Add the unit-verifier adapter next and
   retain the current verifier as a cross-check.
2. Bring over the structured context, scoring, register-atlas, and GCC
   allocation diagnostics with synthetic tests.
3. Add a source-layout/name ledger before broader directory normalization.
4. Adopt assembly/report tooling once the catalogue and source ownership tables
   have stable adapters.
5. Introduce resource codecs and reconstruction tooling only after BattleTanx
   asset boundaries are independently mapped.

The two repositories are GPL-3.0, so code reuse is license-compatible. Any
copied implementation should retain its history and attribution while local
matching evidence records why it applies to BattleTanx.
