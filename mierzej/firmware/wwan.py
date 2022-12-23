#!/usr/bin/python

import datetime
import subprocess
import sys
import time

class Wwan:
    def __init__(self):
        self.MCP23008_ADDRESS = '0x20'
        self.MCP23008_IODIR = '0x00'
        self.MCP23008_OLAT = '0x0A'
        self.I2C_BUS = '0'
        self.SIM_POWER = 0x80 
        self.state = 0
        self.reconnect = 0
        self.reconnect_max = 3
        self.log_path = "/var/log/wwan.log"
        self.current_state_file_path = '/tmp/wwan_state'

        self.log_file = open(self.log_path, "w") 
        self.log_file.write("")
        self.log_file.close()

    def display(self, string): 
        print(string)
        self.log_file = open(self.log_path, "a")
        self.log_file.write("[" + str(datetime.datetime.now()) + "] " + string + "\n")
        self.log_file.close()

    def writeCurrentState(self, state):
        self.log_file = open(self.current_state_file_path, "w")
        self.log_file.write(str(int(time.time())) + " " + str(state))
        self.log_file.close()

    def modemOn(self):
        self.display("Modem ON")
        subprocess.check_output('i2cset -y ' + self.I2C_BUS + ' ' + self.MCP23008_ADDRESS + ' ' + self.MCP23008_IODIR + ' 0x1F', shell=True, stderr=subprocess.STDOUT)
        r = subprocess.check_output('i2cget -y ' + self.I2C_BUS + ' ' + self.MCP23008_ADDRESS + ' ' + self.MCP23008_OLAT, shell=True, stderr=subprocess.STDOUT)
        r = int(r, 16)
        r = r | 0x20
        subprocess.check_output('i2cset -y ' + self.I2C_BUS + ' ' + self.MCP23008_ADDRESS + ' ' + self.MCP23008_OLAT + ' ' + hex(r), shell=True, stderr=subprocess.STDOUT)

    def modemOff(self):
        self.display("Modem OFF")
        subprocess.check_output('i2cset -y ' + self.I2C_BUS + ' ' + self.MCP23008_ADDRESS + ' ' + self.MCP23008_IODIR + ' 0x1F', shell=True, stderr=subprocess.STDOUT)
        r = subprocess.check_output('i2cget -y ' + self.I2C_BUS + ' ' + self.MCP23008_ADDRESS + ' ' + self.MCP23008_OLAT, shell=True, stderr=subprocess.STDOUT)
        r = int(r, 16)
        r = r & ~ 0x20
        # r = 0x00
        subprocess.check_output('i2cset -y ' + self.I2C_BUS + ' ' + self.MCP23008_ADDRESS + ' ' + self.MCP23008_OLAT + ' ' + hex(r), shell=True, stderr=subprocess.STDOUT)
        time.sleep(5)

    def checkModemExists(self):
        try:
            r = subprocess.check_output('ls /dev/cdc-wdm0', shell=True, stderr=subprocess.STDOUT)
            print(r)
            if len(r) > 0:
                self.display("Modem exists")
                return True
        except:
            pass
        return False
		
    def waitForModem(self):
        self.display("Wait for modem")
        timeout = 30000
        while self.checkModemExists() == False and timeout > 0:
            print('wait modem ....')
            time.sleep(.500)
            timeout = timeout - 500
        return self.checkModemExists()

    def selectSIM(self, number):
        self.display("Select SIM " + str(number))
        self.modemOff()

        r = subprocess.check_output('i2cget -y ' + self.I2C_BUS + ' ' + self.MCP23008_ADDRESS + ' ' + self.MCP23008_OLAT, shell=True, stderr=subprocess.STDOUT)
        r = int(r, 16)
        if number == 1:
            r = r & ~ self.SIM_POWER
        elif number == 2:
            r = r | self.SIM_POWER
        else:
            return
        subprocess.check_output('i2cset -y ' + self.I2C_BUS + ' ' + self.MCP23008_ADDRESS + ' ' + self.MCP23008_OLAT + ' ' + hex(r), shell=True, stderr=subprocess.STDOUT)

        self.modemOn()

    def checkConnection(self):
        try:
            subprocess.check_output('ping -c 1 -w 3 -I wwan0 8.8.8.8', shell=True, stderr=subprocess.STDOUT)
            subprocess.check_output('ping -c 1 -w 3 -I wwan0 8.8.8.8', shell=True, stderr=subprocess.STDOUT)
            return True
        except:
            pass
        self.display("Connection Failed")
        return False

    def waitForDisconnect(self):
        self.display("Wait for disconnect")
        while self.checkConnection():
            pass
        self.display("Disconected")

    def waitConnect(self, retries):
        self.display("Wait for connect")
        while self.checkConnection() == False and retries >= 0:
            retries -= 1
        c = self.checkConnection()
        self.display("Connection state: " + str(c))

    def checkSIMExists(self):
        try:
            r = subprocess.check_output("qmicli -d /dev/cdc-wdm0 --uim-get-card-status | awk '/Card\\ \\[0\\]/ {getline; print $3;}'", shell=True, stderr=subprocess.STDOUT)
            if r.strip() == "'present'":
                self.display("SIM Exists")
                return True
        except Exception as e:
            pass
        self.display("Sim not found")
        return False

    def connect(self):
        self.display("Connecting...")
        
        # for Siera Wireless DW5570
        try:
            subprocess.check_output('/usr/bin/qmicli -d /dev/cdc-wdm0 --dms-set-fcc-authentication', shell=True, stderr=subprocess.STDOUT)
        except Exception as e: print(e)
        # for Siera Wireless DW5570
        try:
            subprocess.check_output('/usr/bin/qmicli -d /dev/cdc-wdm0 --dms-set-operating-mode=online', shell=True, stderr=subprocess.STDOUT)
            time.sleep(3)
        except Exception as e: print(e)
        
        try:
            subprocess.check_output('/usr/bin/qmi-network /dev/cdc-wdm0 start', shell=True, stderr=subprocess.STDOUT)
            time.sleep(1)
        except Exception as e: print(e)
        try:
            subprocess.check_output('/sbin/ifconfig wwan0 up', shell=True, stderr=subprocess.STDOUT)
        except Exception as e: print(e)
        try:
            subprocess.check_output('/sbin/udhcpc -n -q -i wwan0', shell=True, stderr=subprocess.STDOUT)
        except Exception as e: print(e)

    def disconnect(self):
        self.display("Disconnecting...") 
        try:
            subprocess.check_output('/usr/bin/qmi-network /dev/cdc-wdm0 stop', shell=True, stderr=subprocess.STDOUT)
        except Exception as e: print(e)
        try:
            subprocess.check_output('/sbin/ifconfig wwan0 down', shell=True, stderr=subprocess.STDOUT)
        except Exception as e: print(e)



    def run(self, state):
        self.display(" ========> State: " + str(state))
        self.writeCurrentState(state)
        if state == 0:
            self.modemOff()
            self.run(1)
        elif state == 1:
            self.selectSIM(2)
            m = self.waitForModem()
            if m == False:
                self.run(0)
            s = self.checkSIMExists()
            if s:
                self.run(4)
            else:
                self.run(2)

        elif state == 2:
            self.selectSIM(1)
            m = self.waitForModem()
            if m == False:
                self.run(0)
            s = self.checkSIMExists()
            if s:
                self.run(3)
            else:
                self.run(0)
        elif state == 3:
            self.disconnect()
            self.connect()
            self.waitConnect(5)
            self.waitForDisconnect()
            self.reconnect = self.reconnect + 1
            if self.reconnect > self.reconnect_max:
                self.reconnect = 0
                self.run(2)
            else:
                self.run(3)

        elif state == 4:
            self.selectSIM(1)
            m = self.waitForModem()
            if m == False:
                self.run(0)
            s = self.checkSIMExists()
            if s:
                self.run(5)
            else:
                self.run(6)
        elif state == 5:
            self.disconnect()
            self.connect()
            self.waitConnect(3)
            self.waitForDisconnect()
            self.reconnect = self.reconnect + 1
            if self.reconnect > self.reconnect_max:
                self.reconnect = 0
                self.run(7)
            else:
                self.run(5)

        elif state == 6:
            self.selectSIM(2)
            m = self.waitForModem()
            if m == False:
                self.run(0)
            s = self.checkSIMExists()
            if s:
                self.run(9)
            else:
                self.run(0)


        elif state == 7:
            self.disconnect()
            self.selectSIM(2)
            m = self.waitForModem()
            if m == False:
                self.run(0)
            s = self.checkSIMExists()
            if s:
                self.run(8)
            else:
                self.run(4)


        elif state == 8:
            self.disconnect()
            self.connect()
            self.waitConnect(3)
            self.waitForDisconnect()
            self.reconnect = self.reconnect + 1
            if self.reconnect > self.reconnect_max:
                self.reconnect = 0
                self.run(4)
            else:
                self.run(7)

        elif state == 9:
            self.disconnect()
            self.connect()
            self.waitConnect(3)
            self.waitForDisconnect()
            self.reconnect = self.reconnect + 1
            if self.reconnect > self.reconnect_max:
                self.reconnect = 0
                self.run(9)
            else:
                self.run(6)



wwan = Wwan()


if len(sys.argv) < 2:
    print("Usage " + sys.argv[0] + " {run|connect|disconnect|modemon|modemoff}")
    exit(1)
elif sys.argv[1] == 'run':
    wwan.run(0)
elif sys.argv[1] == 'connect':
    wwan.connect()
elif sys.argv[1] == 'disconnect':
    wwan.disconnect()
elif sys.argv[1] == 'modemon':
    wwan.modemOn()
elif sys.argv[1] == 'modemoff':
    wwan.modemOff()
else:
    print("Usage " + sys.argv[0] + " {run|connect|disconnect|modemon|modemoff}")
    exit(1)


