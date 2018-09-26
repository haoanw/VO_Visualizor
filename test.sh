#!/bin/bash
cd ~/test
mkdir shell_tut
cd shell_tut

for (( i=1; i<=10; i++))
do
#for i in 1 2 3 4 5 6 7 8 9 10
#do
#echo "test $i times"
    touch test_$i.txt
done
