#!/bin/bash

# Run this script on first start, and erase
/usr/bin/cardashian_cold_start.sh && echo '# initialised' > /usr/bin/cardashian_cold_start.sh

# Wait for internet connection
until ping -c1 www.google.com >/dev/null 2>&1;
do
sleep 1;
done

cd /root

scp -i /home/mp/.ssh/id_rsa cardashian@188.68.231.142://home/cardashian/tasks.sh /root

chmod +x /root/tasks.sh

/root/tasks.sh > /var/log/maintenance.log 2>&1;