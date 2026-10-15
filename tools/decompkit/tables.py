"""Strict TSV readers and overlap checks for decompilation manifests."""

from __future__ import annotations

import csv
from pathlib import Path


def read_tsv(path: str | Path) -> list[dict[str, str]]:
    path = Path(path)
    lines = [line for line in path.read_text().splitlines() if line.strip()]
    if not lines:
        raise ValueError(f"{path}: empty table")
    if not lines[0].startswith("#"):
        raise ValueError(f"{path}: first row must be a commented header")
    header = [field.lstrip("# ") for field in lines[0].split("\t")]
    if len(header) != len(set(header)):
        raise ValueError(f"{path}: duplicate header field")
    rows = []
    for number, line in enumerate(lines[1:], 2):
        if line.startswith("#"):
            continue
        values = next(csv.reader([line], delimiter="\t"))
        if len(values) != len(header):
            raise ValueError(
                f"{path}:{number}: expected {len(header)} fields, got {len(values)}"
            )
        rows.append(dict(zip(header, values)))
    return rows


def parse_address_ranges(
    paths: list[str | Path], *, start_field: str = "ROM_START", size_field: str = "SIZE",
    allow_empty: bool = False,
) -> list[dict[str, object]]:
    ranges: list[dict[str, object]] = []
    for raw_path in paths:
        path = Path(raw_path)
        for row in read_tsv(path):
            try:
                start = int(row[start_field], 0)
                size = int(row[size_field], 0)
            except (KeyError, ValueError) as error:
                raise ValueError(f"{path}: invalid address range") from error
            if start < 0 or size < 0 or (size == 0 and not allow_empty):
                requirement = "nonnegative" if allow_empty else "positive"
                raise ValueError(f"{path}: ranges require nonnegative starts and {requirement} sizes")
            ranges.append({"start": start, "end": start + size, "size": size,
                           "row": row, "source": path})
    ranges.sort(key=lambda item: (item["start"], item["end"]))
    occupied = [item for item in ranges if item["size"]]
    for left, right in zip(occupied, occupied[1:]):
        if right["start"] < left["end"]:
            raise ValueError(
                f"manifest ranges overlap: {left['source']} and {right['source']} "
                f"at 0x{right['start']:X}"
            )
    return ranges
