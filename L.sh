#!/bin/bash

# Exécution du compte à rebours
echo "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ CY TRUCK ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
STOP_TEMPS=false
source "Bonus/Affichage_Temps.sh" &
CPID=$! # Cela prend le PID du processus ($!) qui vient d'être mis en arrière-plan (&) par la commande précédente, et le stocke dans la variable 'CPID'.
# Conclusion : Cela permet de manipuler le processus (la 'source') pour envoyer des signaux et pleins d'autres opérations


# Ligne de code permettant : 
# - cut (Route ID,Distance) (f1,5) du fichier csv (dans data/s) : f1 = $1 et f5 = $2 (dans le awk)
# - on fait alors la somme de chaque étape et ce, pour chaque trajet (...[$1]+= $2)
# - (NR>1) exclut la première ligne et (LC_NUMERIC=en_US.UTF-8) evite les problèmes de formatage numérateur en spécifiant le format (.)
# - À la fin (END) avec la boucle : on parcours le tableau distance et on print le résultat sous forme "%s;%f\n" puis on redirige la sortie vers sort
# - sort (1) : trie de manière numérique (-n) par ordre décroissant (-r) la 2e colonne (%d) puis on redirige la sortie vers head
# - head : on conserve que les 10 premieres lignes puis on redirige la sortie vers sort    
# - sort (2) : revient à trier le résultat (head) par numéro d’identifiant de trajet croissant ($1)
    #debut compteur temps
    temps_debut=$(date +%s.%N)

distance_trajet=$(cut -d';' -f1,5 < "data/$1" | LC_NUMERIC=en_US.UTF-8 awk -F';' 'NR>1 {distance[$1] += $2} END {for (conducteur in distance) printf "%s;%f\n", conducteur, distance[conducteur]}'| sort -t';' -k2 -r -n | head -10 | sort -t';' -k1 -n -r) 

# Envoie des résultats d’exécutions précédentes(echo) dans le dossier 'temp' 
echo "$distance_trajet" > temp/gnu_data_L.txt 

    # Mesurer le temps après l'exécution du processus
    temps_fin=$(date +%s.%N)
    # Calculer la différence de temps
    temps_total=$(echo "$temps_fin - $temps_debut" | bc)

# Exécution du script Gnuplot
file="gnu_script_L.sh"
if [ ! -x "$file" ] ; then # verifie si le fichier a la permission d'exécution
    chmod +x gnu_script_L.sh 
    ./gnu_script_L.sh # on lance le script
else
    ./gnu_script_L.sh 
fi

# Ligne de code : cela enverra le signal SIGUSR1(il se trouve dans Affichage_Temps.sh) au processus identifié par le PID stocké dans la variable $CPID, 
# déclenchant ainsi la fonction stop_compteur dans le script.
kill -SIGUSR1 $CPID
echo #saut de ligne
echo "arret du compte à rebour => TRAITEMENT FINIE" 
echo #saut de ligne

#echo "Le traitement L a mis $t s" 
echo "Le traitement L a mis $temps_total s" 
