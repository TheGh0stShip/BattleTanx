#!/usr/bin/env python3
"""Expose BattleTanx's pinned matching pipeline through Decompkit JSON."""

from __future__ import annotations

import argparse
import json
import subprocess
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]


def main() -> None:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("request", type=Path)
    parser.add_argument("response", type=Path)
    args = parser.parse_args()
    request = json.loads(args.request.read_text())
    if request.get("format") != "decompkit-build-request-v1":
        raise SystemExit("unsupported or missing request format")
    source = Path(request["source"]).resolve()
    try:
        relative = source.relative_to(ROOT)
    except ValueError as error:
        raise SystemExit("source lies outside the project") from error
    command = [
        "python3", str(ROOT / "tools/verify_matching_units.py"),
        "--source", relative.as_posix(), "--response", str(args.response),
    ]
    subprocess.run(command, cwd=ROOT, check=True)
    response = json.loads(args.response.read_text())
    if response.get("pipeline") != request.get("pipeline"):
        raise SystemExit("requested pipeline does not match the source manifest")
    if response.get("vram") != request.get("vram"):
        raise SystemExit("requested VRAM does not match the source manifest")


if __name__ == "__main__":
    main()
