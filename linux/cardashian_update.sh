#!/bin/bash

#rsync -Pav -e "ssh -i /home/mp/.ssh/id_rsa" cardashian@188.68.231.142:/home/cardashian/synchronized/* /home/mp/cardashian/synchronized
#ssh -i /home/mp/.ssh/id_rsa cardashian@188.68.231.142 "md5sum /home/cardashian/cardashian.tar.gz"

# Wait for internet connection
until ping -c1 www.google.com >/dev/null 2>&1;
do
sleep 1;
done


cd /home/mp/

rm -r -f ./cardashian
mkdir ./cardashian
cd ./cardashian

scp -i /home/mp/.ssh/id_rsa -o StrictHostKeyChecking=no cardashian@188.68.231.142://home/cardashian/cardashian.tar.gz .
tar -xzvf cardashian.tar.gz



chmod +x ./scripts/cardashian_install.sh
./scripts/cardashian_install.sh
