from gpsBox import GpsBox

# Helper class to determine the bounding box (min/max lat long) from a GPX object
class Range:
    def single(gpx):
        gpsBox = GpsBox()
        for pos in gpx.positions:
            if (pos.lat > gpsBox.maxLat): 
                gpsBox.maxLat = pos.lat 
            if (pos.lat < gpsBox.minLat): 
                gpsBox.minLat = pos.lat
            if (pos.long > gpsBox.maxLong):
                gpsBox.maxLong = pos.long
            if (pos.long < gpsBox.minLong):
                gpsBox.minLong = pos.long
        return gpsBox
    
    def multiple(gpxList):
        gpsBox = GpsBox()
        for file in gpxList:
            for pos in file.positions:
                if (pos.lat > gpsBox.maxLat): 
                    gpsBox.maxLat = pos.lat 
                if (pos.lat < gpsBox.minLat): 
                    gpsBox.minLat = pos.lat
                if (pos.long > gpsBox.maxLong):
                    gpsBox.maxLong = pos.long
                if (pos.long < gpsBox.minLong):
                    gpsBox.minLong = pos.long
        return gpsBox            