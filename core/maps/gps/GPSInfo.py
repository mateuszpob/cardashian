class GPSInfo:
    def __init__(self, timestamp='20240101000000.000', latitude='52.194653', longitude='22.739830', speed='0.00', fix_status='0'):
        self.timestamp = timestamp
        self.latitude = latitude
        self.longitude = longitude
        self.speed = speed
        self.fix_status = fix_status

    def toDict(self):
        return {
            "timestamp": self.timestamp,
            "latitude": self.latitude,
            "longitude": self.longitude,
            "speed": self.speed,
            "fix_status": self.fix_status
        }

    def __repr__(self):
        return f"GPSInfo(timestamp={self.timestamp}, " \
               f"latitude={self.latitude}, longitude={self.longitude}, " \
               f"speed={self.speed}, fix_status={self.fix_status})"