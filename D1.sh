#!/bin/bash

# Ligne de code permettant de récupérer : 
# - la liste des conducteurs ($5) avec le nombre de trajets ($1) qu’ils ont effectués. 
#(split) : divise la clé composée (conducteur, ville) avec SUBSEP(concateneur des indices du tableau associatif 'routes') et stocke les parties dans un tableau arr. Enfin, Awk compte le nombre de trajets pour chaque conducteur
#          différents qu’ils ont effectués. 
# (NR>1) exclut la première ligne et (LC_NUMERIC=C) evite les problèmes de formatage numérateur lors de l'executable de la commande dans un script.
trajets=$(LC_NUMERIC=C awk -F';' 'NR>1 {routes[$1, $6]++} END {for (route in routes) {split(route, arr, SUBSEP); compteur[arr[2]]++} for (conducteur in compteur) printf "%s;%d\n", conducteur, compteur[conducteur]}' "data/$1" | sort -t';' -k2 -r -n | head -10)
#cut -d';' -f1,6 < $1 | awk -F';' '!arr[$1]++ {arr2[$2]++} END {for (i in arr2) print i ";" arr2[i]}' | sort -t';' -k2,2nr | head -n 10 > temp/d1.temp

# Envoie des résultats d’exécutions précédentes(echo) dans le dossier ‘demo' 
echo "$trajets" > temp/gnuplot_data_D1.txt

# Exécution du script Gnuplot
file="gnuplot_script_D1.sh"
if [ ! -x "$file" ] ; then # verifie si le fichier a la permission d'exécution
    chmod +x gnuplot_script_D1.sh
    ./gnuplot_script_D1.sh
else
    ./gnuplot_script_D1.sh
fi

# Affiche que le temps (avec tail) que ça a mis grâce à la fonction 'time'  
t=$( { time -p LC_NUMERIC=C awk -F';' 'NR>1 {routes[$1, $6]++} END {for (route in routes) {split(route, arr, SUBSEP); compteur[arr[2]]++} for (conducteur in compteur) printf "%s;%d\n", conducteur, compteur[conducteur]}' "data/$1" | sort -t';' -k2 -r -n | head -10; } 2>&1 | awk '/^real/ {print $2}' )
echo "Le traitement D1 a mis $t s" 