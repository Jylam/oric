import math

print("u8 sintable_x[256] = {")
for i in range(0, 256):
    s = math.sin(math.radians((i/256.0)*360.0))
    fp = (((s+1.0)/2.0)*180)
    print("%d, "%(fp), end='')
print("};")

print("u8 sintable_y[256] = {")
for i in range(0, 256):
    s = math.sin(math.radians((i/256.0)*360.0))
    fp = (((s+1.0)/2.0)*82)
    print("%d, "%(fp), end='')
print("};")

