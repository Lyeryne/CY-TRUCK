#!/bin/bash

#Exécution du compte à rebours
echo "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ CY TRUCK ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
STOP_TEMPS=false
source "Bonus/Affichage_Temps.sh" &
CPID=$! # Cela prend le PID du processus ($!) qui vient d'être mis en arrière-plan (&) par la commande précédente, et le stocke dans la variable 'CPID'.
#Conclusion : Cela permet de manipuler le processus (la 'source') pour envoyer des signaux et pleins d'autres opérations
        
# Compilation du programme C
make -C progc
echo #saut de ligne

#debut compteur temps
temps_debut=$(date +%s.%N)

# Exécution du programme C avec le fichier en argument
cut -d";" -f1,5 "data/$1" | tail -n +2 > temp/c_data.txt
cd progc
./Projet
cd ..
head -n 50 "temp/gnuplot_data_S.txt" > "temp/gnu_data_S.txt"

# Mesurer le temps après l'exécution du processus
temps_fin=$(date +%s.%N)

# Calculer la différence de temps
temps_total=$(echo "$temps_fin - $temps_debut" | bc)

# vide le temp pour mettre seulement gnu_data_S.txt
rm -f "temp/c_data.txt"
rm -f "temp/gnuplot_data_S.txt" 

# Exécution du script Gnuplot
file="gnu_script_S.sh"
if [ ! -x "$file" ] ; then
    chmod +x gnu_script_S.sh
    ./gnu_script_S.sh
else
    ./gnu_script_S.sh
fi


kill -SIGUSR1 $CPID
echo #saut de ligne
echo "arret du compte à rebour => TRAITEMENT FINIE" 
echo #saut de ligne

echo "Le traitement S a mis $temps_total s" 
