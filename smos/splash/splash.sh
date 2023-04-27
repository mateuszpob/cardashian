#!/bin/bash

systemctl disable getty@tty1
apt-get install -y install fbi
cp splashscreen.service /etc/systemd/system/splashscreen.service
systemctl enable splashscreen
systemctl start splashscreen
