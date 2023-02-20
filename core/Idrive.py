#!/usr/bin/python3

import threading
import time
import serial
import struct
# from simple_websocket_server import WebSocketServer, WebSocket
from websocket_server import WebsocketServer

class Idrive(threading.Thread):
    def __init__(self, conn):
        self.conn = conn
        self.device_name = 'Idrive'
        self.devices = [
            '/dev/ttyUSB0',
            '/dev/ttyUSB1',
            '/dev/ttyUSB2',
            '/dev/ttyUSB3',
            '/dev/ttyUSB4',
            '/dev/ttyUSB5',
        ]

        
        threading.Thread.__init__(self)

    def connect_serial_device(self):
        while self.searchDevice() == False:
            time.sleep(1)

        # self.ser = serial.Serial(port=path, baudrate=9600, parity=serial.PARITY_NONE, stopbits=serial.STOPBITS_ONE, bytesize=serial.EIGHTBITS, timeout=0)
        # print("connected to: " + self.ser.portstr)
        
    def searchDevice(self):
        for device in self.devices:
            # print("Check device " + device)
            if self.checkDevice(device):
                return True
        return False

    def checkDevice(self, path):
        try:
            self.ser = serial.Serial(port=path, baudrate=19200, parity=serial.PARITY_NONE, stopbits=serial.STOPBITS_ONE, bytesize=serial.EIGHTBITS, timeout=0)
            print("connected to: " + self.ser.portstr)
        except:
            return False

        time.sleep(0.5)
        self.ser.write(bytes('a', 'ascii'))
        time.sleep(0.3)
        line =  self.ser.read(6)
        print(line)
        if line == bytes(self.device_name, 'ascii'):
            return True

        return False

    def read(self):
        line =  self.ser.read(1)
        if line:
            print(">>>" + str(line))
            self.conn.send({"channel": "action", "data": struct.unpack('B', line)})

    def run(self):
        self.connect_serial_device()
        
        while True:
            try:
                self.read()
            except:
                print(self.device_name + " disconnected")
                self.connect_serial_device()
            
            time.sleep(0.01)













                # for client in clients:
                #     # client.sendMessage((str)(line))
                #     server.send_message(client, (str)(line))
            # time.sleep(0.1)

# def new_client(client, server):
#     clients.append(client)
#     server.send_message_to_all("ctrl")
# class Client(WebSocket):
#     def handleMessage(self):
#         pass
#         # self.sendMessage(self.data + "XDD")

#     def handleConnected(self):
#         clients.append(self)
#         print(self.address, 'connected')
        
            
#     def handleClose(self):
#         clients.remove(self)
#         print(self.address, 'closed')


# clients = []
# sr = serialReader()
# sr.start()

# server = WebSocketServer('', 30101, Client)
# server.serveforever()

# server = WebsocketServer(host='127.0.0.1', port=30101)
# server.set_fn_new_client(new_client)
# server.run_forever()

# Create websocket server 
# clients = []
# class Client(WebSocket):
#     def handle(self):
#         # pass
#         print(self.address, "handle")

#     def on_message(self, ws, message):
#         print("[" + id + "] " + 'Client ' + (str)(self.address) + ': ' + (str)(message))

#     def connected(self):
#         print("[" + id + "] " + 'Client ' + (str)(self.address) + ' connected')
#         clients.append(self)

#     def handle_close(self):
#         clients.remove(self)
#         print("[" + id + "] " + 'Client ' + (str)(self.address) + ' disconnect')

# class FrameDispatcher(threading.Thread):
#     def __init__(self):
#         self.server = WebSocketServer("", 30001, Client)

    #     threading.Thread.__init__(self)

    # def run(self):
        
    #     while True:
    #         print("a")
    #         time.sleep(1)

# Connectiong to serial port
# ser = serial.Serial(port='/dev/ttyUSB0', baudrate=9600, parity=serial.PARITY_NONE, stopbits=serial.STOPBITS_ONE, bytesize=serial.EIGHTBITS, timeout=0)
# print("connected to: " + ser.portstr)

# fd = FrameDispatcher()
# fd.start()
# fd.server.serve_forever()

# server = WebSocketServer("localhost", 30091, Client)
# server.serve_forever()

# print("JAZZDAAA")
# while True:
#     for line in ser.read():
#         print("LINE: " + (str)(line))
#         for client in clients:
#             print("111LINE: " + (str)(line))
#             client.send_message((str)(line))
        # if line == 1:
        #     print("left")


# ser = serial.Serial(port='/dev/ttyUSB0', baudrate=9600, parity=serial.PARITY_NONE, stopbits=serial.STOPBITS_ONE, bytesize=serial.EIGHTBITS)
# ser.flushInput()

# while True:
#     try:
#         ser_bytes = ser.readline()
#         # decoded_bytes = float(ser_bytes[0:len(ser_bytes)-2].decode("utf-8"))
#         print(ser_bytes)
#     except:
#         print("Keyboard Interrupt")
#         break


# class Idrive(threading.Thread):
#     def __init__(self):
#         threading.Thread.__init__(self)