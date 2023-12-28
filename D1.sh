#!/bin/bash

# Ligne de code permettant : 
# - # (LC_NUMERIC=C) : evite les problèmes de formatage numérateur lors de l'executable de la commande dans un script.
# - cut route ID et Driver name (f1,6) => dans le awk : f1 = $1 et f6 = $2 (grâce au pipe)
# - !routes[$1]++ : ne compte qu'une fois chaque route ID
# - compteur[$2]++ : compte le nombre de trajets pour chaque conducteur
# - À la fin (END) avec la boucle : on parcours le tableau compteur et on print le résultat sous forme "%s;%d\n" puis on redirige la sortie vers sort
# - sort : trie de manière numérique (-n) par ordre décroissant (-r) la 2e colonne (%d) puis on redirige la sortie vers head
# - head : on conserve que les 10 premieres lignes
trajets=$(LC_NUMERIC=C cut -d';' -f1,6 < "data/$1" | awk -F';' '!routes[$1]++ {compteur[$2]++} END {for (conducteur in compteur) printf "%s;%d\n", conducteur, compteur[conducteur]}' | sort -t';' -k2 -n -r | head -10)

# Envoie des résultats d’exécutions précédentes(echo) dans le dossier temp' 
echo "$trajets" > temp/gnuplot_data_D1.txt

# Exécution du script Gnuplot
file="gnuplot_script_D1.sh"
if [ ! -x "$file" ] ; then # verifie si le fichier a la permission d'exécution
    chmod +x gnuplot_script_D1.sh
    ./gnuplot_script_D1.sh # on lance le script
else
    ./gnuplot_script_D1.sh
fi

# Affiche que le temps (time -p 'la ligne de code') puis on dirige la sortie d'erreur standard (2>) au même endroit que la sortie standard (&1) 
# puis on redirige la sortie vers awk pour extraire le temps "real" de la sortie de time afin de le stocker dans le fichier txt
t=$( { time -p LC_NUMERIC=C cut -d';' -f1,6 < "data/$1" | awk -F';' '!routes[$1]++ {compteur[$2]++} END {for (conducteur in compteur) printf "%s;%d\n", conducteur, compteur[conducteur]}' | sort -t';' -k2 -n -r | head -10; } 2>&1 | awk '/^real/ {print $2}' )
echo "Le traitement D1 a mis $t s" 