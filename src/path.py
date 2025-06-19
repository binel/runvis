import math

from point import Point

class Path: 
    def __init__(self):
        self.pathCoords = []

    def SetPath(self, gpxFile, gpsBox, windowWidth, windowHeight):
        minX, minY = self.LatLongToMercator(gpsBox.minLat, gpsBox.minLong)
        maxX, maxY = self.LatLongToMercator(gpsBox.maxLat, gpsBox.maxLong)
        
        mapWidth = maxX - minX
        mapHeight = maxY - minY

        scale = min(windowWidth / mapWidth, windowHeight / mapHeight)  # uniform scale

        xOffset = (windowWidth - mapWidth * scale) / 2
        yOffset = (windowHeight - mapHeight * scale) / 2 - 50

        for pos in gpxFile.positions:
            x, y = self.LatLongToMercator(pos.lat, pos.long)
            xpos = (x - minX) * scale + xOffset
            ypos = windowHeight - ((y - minY) * scale + yOffset)
            self.pathCoords.append(Point(xpos, ypos))

    def LatLongToMercator(self, lat, lon):
        R = 6378137 # Earth radius in meters 
        x = R * math.radians(lon)
        y = R * math.log(math.tan(math.pi / 4 + math.radians(lat) / 2))
        return x, y