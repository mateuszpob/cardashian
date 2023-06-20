import threading
import time
import socket
import sys
from pprint import pprint
import struct
import math

class EmuSeialClient(threading.Thread):
    def __init__(self, mock=False):
        # Create a TCP/IP socket
        
        self.mock = mock
        if self.mock:
            print("EmuSerial MOCK \n")
        else:
            # Connect the socket to the port where the server is listening
            server_address = ('localhost', 9990)
            self.sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
            self.sock.connect(server_address)
            print("Connected to EmuSerial \n")

        self.frame = None
        threading.Thread.__init__(self)
        
    def run(self):
        while True:
            if self.mock:
                self.frame = self.generate_fake_frame()
                
            else:
                data = self.sock.recv(116)
                self.sock.send(bytes("ok", 'utf-8'))
                
                self.decode(data)
                # print(struct.unpack("f", data))
            time.sleep(0.05)
            
    def decode(self, data):
        precision = [0,         0,          0,          0,          2,      2,          2,              2,                      2,          2,          2,              2,          2,          2,          2,          2,              2,          2,              2,              2,          2,          2,              2,                  2,              0,          2,                          2,          2,              2,          2,          2,              2,              2,              2,              2]
        fields = [  "RPM",      "MAP",      "TPS",      "IAT",      "Batt", "IgnAngle", "pulseWidth",   "scondarypulseWidth",   "Egt1",     "Egt2",    "knockLevel",    "dwellTime","wboAFR",   "gear",     "Baro",     "analogIn1",    "analogIn2","analogIn3",    "analogIn4",    "injDC",    "emuTemp",  "oilPressure",  "oilTemperature",   "fuelPressure", "CLT",      "flexFuelEthanolContent",   "ffTemp",   "wboLambda",    "vssSpeed", "deltaFPR", "fuelLevel",    "tablesSet",    "lambdaTarget", "afrTarget",    "cel"]
        types = [   "uint16_t", "uint16_t", "uint8_t",  "int8_t",   "float","float",    "float",        "float",                "uint16_t", "uint16_t","float",         "float",    "float",    "int8_t",   "uint8_t",  "float",        "float",    "float",        "float",        "float",    "int8_t",   "float",        "uint8_t",          "float",        "int16_t",  "float",                    "int8_t",   "float",        "float",    "uint16_t", "uint8_t",      "uint8_t",      "float",        "float",        "uint16_t"]
        padding = [ 0,          0,          0,          0,          2,      0,           0,             0,                      0,          0,          0,              0,          0,          0,           0,           2,              0,          0,              0,              0,          0,          3,              0,                  3,              0,          2,                          0,          3,              0,          0,          0,              0,              0,              0,              0     ]
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
            
            offset = offset + padding[i]


            if types[i] == 'uint16_t':
                value = struct.unpack('H', data[offset:offset+sizes[types[i]]])[0]
                dataObject[field] = str(round(value, precision[i]))

            if types[i] == 'int16_t':
                value = struct.unpack('h', data[offset:offset+sizes[types[i]]])[0]
                dataObject[field] = str(round(value, precision[i]))

            if types[i] == 'uint8_t':
                value = struct.unpack('B', data[offset:offset+sizes[types[i]]])[0]
                dataObject[field] = str(round(value, precision[i]))

            if types[i] == 'int8_t':
                value = struct.unpack('b', data[offset:offset+sizes[types[i]]])[0]
                dataObject[field] = str(round(value, precision[i]))

            if types[i] == 'float':
                value = struct.unpack('f', data[offset:offset+sizes[types[i]]])[0]
                dataObject[field] = str(round(value, precision[i]))
                

            offset=offset+sizes[types[i]]
            i=i+1
        self.frame = dataObject
        # pprint(dataObject)



    def generate_fake_frame(self):
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
                # print(field)
                # print(struct.unpack('f', data[offset+2:offset+2+sizes[types[i]]]))

            dataObject[field] = 0

            offset=offset+sizes[types[i]]
            i=i+1

        return dataObject
