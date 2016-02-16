#!/bin/bash

FILE="availableNetworkNodes"

echo "Looking for all nodes in WAN"

if [ -f $FILE ];
then
  #it cleans old entries
  rm $FILE
  #it scans for available nodes in the network
  echo `sudo arp-scan --interface=eth0 --localnet | awk 'FNR > 2 {print $1 " " $2}' | head -n -3` >> availableNetworkNodes
else
  echo `sudo arp-scan --interface=eth0 --localnet | awk 'FNR > 2 {print $1 " " $2}' | head -n -3` >> availableNetworkNodes
fi
