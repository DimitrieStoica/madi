#!/bin/bash

echo "Looking for available Wifi adapters"

#takes all the available WiFi adapters
searchWiFiAdapter=(`iw dev | grep "Interface" | awk '{print $2}'`)

#loops over all the WiFi adapters and finds if they are busy or not
#if the adapter is not busy it will start it

for element in "${searchWiFiAdapter[@]}"
do
  value=(`ip link show $element | grep DOWN`)
  if [ -n "$value" ]; then
    echo "$element not used"
    `sudo ip link set $element up`
    value=(`ip link show $element | grep UP`)
    if [ -n "$value" ]; then
      echo "$element successfully started"
      if [ "`iw $element link`" == "Not connected." ]; then
      echo "$element can connect now"
      fi
    else
      echo "$element error starting"
    fi
  else
    echo "$element used"
fi
done

