import threading
import time
import socket
import sys
from pprint import pprint
import struct

class EmuSeialClient(threading.Thread):
    def __init__(self):
        # Create a TCP/IP socket
        self.sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

        # Connect the socket to the port where the server is listening
        server_address = ('localhost', 9990)
        self.sock.connect(server_address)
        print("Connected to EmuSerial \n")

        threading.Thread.__init__(self)
        
    def run(self):
        while True:

            print("=============================")
            data = self.sock.recv(116)
            self.sock.send(bytes("ok", 'utf-8'))
            
            self.decode(data)
            # print(struct.unpack("f", data))
            
    def decode(self, data):
        # pprint(data)
        fields = ["RPM","MAP","TPS","IAT","Batt","IgnAngle","pulseWidth","scondarypulseWidth","Egt1","Egt2","knockLevel","dwellTime","wboAFR","gear","Baro","analogIn1","analogIn2","analogIn3","analogIn4","injDC","emuTemp","oilPressure","oilTemperature","fuelPressure","CLT","flexFuelEthanolContent","ffTemp","wboLambda","vssSpeed","deltaFPR","fuelLevel","tablesSet","lambdaTarget","afrTarget","cel"]
        types = ["uint16_t","uint16_t","uint8_t","int8_t","float","float","float","float","uint16_t","uint16_t","float","float","float","int8_t","uint8_t","float","float","float","float","float","int8_t","float","uint8_t","float","int16_t","float","int8_t","float","float","uint16_t","uint8_t","uint8_t","float","float","uint16_t"]
        
        sizes = {
            "uint16_t": 2,
            "int16_t": 2,
            "uint8_t": 1,
            "int8_t": 1,
            "float": 4
        }
        dataObject = {}
        i = 0
        offset = 0
        
        for field in fields:
            if types[i] == 'float':
                # print(field)
                # print(struct.unpack('f', data[offset+2:offset+2+sizes[types[i]]]))

                dataObject[field] = struct.unpack('f', data[offset+2:offset+2+sizes[types[i]]])

            offset=offset+sizes[types[i]]
            i=i+1

        pprint(dataObject)

            
