#!/bin/bash

#function is_dir(){
#    local dir=$1
#    if [ -d ${dir} ] ; then
#        return 0
#    else
#        return 1
#    fi
#}
#
#arr[0]="aaaa"
#arr[1]="bbbb"
#arr[2]="cccc"
#
#array=("xingyiming" "rendengbin" "xiaoguodong")
#
#echo ${arr[*]}
#echo ${array[*]}
#echo ${array[2]}
#
#for dir in $@
#do
#    if is_dir ${dir} ; then
#        :
#    else
#        echo "${dir} not exit create it "
#        mkdir ${dir} 
#        if [ $? -ne 0 ]; then
#            echo "create dir ${dir} fail"
#            exit 1
#        fi
#    fi
#done

function fibo (){
    arr[0]=1
    arr[1]=1
    i=0
    while [ $i -le $1 ]
    do
        let arr[$i+2]=arr[$i]+arr[$i+1]
        let i++;
    done
    echo ${arr[$1]}
 }

arr=(1 2 3 4 5 6 7 8 9 10)
let max=${arr[0]} 
let min=${max}
sum=0
for (( i=0 ; i<${#arr[@]};++i ))
do
    [ ${arr[$i]} -gt $max  ] && max=${arr[$i]}
    [ ${arr[$i]} -lt $min ] && min=${arr[$i]}
    let sum=sum+${arr[$i]}
done
echo min is $min
echo "max is $max"
echo "sum is $sum"
len=${#arr[@]}
echo $len 
 
array=(2 3 4 5 6 7)

len=${#array[@]}
echo "$len"
fibo $1











