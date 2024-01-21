#!/bin/bash

pkill -9 -f "emuserial"
pkill -9 -f "/home/mp/cardashian/core/main.py"
pkill -9 chromium
pkill -9 'python3 -m http.server'