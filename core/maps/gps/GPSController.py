import threading
import time
from websocket_server import WebsocketServer
from pprint import pprint
import json
from maps.gps.GPSModule import GPSModule
from maps.Server import Server
from maps.gps.GPSInfo import GPSInfo
from maps.gps.DynamicRouteWriter import DynamicRouteWriter

class GPSController(threading.Thread):
    def __init__(self, mock):
        threading.Thread.__init__(self)
        self.mock = mock
        self.server = Server()
        self.server.start()
        self.gps = GPSModule(mock=self.mock)
        self.gps.init()
        self.data = GPSInfo()

        self.route_writer = DynamicRouteWriter()

        # Rozpocznij tworzenie pliku GPX
        self.route_writer.start_gpx()

        # Rozpocznij tworzenie pliku GPX
        self.route_writer.start_gpx()

        # Dodaj porcję koordynatów
        self.route_writer.add_coordinates([(52.2297, 21.0122), (52.2305, 21.0118), (52.2310, 21.0125)])

        





    def run(self):
        while True:
            fresh_coordinates = self.gps.get_gps_location()

            self.route_writer.append_data([(fresh_coordinates.latitude, fresh_coordinates.longitude)])
            # Zakończ XML
            self.route_writer.end_gpx()

            if fresh_coordinates != None:
                self.data = fresh_coordinates

            # print("SEND:", self.data.toDict())
            self.server.send(self.data.toDict())


'''
SEND: {'timestamp': '20240118201755.000', 'latitude': '52.209354', 'longitude': '20.967318', 'speed': '0.00', 'fix_status': '1'}

 {'timestamp': '20240204213949.000', 'latitude': '52.209338', 'longitude': '20.967327', 'speed': '0.00', 'fix_status': '1'}

+CGNSINF: 1,1,20240118201756.000,52.209354,20.967317,126.600,0.00,249.2,1,,0.8,1.2,0.8,,35,8,5,,,51,,

'''