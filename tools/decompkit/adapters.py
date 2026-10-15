"""Subprocess and image adapters for toolchain-neutral unit verification."""

from __future__ import annotations

import json
import subprocess
import tempfile
from dataclasses import dataclass
from pathlib import Path
from typing import Callable, Sequence


class AdapterError(RuntimeError):
    pass


@dataclass(frozen=True)
class CommandBuildAdapter:
    """Invoke a compiler adapter through Decompkit's JSON protocol."""

    command: Sequence[str]
    cwd: Path | None = None

    def __post_init__(self) -> None:
        command = tuple(self.command)
        if not command or "{request}" not in command or "{response}" not in command:
            raise ValueError("adapter command must contain {request} and {response} argv entries")

    def __call__(self, source: str, vram: int, *, pipeline: str) -> dict[str, object]:
        request = {
            "format": "decompkit-build-request-v1",
            "source": str(Path(source).resolve()),
            "vram": vram,
            "pipeline": pipeline,
        }
        with tempfile.TemporaryDirectory(prefix="decompkit-adapter-") as directory:
            request_path = Path(directory) / "request.json"
            response_path = Path(directory) / "response.json"
            request_path.write_text(json.dumps(request))
            argv = [part.format(request=request_path, response=response_path)
                    for part in self.command]
            process = subprocess.run(argv, cwd=self.cwd, capture_output=True, text=True)
            if process.returncode:
                raise AdapterError(
                    f"adapter exited {process.returncode}:\n{process.stdout}{process.stderr}"
                )
            if not response_path.is_file():
                raise AdapterError("adapter did not create its response file")
            try:
                response = json.loads(response_path.read_text())
                if response.get("format") != "decompkit-build-response-v1":
                    raise AdapterError("unsupported or missing adapter response format")
                text = bytes.fromhex(response["text_hex"])
                rodata_value = response.get("rodata_hex")
                rodata = bytes.fromhex(rodata_value) if rodata_value is not None else None
                text_size = int(response.get("text_size", len(text)))
                rodata_vram = response.get("rodata_vram")
                if isinstance(rodata_vram, str):
                    rodata_vram = int(rodata_vram, 0)
            except (KeyError, TypeError, ValueError, json.JSONDecodeError) as error:
                raise AdapterError(f"invalid adapter response: {error}") from error
            if text_size < 0 or len(text) < text_size:
                raise AdapterError("adapter text_size is negative or exceeds emitted text")
            return {
                "text": text,
                "tsz": text_size,
                "rodata": rodata,
                "rodata_vram": rodata_vram,
                "adapter_response": response,
            }


@dataclass(frozen=True)
class ImageReference:
    path: Path
    address_to_offset: Callable[[int], int]

    def __call__(self, address: int, size: int) -> bytes:
        if size < 0:
            raise ValueError("reference size must be non-negative")
        offset = self.address_to_offset(address)
        if offset < 0:
            raise ValueError(f"address 0x{address:X} maps before the reference image")
        with self.path.open("rb") as stream:
            stream.seek(offset)
            data = stream.read(size)
        if len(data) != size:
            raise ValueError(
                f"reference read at 0x{address:X} is short: {len(data)} of {size} bytes"
            )
        return data
