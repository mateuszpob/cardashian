#!/bin/bash

cd /usr/share/X11/xorg.conf.d
sudo rm 40-libinput.conf
sudo ln -s __180__40-libinput.conf 40-libinput.conf

rm /usr/bin/screen_configure.sh
sudo ln -s /usr/bin/screen_rotate_180.sh /usr/bin/screen_configure.sh

sudo systemctl restart lightdm