#!/usr/bin/env bash
set -euo pipefail

root_dir="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
install_dir="$root_dir/.toolchain/sn-gcc-2.8"
wibo_url="https://github.com/decompals/wibo/releases/download/1.2.0/wibo-x86_64"
cc1_url="https://raw.githubusercontent.com/HighwayFrogs/frogger2-n64/883acffd611be1199d60bd2f889aaf8881801f02/SDK/bin/cc1n64.exe"
asn64_url="https://raw.githubusercontent.com/HighwayFrogs/frogger2-n64/883acffd611be1199d60bd2f889aaf8881801f02/SDK/bin/asn64.exe"
parser_url="https://raw.githubusercontent.com/RocketRet/Rocket-Robot-On-Wheels/cd1fc6d3f575841a240373d7b8a2baf532da2f9f/tools/psyq-obj-parser"
wibo_sha256="13f86a2d618f0dbe67179d349625345eabf9b46450295cb4c904e49f6aff85af"
cc1_sha256="d90df1028c46d826e37146dbcc3e3385f78c59e05a9ddd952daa94c9ad379d9c"
asn64_sha256="3279da06e91702bf9e656931d1f39f0a2e64bcabeaedae37dcb816388bb2dd24"
parser_sha256="71626f59e2c7cb3e7f3f34d363375d5418d0f6581b601561fe1469f13cb78ce5"

if [[ -x "$install_dir/wibo" && -f "$install_dir/cc1n64.exe" &&
      -f "$install_dir/asn64.exe" && -x "$install_dir/psyq-obj-parser" ]]; then
    echo "Local SN Systems GCC toolchain already installed"
    exit 0
fi

for command_name in curl sha256sum; do
    command -v "$command_name" >/dev/null 2>&1 || {
        echo "$command_name is required to install the SN matching toolchain" >&2
        exit 1
    }
done

mkdir -p "$install_dir"
curl -L --fail --silent --show-error "$wibo_url" -o "$install_dir/wibo"
curl -L --fail --silent --show-error "$cc1_url" -o "$install_dir/cc1n64.exe"
curl -L --fail --silent --show-error "$asn64_url" -o "$install_dir/asn64.exe"
curl -L --fail --silent --show-error "$parser_url" -o "$install_dir/psyq-obj-parser"

echo "$wibo_sha256  $install_dir/wibo" | sha256sum --check --status
echo "$cc1_sha256  $install_dir/cc1n64.exe" | sha256sum --check --status
echo "$asn64_sha256  $install_dir/asn64.exe" | sha256sum --check --status
echo "$parser_sha256  $install_dir/psyq-obj-parser" | sha256sum --check --status
chmod +x "$install_dir/wibo" "$install_dir/psyq-obj-parser"
echo "Installed the hash-pinned SN Systems GCC matching toolchain under $install_dir"
