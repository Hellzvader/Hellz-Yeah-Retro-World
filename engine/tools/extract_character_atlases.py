#!/usr/bin/env python3
"""Extract animation-ready BMP strips from user-supplied transparent character atlases.

Usage: python engine/tools/extract_character_atlases.py bowser.zip "luigi and mario.zip" peach.zip
Requires: pip install pillow opencv-python numpy

Automatic extraction groups nearby opaque pixels; review the preview sheets before
treating extracted poses as correctly labelled idle/run/jump/attack animations.
"""
from pathlib import Path
import io
import sys
import zipfile
import cv2
import numpy as np
from PIL import Image, ImageDraw

ROOT = Path(__file__).resolve().parents[1]
OUTPUT = ROOT / "assets" / "imported"
SPECS = {"mario": (32,48,4), "luigi": (32,48,4), "bowser": (64,64,4), "peach": (32,48,4)}

def poses(image):
    rgba = np.array(image.convert("RGBA"))
    mask = (rgba[:,:,3] > 32).astype("uint8")
    # Connect detached facial/limb pixels within each individual pose.
    expanded = cv2.dilate(mask, np.ones((7,7),np.uint8), iterations=1)
    count, labels, stats, _ = cv2.connectedComponentsWithStats(expanded, 8)
    found = []
    for x,y,w,h,area in stats[1:]:
        x=max(0,int(x)-3);y=max(0,int(y)-3)
        w=min(image.width-x,int(w)+6);h=min(image.height-y,int(h)+6)
        actual = int(mask[y:y+h,x:x+w].sum())
        if 8 <= w <= 115 and 12 <= h <= 125 and actual >= 65:
            found.append((x,y,w,h,actual))
    return sorted(found, key=lambda b:(b[1]//28,b[0]))

def main():
    if len(sys.argv)<2:
        print("Supply one or more character ZIP files.");return 2
    previews = ROOT / "artwork_previews"
    previews.mkdir(exist_ok=True)
    for archive in map(Path,sys.argv[1:]):
        with zipfile.ZipFile(archive) as z:
            for name in z.namelist():
                who = name.split("/")[0].lower()
                if who not in SPECS or not name.lower().endswith("-1.png"):
                    continue
                im=Image.open(io.BytesIO(z.read(name))).convert("RGBA")
                candidates=poses(im)
                fw,fh,run_frames=SPECS[who]
                if len(candidates)<4:
                    print(f"WARNING {who}: only {len(candidates)} candidate poses");continue
                # Preview all detected poses for manual selection and correction.
                preview=Image.new("RGB",(600,((len(candidates)+7)//8)*90),"#333333")
                draw=ImageDraw.Draw(preview)
                for i,(x,y,w,h,_) in enumerate(candidates):
                    pose=im.crop((x,y,x+w,y+h))
                    pose.thumbnail((64,64),Image.Resampling.NEAREST)
                    col,row=i%8,i//8
                    preview.paste(pose,(col*75,row*90),pose)
                    draw.text((col*75,row*90+65),str(i),fill="white")
                preview.save(previews/f"{who}_poses.png")
                # The first extracted poses are only a provisional animation.
                # Never assert that they correspond to actual run/jump poses.
                for state,n in [("idle",2 if who=="bowser" else 4 if who=="peach" else 1),("run",run_frames),("jump",2 if who=="bowser" else 1)]:
                    strip=Image.new("RGB",(fw*n,fh),(255,0,255))
                    for j in range(n):
                        x,y,w,h,_=candidates[j%len(candidates)]
                        pose=im.crop((x,y,x+w,y+h))
                        pose.thumbnail((fw,fh),Image.Resampling.NEAREST)
                        strip.paste(pose,(j*fw+(fw-pose.width)//2,fh-pose.height),pose.getchannel("A"))
                    dest=OUTPUT/("characters" if who=="peach" else "heroes")/f"{who}_{state}.bmp"
                    if who=="peach" and state!="idle":
                        continue
                    dest.parent.mkdir(parents=True,exist_ok=True)
                    strip.save(dest)
                print(f"{who}: generated provisional manifest-compatible BMP strips; review {who}_poses.png")
    return 0

if __name__=="__main__":
    sys.exit(main())
