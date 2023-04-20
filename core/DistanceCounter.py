import threading
import time
from pprint import pprint
import json

class DistanceCounter(threading.Thread):
    def __init__(self, emu):
        self.emu = emu
        self.total_distance = 0
        self.trip_distance = 0
        self.km_to_sec = 0.27778
        # self.distance_log = open('distance.log', 'r')
        # self.total_distance = int(self.distance_log.read())
        # self.distance_log.close()
        # print("self.total_distance " + str(self.total_distance))
        # self.distance_log = open('distance.log', 'w')

        threading.Thread.__init__(self)

    def calculate_distance(self):
        if self.emu and self.emu.frame.get('vssSpeed'):
            sec_val = (float(self.emu.frame.get('vssSpeed')) * self.km_to_sec / 1000)
            self.trip_distance = self.trip_distance + sec_val
            # print(self.trip_distance)

            # self.total_distance = self.total_distance + self.trip_distance

            # self.distance_log.write(str(round(self.total_distance)))

    def get_total_distance(self):
        return str(round(self.total_distance, 1))
    
    def get_trip_distance(self):
        if self.trip_distance > 0:
            return  str(round(self.trip_distance, 1))
        return 0
    
    
    def run(self):
        while(True):
            try:
                self.calculate_distance()
            except:
                pass
            time.sleep(1)



# 1km/h = 1000m/h = 0.27778m/s