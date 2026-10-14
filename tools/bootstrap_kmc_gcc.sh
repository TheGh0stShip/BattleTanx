#!/usr/bin/env bash
set -euo pipefail

root_dir="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
install_dir="$root_dir/.toolchain/kmc-gcc-2.7.2"
gcc_url="https://github.com/decompals/mips-gcc-2.7.2/releases/download/v0.1/gcc-2.7.2-linux.tar.gz"
binutils_url="https://github.com/decompals/mips-binutils-2.6/releases/download/v0.3/binutils-2.6-linux.tar.gz"
gcc_sha256="e09e7b53d4e47d1b7bab1f854c4498c0bffbea2553b1d7201dc3e0e983923874"
binutils_sha256="5a612cd28344e5b410c3344ec5dcfb92d9d03947756f190cd12404055b4a624d"

if [[ -x "$install_dir/gcc" && -x "$install_dir/as" ]]; then
    echo "Local KMC GCC 2.7.2 toolchain already installed"
    exit 0
fi

for command_name in curl sha256sum tar; do
    command -v "$command_name" >/dev/null 2>&1 || {
        echo "$command_name is required to install the KMC toolchain" >&2
        exit 1
    }
done

download_dir="$(mktemp -d)"
trap 'rm -rf "$download_dir"' EXIT
gcc_archive="$download_dir/gcc.tar.gz"
binutils_archive="$download_dir/binutils.tar.gz"
curl -L --fail --silent --show-error "$gcc_url" -o "$gcc_archive"
curl -L --fail --silent --show-error "$binutils_url" -o "$binutils_archive"
echo "$gcc_sha256  $gcc_archive" | sha256sum --check --status
echo "$binutils_sha256  $binutils_archive" | sha256sum --check --status
mkdir -p "$install_dir"
tar -xzf "$gcc_archive" -C "$install_dir"
tar -xzf "$binutils_archive" -C "$install_dir"
[[ -x "$install_dir/gcc" && -x "$install_dir/as" ]]
echo "Installed pinned KMC GCC 2.7.2 and GNU as 2.6 under $install_dir"
