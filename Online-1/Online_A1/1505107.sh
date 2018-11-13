#./bin/bash

IFS=$'\n'

src=$1
files=$(find . -name \*\.txt -type f)

idx=0
for file in ${files[@]}
do
    file=${file:2}
   
    if [[ $file != $src ]]; then
      searchable[idx]=$file
      idx=`expr $idx + 1` 
    fi
done

while read line
do
    echo "searching for: $line"
    line=${line^^}

    for file in ${searchable[@]}
    do
        k=1
        while read line2
        do
            line2=${line2^^}

            #if line is a part of line2 print
            if [[ $line2 == *"$line"* ]]; then
                echo $file
                echo "copy found at line $k"
            fi

            k=`expr $k + 1`
        done < $file
    done

    echo
done < $src