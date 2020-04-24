#!/usr/bin/python3

print("_copy_buffer\nldy #2\nstart_copy")
for i in range(0, 200):
    print("lda _buffer+(%d*40), y"%(i))
    print("sta $A000+(%d*40), y"%(i))
print("iny\ncpy #40\nbeq end_copy\njmp start_copy\nend_copy\nrts")

#print("_clear_buffer\nldy #2\nlda #64\nstart_clear")
#for i in range(0, 200):
#    print("sta _buffer+(%d*40), y"%(i))
#print("iny\ncpy #40\nbeq end_clear\njmp start_clear\nend_clear\nrts")

