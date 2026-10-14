#!/usr/bin/env python3
"""Decode standard N64 texture layouts (RGBA, CI, IA and I formats) to RGBA8888 and PNG."""

from __future__ import annotations

import struct
import zlib


class TextureError(ValueError):
    """Raised when a texture descriptor and its decoded payload disagree."""


def _five_to_eight(value: int) -> int:
    return (value << 3) | (value >> 2)


def rgba16(pixel: int) -> bytes:
    return bytes(
        (
            _five_to_eight((pixel >> 11) & 0x1F),
            _five_to_eight((pixel >> 6) & 0x1F),
            _five_to_eight((pixel >> 1) & 0x1F),
            0xFF if pixel & 1 else 0,
        )
    )

def _palette(data: bytes, count: int) -> list[bytes]:
    return [rgba16(struct.unpack_from(">H", data, index * 2)[0]) for index in range(count)]


def decode_texture(data: bytes, format_id: int, size_id: int, width: int, height: int) -> bytes:
    """Return row-major RGBA8888 pixels for one decoded image stream.

    The descriptor values use the standard N64 G_IM_FMT/G_IM_SIZ numbers:
    format 0 is RGBA, 2 is CI, 3 is IA, and 4 is I; sizes 0..3 are
    4/8/16/32-bit.
    CI payloads place their RGBA16 palette before the packed indices.
    """

    if width <= 0 or height <= 0:
        raise TextureError("texture dimensions must be positive")
    pixels = width * height
    output = bytearray()

    if (format_id, size_id) == (0, 2):
        expected = pixels * 2
        if len(data) != expected:
            raise TextureError(f"RGBA16 payload is {len(data)} bytes, expected {expected}")
        for offset in range(0, len(data), 2):
            output.extend(rgba16(struct.unpack_from(">H", data, offset)[0]))
    elif (format_id, size_id) == (0, 3):
        expected = pixels * 4
        if len(data) != expected:
            raise TextureError(f"RGBA32 payload is {len(data)} bytes, expected {expected}")
        output.extend(data)
    elif (format_id, size_id) == (2, 0):
        expected = 32 + (pixels + 1) // 2
        row_bytes = (width + 1) // 2
        if len(data) < expected or (len(data) - 32) % row_bytes:
            raise TextureError(
                f"CI4 payload is {len(data)} bytes, expected at least {expected} "
                "and a whole number of stored rows"
            )
        palette = _palette(data, 16)
        emitted = 0
        for byte in data[32:]:
            if emitted == pixels:
                break
            output.extend(palette[byte >> 4])
            emitted += 1
            if emitted < pixels:
                output.extend(palette[byte & 0xF])
                emitted += 1
    elif (format_id, size_id) == (2, 1):
        expected = 512 + pixels
        if len(data) != expected:
            raise TextureError(f"CI8 payload is {len(data)} bytes, expected {expected}")
        palette = _palette(data, 256)
        for index in data[512:]:
            output.extend(palette[index])
    elif (format_id, size_id) == (3, 1):
        if len(data) != pixels:
            raise TextureError(f"IA8 payload is {len(data)} bytes, expected {pixels}")
        for value in data:
            intensity = (value >> 4) * 17
            output.extend((intensity, intensity, intensity, (value & 0xF) * 17))
    elif (format_id, size_id) == (3, 2):
        expected = pixels * 2
        if len(data) != expected:
            raise TextureError(f"IA16 payload is {len(data)} bytes, expected {expected}")
        for intensity, alpha in zip(data[::2], data[1::2]):
            output.extend((intensity, intensity, intensity, alpha))
    elif (format_id, size_id) == (4, 0):
        expected = (pixels + 1) // 2
        if len(data) != expected:
            raise TextureError(f"I4 payload is {len(data)} bytes, expected {expected}")
        emitted = 0
        for value in data:
            for nibble in (value >> 4, value & 0xF):
                if emitted == pixels:
                    break
                intensity = nibble * 17
                output.extend((intensity, intensity, intensity, 0xFF))
                emitted += 1
    elif (format_id, size_id) == (4, 1):
        if len(data) != pixels:
            raise TextureError(f"I8 payload is {len(data)} bytes, expected {pixels}")
        for intensity in data:
            output.extend((intensity, intensity, intensity, 0xFF))
    else:
        raise TextureError(f"unsupported N64 texture format/size: {format_id}/{size_id}")

    return bytes(output)


def encode_png_rgba(width: int, height: int, pixels: bytes) -> bytes:
    """Encode RGBA8888 pixels as a deterministic, non-interlaced PNG."""

    if len(pixels) != width * height * 4:
        raise TextureError("RGBA pixel count does not match the image dimensions")

    def chunk(kind: bytes, payload: bytes) -> bytes:
        body = kind + payload
        return struct.pack(">I", len(payload)) + body + struct.pack(">I", zlib.crc32(body))

    stride = width * 4
    scanlines = b"".join(
        b"\0" + pixels[offset : offset + stride]
        for offset in range(0, len(pixels), stride)
    )
    return b"\x89PNG\r\n\x1a\n" + b"".join(
        (
            chunk(b"IHDR", struct.pack(">IIBBBBB", width, height, 8, 6, 0, 0, 0)),
            chunk(b"IDAT", zlib.compress(scanlines, 9)),
            chunk(b"IEND", b""),
        )
    )
