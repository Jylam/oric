#!/usr/bin/python3

from PIL import Image
import numpy


def gen_image(filename, name):
    im = Image.open(filename)
    pix = im.load()
    print("u8 %s[] = {"%(name))
    for i in range(0, 6):
        #print("u8 %s%d[] = {"%(name, i))
        for y in range(im.size[1]):
            curline = []
            for x in range(im.size[0]):
                curline.append(pix[x,y])
            if name == "sprite_data":
                curline.append(0)
                curline.append(0)
                curline.append(0)
                curline.append(0)
                curline.append(0)
                curline.append(0)
            else:
                curline.append(1)
                curline.append(1)
                curline.append(1)
                curline.append(1)
                curline.append(1)
                curline.append(1)
            line = numpy.roll(curline, i)
            print("0b01", end='')
            for c in range(0, 6):
                print("%d"%line[c], end='')
            print(", 0b01", end='')
            for c in range(6, 12):
                print("%d"%line[c], end='')
            print(", 0b01", end='')
            for c in range(12, 18):
                print("%d"%line[c], end='')
            print(", 0b01", end='')
            for c in range(18, 24):
                print("%d"%line[c], end='')
            print(",")

    print("};")

gen_image('boule_sprite18.png', 'sprite_data')
gen_image('boule_sprite_alpha18.png', 'sprite_alpha_data')

gen_image('boule_sprite12.png', 'sprite12_data')
gen_image('boule_sprite_alpha12.png', 'sprite12_alpha_data')

