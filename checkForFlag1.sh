#!/bin/bash

# Use this if you want to verify for flag 1.

# The format to run the script is:
# bash checkForFlag1.sh <inputFilePath> <outputFilePath> <startIndex> <endIndex>

# PS: It takes quite some time to run, especially if the reversed parts are of a significant size.

n=$3
m=$4
file1=$1
file2=$2

#Check reverse for the initial characters
rev_content=$(head -c $n $file1 | rev)

file2_content=$(head -c $n $file2)

if [ "$rev_content" == "$file2_content" ]; then
    echo "Reverse test for the first $n characters PASSED! :)"
else
    echo "Reverse test for the first $n characters FAILED! :("
fi

#Check identicality for the next m characters
substring1=$(dd if=$file1 bs=1 skip=$((n)) count=$((m-n+1)) 2>/dev/null)

substring2=$(dd if=$file2 bs=1 skip=$((n)) count=$((m-n+1)) 2>/dev/null)

if [ "$substring1" == "$substring2" ]; then
    echo "Identicality test for the characters between indices $n and $m PASSED! :)"
else
    echo "Identicality test for the characters between indices $n and $m FAILED! :("
fi

#Update index for tail
m=$((m+2))

#Check reverse for the latter characters
reversed_substring1=$((tail -c +$m $file1) | rev)

substring2=$(tail -c +$m $file2)

if [ "$reversed_substring1" == "$substring2" ]; then
    echo "Reverse test for the tail characters PASSED! :)"
else
    echo "Reverse test for the tail characters FAILED! :("
fi
