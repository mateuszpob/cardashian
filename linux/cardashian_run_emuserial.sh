#!/bin/bash

EMULOG_FILENAME="/var/log/emu/emulog_"$(date +"%d-%m-%y_%H:%M:%S")
/home/mp/cardashian/emuserialpc/emuserial -d $1 -s $EMULOG_FILENAME > /var/log/cardashian/emuserial.log 2>&1 &