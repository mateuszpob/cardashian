from http.server import SimpleHTTPRequestHandler, HTTPServer
import threading
import logging
import socket
import socketserver
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

    def openKeyboard(self):
        os.system("DISPLAY=:0 /usr/bin/onboard > /var/log/cardashian/maintenance.log 2>&1 &")

    def getInfo(self):
        return {"ip_address": self.get_ip_address() }
    
    def get_ip_address(self):
        # return '127.0.0.1'
        s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        s.connect(("8.8.8.8", 80))
        return s.getsockname()[0]

class HS(SimpleHTTPRequestHandler):
    # def __init__(self, request, client_address, server, tools, map_manager):
    #     self.tools = tools
    #     self.map_manager = map_manager
    #     super().__init__(request, client_address, server)

    def __init__(self, *args, tools, map_manager, **kwargs):
        self.tools = tools
        self.map_manager = map_manager
        super().__init__(*args, **kwargs)

    def do_GET(self):
        data = None
        parsed_path = urlparse(self.path)
        path_components = parsed_path.path.split('/')

        # miałem poprawić a zrobiłem jeszcze gorzej, ale jutro trzeba topić fure ;)
        okeje = [
            "/action/restart_app",
            "/action/update_app",
            "/action/open_keyboard",
            "/get/info",
            "/get/about",
            "/get/map"
        ]
        if self.path in okeje or "get/map" in self.path: 
            if self.path == "/action/restart_app":
                self.tools.restartApp()
            if self.path == "/action/update_app":
                self.tools.updateApp()
            if self.path == "/action/open_keyboard":
                self.tools.openKeyboard()
            if self.path == "/get/info":
                data = self.tools.getInfo()
            if self.path == "/get/about":
                data = 'Smolnia Motorsport 4x4'

            data = bytes(json.dumps(data), 'utf-8')
            
            if path_components[1] == "get" and path_components[2] == "map":
                zoom = int(path_components[3])
                column = int(path_components[4])
                row = int(path_components[5])
                # print("Zoom: " + zoom)
                # print("column: " + column)
                # print("row: " + row)
                with self.map_manager as manager:
                    data = manager.getTile(zoom, column, row)

                if data == None:
                    print('---------------------------------------> empty tile')
                    empty_tile = '/home/mp/maps/empty.png'
                    with open(empty_tile, 'rb') as file:
                        data = file.read()

            
            self._set_response()
            self.wfile.write(data)
        else:
            super().do_GET()

    def _set_response(self):
        self.send_response(200)
        self.send_header('Content-type', 'text/html')
        self.send_header('Access-Control-Allow-Origin', 'http://localhost:8080')
        self.end_headers()        

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
        PORT = 9001
        web_dir = os.path.join(os.path.dirname(__file__), '../../dist')
        os.chdir(web_dir)

        Handler = lambda *args, **kwargs: HS(*args, tools=self.tools, map_manager=self.map_manager, **kwargs)
        httpd = socketserver.TCPServer(("", PORT), Handler)

        print("serving at port", PORT)
        httpd.serve_forever()

        # print('kihj')
        # logging.basicConfig(level=logging.INFO)
        # server_address = ('', 9001)
        # httpd = HTTPServer(server_address, lambda *args, **kwargs: HS(*args, tools=self.tools, map_manager=self.map_manager, **kwargs))
        # logging.info('Starting httpd...\n')
        # try:
        #     httpd.serve_forever()
        # except KeyboardInterrupt:
        #     pass
        # httpd.server_close()
        # logging.info('Stopping httpd...\n')
