#!/bin/bash
#from dust i have come dust i will be

echo "enter a number: "
read var1

echo "enter another number: "
read var2

if [ $((var1%2)) -eq 0 ] && [ $((var2%2)) -eq 1 ]; then
    echo "yes"
elif [ $((var1%2)) -eq 1 ] && [ $((var2%2)) -eq 0 ]; then
    echo "yes"
else
    echo "no"
fi