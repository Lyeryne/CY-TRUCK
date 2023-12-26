#!/bin/bash

if [ $# -ne 1 ] ; then # verifie de n'utiliser qu'un arg
    echo "Tu dois utiliser qu'un argument" 
    exit 1
elif  [ ! -e "data/$1" ] ; then # verifie si $1 existe
    echo "data/$1 n'existe pas"
    exit 2
elif [[ "$1" != *.csv ]] ; then # verifie si $1 est un .CSV 
    echo "Ce n'est pas un fichier csv" 
    exit 3
elif [ ! -f "data/$1" ]  ; then
    echo "data/$1 n'est pas un fichier" #verifie si c'est un fichier
    exit 4
fi


#trajets=$(LC_NUMERIC=C awk -F';' 'NR>1 {routes[$1, $6]++; count[$6]++} END {for (person in count) printf "%s;%d\n", person, count[person]}' "$1" | sort -t';' -k2 -r -n | head -10)
trajets=$(LC_NUMERIC=C awk -F';' 'NR>1 {routes[$1, $6]++} END {for (route in routes) {split(route, arr, SUBSEP); compteur[arr[2]]++} for (conducteur in compteur) printf "%s;%d\n", conducteur, compteur[conducteur]}' "data/$1" | sort -t';' -k2 -r -n | head -10)
#trajets=$(LC_NUMERIC=C awk -F';' 'NR>1 {routes[$1, $6]++} END {for (route in routes) {split(route, arr, SUBSEP); compteur[arr[2]]++} for (conducteur in compteur) printf "%s;%d\n", conducteur, compteur[conducteur]}' "data/$1" | sort -t';' -k2 -r -n | head -10)

# si le dossier 'demo' n'existe pas alors on le mkdir
if [ ! -e demo ] ; then 
    mkdir demo
fi
# si le dossier 'images' n'existe pas alors on le mkdir
if [ ! -e images ] ; then 
    mkdir images
fi
echo "$trajets" > demo/gnuplot_data_D1.txt

# Exécution du script Gnuplot
chmod +x gnuplot_script_D1.sh
./gnuplot_script_D1.sh

t=$(time LC_NUMERIC=C awk -F';' 'NR>1 {routes[$1, $6]++} END {for (route in routes) {split(route, arr, SUBSEP); compteur[arr[2]]++} for (conducteur in compteur) printf "%s;%d\n", conducteur, compteur[conducteur]}' "data/$1" | sort -t';' -k2 -r -n | head -10) | tail -3
echo "$t"