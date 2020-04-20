import math

print("u8 sintable[256] = {")
for i in range(0, 255):
    s = math.sin(math.radians(i))
    fp = s*255;
    if fp < 0:
        fp = fp + 2**8
    print("%d, "%(fp), end='')
print("};")
