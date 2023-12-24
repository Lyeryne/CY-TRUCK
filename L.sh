#!/bin/bash

if [ $# -ne 1 ] ; then
    echo "Tu dois utiliser qu'un argument" 
    exit 1
elif [ "$1" != "data.csv" ] || [ ! -f $1 ] || [ ! -e $1 ] ; then
    echo "Ce n'est pas le fichier qu'on attend" 
    exit 2
fi

distance_trajet=$(LC_NUMERIC=C awk -F';' 'NR>1 {if(NR>1) distance[$1] += $5} END {for (personne in distance) printf "%s %.6f\n", personne, distance[personne]}' "$1" | sort -t' ' -k2 -r -n | head -10 | sort -t' ' -k1 -n) 
#if [ ! -e demo et images ] ; then creer le dos
echo "$distance_trajet" > demo/gnuplot_data_L.txt

# Exécution du script Gnuplot
gnuplot -c gnuplot_script_L.gnu