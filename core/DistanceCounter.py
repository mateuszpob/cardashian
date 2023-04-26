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

        self.total_distance = self.readDistanceFromFile()
        self.temp_total_distance = self.total_distance;
        threading.Thread.__init__(self)

    def readDistanceFromFile(self):
        f = open("/var/log/emu/distance.txt", "r")
        distance = int(f.read())
        f.close()
        return distance
    
    def writeDistanceToFile(self, distance):
        f = open("/var/log/emu/distance.txt", "w")
        f.write(str(distance))
        f.close()
        return distance
    
    def calculate_distance(self):
        if self.emu and self.emu.frame.get('vssSpeed'):
            frame_distran = (float(self.emu.frame.get('vssSpeed')) * self.km_to_sec / 1000)
            self.trip_distance = self.trip_distance + frame_distran

            self.temp_total_distance = self.temp_total_distance + frame_distran
            if self.total_distance < int(self.temp_total_distance):
                self.total_distance = int(self.temp_total_distance)
                self.writeDistanceToFile(self.total_distance)


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