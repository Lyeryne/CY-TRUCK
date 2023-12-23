#!/bin/bash

if [ $# -ne 1 ] ; then
    echo "Tu dois utiliser qu'un argument" 
    exit 1
elif [ "$1" != "data.csv" ] || [ ! -f $1 ] || [ ! -e $1 ] ; then
    echo "Ce n'est pas le fichier qu'on attend" 
    exit 2
fi

trajets=$(awk -F';' 'NR>1 {if(NR>1) count[$6]++} END {for (person in count) print person, count[person]}' "$1" | sort -t' ' -k3 -r -n | head -10)
echo "$trajets" # > temp/?.txt > gnuplot

