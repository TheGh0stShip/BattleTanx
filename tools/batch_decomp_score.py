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
import hashlib
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
CACHE_PATH = ROOT / "build" / "decomp_score_cache.json"


def cache_fingerprint(args: argparse.Namespace, path: Path) -> str:
    """Fingerprint inputs that can change a candidate's generated object."""
    digest = hashlib.sha256()
    digest.update(path.read_bytes())
    digest.update(f"{args.vram:x}\0{args.function}\0{args.pipeline}".encode())
    for dependency in (
        ROOT / "config/us/recomp_function_boundaries.toml",
        ROOT / "build/us/symbols.ld",
        ROOT / "tools/normalize_kmc_gcc_asm.py",
        ROOT / "tools/modern_asn64.py",
        ROOT / "build/decomp_compile.py",
        ROOT / "build/decomp_score.py",
    ):
        if dependency.exists():
            stat = dependency.stat()
            digest.update(f"{dependency}:{stat.st_mtime_ns}:{stat.st_size}".encode())
    return digest.hexdigest()


def load_cache() -> dict[str, dict[str, object]]:
    try:
        value = json.loads(CACHE_PATH.read_text())
        return value if isinstance(value, dict) else {}
    except (FileNotFoundError, json.JSONDecodeError):
        return {}


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
    parser.add_argument("--no-cache", action="store_true")
    args = parser.parse_args()

    missing = [path for path in args.candidates if not path.is_file()]
    if missing:
        parser.error("missing candidate(s): " + ", ".join(map(str, missing)))

    cache = {} if args.no_cache else load_cache()
    pending = []
    results = []
    keys = {}
    for path in args.candidates:
        key = cache_fingerprint(args, path)
        keys[path] = key
        if key in cache:
            hit = dict(cache[key])
            hit["path"] = str(path)
            hit["seconds"] = 0.0
            hit["cached"] = True
            results.append(hit)
        else:
            pending.append(path)

    jobs = max(1, min(args.jobs, len(pending))) if pending else 1
    with concurrent.futures.ThreadPoolExecutor(max_workers=jobs) as executor:
        fresh = list(executor.map(lambda path: score_candidate(path, args), pending))
    results.extend(fresh)
    if not args.no_cache and fresh:
        CACHE_PATH.parent.mkdir(parents=True, exist_ok=True)
        for path, result in zip(pending, fresh):
            if "error" not in result:
                cache[keys[path]] = {k: v for k, v in result.items() if k != "path"}
        CACHE_PATH.write_text(json.dumps(cache, sort_keys=True) + "\n")
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
            f"{result['seconds']:6.3f}s{' cached' if result.get('cached') else '       '}\t"
            f"{result['path']}"
        )

    if args.json:
        args.json.write_text(json.dumps(results, indent=2, sort_keys=True) + "\n")
    return 1 if all("error" in result for result in results) else 0


if __name__ == "__main__":
    raise SystemExit(main())
