#!/usr/bin/env python3
"""Encode and decode BattleTanx big-endian LZARI streams.

Adapted from the BattleTanx: Global Assault decompilation's tools/lzari.py
(GPL-3.0).  BattleTanx uses the same stream format, as recovered from its
decoder in src/code/compression/lzari_decode.c and lzari_model.c: a
big-endian u32 expanded size followed by Okumura LZARI arithmetic-coded bits
(N=4096, F=60, THRESHOLD=2).
"""

from __future__ import annotations

import argparse
import struct
from dataclasses import dataclass
from pathlib import Path


N = 4096
F = 60
THRESHOLD = 2
N_CHAR = 256 - THRESHOLD + F
Q1 = 1 << 15
Q2 = 2 * Q1
Q3 = 3 * Q1
Q4 = 4 * Q1
MAX_CUM = Q1 - 1


class LzariError(ValueError):
    pass


@dataclass(frozen=True)
class DecompressionResult:
    data: bytes
    consumed_bytes: int
    padding_bits: int


class BitWriter:
    def __init__(self):
        self.output = bytearray()
        self.byte = 0
        self.mask = 0x80

    def put(self, bit: int) -> None:
        if bit:
            self.byte |= self.mask
        self.mask >>= 1
        if self.mask == 0:
            self.output.append(self.byte)
            self.byte = 0
            self.mask = 0x80


class Encoder:
    def __init__(self, source: bytes):
        self.source = source
        self.low = 0
        self.high = Q4
        self.pending = 0
        self.writer = BitWriter()

        self.char_to_sym = [0] * N_CHAR
        self.sym_to_char = [0] * (N_CHAR + 1)
        self.sym_freq = [0] * (N_CHAR + 1)
        self.sym_cum = [0] * (N_CHAR + 1)
        self.position_cum = [0] * (N + 1)
        for sym in range(N_CHAR, 0, -1):
            character = sym - 1
            self.char_to_sym[character] = sym
            self.sym_to_char[sym] = character
            self.sym_freq[sym] = 1
            self.sym_cum[sym - 1] = self.sym_cum[sym] + 1
        for index in range(N, 0, -1):
            self.position_cum[index - 1] = (
                self.position_cum[index] + 10000 // (index + 200)
            )

        self.buffer = bytearray(N + F - 1)
        self.left = [N] * (N + 1)
        self.right = [N] * (N + 257)
        self.parent = [N] * (N + 1)
        self.match_position = 0
        self.match_length = 0

    def _update_model(self, sym: int) -> None:
        if self.sym_cum[0] >= MAX_CUM:
            total = 0
            for index in range(N_CHAR, 0, -1):
                self.sym_cum[index] = total
                self.sym_freq[index] = (self.sym_freq[index] + 1) >> 1
                total += self.sym_freq[index]
            self.sym_cum[0] = total

        index = sym
        while self.sym_freq[index] == self.sym_freq[index - 1]:
            index -= 1
        if index < sym:
            first = self.sym_to_char[index]
            second = self.sym_to_char[sym]
            self.sym_to_char[index], self.sym_to_char[sym] = second, first
            self.char_to_sym[first] = sym
            self.char_to_sym[second] = index
        self.sym_freq[index] += 1
        index -= 1
        while index >= 0:
            self.sym_cum[index] += 1
            index -= 1

    def _output(self, bit: int) -> None:
        self.writer.put(bit)
        while self.pending:
            self.writer.put(not bit)
            self.pending -= 1

    def _renormalize(self) -> None:
        while True:
            if self.high <= Q2:
                self._output(0)
            elif self.low >= Q2:
                self._output(1)
                self.low -= Q2
                self.high -= Q2
            elif self.low >= Q1 and self.high <= Q3:
                self.pending += 1
                self.low -= Q1
                self.high -= Q1
            else:
                return
            self.low *= 2
            self.high *= 2

    def _character(self, character: int) -> None:
        sym = self.char_to_sym[character]
        span = self.high - self.low
        base = self.low
        self.high = base + span * self.sym_cum[sym - 1] // self.sym_cum[0]
        self.low = base + span * self.sym_cum[sym] // self.sym_cum[0]
        self._renormalize()
        self._update_model(sym)

    def _position(self, position: int) -> None:
        span = self.high - self.low
        base = self.low
        self.high = base + span * self.position_cum[position] // self.position_cum[0]
        self.low = base + span * self.position_cum[position + 1] // self.position_cum[0]
        self._renormalize()

    def _insert(self, node: int) -> None:
        parent = N + 1 + self.buffer[node]
        comparison = 1
        self.right[node] = self.left[node] = N
        self.match_length = 0
        while True:
            if comparison >= 0:
                if self.right[parent] != N:
                    parent = self.right[parent]
                else:
                    self.right[parent] = node
                    self.parent[node] = parent
                    return
            elif self.left[parent] != N:
                parent = self.left[parent]
            else:
                self.left[parent] = node
                self.parent[node] = parent
                return

            length = 1
            while length < F:
                comparison = self.buffer[node + length] - self.buffer[parent + length]
                if comparison:
                    break
                length += 1
            if length > THRESHOLD:
                distance = (node - parent) & (N - 1)
                if length > self.match_length:
                    self.match_position = distance
                    self.match_length = length
                    if length >= F:
                        break
                elif length == self.match_length and distance < self.match_position:
                    self.match_position = distance

        self.parent[node] = self.parent[parent]
        self.left[node] = self.left[parent]
        self.right[node] = self.right[parent]
        self.parent[self.left[parent]] = node
        self.parent[self.right[parent]] = node
        if self.right[self.parent[parent]] == parent:
            self.right[self.parent[parent]] = node
        else:
            self.left[self.parent[parent]] = node
        self.parent[parent] = N

    def _delete(self, node: int) -> None:
        if self.parent[node] == N:
            return
        if self.right[node] == N:
            replacement = self.left[node]
        elif self.left[node] == N:
            replacement = self.right[node]
        else:
            replacement = self.left[node]
            if self.right[replacement] != N:
                while self.right[replacement] != N:
                    replacement = self.right[replacement]
                self.right[self.parent[replacement]] = self.left[replacement]
                self.parent[self.left[replacement]] = self.parent[replacement]
                self.left[replacement] = self.left[node]
                self.parent[self.left[node]] = replacement
            self.right[replacement] = self.right[node]
            self.parent[self.right[node]] = replacement
        self.parent[replacement] = self.parent[node]
        if self.right[self.parent[node]] == node:
            self.right[self.parent[node]] = replacement
        else:
            self.left[self.parent[node]] = replacement
        self.parent[node] = N

    def encode(self) -> bytes:
        if not self.source:
            return struct.pack(">I", 0)

        read_at = min(F, len(self.source))
        remaining = read_at
        write_at = N - F
        expire_at = 0
        self.buffer[:write_at] = b" " * write_at
        self.buffer[write_at:write_at + read_at] = self.source[:read_at]
        for index in range(1, F + 1):
            self._insert(write_at - index)
        self._insert(write_at)

        while remaining:
            self.match_length = min(self.match_length, remaining)
            if self.match_length <= THRESHOLD:
                self.match_length = 1
                self._character(self.buffer[write_at])
            else:
                self._character(255 - THRESHOLD + self.match_length)
                self._position(self.match_position - 1)

            consumed = self.match_length
            advanced = 0
            while advanced < consumed and read_at < len(self.source):
                self._delete(expire_at)
                character = self.source[read_at]
                read_at += 1
                self.buffer[expire_at] = character
                if expire_at < F - 1:
                    self.buffer[expire_at + N] = character
                expire_at = (expire_at + 1) & (N - 1)
                write_at = (write_at + 1) & (N - 1)
                self._insert(write_at)
                advanced += 1
            while advanced < consumed:
                self._delete(expire_at)
                expire_at = (expire_at + 1) & (N - 1)
                write_at = (write_at + 1) & (N - 1)
                remaining -= 1
                if remaining:
                    self._insert(write_at)
                advanced += 1

        self.pending += 1
        self._output(0 if self.low < Q1 else 1)
        for _ in range(7):
            self.writer.put(0)
        return struct.pack(">I", len(self.source)) + bytes(self.writer.output)


class Decoder:
    def __init__(self, source: bytes):
        self.source = source
        self.offset = 0
        self.mask = 0
        self.byte = 0
        self.padding_bits = 0
        self.low = 0
        self.high = Q4
        self.value = 0

        self.sym_to_char = [0] * (N_CHAR + 1)
        self.sym_freq = [0] * (N_CHAR + 1)
        self.sym_cum = [0] * (N_CHAR + 1)
        self.position_cum = [0] * (N + 1)
        self._start_model()

    def _bit(self) -> int:
        self.mask >>= 1
        if self.mask == 0:
            if self.offset >= len(self.source):
                # Okumura's GetBit uses getc(), whose EOF value behaves as an
                # all-one byte. Retail streams rely on this arithmetic-coder
                # tail padding, but cap it so a truncated stream cannot run on.
                self.padding_bits += 8
                if self.padding_bits > 32:
                    raise LzariError("compressed stream ended before output was complete")
                self.byte = 0xFF
            else:
                self.byte = self.source[self.offset]
                self.offset += 1
            self.mask = 0x80
        return int(bool(self.byte & self.mask))

    def _start_model(self) -> None:
        for sym in range(N_CHAR, 0, -1):
            self.sym_to_char[sym] = sym - 1
            self.sym_freq[sym] = 1
            self.sym_cum[sym - 1] = self.sym_cum[sym] + 1
        for index in range(N, 0, -1):
            self.position_cum[index - 1] = (
                self.position_cum[index] + 10000 // (index + 200)
            )

    def _update_model(self, sym: int) -> None:
        if self.sym_cum[0] >= MAX_CUM:
            total = 0
            for index in range(N_CHAR, 0, -1):
                self.sym_cum[index] = total
                self.sym_freq[index] = (self.sym_freq[index] + 1) >> 1
                total += self.sym_freq[index]
            self.sym_cum[0] = total

        index = sym
        while self.sym_freq[index] == self.sym_freq[index - 1]:
            index -= 1
        if index < sym:
            self.sym_to_char[index], self.sym_to_char[sym] = (
                self.sym_to_char[sym],
                self.sym_to_char[index],
            )
        self.sym_freq[index] += 1
        index -= 1
        while index >= 0:
            self.sym_cum[index] += 1
            index -= 1

    def _renormalize(self) -> None:
        while True:
            if self.low >= Q2:
                self.value -= Q2
                self.low -= Q2
                self.high -= Q2
            elif self.low >= Q1 and self.high <= Q3:
                self.value -= Q1
                self.low -= Q1
                self.high -= Q1
            elif self.high > Q2:
                return
            self.low *= 2
            self.high *= 2
            self.value = self.value * 2 + self._bit()

    @staticmethod
    def _search(cumulative: list[int], value: int, high: int) -> int:
        low = 1
        while low < high:
            middle = (low + high) // 2
            if cumulative[middle] > value:
                low = middle + 1
            else:
                high = middle
        return low

    def start(self) -> None:
        for _ in range(17):
            self.value = self.value * 2 + self._bit()

    def character(self) -> int:
        span = self.high - self.low
        scaled = ((self.value - self.low + 1) * self.sym_cum[0] - 1) // span
        sym = self._search(self.sym_cum, scaled, N_CHAR)
        self.high = self.low + span * self.sym_cum[sym - 1] // self.sym_cum[0]
        self.low += span * self.sym_cum[sym] // self.sym_cum[0]
        self._renormalize()
        character = self.sym_to_char[sym]
        self._update_model(sym)
        return character

    def position(self) -> int:
        span = self.high - self.low
        scaled = ((self.value - self.low + 1) * self.position_cum[0] - 1) // span
        position = self._search(self.position_cum, scaled, N) - 1
        self.high = self.low + span * self.position_cum[position] // self.position_cum[0]
        self.low += span * self.position_cum[position + 1] // self.position_cum[0]
        self._renormalize()
        return position


def decompress_with_info(
    stream: bytes, *, max_output: int = 64 * 1024 * 1024
) -> DecompressionResult:
    if len(stream) < 4:
        raise LzariError("stream is too short")
    output_size = struct.unpack_from(">I", stream)[0]
    if output_size == 0:
        return DecompressionResult(b"", 4, 0)
    if len(stream) < 7:
        raise LzariError("stream is too short")
    if output_size > max_output:
        raise LzariError(
            f"declared output size 0x{output_size:X} exceeds limit 0x{max_output:X}"
        )

    decoder = Decoder(stream[4:])
    decoder.start()
    ring = bytearray(N)
    ring[:N - F] = b" " * (N - F)
    ring_offset = N - F
    output = bytearray()

    while len(output) < output_size:
        character = decoder.character()
        if character < 256:
            output.append(character)
            ring[ring_offset] = character
            ring_offset = (ring_offset + 1) & (N - 1)
            continue

        source_offset = (ring_offset - decoder.position() - 1) & (N - 1)
        length = character - 255 + THRESHOLD
        if len(output) + length > output_size:
            raise LzariError("match extends beyond the declared output size")
        for index in range(length):
            character = ring[(source_offset + index) & (N - 1)]
            output.append(character)
            ring[ring_offset] = character
            ring_offset = (ring_offset + 1) & (N - 1)

    return DecompressionResult(
        bytes(output), 4 + decoder.offset, decoder.padding_bits
    )


def decompress(stream: bytes, *, max_output: int = 64 * 1024 * 1024) -> bytes:
    return decompress_with_info(stream, max_output=max_output).data


def compress(data: bytes) -> bytes:
    """Encode using the exact 1989 LZARI parser used by the retail assets."""
    return Encoder(data).encode()


def main() -> None:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("input", type=Path)
    parser.add_argument("output", type=Path)
    parser.add_argument("--encode", action="store_true")
    parser.add_argument("--max-output", type=lambda value: int(value, 0), default=64 << 20)
    args = parser.parse_args()
    source = args.input.read_bytes()
    result = compress(source) if args.encode else decompress(source, max_output=args.max_output)
    args.output.write_bytes(result)


if __name__ == "__main__":
    main()
