#!/bin/bash

#shell splits on <space><tab><newline> so we change IFS
#https://unix.stackexchange.com/questions/9496/looping-through-files-with-spaces-in-the-names
IFS=$'\n'

echo "started executing the script"
echo

#--------------------------------------------------------------------------------------------------
#open absent list and marks file
touch absent.txt
touch marks.txt
#--------------------------------------------------------------------------------------------------


#--------------------------------------------------------------------------------------------------
#unzip the file where all the submission are
unzip SubmissionsAll.zip

#delete the zip
rm -r SubmissionsAll.zip
#--------------------------------------------------------------------------------------------------


#--------------------------------------------------------------------------------------------------
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


#--------------------------------------------------------------------------------------------------
#whenever a roll is found in the files, he is considered as present
for((i=0;i<$totalStudent;i++))
do
    present[i]=0
    marks[i]=0
done

idx=0
for roll in ${studentID[@]}
do
    for file in ${zips[@]}
    do
        if [[ $file == *"$roll"* ]]; then
            present[idx]=1
            break
        fi
    done
    idx=`expr $idx + 1`
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
#for all the submissions-
for file in ${zips[@]}
do 
    #unzip in a temporary file in a new folder called temp
    unzip -d temporary_folder/ $file
    
    cd temporary_folder

    #check number of directories in temp
    #noOfDirectory=$(*/ | wc -w) not working
    #works fine when echo */ | wc -w
    noOfDirectory=0
    for file2 in $(ls)
    do
        noOfDirectory=`expr $noOfDirectory + 1`
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
        tmarks=0
        actual_id=0
        extra=0

        for roll in ${studentID[@]}
        do
            if [ $roll == $dirName ]; then
                flag=1
                tmarks=10
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
                    tmarks=5
                    actual_id=$roll
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
                    actual_id=$roll
                    break
                fi
            done
        fi
        #--------------------------------------------------

        #--------------------------------------------------
        #now we try to retrieve the studentID using the studentName written in the zip and the csv
        #if two or more un-determined people have this name then not possible to determine
        if [ $flag == 0 ]; then

            #tname is the name in zip files name. adding sum char to the original name from csv(which is tname2 now) will result in tname
            cnt=0
            troll=-1

            #here we extracted the zip files name
            zname=$file
            zname=$(echo $zname|cut -d '_' -f 1)
            zname=${zname:2}
            zname=${zname^^}

            for((i=0;i<$totalStudent;i++))
            do
                csvName=${studentName[$i]}
                csvName=${csvName^^}

                #if absent then check for ambiguity
                #here the name from csv may have some space or other char that can't be seen
                #so i used =~ instead of ==
                if [ ${present[$i]} == 0 ]; then
                    if [[ $zname =~ $csvName ]] || [[ $csvName =~ $zname ]]; then
                        troll=${studentID[$i]}
                        cnt=`expr $cnt + 1`
                    fi
                fi
            done

            if [ $cnt == 1 ]; then
                actual_id=$troll
                flag=1
            fi
        fi

        #if flag is 1 then move to output folder, else in extra folder
        if [ $flag == 1 ]; then
            for((i=0;i<$totalStudent;i++))
            do
                if [ ${studentID[$i]} == $actual_id ]; then
                    marks[i]=$tmarks
                    present[i]=1
                    break
                fi
            done

            #first rename if necessary
            if [[ $dirName != $actual_id ]]; then
                mv $dirName $actual_id
            fi

            #move
            mv * ../output
        else
            temp_name=$file+" extra"
            
            mv * $temp_name
            mv * ../output/extra
        fi
        #---------------------------------------------------------------------
    else
        #---------------------------------------------------------------------
        #more than one directory, same as the last stage of if 
        #--------------------------------------------------
        #now we try to retrieve the studentID from the name of the zip
        for roll in ${studentID[@]}
        do
            if [[ $file == *"$roll"* ]]; then
                flag=1
                actual_id=$roll
                break
            fi
        done
        #--------------------------------------------------

        #--------------------------------------------------
        #now we try to retrieve the studentID using the studentName written in the zip and the csv
        #if two or more un-determined people have this name then not possible to determine
        if [ $flag == 0 ]; then

            #tname is the name in zip files name. adding sum char to the original name from csv(which is tname2 now) will result in tname
            cnt=0
            troll=-1
            
            #here we extracted the zip files name
            zname=$file
            zname=$(echo $zname|cut -d '_' -f 1)
            zname=${zname:2}
            zname=${zname^^}

            for((i=0;i<$totalStudent;i++))
            do
                csvName=${studentName[$i]}
                csvName=${csvName^^}

                #if absent then check for ambiguity
                #here the name from csv may have some space or other char that can't be seen
                #so i used =~ instead of ==
                if [ ${present[$i]} == 0 ]; then
                    if [[ $zname =~ $csvName ]] || [[ $csvName =~ $zname ]]; then
                        troll=${studentID[$i]}
                        cnt=`expr $cnt + 1`
                    fi
                fi
            done

            if [ $cnt == 1 ]; then
                actual_id=$troll
                flag=1
            fi
        fi

        #if flag is 1 then move to output folder, else in extra folder but first copy everything in a folder
        if [ $flag == 1 ]; then
            for((i=0;i<$totalStudent;i++))
            do
                if [ ${studentID[$i]} == $actual_id ]; then
                    present[i]=1
                    break
                fi
            done

            #first create a folder
            mkdir $actual_id
            for file2 in $(ls)
            do
                if [[ $file2 != $actual_id ]]; then
                    mv $file2 $actual_id
                fi
            done

            #move
            mv * ../output
        else
            #first create a folder having the same name as the zip

            temp_name=$file+" extra"
            mkdir $temp_name
            for file2 in $(ls)
            do
                if [[ $file2 != $file ]] && [[ $file2 != $temp_name ]]; then
                    mv $file2 $temp_name
                fi
            done
            mv * ../output/extra
        fi
    fi
    #---------------------------------------------------------------------

    #work done remove the temporary file
    cd ..
    rm -r temporary_folder
done


#------------------------------
#print the absent list and marks list
for((i=0;i<$totalStudent;i++))
do
    if [ ${present[$i]} == 0 ]; then
    echo ${studentID[$i]} >> absent.txt
    fi

    echo "${studentID[$i]} : ${marks[$i]}" >> marks.txt
done
#------------------------------


#------------------------------
#remove all the submissions
for file in ${zips[@]}
do
    rm -r $file
done
#--------------------------------------------------------------------------------------------------