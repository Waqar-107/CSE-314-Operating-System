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
totalStudent=${#studentID[@]}
echo "total : $totalStudent"
#using the csv make the absent list. every submission has name at first, compare ignoring the cases


#make a new directory "output" and inside it another directory called "extra"
mkdir output
cd output
mkdir extra
cd ..

for file in $zips
do 
    #unzip in a temporary file in a new folder called temp
    unzip -d temp/ $file
    
    cd temp

    #check number of directories in temp
    #noOfDirectory=$(*/ | wc -w) not working
    #works fine when echo */ | wc -w
    noOfDirectory=0
    for file2 in $(ls)
    do
        if [ -d $file2 ]; then
            noOfDirectory=`expr $noOfDirectory + 1`
        fi
    done

    #---------------------------------------------------------------------
    if [ $noOfDirectory -eq 1 ]; then
        
        #--------------------------------------------------
        #get directory name
        for file2 in $(ls)
        do
            if [ -d $file2 ]; then
                dirName=$file2
            fi
        done
        #--------------------------------------------------

        #--------------------------------------------------
        #check if it is in the csv
        #first check if it is in format-> 1405001
        flag=0
        marks=0
        actual_id=0

        for roll in $studentID
        do
            if [ $roll == $dirName ]; then
                flag=1
                marks=10
                actual_id=$roll;
            fi
        done
        #--------------------------------------------------

        #--------------------------------------------------
        #check if it has studentID inside the string like-> 1405001_cse322
        if [ $flag == 0 ]; then
            for roll in $studentID
            do
                if [[ $dirName == *"$roll"* ]]; then
                    flag=1
                    marks=5
                    actual_id=roll
                fi
            done
        fi
        #--------------------------------------------------

    fi
    #---------------------------------------------------------------------
    
    #work done remove the temporary file
    rm temp

done
