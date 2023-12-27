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
# - la distance totale ($5) pour chaque conducteur ($6) 
# en faisant la somme des distances de toutes les étapes qui leurs sont associées (...[$6]+= $5)
distance_conducteur=$(LC_NUMERIC=C awk -F';' 'NR>1 {if(NR>1) distance[$6] += $5} END {for (conducteur in distance) printf "%s;%.6f\n", conducteur, distance[conducteur]}' "data/$1" | sort -t';' -k2 -r -n | head -10)

# si le dossier 'demo' n'existe pas alors on le mkdir
if [ ! -e demo ] ; then 
    mkdir demo
fi
# si le dossier 'images' n'existe pas alors on le mkdir
if [ ! -e images ] ; then 
    mkdir images
fi

# Envoie des résultats d’exécutions précédentes(echo) dans le dossier ‘demo' 
echo "$distance_conducteur" > demo/gnuplot_data_D2.txt

# Exécution du script Gnuplot
file="gnuplot_script_D2.sh"
if [ ! -x "$file" ] ; then # verifie si le fichier a la permission d'exécution
    chmod +x gnuplot_script_D2.sh
    ./gnuplot_script_D2.sh
else
    ./gnuplot_script_D2.sh
fi

# Affiche que le temps (avec tail) que ça a mis grâce à la fonction 'time'  
t=$(time LC_NUMERIC=C awk -F';' 'NR>1 {if(NR>1) distance[$6] += $5} END {for (conducteur in distance) printf "%s;%.6f\n", conducteur, distance[conducteur]}' "data/$1" | sort -t';' -k2 -r -n | head -10) | tail -3
echo "$t"
