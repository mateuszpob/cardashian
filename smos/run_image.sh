#!/bin/bash

./stop_image.sh

IMAGE_NAME=$1
echo 'Process image: '$IMAGE_NAME

losetup -f -P $IMAGE_NAME

mount -o rw /dev/loop0p2 /mnt;
mount -o rw /dev/loop0p1 /mnt/boot;

mount -o bind /dev /mnt/dev/;
mount -o bind /proc /mnt/proc/;
mount -o bind /sys /mnt/sys/;
mount -o bind /dev/pts /mnt/dev/pts/;

chmod 777 /mnt/tmp;
cp /etc/resolv.conf /mnt/etc/;

sed -i 's/^/#/g' /mnt/etc/ld.so.preload
cp /usr/bin/qemu-arm-static /mnt/usr/bin/

echo -e '\e[32m[SMOS] - Chroot rootfs\e[0m'

chroot /mnt /usr/bin/bash











