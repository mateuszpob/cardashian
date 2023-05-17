Core:
    - main
    - Connector - server WebSocket wysyłający do lada_front dane zebrane z podsystemów takich jak Mierzej, Emuserialpc
    - MierzejClient - client urządzenia Mierzej (do odczytu dodatkowych czujników analogowych)

Emuserialpc: pobiera dane ze sterownika silnika poprzez port szeregowy


emuserial {/emu/device/path}












#!/bin/bash

pkill -9 -f "emuserial"
pkill -9 -f "python3 ./core/main.py"
pkill -9 chromium
pkill -9 'python3 -m http.server'

cd /home/pi/cardashian/synchronized/cardashian
./emuserialpc/emuserial > /var/log/cardashian/emuserial.log 2>&1 &
python3 ./core/main.py > /var/log/cardashian/core.log 2>&1 &
 
cd /home/pi/cardashian/synchronized/cardashian/dist
python3 -m http.server > /var/log/cardashian/http.log 2>&1 &

sudo -u pi DISPLAY=:0 chromium-browser \
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
        --kiosk \
        --incognito http://127.0.0.1:8000 > /dev/null 2>&1 &
