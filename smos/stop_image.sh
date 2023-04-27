#!/bin/bash


umount /mnt/{dev/pts,dev,sys,proc,boot,}
losetup -d /dev/loop0;

echo -e '\e[32m[SMOS] - Finish creating the os image at: '; date; echo -e '\e[0m';














