FILE=myDescription
i=0;

cat $FILE | while read line; do
  echo "$line"
  i=i+1
done
