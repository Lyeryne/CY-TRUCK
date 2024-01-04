#!/bin/bash


# Compilation du programme C
make -C progc
#CLEMMM supprime les # a gauche quand tu as fini ton traitement
    #sleep 2
    #clear

#CLEMMM supprime les # a gauche quand tu as fini ton traitement
    # Exécution du compte à rebours
    #echo "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ CY TRUCK ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
    #STOP_TEMPS=false
    #source "Bonus/Affichage_Temps.sh" &
    #CPID=$! # Cela prend le PID du processus ($!) qui vient d'être mis en arrière-plan (&) par la commande précédente, et le stocke dans la variable 'CPID'.
    # #Conclusion : Cela permet de manipuler le processus (la 'source') pour envoyer des signaux et pleins d'autres opérations

# Exécution du programme C avec le fichier en argument
cut -d";" -f1,5 "data/$1" | tail -n +2 > temp/c_data.txt
cd progc
./Projet

#aide a savoir ou tu te trouves (supprime les 2 echo si tu as reussi le traitement)
echo "Le répertoire actuel est : $(pwd)"
cd .. 
echo "Le répertoire actuel est : $(pwd)"

head -n 50 "temp/gnuplot_data_S.txt" > "temp/gnu_data_S.txt"
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

#CLEMMM supprime les # a gauche de kill et des 3 echo (et non les lignes) quand tu as fini ton traitement
#kill -SIGUSR1 $CPID
#echo #saut de ligne
#echo "arret du compte à rebour => TRAITEMENT FINIE" 
#echo #saut de ligne
