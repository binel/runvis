
class Coordinate: 
    def __init__(self, lat, long, eleMeters, timeUtc):
        self.lat = lat
        self.long = long
        self.eleMeters = eleMeters 
        self.timeUtc = timeUtc 

    def __str__(self):
        return f"({self.lat}, {self.long})"
