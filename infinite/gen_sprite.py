from PIL import Image
import numpy

#print(im.size)



def gen_image(filename, name):
    im = Image.open(filename)
    pix = im.load()
    for i in range(0, 6):
        print("u8 %s%d[] = {"%(name, i))
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

gen_image('boule_sprite.png', 'sprite')
gen_image('boule_sprite_alpha.png', 'sprite_alpha')

