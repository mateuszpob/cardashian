#!/bin/bash

sudo ip link set wlan0 down;
wpa_cli -i wlan0 reconfigure;
systemctl restart wpa_supplicant;

rfkill unblock all;
ifconfig wlan0 up;


# rsync -Pav -e "ssh -i /root/.ssh/id_rsa" start@boot.noatech.pl:/home/start/cold_start2.sh /root/
# sleep 20
# /root/cold_start2.sh