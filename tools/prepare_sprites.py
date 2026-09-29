#!/usr/bin/env python3
"""Hellz Yeah Retro World local sprite-sheet preparation tool.

Source sheets stay outside Git. This tool crops selected rectangles, removes a
flat sheet background, pads frames to a common size, and writes horizontal BMP
animation strips consumed by the native engine.

Requires Pillow: py -m pip install pillow
Example:
 py tools/prepare_sprites.py --sheet mario.png --out engine/assets/imported/heroes/mario_run.bmp --bg 0,153,153 --frame 8,8,24,40 --frame 40,8,24,40
"""
from PIL import Image
import argparse, os

def rgb(s):
    v=tuple(int(x) for x in s.split(","))
    if len(v)!=3: raise argparse.ArgumentTypeError("use R,G,B")
    return v

p=argparse.ArgumentParser()
p.add_argument("--sheet",required=True)
p.add_argument("--out",required=True)
p.add_argument("--bg",type=rgb)
p.add_argument("--frame",action="append",required=True,help="x,y,w,h; repeat in animation order")
p.add_argument("--pad",type=int,default=2)
a=p.parse_args()

src=Image.open(a.sheet).convert("RGBA")
frames=[]
for spec in a.frame:
    x,y,w,h=(int(n) for n in spec.split(","))
    im=src.crop((x,y,x+w,y+h))
    if a.bg:
        px=im.load()
        for yy in range(im.height):
            for xx in range(im.width):
                r,g,b,alpha=px[xx,yy]
                if (r,g,b)==a.bg: px[xx,yy]=(255,0,255,0)
    frames.append(im)

fw=max(i.width for i in frames)+a.pad*2
fh=max(i.height for i in frames)+a.pad*2
strip=Image.new("RGBA",(fw*len(frames),fh),(255,0,255,0))
for i,im in enumerate(frames):
    strip.alpha_composite(im,(i*fw+(fw-im.width)//2,(fh-im.height)//2))

# BMP runtime uses magenta color key; flatten transparent pixels to magenta.
flat=Image.new("RGB",strip.size,(255,0,255))
flat.paste(strip,mask=strip.getchannel("A"))
os.makedirs(os.path.dirname(a.out) or ".",exist_ok=True)
flat.save(a.out,"BMP")
print(f"wrote {a.out}: {len(frames)} frames, {fw}x{fh} each")
