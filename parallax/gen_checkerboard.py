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

    board = pygame.Surface((216, 100))
    screen.fill((255, 0, 255))

    cur_img = 0
    size = 27
    xoffset = 0;
    while cur_img < 54:
        cnt = 0
        ysize = 27.0
        y = 0.0
        while y <= 216:
            cnt=cnt+1
            for x in range(-8, 8):
                color = (0,0,0)
                if cnt&1:
                    color = (255, 255, 255)
                pygame.draw.rect(board, color, (x*size+xoffset, int(y), size, int(ysize)))
                cnt = cnt+1
            y+=ysize
            ysize*=0.80
            if ysize<0.00001:
                ysize = 0.1
        board = pygame.transform.flip(board, False, True)
        for i in range(0, 100):
            t = pygame.transform.scale(board, (int(216*(i/100.0)), 100))
            screen.blit(t, (0, i), (0,i,216,1))
        print("Saving checkerboard%02d.png"%(cur_img))
        pygame.image.save(screen, "checkerboard%02d.png"%(cur_img))
        pygame.display.flip()
        cur_img+=1
        if cur_img == 54:
            pygame.quit()
        xoffset+=1
pygame.quit()
