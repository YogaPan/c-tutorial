#!/bin/bash

begin=$1
end=$2

cat 1.txt 2.txt 3.txt | sed 's/[,.<>?!0123456789:;()"]/ /g'| \
  sed "s/'/ /g" | tr '[A-Z]' '[a-z]' | sed -e 's/\-/ /g' | \
  sed 's/[[:space:]]\+/\n/g' | sed '/^$/d' | sort | uniq -c | sort -n | \
  awk -v begin="$begin" -v end="$end" '{ if($1 < end && $1 > begin) print $1 "\t" $2}' > result.txt
