#!/bin/bash

sudo adduser mohamed_fouad
sudo groupadd Youssef
sudo usermod -aG Youssef mohamed_fouad 

cat /etc/passwd | grep  "mohamed_fouad" 
cat /etc/group  | grep  "Youssef"




