#!/bin/bash
#from dust i have come dust i will be

ls -l

#newline
echo 

for file in $*
do
    #check if the file is regular
    if [ -f file ]; then
        chmod a-x file
    fi
done

ls -l

