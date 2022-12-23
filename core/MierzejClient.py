import threading
import time
import serial
from pprint import pprint

class MierzejClient(threading.Thread):
    def __init__(self):
        self.channels = [0, 0, 0, 0, 0]
        self.ser = serial.Serial(port='/dev/ttyUSB0', baudrate=9600, parity=serial.PARITY_NONE, stopbits=serial.STOPBITS_ONE, bytesize=serial.EIGHTBITS, timeout=0)
        print("connected to: " + self.ser.portstr)
        threading.Thread.__init__(self)

    def decode_read_value(self, frame_):
        frame = bytearray(frame_)
        self.channels = [
            (frame[10] << 24) | (frame[9] << 16) | (frame[8] << 8) | frame[7],
            (frame[14] << 24) | (frame[13] << 16) | (frame[12] << 8) | frame[11],
            (frame[18] << 24) | (frame[17] << 16) | (frame[16] << 8) | frame[15],
            (frame[22] << 24) | (frame[21] << 16) | (frame[20] << 8) | frame[19],
            (frame[26] << 24) | (frame[25] << 16) | (frame[24] << 8) | frame[23]
        ]

    def get_values(self):
        return self.channels
        
    def run(self):
        while True:
            time.sleep(1)
            
            self.ser.write([0x02, 0x09, 0xaa, 0xbb, 0xcc, 0xdd, 0x04, 0x0f, 0x03])
         
            frame = self.ser.read(49)

            if not frame:
                continue

            self.decode_read_value(frame)

            
