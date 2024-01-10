#!/bin/bash

# Affichage
echo "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ CY TRUCK ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"

    # Tue le programme si le fichiers .C ou .h ou le makefile n'existe pas     
    if [ ! -e "progc/T.c" ] || [ ! -e "progc/AVL_T.c" ] || [ ! -e "progc/AVL_T.h" ] || [ ! -e "progc/T.h" ] ; then
        echo "Il vous manque un fichier .c ou .h"
        echo "Le traitement T a mis 0.000000000 s"
        exit 59
    fi
    if [ ! -e "progc/makefile" ] ; then
        echo "Il vous manque le makefile"
        echo "Le traitement T a mis 0.000000000 s"
        exit 60
    fi

# Compilation du programme C
    make -C progc
        # Tue le programme si la compilation ne s'est pas bien terminée
        if [ $? -ne 0 ] ; then
            echo "Erreur : La compilation a échoué. Sortie du programme."
            echo "Le traitement T a mis 0.000000000 s"
            exit 61
        fi
    echo #saut de ligne
    
# Exécution du compte à rebours
STOP_TEMPS=false
source "Bonus/Affichage_Temps.sh" &
CPID=$! # Cela prend le PID du processus ($!) qui vient d'être mis en arrière-plan (&) par la commande précédente, et le stocke dans la variable 'CPID'.
# Conclusion : Cela permet de manipuler le processus (la 'source') pour envoyer des signaux et pleins d'autres opérations

    # Tue le programme si la compilation ne s'est pas bien terminée
    if [ $? -ne 0 ] ; then
        echo "Erreur : La commande a échoué. Sortie du programme."
        echo "Le traitement T a mis 0.000000000 s"
        # Tue le processus de compte à rebours
        kill -SIGTERM $CPID
        exit 62
    fi

#debut compteur temps
temps_debut=$(date +%s.%N)
    # Tue le programme si la commande ne s'est pas bien terminée
    if [ $? -ne 0 ] ; then
        echo "Erreur : la durée du traitement ne peut pas être affichée."            
        echo "Le traitement T a mis 0.000000000 s" 
        kill -SIGTERM $CPID
        exit 64
    fi

# Exécution du programme C avec le fichier en argument
cut -d";" -f1,5 "data/$1" | tail -n +2 > temp/c_data_T.txt
cd progc
./Projet

#aide
echo "Le répertoire actuel est : $(pwd)"
cd .. 
echo "Le répertoire actuel est : $(pwd)"

#head -n 50 "temp/gnuplot_data_T.txt" > "temp/gnu_data_T.txt"
rm -f "temp/c_data_T.txt"
rm -f "temp/gnuplot_data_T.txt" 

# Exécution du script Gnuplot
    file="gnu_script_T.sh"
        # Tue le programme si la compilation ne s'est pas bien terminée
        if [ $? -ne 0 ] ; then
            echo "Erreur : La commande a échoué. Sortie du programme."
            echo "Le traitement T n'a pu que mettre $temps_total s" 
            kill -SIGTERM $CPID
            exit 79
        fi
    if [ ! -x "$file" ] ; then
        chmod +x gnu_script_T.sh
            # Tue le programme si la compilation ne s'est pas bien terminée
            if [ $? -ne 0 ] ; then
                echo "Erreur : La commande a échoué. Sortie du programme."
                echo "Le traitement T n'a pu que mettre $temps_total s" 
                kill -SIGTERM $CPID
                exit 80
            fi
    else
        ./gnu_script_T.sh
            # Tue le programme si la compilation ne s'est pas bien terminée
            if [ $? -ne 0 ] ; then
                echo "Erreur : La commande a échoué. Sortie du programme."
                echo "Le traitement T n'a pu que mettre $temps_total s" 
                kill -SIGTERM $CPID
                exit 81
            fi
    fi


kill -SIGUSR1 $CPID
echo #saut de ligne
echo "arret du compte à rebour => TRAITEMENT FINIE" 
echo #saut de ligne

echo ">> Le traitement T a mis $temps_total s <<" 
