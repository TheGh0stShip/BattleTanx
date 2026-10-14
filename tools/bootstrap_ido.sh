#!/usr/bin/env bash
set -euo pipefail

root_dir="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
install_dir="$root_dir/.toolchain/ido5.3"
archive_url="https://github.com/decompals/ido-static-recomp/releases/download/v1.2/ido-5.3-recomp-linux.tar.gz"
archive_sha1="976b115acb973c3828a7215b531b203537135e38"

if [[ -x "$install_dir/cc" ]]; then
    echo "Local IDO 5.3 recomp toolchain already installed"
    exit 0
fi

for command_name in curl sha1sum tar; do
    command -v "$command_name" >/dev/null 2>&1 || {
        echo "$command_name is required to install the matching compiler" >&2
        exit 1
    }
done

download_dir="$(mktemp -d)"
trap 'rm -rf "$download_dir"' EXIT
archive="$download_dir/ido-5.3-recomp-linux.tar.gz"
curl -L --fail --silent --show-error "$archive_url" -o "$archive"
echo "$archive_sha1  $archive" | sha1sum --check --status || {
    echo "IDO toolchain archive checksum mismatch" >&2
    exit 1
}
mkdir -p "$install_dir"
tar -xzf "$archive" -C "$install_dir"
[[ -x "$install_dir/cc" ]]
echo "Installed pinned IDO 5.3 recomp toolchain under $install_dir"
