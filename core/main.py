from MierzejClient import MierzejClient
from EmuSeialClient import EmuSeialClient
from Connector import Connector
from websocket_server import WebsocketServer
from Idrive import Idrive
import time
from pprint import pprint
import sys

# def generate_fake_frame():
#     # pprint(data)
#     fields = ["RPM","MAP","TPS","IAT","Batt","IgnAngle","pulseWidth","scondarypulseWidth","Egt1","Egt2","knockLevel","dwellTime","wboAFR","gear","Baro","analogIn1","analogIn2","analogIn3","analogIn4","injDC","emuTemp","oilPressure","oilTemperature","fuelPressure","CLT","flexFuelEthanolContent","ffTemp","wboLambda","vssSpeed","deltaFPR","fuelLevel","tablesSet","lambdaTarget","afrTarget","cel"]
#     types = ["uint16_t","uint16_t","uint8_t","int8_t","float","float","float","float","uint16_t","uint16_t","float","float","float","int8_t","uint8_t","float","float","float","float","float","int8_t","float","uint8_t","float","int16_t","float","int8_t","float","float","uint16_t","uint8_t","uint8_t","float","float","uint16_t"]
    
#     sizes = {
#         "uint16_t": 2,
#         "int16_t": 2,
#         "uint8_t": 1,
#         "int8_t": 1,
#         "float": 4
#     }
#     dataObject = {}
#     i = 0
#     offset = 0
    
#     for field in fields:
#             # print(field)
#             # print(struct.unpack('f', data[offset+2:offset+2+sizes[types[i]]]))

#         dataObject[field] = 0

#         offset=offset+sizes[types[i]]
#         i=i+1

#     return dataObject


def main():
#    mierzej = MierzejClient()
#    mierzej.start()

    idrive_path = '/dev/ttyUSB0'
    if len(sys.argv) > 1:
        idrive_path = sys.argv[1]

    print('Idrive path: ' + idrive_path)

    conn = Connector()
    conn.start()

    try:
        idrive = Idrive(conn, idrive_path)
        idrive.start()
    except:
        print('Idrive not found')
    
    try:
        emu = EmuSeialClient()
        emu.start()
    except:
        print('Emu not found')

    while True:
        # print(mierzej.get_values())
        # conn.send({"channels": mierzej.get_values()})

        # frame = generate_fake_frame()
        # pprint(frame)
        conn.send({"channel": "dashframe", "data": emu.frame})
        time.sleep(0.1)

if __name__ == '__main__':
    main()
