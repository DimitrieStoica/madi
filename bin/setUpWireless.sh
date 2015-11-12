listFileWiFi=listWiFiInterfaces
descriptionfile=myDescription
i=0;

while read line; do
  name="$line";
  i=i+1
done < $descriptionfile

OIFS=$IFS;
IFS=" ";

#take the lines in the respective file
while read line; do
  listWiFi=($line);
  echo "Taking random WiFi adapter available"
  #find the number of elements in the respetive line
  numberWiFiInterface=${#listWiFi[*]}
  WiFi=${listWiFi[$((RANDOM%numberWiFiInterface))]}
  echo "$WiFi will be used"
done < $listFileWiFi
IFS=$OIFS;

echo "[connection]
id=$name
uuid=`uuidgen`
type=802-11-wireless
autoconnect=false

[802-11-wireless]
ssid=$name
mode=ap
mac-address=`ifconfig $WiFi | awk '/HWaddr/ {print $5}'`

[ipv6]
method=auto

[ipv4]
method=shared" > $name
