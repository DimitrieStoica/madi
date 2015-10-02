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
  if [ "$i" = "${value}" ]; then
    WiFiAdapters=( "${WiFiAdapters[@]}" "${searchWiFiAdapter[$[$index + 1]]}")
  fi 
  index="$[$index + 1]"
done

printf "${WiFiAdapters[@]}\n"

for i in ${WiFiAdapters[@]}
do
  value=(`ip link show ${WiFiAdapters[$i]} | grep DOWN`)
  if [ -n "$value" ]; then
    echo "${WiFiAdapters[$i]} not used"
    `sudo ip link set ${WiFiAdapters[$i]} up`
    value=(`ip link show ${WiFiAdapters[$i]} | grep UP`)
    if [ -n "$value" ]; then
      echo "${WiFiAdapters[$i]} successfully started"
    else
      echo "${WiFiAdapters[$i]} error starting"
    fi
  else
    echo "${WiFiAdapters[$i]} used"
fi
done
