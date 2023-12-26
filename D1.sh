#!/bin/bash

if [ $# -ne 1 ] ; then
    echo "Tu dois utiliser qu'un argument" 
    exit 1
elif [ "$1" != "data.csv" ] || [ ! -f $1 ] || [ ! -e $1 ] ; then
    echo "Ce n'est pas le fichier qu'on attend" 
    exit 2
fi

#trajets=$(LC_NUMERIC=C awk -F';' 'NR>1 {routes[$1, $6]++; count[$6]++} END {for (person in count) printf "%s;%d\n", person, count[person]}' "$1" | sort -t';' -k2 -r -n | head -10)
trajets=$(LC_NUMERIC=C awk -F';' 'NR>1 {routes[$1, $6]++} END {for (route in routes) {split(route, arr, SUBSEP); compteur[arr[2]]++} for (conducteur in compteur) printf "%s;%d\n", conducteur, compteur[conducteur]}' "$1" | sort -t';' -k2 -r -n | head -10)
#if [ ! -e demo et images ] ; then creer le dos
echo "$trajets" > demo/gnuplot_data_D1.txt

# Exécution du script Gnuplot
chmod +x gnuplot_script_D1.sh
./gnuplot_script_D1.sh
