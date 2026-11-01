#!/usr/bin/env python3
"""Import horizontal PNG sprite strips into SDL3-compatible 32-bit BMP assets.

Usage:
  python -m pip install Pillow
  python engine/tools/import_sprites.py /path/to/my-sprite-sheets
Source folder must mirror paths in VisualManifest.hpp, e.g. heroes/mario_run.png.
This script never downloads or supplies third-party copyrighted artwork.
"""
from pathlib import Path
import re
import sys

ENGINE = Path(__file__).resolve().parents[1]
MANIFEST = ENGINE / "include" / "VisualManifest.hpp"
DEST = ENGINE / "assets" / "imported"

def main():
    if len(sys.argv) != 2:
        print("Usage: python engine/tools/import_sprites.py SOURCE_FOLDER")
        return 2
    try:
        from PIL import Image
    except ImportError:
        print("Install Pillow first: python -m pip install Pillow")
        return 2
    root = Path(sys.argv[1]).expanduser().resolve()
    if not root.is_dir():
        print(f"Source directory not found: {root}")
        return 2
    entries = re.findall(
        r'\{"([^"]+)",\{"([^"]+\.bmp)",\{(\d+),(\d+),(\d+),([\d.]+)\}',
        MANIFEST.read_text(encoding="utf-8"),
    )
    if not entries:
        print("No visual manifest entries parsed.")
        return 2
    count = 0
    for name, rel, fw, fh, frames, _fps in entries:
        source = root / Path(rel).with_suffix(".png")
        if not source.is_file():
            print(f"SKIP {name}: missing {source.relative_to(root)}")
            continue
        with Image.open(source) as im:
            im = im.convert("RGBA")
            required = (int(fw) * int(frames), int(fh))
            if im.size != required:
                print(f"ERROR {name}: image {im.size} != required {required}")
                return 1
            # SDL_LoadBMP + magenta color key is used by the native renderer.
            # Magenta in the source becomes transparent; semi-transparent pixels
            # are thresholded for this color-key format.
            out = Image.new("RGB", im.size, (255, 0, 255))
            opaque = Image.new("RGB", im.size, (255, 0, 255))
            opaque.paste(im, mask=im.getchannel("A").point(lambda a: 255 if a >= 128 else 0))
            target = DEST / rel
            target.parent.mkdir(parents=True, exist_ok=True)
            opaque.save(target, format="BMP")
            print(f"IMPORTED {name}: {target.relative_to(ENGINE)}")
            count += 1
    print(f"Imported {count}/{len(entries)} manifest sprite strips.")
    return 0 if count else 1

if __name__ == "__main__":
    sys.exit(main())
