#!/bin/bash

/usr/bin/cardashian_stop.sh

#EMULOG_FILENAME="/var/log/cardashian/emulog_"$(date +"%d-%m-%y_%H:%M:%S")
#/home/mp/cardashian/emuserialpc/emuserial -d /dev/emu -s $EMULOG_FILENAME > /home/mp/cardashian/emuserial.log 2>&1 &

python3 /home/mp/cardashian/core/main.py /dev/idrive > /var/log/cardashian/core.log 2>&1 &
 

cd /home/mp/cardashian/dist
python3 -m http.server > /var/log/cardashian/http.log 2>&1 &

# DISPLAY=:0 midori -e Fullscreen -a http://127.0.0.1:8000
# DISPLAY=:0 firefox -kiosk -private-window http://127.0.0.1:8000
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
        --aggressive-cache-discard \
	    --kiosk http://127.0.0.1:8000 > /dev/null 2>&1 &