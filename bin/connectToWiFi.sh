#!/bin/bash

echo "Looking for available Wifi adapters"

#command that prints all the available internet adapters and further information
searchWiFiAdapter=(`iw dev`)

#array that stores names of internet adapters
WiFiAdapters=()

value="Interface"
index=0

for i in ${searchWiFiAdapter[@]}
do
  if [ "$i" = "${value}" ] 
  then
    WiFiAdapters=( "${WiFiAdapters[@]}" "${searchWiFiAdapter[$[$index + 1]]}")
  fi 
  index="$[$index + 1]"
done

printf "${WiFiAdapters[@]}\n"

for i in ${WiFiAdapters[@]}
do
  echo `ip link show ${WiFiAdapters[$i]}`
done
