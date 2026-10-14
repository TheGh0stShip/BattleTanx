#!/usr/bin/env python3
"""Verify a local supported dump and copy it to the canonical ignored path."""

from __future__ import annotations

import argparse
import shutil
from pathlib import Path

from verify_rom import verify

CANDIDATES = (Path("BattleTanx (USA).z64"), Path("BattleTanx.z64"), Path("baserom.z64"))


def main() -> None:
    parser = argparse.ArgumentParser()
    parser.add_argument("--input", type=Path)
    parser.add_argument("--output", required=True, type=Path)
    args = parser.parse_args()
    source = args.input or next((p for p in CANDIDATES if p.is_file()), None)
    if source is None:
        raise SystemExit("No supported ROM candidate found; pass --input /path/to/dump.z64")
    verify(source)
    args.output.parent.mkdir(parents=True, exist_ok=True)
    if source.resolve() != args.output.resolve():
        shutil.copyfile(source, args.output)
    verify(args.output)
    print(f"Prepared {args.output}")


if __name__ == "__main__":
    main()
