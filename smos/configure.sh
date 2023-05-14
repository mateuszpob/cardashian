#!/bin/bash



echo -e '\e[32m[SMOS] - create user\e[0m'
userdel -r pi
useradd mp --home /home/mp
chown -R mp:mp /home/mp
chsh -s /bin/bash mp
usermod -a -G sudo mp
echo -e "123456\n123456" | passwd mp

# update & install
echo -e '\e[32m[SMOS] - update & install\e[0m'
apt -y update
apt -y install xorg xinit i3 i3status lightdm less vim gcc git nano build-essential chromium-browser udhcpc libqmi-utils lsof screen

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

mkdir /var/log/emu/
chown -R mp:mp /var/log/emu/
touch /var/log/emu/distance.txt
chmod 777 /var/log/emu/distance.txt

touch /var/log/maintenance.log
chmod 777 /var/log/maintenance.log

touch /usr/bin/cardashian_start.sh
touch /usr/bin/cardashian_stop.sh
touch /usr/bin/cardashian_run_emuserial.sh

chmod 777 /usr/bin/cardashian_*
chmod 777 /root/cardashian_check.sh


echo -e '\e[32m[SMOS] - Configure mp user i3\e[0m'
# i3 configuration for mp user
mkdir /home/mp/.config/
mkdir /home/mp/.config/i3/
cp /home/mp/i3_config /home/mp/.config/i3/
mv /home/mp/.config/i3/i3_config /home/mp/.config/i3/config
chmod 755 /home/mp/.config/i3/config
chown mp:mp -R /home/mp/.config/

touch /home/mp/configured
