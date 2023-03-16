#!/bin/bash

#rsync -Pav -e "ssh -i /home/pi/.ssh/id_rsa" cardashian@188.68.231.142:/home/cardashian/synchronized/* /home/pi/cardashian/synchronized
#ssh -i /home/pi/.ssh/id_rsa cardashian@188.68.231.142 "md5sum /home/cardashian/cardashian.tar.gz"

cd /home/pi/

scp -i /home/pi/.ssh/id_rsa cardashian@188.68.231.142://home/cardashian/cardashian.tar.gz /home/pi

# ok?

rm -r -f ./cardashian/*
mv cardashian.tar.gz ./cardashian
cd ./cardashian
tar -xzvf cardashian.tar.gz 

chmod +x ./scripts/cardashian_install.sh
./scripts/cardashian_install.sh
