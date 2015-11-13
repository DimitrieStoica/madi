#!/bin/bash

echo "Searching for available WiFi networks"

#search for all available WiFi networks

WiFiAvailableNetworks=(`sudo iw wlan1 scan | grep SSID | awk {'print $2'}`)

descriptionfile=myDescription
i=0;

while read line; do
  name="$line";
  i=i+1
done < $descriptionfile

until `nmcli d wifi connect $name`; do
  echo "Connecting to $name"
  echo -ne '#####                     (20%)\r'
  sleep 2
  echo -ne '##########                (40%)\r'
  sleep 2
  echo -ne '###############           (60%)\r'
  sleep 2
  echo -ne '####################      (80%)\r'
  sleep 2
  echo -ne '######################### (100%)\r'
  echo -ne '\n'
  echo "Connection was established"
  sleep 20
done
