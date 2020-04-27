#!/usr/bin/python3
# vim: tabstop=8 expandtab shiftwidth=4 softtabstop=4

from PIL import Image
import numpy


def gen_data(filename):
    im = Image.open(filename)
    pix = im.load()
    width, height = im.size

    total = 0
    rle_total = 0
    for y in range(0, height):
        old_color = (255, 0, 255)
        length = 0
        for x in range(0, width):
            color = im.getpixel((x, y))
            if color == (255, 0, 255):
                print("")
                break
            else:
                if old_color != color:
                    if length!=0:
                        print("[%d %d] "%(length, old_color[0]==255), end='')
                        rle_total += 2
                    length=1
                else:
                    length+=1
                total+=1
                old_color = color
            #    print(color[0], end='')
    print("%d bytes, rle_total %d"%(total/8, rle_total))
gen_data("checkerboard00.png")
