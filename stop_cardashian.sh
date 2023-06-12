#!/bin/bash

# kill backend
pkill -9 -f "emuserial_x86"
pkill -9 -f "core/main.py"
