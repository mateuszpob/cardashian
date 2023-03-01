#!/bin/bash

# kill backend
pkill -9 -f "emuserial"
pkill -9 -f "python3 ./core/main.py"
