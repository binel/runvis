import sys
import os 

import pygame

from gpx import Gpx
from gpsBox import GpsBox
from range import Range
from path import Path 

def main():
    if len(sys.argv) != 2:
        print("Usage: main.py <path/to/gpx/file>")
        print("Or: main.py <path/to/gpx/folder>")
        return
    
    path = sys.argv[1]
    # controls if we are plotting one path or multiple 
    multifile = False
    if os.path.isfile(path):
        print("running in single file mode")
    elif os.path.isdir(path):
        multifile = True
        print("running in directory mode")
    else:
        print("ERROR - path does not exist")
        return

    gpxFileList = []
    if multifile:
        file_paths = [os.path.join(path, f) for f in os.listdir(path) if os.path.isfile(os.path.join(path, f))]
        for filepath in file_paths: 
            if not filepath.endswith('.gpx'):
                continue
            print(filepath)
            gpxFile = Gpx()
            gpxFile.parse(filepath)
            gpxFileList.append(gpxFile)
    else: 
        gpxFile = Gpx()
        gpxFile.parse(path)
        gpxFileList.append(gpxFile)

    # find the min and max lat and long
    gpsBox = Range.multiple(gpxFileList)

    windowWidth = 500
    windowHeight = 500 
    paths = []
    for file in gpxFileList:
        path = Path()
        path.SetPath(file, gpsBox, windowWidth, windowHeight)
        paths.append(path)

    pygame.init()

    window = pygame.display.set_mode((100 + windowWidth, 100 + windowHeight))
    pygame.display.set_caption('runvis')

    running = True
    while running:
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                running = False

        window.fill((0,0,0))
        for path in paths: 
            for pos in path.pathCoords:
                pygame.draw.circle(window, (255, 0, 0), (pos.xpos, pos.ypos), 2)
        pygame.display.flip()
    pygame.quit()

main()