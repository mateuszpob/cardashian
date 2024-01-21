#!/bin/bash



echo -e '\e[32m[SMOS] - create user\e[0m'
userdel -r pi;
useradd mp --home /home/mp;
chown -R mp:mp /home/mp;
chsh -s /bin/bash mp;
usermod -a -G sudo mp;
usermod -a -G dialout mp;
echo -e "123456\n123456" | passwd mp;

# update & install
echo -e '\e[32m[SMOS] - update & install\e[0m'
apt -y update
apt -y install xorg xinit fluxbox lightdm less vim gcc git nano build-essential chromium-browser udhcpc libqmi-utils lsof screen python3-pip onboard

# install python packages
sudo -u mp pip3 install pyserial
sudo -u mp pip3 install websocket_server
# timedatectl set-timezone Europe/Warsaw

# start / stop services
echo -e '\e[32m[SMOS] - start / stop services\e[0m'
systemctl disable userconfig
systemctl mask userconfig
systemctl enable lightdm
systemctl enable wpa_supplicant
# systemctl disable raspi-config.service
# systemctl disable splashscreen
# systemctl start splashscreen

crontab /root/rootcrontab

echo -e '\e[32m[SMOS] - cardashian files\e[0m'
# cardashian files
touch /boot/ssh

# chromium-browser --load-extension

mkdir /var/log/cardashian;
touch /var/log/cardashian/distance.txt;
touch /var/log/cardashian/core.log;
touch /var/log/cardashian/http.log;
touch /var/log/cardashian/emuserial.log;
touch /var/log/cardashian/maintenance.log
chown mp:mp -R /var/log/cardashian;


touch /usr/bin/cardashian_start.sh
touch /usr/bin/cardashian_stop.sh
touch /usr/bin/cardashian_run_emuserial.sh

chown -R mp:mp /usr/bin/cardashian_*
chmod 775 /usr/bin/cardashian_*
chmod 775 /root/cardashian_check.sh


# echo -e '\e[32m[SMOS] - Configure mp user i3\e[0m'
# i3 configuration for mp user
mkdir /home/mp/.config/
# mkdir /home/mp/.config/i3/
# cp /home/mp/i3_config /home/mp/.config/i3/
# mv /home/mp/.config/i3/i3_config /home/mp/.config/i3/config
# chmod 755 /home/mp/.config/i3/config
chown mp:mp -R /home/mp/.config/


chmod +x /usr/bin/configure_display.sh
chmod +x /usr/bin/screen_rotate_*
chmod +x /usr/bin/set_screen_*

# Add to the script the possibility to be executed by standard user with root privileges 
chmod 440 /etc/sudoers.d/010_mp-rotate

touch /home/mp/configured
