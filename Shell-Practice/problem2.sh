#!/bin/bash
#from dust i have come dust i will be

read var

if [ $var -gt 0 ]; then
    sum=$var
fi


while [ $var -ne 0 ]
do
    read var
    if [ $var -gt 0 ]; then
        sum=`expr $sum + $var`
    fi
done

echo $sum