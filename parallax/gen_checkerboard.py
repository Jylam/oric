#!/usr/bin/python3
# vim: tabstop=8 expandtab shiftwidth=4 softtabstop=4
import pygame
import time
pygame.init()

screen = pygame.display.set_mode([216, 100])

running = True
while running:

    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            running = False

    board = pygame.Surface((216, 216))
    screen.fill((255, 0, 255))

    size = 27
    xoffset = 0;
    while True:
        cnt = 0
        for y in range(0, 8):
            cnt=cnt+1
            for x in range(-8, 8):
                color = (0,0,0)
                if cnt&1:
                    color = (255, 255, 255)
                pygame.draw.rect(board, color, (x*size+xoffset, y*size, size, size))
                cnt = cnt+1

        for i in range(0, 100):
            t = pygame.transform.scale(board, (int(216*(i/100.0)), 100))
            screen.blit(t, (0, i), (0,i,216,1))
    #    pygame.image.save(screen, "checkerboard.png")
        pygame.display.flip()
        time.sleep(.1)
        xoffset+=1
pygame.quit()
