#!/usr/bin/python3

print("_copy_buffer\nldy #0\nstart_copy")
for i in range(0, 200):
    print("lda _buffer+(%d*40), y"%(i))
    print("sta $A000+(%d*40), y"%(i))
print("iny\ncpy #40\nbeq end_copy\njmp start_copy\nend_copy\nrts")
