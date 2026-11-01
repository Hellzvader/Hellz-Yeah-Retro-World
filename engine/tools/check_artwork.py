#!/usr/bin/env python3
"""Validate imported BMP sprite strips against the C++ visual manifest.

Run from anywhere: python engine/tools/check_artwork.py
Exit 0 only when every required hero/enemy/boss sheet is present and valid.
"""
from pathlib import Path
import re
import struct
import sys

ENGINE = Path(__file__).resolve().parents[1]
MANIFEST = ENGINE / "include" / "VisualManifest.hpp"
ASSETS = ENGINE / "assets" / "imported"

def main():
    source = MANIFEST.read_text(encoding="utf-8")
    entries = re.findall(
        r'\{"([^"]+)",\{"([^"]+\.bmp)",\{(\d+),(\d+),(\d+),([\d.]+)\}',
        source,
    )
    if not entries:
        print("ERROR: No sprite definitions parsed from VisualManifest.hpp")
        return 2
    missing, invalid, ready = [], [], []
    for name, relative, fw, fh, frames, _fps in entries:
        path = ASSETS / relative
        if not path.is_file():
            missing.append((name, relative))
            continue
        try:
            with path.open("rb") as f:
                header = f.read(54)
            if len(header) < 54 or header[:2] != b"BM":
                raise ValueError("not a BMP file")
            width = struct.unpack_from("<i", header, 18)[0]
            height = abs(struct.unpack_from("<i", header, 22)[0])
            expected_width = int(fw) * int(frames)
            if width < expected_width or height < int(fh):
                raise ValueError(
                    f"sheet {width}x{height}, needs at least {expected_width}x{fh}"
                )
            ready.append(name)
        except (OSError, ValueError, struct.error) as exc:
            invalid.append((name, str(exc)))
    print(f"Artwork check: {len(ready)}/{len(entries)} manifest sheets valid")
    for name, path in missing:
        print(f"MISSING {name}: assets/imported/{path}")
    for name, reason in invalid:
        print(f"INVALID {name}: {reason}")
    if missing or invalid:
        print("NOT PLAY-TEST READY: required imported artwork is missing or invalid")
        return 1
    print("Manifest sprite sheets present; in-game rendering still needs a Windows play-test.")
    return 0

if __name__ == "__main__":
    sys.exit(main())
