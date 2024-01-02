#!/bin/bash

# Exécution du compte à rebours
echo "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ CY TRUCK ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
STOP_TEMPS=false
source "Bonus/Affichage_Temps.sh" &
CPID=$! # Cela prend le PID du processus ($!) qui vient d'être mis en arrière-plan (&) par la commande précédente, et le stocke dans la variable 'CPID'.
# Conclusion : Cela permet de manipuler le processus (la 'source') pour envoyer des signaux et pleins d'autres opérations


# Ligne de code permettant de récupérer : 
# - la distance totale ($5) pour chaque conducteur ($6) 
# en faisant la somme des distances de toutes les étapes qui leurs sont associées (...[$6]+= $5)
# - (NR>1) exclut la première ligne et (LC_NUMERIC=C) evite les problèmes de formatage numérateur lors de l'executable de la commande dans un script.
distance_conducteur=$(LC_NUMERIC=C awk -F';' 'NR>1 {distance[$6] += $5} END {for (conducteur in distance) printf "%s;%.6f\n", conducteur, distance[conducteur]}' "data/$1" | sort -t';' -k2 -r -n | head -10)

# Envoie des résultats d’exécutions précédentes(echo) dans le dossier temp' 
echo "$distance_conducteur" > temp/gnuplot_data_D2.txt

# Exécution du script Gnuplot
file="gnuplot_script_D2.sh"
if [ ! -x "$file" ] ; then # verifie si le fichier a la permission d'exécution
    chmod +x gnuplot_script_D2.sh
    ./gnuplot_script_D2.sh # on lance le script
else
    ./gnuplot_script_D2.sh
fi

# Affiche que le temps (time -p 'la ligne de code') puis on dirige la sortie d'erreur standard (2>) au même endroit que la sortie standard (&1) 
# puis on redirige la sortie vers awk pour extraire le temps "real" de la sortie de time afin de le stocker dans le fichier txt 
t=$( { time -p LC_NUMERIC=C awk -F';' 'NR>1 {distance[$6] += $5} END {for (conducteur in distance) printf "%s;%.6f\n", conducteur, distance[conducteur]}' "data/$1" | sort -t';' -k2 -r -n | head -10; } 2>&1 | awk '/^real/ {print $2}' )

# Ligne de code : cela enverra le signal SIGUSR1(il se trouve dans Affichage_Temps.sh) au processus identifié par le PID stocké dans la variable $CPID, 
# déclenchant ainsi la fonction stop_compteur dans le script.
kill -SIGUSR1 $CPID
echo # Retour à la ligne
echo "arret du compte à rebour => TRAITEMENT FINIE" 
echo # Retour à la ligne

echo "Le traitement D2 a mis $t s" 

