#!/bin/bash

#read val
val=10
case $val in
     10 )
        echo "enter is $val"
        ;;
     b ) 
        echo "enter is b"
        ;;
     c ) 
        echo "enter si c"
        ;;
     * ) 
        echo "........"
        ;;
esac

for i in {a..c}
do
    echo "printf val is : $i"
done

for (( i=0; i<3; i++ ))
do
    echo "printf val is : $i"
done

password=yes #no
while [ ! $password = "yes" ]
do
    echo "try again"
    read password
done

count=0;
while [ $count -lt 5 ]
do
    echo "this is ${count} time"
    ((count++))
done

echo "parameter count is argc - 1 $#"
echo "parameter list is $@"
echo "exit code is $?"
echo "parameter 0 is $0"
echo "process code is $$"







