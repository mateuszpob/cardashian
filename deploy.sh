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

# Copy Emuserial - will be build on the device
rm -r -f ./emuserialpc/build
cp -r ./emuserialpc ./build

# Build frontend app
cd ./lada_front
npm run build
cd ../
cp -r ./lada_front/dist ./build

# Build package 
cd ./build
tar -czvf ../cardashian.tar.gz *

# Send package to server
scp ../cardashian.tar.gz tlusty://home/cardashian
