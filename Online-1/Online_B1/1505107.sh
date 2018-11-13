#!/bin/bash

IFS=$'\n'

for file in $(ls)
do
    if [[ -d $file ]]; then
        tname=$file
        touch $tname.txt

        mv $tname $file
        cd $file

        for file2 in $(ls)
        do
            mv $tname $file2
            for txt_files in $(find . -name \*\.txt -type f)
            do
                cat $tname $txt_files
            done
            mv $tname ../
        done

        mv $tname ../
    fi
done
