#!/bin/bash

# kill backend
./stop_cardashian.sh


 ./emuserialpc/emuserial -r ./emuserialpc/emulogs/emulog1 > ./logs/emuserial.log 2>&1 &
python3 ./core/main.py -m > ./logs/core.log 2>&1 &

cd ./lada_front
npm run serve