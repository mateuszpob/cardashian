#!/bin/bash

# kill backend
pkill -9 -f "emuserial"
pkill -9 -f "python3 ./core/main.py"


./emuserialpc/emuserial > ./logs/emuserial.log 2>&1 &
python3 ./core/main.py > ./logs/core.log 2>&1 &

cd ./lada_front
npm run serve