import math

for i in range(0, 255):
    s = math.sin(math.radians(i))
    print("%u: %f, "%(int(i), s))
