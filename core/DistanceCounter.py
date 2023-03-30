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

    def get_total_distance(self):
        return self.total_distance
    
    def get_trip_distance(self):
        return self.trip_distance
    
    def run(self):
        while(True):
            self.calculate_distance()
            time.sleep(1)