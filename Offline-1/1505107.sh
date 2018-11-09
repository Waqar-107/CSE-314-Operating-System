#!/bin/bash

#shell splits on <space><tab><newline> so we change IFS
#https://unix.stackexchange.com/questions/9496/looping-through-files-with-spaces-in-the-names
IFS=$'\n'

echo -n "started executing the script"

#unzip the file where all the submission are
unzip "submissionsAll.zip"

#delete the zip
rm -r submissionsAll.zip

#get all the zips
zips=$(find . -name \*\.zip -type f)

#read the csv
#sed 's/whom you want to replace/substitute/g'
studentID=$(cut CSE_322.csv -d ',' -f1|sed 's/"//g'|sed 's/	//g')
studentName=$(cut CSE_322.csv -d ',' -f2)

#make a new directory "output" and inside it another directory called "extra"
mkdir output
cd output
mkdir extra
cd ..

for file in $zips
do 
    #unzip in a temporary file
    unzip -d temp/ $file
    
    cd temp
    for name in $(ls)
    do
        if [ -d $name ]; then
            
        fi
    done
    
    #work done remove the temporary file
    rm temp

done
