import sys

import pygame

from gpx import Gpx

def main():
    if len(sys.argv) != 2:
        print("Usage: main.py <path/to/gpx/file>")
        return
    
    path = sys.argv[1]
    gpxFile = Gpx()
    gpxFile.parse(path)

    return

    pygame.init()

    window = pygame.display.set_mode((400, 300))
    pygame.display.set_caption('runvis')

    running = True
    while running:
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                running = False

        window.fill((0,0,0))
        pygame.draw.circle(window, (255, 0, 0), (200, 150), 50)
        pygame.display.flip()

    pygame.quit()

main()