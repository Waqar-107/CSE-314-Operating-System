#!/bin/bash

IFS=$'\n'

#directories are considerd as internal nodes, other files as leaf
dfs(){
    for file in $(ls)
    do
        #move to that directory recursively
        if [ -d $file ]; then

            echo "moving to $file"
            cd $file
            dfs
            cd ..
        elif [[ $file == *".cpp" ]]; then

            target=$(echo $file|sed 's/cpp/exe/g')

            #execute the cpp file from test.cpp to test.exe
            
            g++ $file -o $target 
        fi
    done
}

dfs