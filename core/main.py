from MierzejClient import MierzejClient
from EmuSeialClient import EmuSeialClient
from Connector import Connector
from DeviceManager import DeviceManager
from websocket_server import WebsocketServer
from Idrive import Idrive
import time
from pprint import pprint
import sys
import os


def main():
    mock = False
#    mierzej = MierzejClient()
#    mierzej.start()

    # check caommand line parameters
    if len(sys.argv) > 1:
        if sys.argv[1] == '-h':
            print(sys.argv[0] + ' -m    # run emuserial mock')
            exit(0)
        if sys.argv[1] == '-m':
            mock = True

    dm = DeviceManager()

    idrive_path = dm.find('idrive')
    emu_path = dm.find('emu')

    conn = Connector()
    conn.start()

    idrive = Idrive(conn, idrive_path)
    idrive.start()

    os.system("/usr/bin/run_emuserial.sh " + emu_path)
    time.sleep(3)
    emu = None
    
    try:
        emu = EmuSeialClient()
        emu.start()
    except:
        print('Emu not found')

    while True:
        # print(mierzej.get_values())
        # conn.send({"channels": mierzej.get_values()})

        if emu is not None:
            conn.send({"channel": "dashframe", "data": emu.frame})
        time.sleep(0.1)

if __name__ == '__main__':
    main()
