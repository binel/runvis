import unittest
from src.coordinate import Coordinate 

class TestCoordinate(unittest.TestCase):
    
    def test_str(self):
        coord = Coordinate(-41, 90)
        strCoord = str(coord)
        self.assertEqual(strCoord, "(-41, 90)")

    def test_str_decimal(self):
        coord = Coordinate(-41.1, 90.1)
        strCoord = str(coord)
        self.assertEqual(strCoord, "(-41.1, 90.1)")
