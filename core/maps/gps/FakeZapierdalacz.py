import re
import random
import time

from maps.gps.GPSInfo import GPSInfo

class FakeZapierdalacz:
    def __init__(self, base_longitude, base_latitude):
        self.base_longitude = base_longitude
        self.base_latitude = base_latitude

    def simulate_random_movement(self, max_deviation=0.0005, max_speed=5.0, fix_status='1'):
        time.sleep(1)
        # Symulacja losowego ruchu w okolicy podanej lokalizacji
        self.base_latitude = float(self.base_latitude) + random.uniform(0, max_deviation)
        self.base_longitude = float(self.base_longitude) + random.uniform(0, max_deviation)
        speed = round(random.uniform(0, max_speed), 2)

        # Pobierz aktualny czas w formacie NMEA
        timestamp = time.strftime("%Y%m%d%H%M%S.000", time.gmtime())

        return GPSInfo(timestamp=str(timestamp), latitude=str(self.base_latitude), longitude=str(self.base_longitude), speed=str(speed), fix_status=fix_status)
