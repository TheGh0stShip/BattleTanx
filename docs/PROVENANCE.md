# Research provenance

The initial function catalogue was imported on 2026-10-14 from
`bdragoncore/battle-tanx-recomp`, file
`BattleTanxSyms/battletanx.us.rev0.syms.toml`, under GPL-3.0. That project says
the table began with splat/spimdisasm and n64sym analysis and was subsequently
corrected during static-recompilation bring-up. Original comments are retained.

Upstream source: <https://github.com/bdragoncore/battle-tanx-recomp>

The catalogue contains boundaries and library-name hypotheses. It does not by
itself demonstrate source recovery or a matching rebuild. This repository's
matching claims require byte comparisons against the verified retail ROM.

The initial `src/libultra` units were transferred from the completed matching
Global Assault decompilation after each entire text section was found
byte-identical in this game. Local verification recompiles each source
independently and compares all 1,840 bytes against the supported BattleTanx
ROM; cross-version identity was used only to discover candidates.
