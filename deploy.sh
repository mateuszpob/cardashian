#!/bin/bash

# Local machine ci/cd script

# Remove old build
rm -r -f ./build

mkdir ./build
mkdir ./build/scripts

# Copy installation scripts
cp ./linux/* ./build/scripts

# Copy Core
cp -r ./core ./build

# Copy Emuserial
cd ./emuserialpc
rm -r -f ./build
make
cd ..
cp ./emuserialpc/emuserial ./build

# Build frontend app
cd ./displayapp
rm -r dist
npm run build
cd ../
cp -r ./displayapp/dist ./build

# Build package 
cd ./build
tar -czvf ../cardashian.tar.gz *

# Send package to server
scp ../cardashian.tar.gz smolnia:/home/ubuntu
ssh smolnia sudo mv /home/ubuntu/cardashian.tar.gz /home/cardashian

cd ../

# Send start tasks to server
./deploy_tasks.sh