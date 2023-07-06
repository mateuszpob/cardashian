from http.server import BaseHTTPRequestHandler, HTTPServer
import threading
import logging
import socket
import os
import json 
from pprint import pprint

class Tools():
    def restartApp(self):
        os.system("/usr/bin/cardashian_start.sh")
    
    def updateApp(self):
        os.system("/usr/bin/cardashian_update.sh; /usr/bin/cardashian_start.sh")

    def openKeyboard(self):
        os.system("DISPLAY=:0 /usr/bin/onboard > /dev/null 2>&1 &")

    def getInfo(self):
        return {"ip_address": self.get_ip_address() }
    
    def get_ip_address(self):
        # return '127.0.0.1'
        s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        s.connect(("8.8.8.8", 80))
        return s.getsockname()[0]

class HS(BaseHTTPRequestHandler):
    def _set_response(self):
        self.send_response(200)
        self.send_header('Content-type', 'text/html')
        self.send_header('Access-Control-Allow-Origin', 'http://localhost:8080')
        self.end_headers()

    def do_GET(self):
        tools = Tools()
        data = None
        if self.path == "/action/restart_app":
            tools.restartApp()
        if self.path == "/action/update_app":
            tools.updateApp()
        if self.path == "/action/open_keyboard":
            tools.openKeyboard()
        if self.path == "/get/info":
            data = tools.getInfo()
        if self.path == "/get/about":
            data = 'Smolnia Motorsport 4x4'

        data = bytes(json.dumps(data), 'utf-8')
        self._set_response()
        self.wfile.write(data)
        # self.wfile.write(data.format(self.path).encode('utf-8'))

        # logging.info("GET request,\nPath: %s\nHeaders:\n%s\n", str(self.path), str(self.headers))
        # self._set_response()
        # self.wfile.write("GET request for {}".format(self.path).encode('utf-8'))

    def do_POST(self):
        tools = Tools()
        response_data = None

        content_length = int(self.headers['Content-Length']) # <--- Gets the size of data
        post_data = self.rfile.read(content_length)

        pprint(post_data)

        if self.path == '/action/set_wifi':
            tools.setWifi()

        response_data = bytes(json.dumps(response_data), 'utf-8')
        self._set_response()
        self.wfile.write(response_data)
        # content_length = int(self.headers['Content-Length']) # <--- Gets the size of data
        # post_data = self.rfile.read(content_length) # <--- Gets the data itself
        # logging.info("POST request,\nPath: %s\nHeaders:\n%s\n\nBody:\n%s\n",
        #         str(self.path), str(self.headers), post_data.decode('utf-8'))

        # self._set_response()
        # self.wfile.write("POST request for {}".format(self.path).encode('utf-8'))


class Httpowy(threading.Thread):
    def __init__(self):
        threading.Thread.__init__(self)

    def run(self):
        print('kihj')
        logging.basicConfig(level=logging.INFO)
        server_address = ('', 9001)
        httpd = HTTPServer(server_address, HS)
        logging.info('Starting httpd...\n')
        try:
            httpd.serve_forever()
        except KeyboardInterrupt:
            pass
        # httpd.server_close()
        # logging.info('Stopping httpd...\n')
