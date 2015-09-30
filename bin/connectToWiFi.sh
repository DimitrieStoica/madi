#!/bin/bash

echo "Looking for available Wifi adapters"
searchWiFiAdapter=(`iw dev`)
for i in ${searchWiFiAdapter[@]}
do
  echo $i
done
