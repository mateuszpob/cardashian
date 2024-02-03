from http.server import BaseHTTPRequestHandler, HTTPServer
import threading
import logging
import socket
import os
import json 
from pprint import pprint
from urllib.parse import urlparse, parse_qs

'''
TODO Tu trzeba refactor zrobić bo tu jest jakaś tragedia
'''
class Tools():
    def restartApp(self):
        os.system("/usr/bin/cardashian_start.sh")
    
    def updateApp(self):
        os.system("/usr/bin/cardashian_update.sh; /usr/bin/cardashian_start.sh")

    def getInfo(self):
        return {"ip_address": self.get_ip_address() }
    
    def get_ip_address(self):
        # return '127.0.0.1'
        s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        s.connect(("8.8.8.8", 80))
        return s.getsockname()[0]

class HS(BaseHTTPRequestHandler):
    def __init__(self, request, client_address, server, tools, map_manager):
        self.tools = tools
        self.map_manager = map_manager
        super().__init__(request, client_address, server)

    def _set_response(self):
        self.send_response(200)
        self.send_header('Content-type', 'text/html')
        self.send_header('Access-Control-Allow-Origin', 'http://localhost:8080')
        self.end_headers()

    def do_GET(self):
        # tools = Tools()
        data = None
        parsed_path = urlparse(self.path)
        path_components = parsed_path.path.split('/')

        if self.path == "/action/restart_app":
            self.tools.restartApp()
        if self.path == "/action/update_app":
            self.tools.updateApp()
        if self.path == "/get/info":
            data = self.tools.getInfo()
        if self.path == "/get/about":
            data = 'Smolnia Motorsport 4x4'

        data = bytes(json.dumps(data), 'utf-8')

        if path_components[1] == "get-map":
            zoom = int(path_components[2])
            column = int(path_components[3])
            row = int(path_components[4])
            with self.map_manager as manager:
                data = manager.getTile(zoom, column, row)

            if data == None:
                print('---------------------------------------> empty tile')
                empty_tile = '/home/mp/workspace/home/navi/nocny/mapserver/empty.png'
                with open(empty_tile, 'rb') as file:
                    data = file.read()
        
        self._set_response()
        self.wfile.write(data)

    def do_POST(self):
        response_data = None

        content_length = int(self.headers['Content-Length']) # <--- Gets the size of data
        post_data = self.rfile.read(content_length)

        pprint(post_data)

        if self.path == '/action/set_wifi':
            self.tools.setWifi()

        response_data = bytes(json.dumps(response_data), 'utf-8')
        self._set_response()
        self.wfile.write(response_data)


class Httpowy(threading.Thread):
    def __init__(self, map_manager):
        threading.Thread.__init__(self)
        self.db_lock = threading.Lock()
        self.map_manager = map_manager
        self.tools = Tools()

    def run(self):
        print('kihj')
        logging.basicConfig(level=logging.INFO)
        server_address = ('', 9001)
        httpd = HTTPServer(server_address, lambda *args, **kwargs: HS(*args, tools=self.tools, map_manager=self.map_manager, **kwargs))
        logging.info('Starting httpd...\n')
        try:
            httpd.serve_forever()
        except KeyboardInterrupt:
            pass
        # httpd.server_close()
        # logging.info('Stopping httpd...\n')
