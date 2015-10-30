#!/bin/bash

echo "Searching for available WiFi networks"

#search for all available WiFi networks

WiFiAvailableNetworks=(`sudo iw wlan1 scan | grep SSID | awk {'print $2'}`)
value="QandA"

for element in "${WiFiAvailableNetworks[@]}"
do
  if [ "$element" = "$value" ]; then
    echo "Connecting shortly to $value" 
  else
    echo "I was not able to find WiFi pair"
  fi
done
