import re
import random
import time

from maps.gps.GPSInfo import GPSInfo

class GPSInfoParser:
    @staticmethod
    def parse_cgnsinf_string(cgnsinf_string):
        # Przykładowe parsowanie; dostosuj to do rzeczywistego formatu odpowiedzi
        # Oczekiwany format: "+CGNSINF: 1,0,..."
        parts = GPSInfoParser.remove_syf(cgnsinf_string).strip().split(',')

        if len(parts) < 7:
            return None
        
        # Przykładowe wartości; dostosuj to do rzeczywistych danych
        # status = int(parts[0])
        fix_status = parts[1] if parts[1] else 0
        timestamp = parts[2]
        latitude = parts[3]
        longitude = parts[4]
        # altitude = float(parts[5])
        speed = parts[6]
        # course = float(parts[7])
        # fix_age = int(parts[8])
        # hdop = float(parts[9])
        # vdop = float(parts[10])
        # pdop = float(parts[11])
        # satellites_used = int(parts[12])
        # current_satellite = int(parts[13])
        # fix_indicator = int(parts[14])
        # next_satellite = int(parts[15])
        # hot_fix = int(parts[16])
        # altitude_msl = float(parts[17])
        # speed_over_ground = float(parts[18])
        # course_over_ground = float(parts[19])

        return GPSInfo(timestamp, latitude, longitude, speed, fix_status)
    
    @staticmethod
    def remove_syf(string):
        # Użyj wyrażenia regularnego, aby uzyskać tylko cyfry, kropki i przecinki
        pattern = re.compile(r'[0-9.,]+')
        matches = re.findall(pattern, string)

        # Połącz dopasowane fragmenty w jeden string
        result = ''.join(matches)

        return result
    