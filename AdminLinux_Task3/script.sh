#!/bin/bash

cd ~
if [ -f .bashrc ]; then 
echo ".bashrc is found " 
echo "export HELLO=$HOSTNAME">> .bashrc
echo "LOCAL=$(whoami)" >> .bashrc
gnome-terminal 
else 
echo ".bashrc not found "
fi

