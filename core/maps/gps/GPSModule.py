import serial
import time

from maps.gps.GPSInfoParser import GPSInfoParser
from maps.gps.FakeZapierdalacz import FakeZapierdalacz

class GPSModule:
    def __init__(self, serial_port='/dev/ttyUSB0', baud_rate=9600, timeout=1, mock=True):
        self.mock = mock
        self.ser = None

        if self.mock == False:
            self.ser =  serial.Serial(serial_port, baud_rate, timeout=timeout)
        
        self.gps_info_parser = GPSInfoParser()
        self.fakeZapierdalacz = FakeZapierdalacz('20.967317', '52.208354')

    def send_at_command(self, command, timeout=1):
        self.ser.write((command + '\r\n').encode())
        time.sleep(timeout)
        return self.ser.read(self.ser.in_waiting).decode()

    def enable_gps_power(self):
        # Włącz zasilanie GPS
        self.send_at_command('AT+CGNSPWR=1')

        # Poczekaj na dostateczny czas dla modułu GPS do włączenia
        time.sleep(5)

    def disable_echo(self):
        # Wyślij komendę ATE0, aby wyłączyć echo
        response = self.send_at_command('ATE0')

        # Sprawdź odpowiedź modułu
        if 'OK' in response:
            print('Echo zostało wyłączone.')
        else:
            print('Błąd podczas wyłączania echo. Ponawiam...')
            time.sleep(1)
            self.disable_echo()

    def init(self):
        if self.mock == False:
            self.enable_gps_power()
            self.disable_echo()

    def close_connection(self):
        print("Dorobić zamykanie polaczenia")

    def print_gps_location(self):
        
        while True:
            # Pobierz informacje o lokalizacji
            response = self.send_at_command('AT+CGNSINF')

            # Sprawdź odpowiedź modułu
            if 'ERROR' in response:
                print('Błąd podczas pobierania lokalizacji.')
            else:
                # print(response.strip())
                gps_info = self.gps_info_parser.parse_cgnsinf_string(response)
                print('Lokalizacja:', gps_info)

            # Poczekaj 1 sekundę przed ponownym odpytaniem
            time.sleep(1)

    def get_gps_location(self):
        if self.mock == True:
            return self.fakeZapierdalacz.simulate_random_movement()
        
        response = self.send_at_command('AT+CGNSINF')
        # response = '1,1,20240118201756.000,52.209354,20.967317,126.600,0.00,249.2,1,,0.8,1.2,0.8,,35,8,5,,,51,,'
        if 'ERROR' not in response:
            print(response)
            return self.gps_info_parser.parse_cgnsinf_string(response)

if __name__ == "__main__":
    gps_module = GPSModule()

    # Włącz zasilanie GPS
    gps_module.enable_gps_power()

    # Wyłącz echo
    gps_module.disable_echo()

    # Pobierz lokalizację co 1 sekundę
    gps_module.print_gps_location()