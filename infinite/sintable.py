import math

for i in range(0, 255):
    s = math.sin(math.radians((i/255.0)*360.0))*255.0
    print("%u, "%(int(s)))
