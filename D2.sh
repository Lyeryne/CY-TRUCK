#!/bin/bash

if [ $# -ne 1 ] ; then
    echo "Tu dois utiliser qu'un argument"
    exit 1
elif [ "$1" != "data.csv" ] || [ ! -f $1 ] || [ ! -e $1 ] ; then
    echo "Ce n'est pas le fichier qu'on attend" 
    exit 2
fi

distance_conducteur=$(LC_NUMERIC=C awk -F';' 'NR>1 {if(NR>1) distance[$6] += $5} END {for (conducteur in distance) printf "%s;%.6f\n", conducteur, distance[conducteur]}' "$1" | sort -t';' -k2 -r -n | head -10)
#if [ ! -e demo et images] ; then creer le dos
echo "$distance_conducteur" > demo/gnuplot_data_D2.txt

# Exécution du script Gnuplot
chmod +x gnuplot_script_D2.sh
./gnuplot_script_D2.sh
