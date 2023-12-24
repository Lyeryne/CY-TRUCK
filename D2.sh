#!/bin/bash

if [ $# -ne 1 ] ; then
    echo "Tu dois utiliser qu'un argument"
    exit 1
elif [ "$1" != "data.csv" ] || [ ! -f $1 ] || [ ! -e $1 ] ; then
    echo "Ce n'est pas le fichier qu'on attend" 
    exit 2
fi

distance_conducteur=$(LC_NUMERIC=C awk -F';' 'NR>1 {if(NR>1) distance[$6] += $5} END {for (personne in distance) printf "%s %.6f\n", personne, distance[personne]}' "$1" | sort -t' ' -k3 -r -n | head -10)
#if [ ! -e demo et images] ; then creer le dos
echo "$distance_conducteur" > demo/gnuplot_data_D2.txt

# Exécution du script Gnuplot
gnuplot -c gnuplot_script_D2.gnu