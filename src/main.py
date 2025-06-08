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

    # find the min and max lat and long
    minLat = 90 
    maxLat = -90
    minLong = 180
    maxLong = -180
    for pos in gpxFile.positions:
        if (pos.lat > maxLat): 
            maxLat = pos.lat 
        if (pos.lat < minLat): 
            minLat = pos.lat
        if (pos.long > maxLong):
            maxLong = pos.long
        if (pos.long < minLong):
            minLong = pos.long
        print(pos)

    print(f"max lat {maxLat}")
    print(f"min lat {minLat}")
    print(f"max long {maxLong}")
    print(f"min long {minLong}")

    # determine scale 
    windowWidth = 500
    windowHeight = 500 

    latScale = windowHeight / (maxLat - minLat)
    longScale = windowWidth / (maxLong - minLong)
    print(f"lat scale: {latScale}")
    print(f"long scale: {longScale}")

    pygame.init()

    window = pygame.display.set_mode((windowWidth, windowHeight))
    pygame.display.set_caption('runvis')

    running = True
    while running:
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                running = False

        window.fill((0,0,0))
        for pos in gpxFile.positions:
            xpos = (pos.long - minLong) * longScale
            ypos = windowHeight - ((pos.lat - minLat) * latScale)
            pygame.draw.circle(window, (255, 0, 0), (xpos, ypos), 2)
        pygame.display.flip()
    pygame.quit()

main()