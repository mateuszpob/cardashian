import threading
import time
from pprint import pprint
import json

class DistanceCounter(threading.Thread):
    def __init__(self):
        self.total_distance = 124522
        self.trip_distance = 554
        threading.Thread.__init__(self)

    def calculate_distance(self):
        print(1)

    def decore_frame(self, frame):
        # pprint(frame)
        setattr(frame, 'total_distance', self.total_distance)
        # frame['total_distance'] = self.total_distance
        # frame.trip_distance = self.trip_distance
        return frame
    
    def run(self):
        while(True):
            self.calculate_distance()
            time.sleep(1)