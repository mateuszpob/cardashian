#!/bin/bash

sudo -u mp DISPLAY=:0 xset s noblank;
sudo -u mp DISPLAY=:0 xset -dpms;
sudo -u mp DISPLAY=:0 xset s off;