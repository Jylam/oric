#!/usr/bin/python3

print("_copy_buffer\nldy #0")
for i in range(0, 200):
    print("lda _buffer+(%d*40), y"%(i))
    print("sta _screen+(%d*40), y"%(i))
print("iny\ncpy #40\nbeq end_copy\njmp _copy_buffer\nend_copy")
