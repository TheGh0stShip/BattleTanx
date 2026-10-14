#!/usr/bin/env python3
"""Reject copyrighted/generated artifacts and unsafe architecture regressions."""

from __future__ import annotations

import subprocess
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
FORBIDDEN_SUFFIXES = {".z64", ".n64", ".v64", ".elf", ".o", ".a", ".vpk", ".self", ".velf", ".psp2dmp"}


def main() -> None:
    tracked = subprocess.check_output(["git", "ls-files", "-z"], cwd=ROOT).decode().split("\0")
    errors = []
    for name in filter(None, tracked):
        path = Path(name)
        if path.suffix.lower() in FORBIDDEN_SUFFIXES:
            errors.append(f"forbidden tracked artifact: {name}")
        if path.parts and path.parts[0] in {"asm", "build", ".research"}:
            errors.append(f"generated/research path is tracked: {name}")
    if errors:
        raise SystemExit("Repository safety check failed:\n- " + "\n- ".join(errors))
    print(f"Repository safety check passed ({len(list(filter(None, tracked)))} tracked paths)")


if __name__ == "__main__":
    main()
