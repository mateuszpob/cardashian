#!/bin/bash

sleep 1;
ip link set wlan0 down;

sleep 1;
/usr/sbin/wpa_cli -i wlan0 reconfigure;

sleep 1;
systemctl restart wpa_supplicant;

sleep 1;
/usr/sbin/rfkill unblock all;

sleep 1;
/usr/sbin/ifconfig wlan0 up;

sleep 1;
systemctl enable cardashian.service
systemctl start cardashian.service