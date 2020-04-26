#!/usr/bin/python3
# vim: tabstop=8 expandtab shiftwidth=4 softtabstop=4
import pygame
pygame.init()

screen = pygame.display.set_mode([216, 100])

running = True
while running:

    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            running = False

    board = pygame.Surface((216, 216))
    screen.fill((255, 255, 255))

    size = 27
    cnt = 0
    for y in range(0, 8):
        cnt=cnt+1
        for x in range(0, 8):
            color = (0,0,0)
            if cnt&1:
                color = (255, 0, 0)
            pygame.draw.rect(board, color, (x*size, y*size, size, size))
            cnt = cnt+1
    screen.blit(board, (0, 0), (0,0,216,10))
    pygame.display.flip()

pygame.quit()
