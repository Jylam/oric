#!/usr/bin/python3
# vim: tabstop=8 expandtab shiftwidth=4 softtabstop=4

from PIL import Image
import numpy


def read_data(filename):
    im = Image.open(filename)
    pix = im.load()
    width, height = im.size

    total = 0
    rle_total = 0
    lines = []
    for y in range(0, height):
        old_color = (255, 0, 255)
        length = 0
        line = []
        for x in range(0, width):
            color = im.getpixel((x, y))
            if color == (255, 0, 255):
                lines.append(line)
                break
            else:
                if old_color != color:
                    if length!=0:
                        print("[%d %d] "%(length, old_color[0]==255), end='')
                        rle_total += 2
                    length=1
                else:
                    length+=1
                line.append(int(color==(255,255,255)))
                total+=1
                old_color = color
            #    print(color[0], end='')
    print("%d bytes"%(total/8))
    return lines

def gen_RLE(lines):
    changes = 0
    for line in lines:
        print(line, end='')
        line_changes = 0
        old_b = 0
        length = 0
        for b in line:
            if b!=old_b:
                length=1
                changes+=1
                line_changes+=1
            old_b = b
        print(" %d"%(line_changes))
    print("%d changes"%(changes))
lines = read_data("checkerboard00.png")
gen_RLE(lines)

