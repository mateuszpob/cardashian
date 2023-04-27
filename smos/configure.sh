#!/bin/bash

# sudo systemctl enable splashscreen
# sudo systemctl start splashscreen

userdel -r pi
useradd mp --home /home/mp
chown -R mp:mp /home/mp
chsh -s /bin/bash mp
usermod -a -G sudoers mp

apt -y update
apt -y install xorg xinit i3 i3status lightdm less vim gcc git nano build-essential

# timedatectl set-timezone Europe/Warsaw

systemctl enable lightdm


# cardashian files
touch /var/log/emu/distance.txt
chmod 777 /var/log/emu/distance.txt

echo -e '\e[32m[SMOS] - Configure mp user i3\e[0m'
# i3 configuration for mp user
mkdir /home/mp/.config/
mkdir /home/mp/.config/i3/
cp /home/mp/i3_config /home/mp/.config/i3/
mv /home/mp/.config/i3/i3_config /home/mp/.config/i3/config
chmod 755 /home/mp/.config/i3/config
chown mp:mp -R /home/mp/.config/

touch /home/mp/configured
