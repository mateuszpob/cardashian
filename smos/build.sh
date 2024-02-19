#!/bin/bash

echo -e '\e[12m[SMOS] - Start creating the os image at: '; date; echo -e '\e[0m';




echo -e '\e[12m[SMOS] - Extract, resize partition and mount image\e[0m'
#IMAGE_NAME=$(unzip -Z1 raspbian_lite_latest)

# ================================ RESIZE FS ========================================================
IMAGE_NAME=$1
echo 'Process image: '$IMAGE_NAME
#unzip -o -q raspbian_lite_latest
SIZE_PRE=$(ls -l $IMAGE_NAME  | cut -d " " -f5)
# total = 3909091328; total - 8 = 3900702720
TOTAL_FLASH_SIZE=3900702720
TO_ADD=$(($TOTAL_FLASH_SIZE-$SIZE_PRE))

dd if=/dev/zero count=$(($TO_ADD / 512)) >> $IMAGE_NAME

losetup -f -P $IMAGE_NAME
parted /dev/loop0 resizepart 2 99%
e2fsck -f /dev/loop0p2
resize2fs /dev/loop0p2
PARTUUID=$(blkid -o export /dev/loop0p2 | grep PARTUUID | cut -c 10-100 | rev | cut -c 4- | rev)

echo 'PARTUUID after part '$PARTUUID'\e[0m'

mount -o rw /dev/loop0p2 /mnt
mount -o rw /dev/loop0p1 /mnt/boot
echo 'dwc_otg.lpm_enable=0 console=serial0,115200 console=tty1 root=PARTUUID='$PARTUUID'-02 rootfstype=ext4 elevator=deadline fsck.repair=yes rootwait quiet plymouth.ignore-serial-consoles' > /mnt/boot/cmdline.txt

cp /mnt/etc/fstab fstab_tmp
sed 's/PARTUUID=[0-9a-fA-F]*/PARTUUID='$PARTUUID'/g' fstab_tmp > /mnt/etc/fstab
rm fstab_tmp
cat /mnt/etc/fstab




echo -e '\e[32m[SMOS] - Copy install script\e[0m'
cp ./configure.sh /mnt/root/;

# # Splash screen
# cp ./splash/splashscreen.service /mnt/etc/systemd/system/splashscreen.service
# cp ./splash/cmdline.txt /mnt/boot/cmdline.txt
# cp ./splash/splash.png /mnt/opt/splash.png


mount -o bind /dev /mnt/dev/;
mount -o bind /proc /mnt/proc/;
mount -o bind /sys /mnt/sys/;
mount -o bind /dev/pts /mnt/dev/pts/;

chmod 777 /mnt/tmp;
cp /etc/resolv.conf /mnt/etc/;

# Create home directory
mkdir /mnt/home/mp/

# Lightdm configuration
mkdir /mnt/etc/lightdm
mkdir /mnt/etc/lightdm/lightdm.conf.d/
cp ./configs/lightdm/50-mp.conf /mnt/etc/lightdm/lightdm.conf.d/

# i3 config
# cp ./configs/i3_config /mnt/home/mp/

# other configs
cp ./configs/config.txt /mnt/boot     
cp ./configs/wpa_supplicant.conf /mnt/etc/wpa_supplicant/
mkdir /mnt/home/mp/.ssh/
cp ./configs/ssh/* /mnt/home/mp/.ssh/
cp ./configs/rootcrontab /mnt/root
cp ./configs/fluxbox/startup /mnt/home/mp/.fluxbox/

# script with the root privileges for standard user
cp ./configs/010_mp-rotate /mnt/etc/sudoers.d/010_mp-rotate

# scripts
cp ../linux/screen_rotate_180.sh /mnt/usr/bin
cp ../linux/screen_rotate_360.sh /mnt/usr/bin
cp ../linux/set_screen_180.sh /mnt/usr/bin
cp ../linux/set_screen_360.sh /mnt/usr/bin


# maintenance scripts
cp ../linux/cardashian_update.sh /mnt/usr/bin
cp ../linux/cardashian_cold_start.sh /mnt/usr/bin
cp ../linux/cardashian_check.sh /mnt/root
cp ../linux/cardashian_start.sh
cp ../linux/cardashian_stop.sh
cp ../linux/cardashian_run_emuserial.sh

# application services
mkdir -p /mnt/home/mp/.config/systemd/user
cp ../linux/core.service /mnt/home/mp/.config/systemd/user
cp ../linux/chrome.service /mnt/home/mp/.config/systemd/user

sed -i 's/^/#/g' /mnt/etc/ld.so.preload
cp /usr/bin/qemu-arm-static /mnt/usr/bin/

echo -e '\e[32m[SMOS] - Chroot rootfs\e[0m'
chroot /mnt /root/configure.sh


sed -i 's/^#//g' /mnt/etc/ld.so.preload
umount /mnt/{dev/pts,dev,sys,proc,boot,}
losetup -d /dev/loop0;

echo -e "\e[32m[SMOS] - Finish creating the os image at: $(date)\e[0m";














