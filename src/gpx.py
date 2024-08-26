import xml.etree.ElementTree as ET 

from coordinate import Coordinate 

class Gpx: 
    def __init__(self):
        self.positions = []
        self.startUtc = None;
        self.endUtc = None;
        self.distanceKm = 0.0;

    def parse(self, filePath):
        xmlTree = ET.parse(filePath)
        root = xmlTree.getroot()
        
        print(f"Root element: {root.tag}")

        ns = "{http://www.topografix.com/GPX/1/1}"

        tracks = root.findall(f'{ns}trk')

        tracksCount = len(tracks)
        print(f"found {tracksCount} tracks")

        if tracksCount > 1:
            raise Exception("Encountered more than 1 track, I can't deal with that yet")
        
        trackSegments = tracks[0].findall(f'{ns}trkseg')
        segCount = len(trackSegments)
        print(f"found {segCount} track segments")

        if segCount > 1:
            raise Exception("Encountered more than 1 segment, I can't deal with that yet")

        points = trackSegments[0].findall(f'{ns}trkpt')
        pointCount = len(points)

        for point in points:
            lat = point.get('lat')
            long = point.get('lon')
            timeEle = point.find(f'{ns}time')

            time = None
            if timeEle == None:
                print("Unable to find time Element!")
            else:
                time = timeEle.text 
            
            eleEle = point.find(f'{ns}ele')

            eleMeters = None
            if eleEle == None:
                print("Unable to find elevation element!")
            else:
                eleMeters = eleEle.text

            coord = Coordinate(lat, long, eleMeters, timeEle)
            self.positions.append(coord)
            



