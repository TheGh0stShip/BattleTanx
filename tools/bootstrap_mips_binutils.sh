#!/usr/bin/env bash
set -euo pipefail

root_dir="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
local_prefix="$root_dir/.toolchain/mips-binutils"

if command -v mips-linux-gnu-as >/dev/null 2>&1; then
    echo "Using $(command -v mips-linux-gnu-as)"
    exit 0
fi

if [[ -x "$local_prefix/usr/bin/mips-linux-gnu-as" ]]; then
    echo "Local MIPS binutils already installed"
    exit 0
fi

command -v apt-get >/dev/null 2>&1 || {
    echo "Install GNU binutils for big-endian MIPS (mips-linux-gnu)" >&2
    exit 1
}
command -v dpkg-deb >/dev/null 2>&1 || {
    echo "dpkg-deb is required for the unprivileged local installation" >&2
    exit 1
}

download_dir="$(mktemp -d)"
(
    cd "$download_dir"
    apt-get download binutils-mips-linux-gnu
    package="$(find . -maxdepth 1 -name 'binutils-mips-linux-gnu_*.deb' -print -quit)"
    [[ -n "$package" ]]
    dpkg-deb -x "$package" "$local_prefix"
)

echo "Installed local MIPS binutils under $local_prefix"
