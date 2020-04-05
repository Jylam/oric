from PIL import Image
import numpy

im = Image.open('boule_sprite.png')
pix = im.load()
#print(im.size)

for i in range(0, 6):
    print("u8 sprite%d[] = {"%i)
    for y in range(im.size[1]):
        curline = []
        for x in range(im.size[0]):
            curline.append(pix[x,y])
        curline.append(0)
        curline.append(0)
        curline.append(0)
        curline.append(0)
        curline.append(0)
        curline.append(0)
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


