#!/bin/bash

#shell splits on <space><tab><newline> so we change IFS
#https://unix.stackexchange.com/questions/9496/looping-through-files-with-spaces-in-the-names
IFS=$'\n'

echo -n "started executing the script"

#open absent list and marks file
touch absent.txt
touch marks.txt

#unzip the file where all the submission are
unzip "submissionsAll.zip"

#delete the zip
rm -r submissionsAll.zip

#get all the zips
temp=$(find . -name \*\.zip -type f)
idx=0
for i in $temp
do
    zips[idx]=$i
    idx=`expr $idx + 1`
done

#read the csv
#sed 's/whom you want to replace/substitute/g'
temp=$(cut CSE_322.csv -d ',' -f1|sed 's/"//g'|sed 's/	//g')
idx=0
for i in $temp
do
    studentID[idx]=$i
    idx=`expr $idx + 1`
done

temp=$(cut CSE_322.csv -d ',' -f2)
idx=0
for i in $temp
do
    studentName[idx]=$i
    idx=`expr $idx + 1`
done

totalStudent=${#studentID[@]}

#--------------------------------------------------------------------------------------------------
#using the csv make the absent list.
for((i=0;i<145;i++))
do
    tempList[i]=-1
done

for roll in $studentID
do
    for file in $(ls)
    do

    done
done

#--------------------------------------------------------------------------------------------------

#--------------------------------------------------------------------------------------------------
#make a new directory "output" and inside it another directory called "extra"
mkdir output
cd output
mkdir extra
cd ..
#--------------------------------------------------------------------------------------------------

#--------------------------------------------------------------------------------------------------
for file in ${zips[@]}
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
        extra=0

        for roll in ${studentID[@]}
        do
            if [ $roll == $dirName ]; then
                flag=1
                marks=10
                actual_id=$roll
                break
            fi
        done
        #--------------------------------------------------

        #--------------------------------------------------
        #check if it has studentID inside the string like-> 1405001_cse322
        if [ $flag == 0 ]; then
            for roll in ${studentID[@]}
            do
                if [[ $dirName == *"$roll"* ]]; then
                    flag=1
                    marks=5
                    actual_id=roll
                    break
                fi
            done
        fi
        #--------------------------------------------------

        #--------------------------------------------------
        #now we try to retrieve the studentID from the name of the zip
        if [ $flag == 0 ]; then
            for roll in ${studentID[@]}
            do
                if [[ $file == *"$roll"* ]]; then
                    flag=1
                    actual_id=roll
                    break
                fi
            done
        fi
        #--------------------------------------------------

        #--------------------------------------------------
        #now we try to retrieve the studentID using the studentName written in the zip and the csv
        #if two or more have same name then check if someone has already been processed
        #if we can't determine the person then this guy will go to 'extra' folder
        if [ $flag == 0 ]; then
        fi


    fi
    #---------------------------------------------------------------------
    
    #work done remove the temporary file
    rm temp

done
#--------------------------------------------------------------------------------------------------



#important basics- declare, assign, print in array
#idx=0
#for((i=0;i<145;i++))
#do
#    tempList[i]=$idx
#    idx=`expr $idx + 1`
#done
#--------------------------------------------------------------------------------------------------

#idx=0
#while [ $idx -lt ${#tempList[@]} ]
#do
#    echo ${tempList[$idx]}
#    idx=`expr $idx + 1`
#done
#for((i=0;i<$totalStudent;i++))
#do
#echo ${studentID[$i]}, ${studentName[i]}
#done