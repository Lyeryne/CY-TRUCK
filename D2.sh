#!/bin/bash

# Ligne de code permettant de récupérer : 
# - la distance totale ($5) pour chaque conducteur ($6) 
# en faisant la somme des distances de toutes les étapes qui leurs sont associées (...[$6]+= $5)
distance_conducteur=$(LC_NUMERIC=C awk -F';' 'NR>1 {if(NR>1) distance[$6] += $5} END {for (conducteur in distance) printf "%s;%.6f\n", conducteur, distance[conducteur]}' "data/$1" | sort -t';' -k2 -r -n | head -10)

# Envoie des résultats d’exécutions précédentes(echo) dans le dossier ‘demo' 
echo "$distance_conducteur" > temp/gnuplot_data_D2.txt

# Exécution du script Gnuplot
file="gnuplot_script_D2.sh"
if [ ! -x "$file" ] ; then # verifie si le fichier a la permission d'exécution
    chmod +x gnuplot_script_D2.sh
    ./gnuplot_script_D2.sh
else
    ./gnuplot_script_D2.sh
fi

# Affiche que le temps (avec tail) que ça a mis grâce à la fonction 'time'  
t=$( { time -p LC_NUMERIC=C awk -F';' 'NR>1 {if(NR>1) distance[$6] += $5} END {for (conducteur in distance) printf "%s;%.6f\n", conducteur, distance[conducteur]}' "data/$1" | sort -t';' -k2 -r -n | head -10; } 2>&1 | awk '/^real/ {print $2}' )
echo "Le traitement D2 a mis $t s" 
