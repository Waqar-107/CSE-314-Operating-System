#!/bin/bash

#Give the name of the .c file as an argument. This sh file will compile and run it

#gcc $1 -lpthread
#gcc -pthread $1
gcc $1
./a.out

