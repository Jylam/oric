#!/usr/bin/python3

print("DrawSpriteJumpTableLow")
for x in range(0,200):
    print("\t.byt <(DrawSpriteUnrolled+"+str(8*x)+")")
print("DrawSpriteJumpTableHigh")
for x in range(0,200):
    print("\t.byt >(DrawSpriteUnrolled+"+str(8*x)+")")


print("; Assumes the stack pointer is on the graphics")
print("; and X has the correct screen column")
print("DrawSpriteUnrolled")
for x in range(0,200):
    print("\tpla                                             ; 4 cycles - 1 byte")
    print("\tsta $a000+40*"+str(x)+"+0,x              ; 5 cycles - 3 bytes")
    print("\tpla                                             ; 4 cycles - 1 byte")
    print("\tsta $a000+40*"+str(x)+"+1,x              ; 5 cycles - 3 bytes")
    print("")


print("ClearSpriteJumpTableLow")
for x in range(0,200):
    print("\t.byt <(ClearSpriteUnrolled+"+str(6*x)+")")
print("ClearSpriteJumpTableHigh")
for x in range(0,200):
    print("\t.byt >(ClearSpriteUnrolled+"+str(6*x)+")")


print("; Assumes the stack pointer is on the graphics")
print("; and X has the correct screen column")
print("ClearSpriteUnrolled")
for x in range(0,200):
    print("\tsta $a000+40*"+str(x)+"+0,x              ; 5 cycles - 3 bytes")
    print("\tsta $a000+40*"+str(x)+"+1,x              ; 5 cycles - 3 bytes")
    print("")



