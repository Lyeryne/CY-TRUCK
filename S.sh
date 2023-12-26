#!/bin/bash

if [ $# -ne 1 ] ; then
    echo "Tu dois utiliser qu'un argument" 
    exit 1
elif [ "$1" != "data.csv" ] || [ ! -f $1 ] || [ ! -e $1 ] ; then
    echo "Ce n'est pas le fichier qu'on attend" 
    exit 2
fi


gcc -o exe progc/S.c
res=$(cut -f1,5 "data/$1" > ./exe)





if [ ! -e demo ] ; then
    mkdir demo
fi
if [ ! -e images ] ; then 
    mkdir images
fi