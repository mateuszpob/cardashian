from MierzejClient import MierzejClient
from EmuSeialClient import EmuSeialClient
from Connector import Connector
from websocket_server import WebsocketServer
import time


def main():
#    mierzej = MierzejClient()
#    mierzej.start()

    emu = EmuSeialClient()
    emu.start()

    conn = Connector()
    conn.start()

    while True:
        # print(mierzej.get_values())
        # conn.send({"channels": mierzej.get_values()})
        time.sleep(1)

if __name__ == '__main__':
    main()
