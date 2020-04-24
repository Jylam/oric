#!/usr/bin/python3
"""
 Simulation of a rotating 3D Cube
 Developed by Leonel Machava <leonelmachava@gmail.com>

 http://codeNtronix.com
"""
import os
os.environ['PYGAME_HIDE_SUPPORT_PROMPT'] = "hide"
import sys, math, pygame
from operator import itemgetter
import time
class Point3D:
    def __init__(self, x = 0, y = 0, z = 0):
        self.x, self.y, self.z = float(x), float(y), float(z)

    def rotateX(self, angle):
        """ Rotates the point around the X axis by the given angle in degrees. """
        rad = angle * math.pi / 180
        cosa = math.cos(rad)
        sina = math.sin(rad)
        y = self.y * cosa - self.z * sina
        z = self.y * sina + self.z * cosa
        return Point3D(self.x, y, z)

    def rotateY(self, angle):
        """ Rotates the point around the Y axis by the given angle in degrees. """
        rad = angle * math.pi / 180
        cosa = math.cos(rad)
        sina = math.sin(rad)
        z = self.z * cosa - self.x * sina
        x = self.z * sina + self.x * cosa
        return Point3D(x, self.y, z)

    def rotateZ(self, angle):
        """ Rotates the point around the Z axis by the given angle in degrees. """
        rad = angle * math.pi / 180
        cosa = math.cos(rad)
        sina = math.sin(rad)
        x = self.x * cosa - self.y * sina
        y = self.x * sina + self.y * cosa
        return Point3D(x, y, self.z)

    def project(self, win_width, win_height, fov, viewer_distance):
        """ Transforms this 3D point to 2D using a perspective projection. """
        factor = fov / (viewer_distance + self.z)
        x = self.x * factor + win_width / 2
        y = -self.y * factor + win_height / 2
        return Point3D(x, y, self.z)

class Simulation:
    def __init__(self, win_width = 228, win_height = 176):
        total_size = 0
        pygame.init()
        self.min_z = float('inf')
        self.max_z = float('-inf')
        self.screen = pygame.display.set_mode((win_width, win_height))
        pygame.display.set_caption("Simulation of a rotating 3D Cube (http://codeNtronix.com)")

        self.clock = pygame.time.Clock()
        self.vertices = []
        if False:
            self.vertices.append(Point3D(-1,1,-1))
            self.vertices.append(Point3D(1,1,-1))
            self.vertices.append(Point3D(1,-1,-1))
            self.vertices.append(Point3D(-1,-1,-1))
            self.vertices.append(Point3D(-1,1,1))
            self.vertices.append(Point3D(1,1,1))
            self.vertices.append(Point3D(1,-1,1))
            self.vertices.append(Point3D(-1,-1,1))
        else:
            pt_count = 0
            M = 4
            N = 6
            for m in range(0, M):
                for n in range(0, N):
                    self.vertices.append(Point3D(
                        math.sin(math.pi * m/M)*math.cos(2*math.pi * n/N),
                        math.sin(math.pi * m/M)*math.sin(2*math.pi * n/N),
                        math.cos(math.pi * m/M)))
                    pt_count+=1
            self.vertices = self.vertices[6:]
        # Define the vertices that compose each of the 6 faces. These numbers are
        # indices to the vertices list defined above.
        self.faces  = [(0,1,2,3),(1,5,6,2),(5,4,7,6),(4,0,3,7),(0,4,5,1),(3,2,6,7)]

        self.edges  = [(0,1),(1,2),(2,3),(3,0), # Front
                       (1,5),(5,6),(6,2),
                       (0,4),(4,5),
                       (3,7),(7,6),
                       (7,4),
                      ]

        # Define colors for each face
        self.colors = [(255,0,255),(255,0,0),(0,255,0),(0,0,255),(0,255,255),(255,255,0)]

        self.angle = 0
        self.frame = 0
    def run(self):
        """ Main Loop """
        print("u8 anim[] = {")
        while 1:
            circles = []
            for event in pygame.event.get():
                if event.type == pygame.QUIT:
                    pygame.quit()
                    sys.exit()

            self.clock.tick(50)
            self.screen.fill((0,32,0))

            # It will hold transformed vertices.
            t = []

            for v in self.vertices:
                # Rotate the point around X axis, then around Y axis, and finally around Z axis.
                r = v.rotateX(self.angle).rotateY(self.angle).rotateZ(self.angle)
                # Transform the point from 3D to 2D
                fov = 256
                distance = 4
                p = r.project(self.screen.get_width(), self.screen.get_height(), fov, distance)
                # Put the point in the list of transformed vertices
                t.append(p)
            t.sort(key=lambda p: p.z, reverse=True)
            for v in t:
                if v.z < self.min_z:
                    self.min_z = v.z
                if v.z > self.max_z:
                    self.max_z = v.z
            I = 0
            for v in t:
                y_offset = 0
                h = 18
                w = 24 # 4 bytes wide
                ssize = 9
                sprite = 0
                if v.z   >= -.5:
                    ssize      = 8
                    sprite = 1
                if v.z >=  0:
                    ssize      = 6
                    sprite = 2
                if v.z >=  .5:
                    y_offset = 4
                    ssize      = 4
                    sprite = 3
                overlap = False

                # Check if current circle overlaps a previous one
                #for c in circles:
                #    dist = math.sqrt((v.x - c[0].x)**2 + (v.y - c[0].y)**2)
                #    if dist < (c[1]+ssize):
                #        overlap = True
                # That's silly, overlaping is 18x18 for now
                overlap = False
                Bx1 = v.x
                By1 = v.y
                Bx2 = v.x+w
                By2 = v.y+h
                for c in circles:
                    Ax1 = c[0].x
                    Ay1 = c[0].y
                    Ax2 = c[0].x+c[1]
                    Ay2 = c[0].y+c[2]

                    if (Ax1 < Bx2) and (Ax2 > Bx1) and (Ay1 < By2) and (Ay2 > By1):
                        overlap = True
                        #pygame.draw.rect(self.screen, (255,0,0),(Ax1, Ay1, 18, 18))
                    #else:
                        #pygame.draw.rect(self.screen, (0,0,255),(Ax1, Ay1, 18, 18))

                circles.append((v, w, h))
                color = 0
                if overlap:
                    color = (255,0,0)
                else:
                    color = (255,255,0)
                pygame.draw.circle(self.screen, color, (int(v.x), int(v.y)), int(ssize))
                print("%d, %d, %d,"%(int(v.x), int(v.y+y_offset), sprite+(int(overlap)*4)))
                total_size+=3
            self.angle += 3
            self.frame+=1
            if self.frame == 60:
                print("};\n#define PT_COUNT %d\n// %d bytes"%(len(t), len(t)*3*self.frame))
                pygame.quit()
                sys.exit();
            pygame.display.flip()
            #time.sleep(.5)
if __name__ == "__main__":
    Simulation().run()
