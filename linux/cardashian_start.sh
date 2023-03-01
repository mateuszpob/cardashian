#!/bin/bash

/usr/bin/cardashian_stop.sh

EMULOG_FILENAME="/home/pi/emulog_"$(date +"%d-%m-%y_%H:%M:%S")
/home/pi/cardashian/emuserialpc/emuserial -d /dev/emu -s $EMULOG_FILENAME > /home/pi/cardashian/logs/emuserial.log 2>&1 &

python3 /home/pi/cardashian/core/main.py /dev/idrive > /home/pi/cardashian/logs/core.log 2>&1 &
 

cd /home/pi/cardashian/dist
python3 -m http.server > /home/pi/cardashian/logs/http.log 2>&1 &


DISPLAY=:0 chromium-browser \
        --disable-session-crashed-bubble \
        --disable-notifications \
        --disable-translate \
        --disable-infobars \
        --disable-suggestions-service \
        --disable-touch-drag-drop \
        --disable-save-password-bubble \
        --disable-component-update \
        --overscroll-history-navigation=0 \
	    --check-for-update-interval=2147483647 \
	--kiosk http://127.0.0.1:8000 > /dev/null 2>&1 &