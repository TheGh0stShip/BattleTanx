#!/usr/bin/env python3
"""Compile and rank several matching-decomp candidates concurrently.

This is the fast exploration layer.  It uses the same compiler, linker, ROM
comparison, and mismatch classifier as ``build/decomp_score.py``, but avoids
serial one-candidate invocations and supplies address-named linker symbols
automatically.  An exact candidate must still pass verify_matching_units.py
after it is added to a manifest.
"""

from __future__ import annotations

import argparse
import concurrent.futures
import json
import re
import sys
import time
from pathlib import Path


ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / "build"))

import decomp_compile  # noqa: E402
import decomp_score  # noqa: E402


ADDRESS_SYMBOL = re.compile(r"\b(?:D|func)_([0-9A-Fa-f]{8})\b")


def add_address_symbols(text: str, focus: str) -> str:
    """Define unresolved address-named symbols without masking relocations."""
    symbols = {
        match.group(0): match.group(1)
        for match in ADDRESS_SYMBOL.finditer(text)
        if match.group(0) != focus
    }
    markers = "".join(
        f"/* LDSYM {name}=0x{address} */\n"
        for name, address in sorted(symbols.items())
    )
    return markers + text


def score_candidate(path: Path, args: argparse.Namespace) -> dict[str, object]:
    started = time.monotonic()
    try:
        text = add_address_symbols(path.read_text(), args.function)
        result = decomp_compile.build(
            str(path),
            args.vram,
            focus=args.function,
            pipeline=args.pipeline,
            text=text,
        )
        score = decomp_score.classify(result, args.function)
        return {
            "path": str(path),
            "words": score["words"],
            "structural": score["structural"],
            "built_size": score["built_size"],
            "rom_size": score["rom_size"],
            "classes": score["classes"],
            "frame": score["frame"],
            "seconds": round(time.monotonic() - started, 3),
        }
    except Exception as error:  # Keep one bad variant from discarding the batch.
        return {
            "path": str(path),
            "error": str(error),
            "seconds": round(time.monotonic() - started, 3),
        }


def parse_int(value: str) -> int:
    return int(value, 0)


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("vram", type=parse_int)
    parser.add_argument("function")
    parser.add_argument("candidates", nargs="+", type=Path)
    parser.add_argument(
        "--pipeline", choices=("production", "asn64", "raw-kmc"),
        default="production",
    )
    parser.add_argument("--jobs", type=int, default=8)
    parser.add_argument("--json", type=Path)
    args = parser.parse_args()

    missing = [path for path in args.candidates if not path.is_file()]
    if missing:
        parser.error("missing candidate(s): " + ", ".join(map(str, missing)))

    jobs = max(1, min(args.jobs, len(args.candidates)))
    with concurrent.futures.ThreadPoolExecutor(max_workers=jobs) as executor:
        results = list(executor.map(lambda path: score_candidate(path, args), args.candidates))
    results.sort(key=lambda item: (
        "error" in item,
        item.get("words", sys.maxsize),
        item.get("structural", sys.maxsize),
        item["path"],
    ))

    for result in results:
        if "error" in result:
            print(f"ERROR\t{result['path']}\t{result['error']}")
            continue
        print(
            f"{result['words']:5d} words\t{result['structural']:3d} structural\t"
            f"{result['built_size']:5d}/{result['rom_size']:5d} bytes\t"
            f"{result['seconds']:6.3f}s\t{result['path']}"
        )

    if args.json:
        args.json.write_text(json.dumps(results, indent=2, sort_keys=True) + "\n")
    return 1 if all("error" in result for result in results) else 0


if __name__ == "__main__":
    raise SystemExit(main())
