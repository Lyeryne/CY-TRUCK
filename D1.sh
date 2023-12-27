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

# Ligne de code permettant de récupérer : 
# - la liste des conducteurs ($5) avec le nombre de trajets ($1) qu’ils ont effectués. 
#(split) : divise la clé composée (conducteur, ville) avec SUBSEP(concateneur des indices du tableau associatif 'routes') et stocke les parties dans un tableau arr. Enfin, Awk compte le nombre de trajets pour chaque conducteur
#          différents qu’ils ont effectués. 
# (NR>1) exclut la première ligne et (LC_NUMERIC=C) evite les problèmes de formatage num lors de l'exec de cmd dans un script.
trajets=$(LC_NUMERIC=C awk -F';' 'NR>1 {routes[$1, $6]++} END {for (route in routes) {split(route, arr, SUBSEP); compteur[arr[2]]++} for (conducteur in compteur) printf "%s;%d\n", conducteur, compteur[conducteur]}' "data/$1" | sort -t';' -k2 -r -n | head -10)


# si le dossier 'demo' n'existe pas alors on le mkdir
if [ ! -e demo ] ; then 
    mkdir demo
fi
# si le dossier 'images' n'existe pas alors on le mkdir
if [ ! -e images ] ; then 
    mkdir images
fi

# Envoie des résultats d’exécutions précédentes(echo) dans le dossier ‘demo' 
echo "$trajets" > demo/gnuplot_data_D1.txt

# Exécution du script Gnuplot
file="gnuplot_script_D1.sh"
if [ ! -x "$file" ] ; then # verifie si le fichier a la permission d'exécution
    chmod +x gnuplot_script_D1.sh
    ./gnuplot_script_D1.sh
else
    ./gnuplot_script_D1.sh
fi

# Affiche que le temps (avec tail) que ça a mis grâce à la fonction 'time'  
t=$(time LC_NUMERIC=C awk -F';' 'NR>1 {routes[$1, $6]++} END {for (route in routes) {split(route, arr, SUBSEP); compteur[arr[2]]++} for (conducteur in compteur) printf "%s;%d\n", conducteur, compteur[conducteur]}' "data/$1" | sort -t';' -k2 -r -n | head -10) | tail -3
echo "$t"