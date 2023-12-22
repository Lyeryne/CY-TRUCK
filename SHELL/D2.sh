#!/bin/bash

if [ $# -ne 1 ] ; then
    echo "Tu dois utiliser qu'un argument" >&2
    exit 1
elif [ "$1" != "data.csv" ] || [ ! -f $1 ] || [ ! -e $1 ] ; then
    echo "Ce n'est pas le fichier qu'on attend" >&2
    exit 2
fi

distance=`awk -F';' '{if(NR>1) count[$6]++} END {for (distance in count) print $6,distance, count[distance]}' data.csv | sort -t' ' -k3 -r | head -10`
echo "$distance"
