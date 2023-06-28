#!/bin/bash

echo $(date) >> /var/log/tmp.log;
sudo -u mp DISPLAY=:0 xset s noblank;
sudo -u mp DISPLAY=:0 xset -dpms;
sudo -u mp DISPLAY=:0 xset s off;
sudo -u mp DISPLAY=:0 xrandr --output HDMI-1 --rotate inverted;
