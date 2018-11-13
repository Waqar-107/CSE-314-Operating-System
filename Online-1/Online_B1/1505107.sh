#!/bin/bash

IFS=$'\n'

solve(){
    
    #the targeted directory e.g- austrlia, bangladesh etc.
    target=$1
    cd $target

    touch temp.txt
   
    #move the temp file in each folder and concatenate others with it
    for folder in $(ls)
    do
        #move to directories e.g- bowler, all-rounder etc.
        if [ -d $folder ]; then
            cd $folder
            cat *.txt >> ../temp.txt 
            cd ..
        fi
    done

    #move the temporary file to the working directory and rename it
    mv temp.txt ../
    cd ..
    mv temp.txt "$target.txt"
}

solve "Australia"
solve "Bangladesh"
solve "South Africa"

