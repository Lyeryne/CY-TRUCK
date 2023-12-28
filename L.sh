#!/bin/bash

# Ligne de code permettant de récupérer : 
# - la distance totale de chaque trajet ($1) 
# - en ordonnant le résultat par numéro d’identifiant ($5) de trajet croissant
distance_trajet=$(LC_NUMERIC=C awk -F';' 'NR>1 {if(NR>1) distance[$1] += $5} END {for (conducteur in distance) printf "%s;%.6f\n", conducteur, distance[conducteur]}' "data/$1" | sort -t';' -k2 -r -n | head -10 | sort -t';' -k1 -n -r) 

# Envoie des résultats d’exécutions précédentes(echo) dans le dossier ‘demo' 
echo "$distance_trajet" > temp/gnuplot_data_L.txt 

# Exécution du script Gnuplot
file="gnuplot_script_L.sh"
if [ ! -x "$file" ] ; then # verifie si le fichier a la permission d'exécution
    chmod +x gnuplot_script_L.sh
    ./gnuplot_script_L.sh
else
    ./gnuplot_script_L.sh
fi

# Affiche que le temps (avec tail) que ça a mis grâce à la fonction 'time'  
t=$( { time -p LC_NUMERIC=C awk -F';' 'NR>1 {if(NR>1) distance[$1] += $5} END {for (conducteur in distance) printf "%s;%.6f\n", conducteur, distance[conducteur]}' "data/$1" | sort -t';' -k2 -r -n | head -10 | sort -t';' -k1 -n -r; } 2>&1 | awk '/^real/ {print $2}' )
echo "Le traitement L a mis $t s" 

