#!/usr/bin/python3

from PIL import Image
import numpy

total_size = 0;

def gen_image(filename, name):
    global total_size
    im = Image.open(filename)
    pix = im.load()
    print("u8 %s[] = {"%(name))
    for i in range(0, 6):
        #print("u8 %s%d[] = {"%(name, i))
        for y in range(im.size[1]):
            curline = []
            for x in range(im.size[0]):
                curline.append(pix[x,y])
            if name == "sprite18_data" or name == "sprite12_data" or name == "sprite8_data" or name == "sprite16_data":
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
            total_size+=4
    print("};")

gen_image('boule_sprite18.png', 'sprite18_data')
gen_image('boule_sprite_alpha18.png', 'sprite18_alpha_data')

gen_image('boule_sprite16.png', 'sprite16_data')
gen_image('boule_sprite_alpha16.png', 'sprite16_alpha_data')

gen_image('boule_sprite12.png', 'sprite12_data')
gen_image('boule_sprite_alpha12.png', 'sprite12_alpha_data')

gen_image('boule_sprite8.png', 'sprite8_data')
gen_image('boule_sprite_alpha8.png', 'sprite8_alpha_data')

print("// Size %d"%(total_size))
