#!/bin/bash

# Send start tasks to server
scp ./linux/tasks.sh smolnia:/home/ubuntu
ssh smolnia sudo mv /home/ubuntu/tasks.sh /home/cardashian
