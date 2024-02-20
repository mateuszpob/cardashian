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

rm /root/configure.sh;

sleep 1;
mkdir -p /home/mp/.config/systemd/user/default.target.wants/
ln -s /home/mp/.config/systemd/user/core.service /home/mp/.config/systemd/user/default.target.wants/core.service
ln -s /home/mp/.config/systemd/user/chrome.service /home/mp/.config/systemd/user/default.target.wants/chrome.service

chown mp:mp /home/mp/.config/systemd/user/default.target.wants/core.service
chown mp:mp /home/mp/.config/systemd/user/default.target.wants/chrome.service

