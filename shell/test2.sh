#!/bin/bash

#VALUE=10
#
#test $VALUE -gt 9
#echo $?
#test $VALUE -gt 11
#echo $?
#test $VALUE -gt 10
#echo $?
#
#[ $VALUE -gt 8 ]
#echo $?
#
#[ -d shell ]
#echo $?
#[ -f test1.sh ]
#echo $?
#string=""
#[ -z "$string" ]
#echo $?
#string1="hello world"
#[ -n "$string" ]
#echo $?
#string2="hello world"
#[ "$string1" = "$string2" ]
#echo $?
#[ "$string1" != "$string2" ]
#echo $?

#str="huhuhahaha"
#[ -f test1.sh -a "$str" = "huhuhahaha" ]
#echo $?
#[ -d test1.sh -a "$str" = "huhuhahaha" ]
#echo $?
#[ -d test1.sh -o "$str" = "huhuhahaha" ]
#echo $?

#echo "please enter your string"
#read ustr
#if [ "$ustr" = "xingyiming" ] ;then
#    echo "enter is xingyiming"
#fi
#
#read ustr2
#if [ "$ustr2" = "xingyiming" ] ; then
#    echo "enter is xingyiming"
#elif [ "$ustr2" = "zuidiao" ] ; then 
#    echo "enter is zuidiao"
#else
#    echo "don't kown what you enter"
#fi
#
#if : ; then
#    echo "huhuhuhahah"
#fi

[ -f test1.sh ] && {
    echo "test1.sh is file"
}

[ -d a ] || {
    echo "a is not dir"
}

val=10
str="this"

test $val -eq 10 -a "$str" = "this"
echo $?
test $val -eq 10 && test "$str" = "this"
echo $?







