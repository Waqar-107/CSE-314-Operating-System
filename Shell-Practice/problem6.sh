#!/bin/bash
#from dust i have come, dust i will be

list=$(ls)

for x in $list
do
    # *[0-9]* is a regex
    if [[ $x == *[0-9]* ]]; then
    echo "deleting $x"
    rm -r $x
    fi
done