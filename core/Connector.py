import threading
import time
from websocket_server import WebsocketServer
from pprint import pprint
import json

class Connector(threading.Thread):
    def __init__(self):
        self.clients = []
        self.server = WebsocketServer(host='127.0.0.1', port=30101)
        self.server.set_fn_new_client(self.new_client)
        threading.Thread.__init__(self)

    def new_client(self, client, server):
        print("New ws client")
        self.clients.append(client)

    def send(self, data):
        data = json.dumps(data)
        self.server.send_message_to_all(data)

    def run(self):
        self.server.run_forever()