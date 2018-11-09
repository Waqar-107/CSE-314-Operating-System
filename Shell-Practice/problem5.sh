#!/bin/bash
#from dust i have come dust i will be

#first arg is the line number
n=$1

#second arg is the pattern
pattern=$2

#get txt files
list=$(find . -name "*.txt" -type f)

for x in $list
do
    if [ -f $x ]; then
    temp=$(head -$n $x|tail -1)
    echo "temp: $temp"
        # *"$pattern"* is a regex
        if [[ $temp == *"$pattern"* ]]; then
            rm $x
        fi
    fi
done