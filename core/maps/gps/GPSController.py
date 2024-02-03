import threading
import time
from websocket_server import WebsocketServer
from pprint import pprint
import json
from maps.gps.GPSModule import GPSModule
from maps.Server import Server
from maps.gps.GPSInfo import GPSInfo

class GPSController(threading.Thread):
    def __init__(self):
        threading.Thread.__init__(self)
        self.server = Server()
        self.server.start()
        self.gps = GPSModule()
        self.gps.init()
        self.data = GPSInfo()



    def run(self):
        while True:
            fresh_coordinates = self.gps.get_gps_location()

            if fresh_coordinates != None:
                self.data = fresh_coordinates

            print("SEND:", self.data.toDict())
            self.server.send(self.data.toDict())


'''
SEND: {'timestamp': '20240118201755.000', 'latitude': '52.209354', 'longitude': '20.967318', 'speed': '0.00', 'fix_status': '1'}

+CGNSINF: 1,1,20240118201756.000,52.209354,20.967317,126.600,0.00,249.2,1,,0.8,1.2,0.8,,35,8,5,,,51,,

'''