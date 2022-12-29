#!/bin/bash

./emuserial > ./logs/emuserial.log 2>&1 &
python3 ./core/main.py > ./logs/core.log 2>&1 &

cd ./lada_front
npm run serve