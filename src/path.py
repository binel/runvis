from point import Point

class Path: 
    def __init__(self):
        self.pathCoords = []

    def SetPath(self, gpxFile, gpsBox, windowWidth, windowHeight):
        latScale = windowHeight / (gpsBox.maxLat - gpsBox.minLat)
        longScale = windowWidth / (gpsBox.maxLong - gpsBox.minLong)

        for pos in gpxFile.positions:
            xpos = 50 + (pos.long - gpsBox.minLong) * longScale
            ypos = windowHeight + 50 - ((pos.lat - gpsBox.minLat) * latScale)
            self.pathCoords.append(Point(xpos, ypos))
