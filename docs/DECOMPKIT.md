# Decompkit

BattleTanx uses the portable Decompkit infrastructure shared with the completed
BattleTanx: Global Assault decompilation. Project policy is held in
`config/decompkit.toml`; reusable implementation belongs under
`tools/decompkit/` and must not embed ROM paths, game addresses, or compiler
assumptions.

The current integration makes Decompkit's configuration and strict TSV parser
part of the production recomp.fyi report. Consequently, malformed manifests,
duplicate columns, invalid ranges, and overlaps between IDO, KMC, and authentic
assembly units fail `make report` and `make check` instead of being silently
counted. Zero-length text rows are allowed only in the combined code inventory,
where they represent verified data-only SDK objects.

```sh
make report
make check
```

The existing compiler-specific verifier remains the byte-exact authority. Its
single-source mode is exposed through `tools/decompkit_build_adapter.py` using
Decompkit's JSON subprocess protocol; this was cross-checked against a retail
unit through the pinned compiler pipeline. Decompkit does not weaken
the matching gate: every completed code or data unit must still reproduce the
verified USA Rev 0 ROM bytes.

The next adapters are register-allocation diagnostics, assembly classification,
and deterministic resource rebuilding.
Each adapter must be checked against the existing BattleTanx result before it
replaces project-specific code.
