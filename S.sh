#!/bin/bash

#Exécution du compte à rebours
echo "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ CY TRUCK ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
STOP_TEMPS=false
source "Bonus/Affichage_Temps.sh" &
    # Tue le programme si la compilation ne s'est pas bien terminée
    if [ $? -ne 0 ] ; then
        echo "Erreur : Le RM a échoué. Sortie du programme."
        kill -SIGTERM $CPID
        exit 1
    fi
CPID=$! # Cela prend le PID du processus ($!) qui vient d'être mis en arrière-plan (&) par la commande précédente, et le stocke dans la variable 'CPID'.
#Conclusion : Cela permet de manipuler le processus (la 'source') pour envoyer des signaux et pleins d'autres opérations

    # Tue le programme si le fichiers .C ou .h ou le makefile n'existe pas     
    if [ ! -e "progc/S.c" ] || [ ! -e "progc/AVL_S.c" ] || [ ! -e "progc/AVL_S.h" ] || [ ! -e "progc/S.h" ]  ; then
        echo "Il vous manque un fichier .c ou .h"
        kill -SIGTERM $CPID
        exit 1
    fi
    if [ ! -e "progc/makefile" ] ; then
        echo "Il vous manque le makefile"
        kill -SIGTERM $CPID
        exit 1
    fi

# Compilation du programme C
    make -C progc
        # Tue le programme si la compilation ne s'est pas bien terminée
        if [ $? -ne 0 ] ; then
            echo "Erreur : La compilation a échoué. Sortie du programme."
            kill -SIGTERM $CPID
            exit 1
        fi
    echo #saut de ligne

#debut compteur temps
temps_debut=$(date +%s.%N)
    # Tue le programme si la compilation ne s'est pas bien terminée
    if [ $? -ne 0 ] ; then
        echo "Erreur : Le RM a échoué. Sortie du programme."
        kill -SIGTERM $CPID
        exit 1
    fi

# Exécution du programme C avec le fichier en argument
    cut -d';' -f1,5 < "data/$1" | LC_NUMERIC=en_US.UTF-8 tail -n +2 > temp/c_data.txt
        # Tue le programme si la commande ne s'est pas bien terminée
        if [ $? -ne 0 ] ; then
            echo "Erreur : La commande de traitement des données a échoué. Sortie du programme."
            kill -SIGTERM $CPID
            exit 1
        fi
    cd progc
        # Tue le programme si la compilation ne s'est pas bien terminée
        if [ $? -ne 0 ] ; then
            echo "Erreur : Le RM a échoué. Sortie du programme."
            kill -SIGTERM $CPID
            exit 1
        fi
    ./Projet
        # Tue le programme si l'execution ne s'est pas bien terminée
        if [ $? -ne 0 ] ; then
            echo "Erreur : L'exécution du programme C a échoué. Sortie du programme."
            kill -SIGTERM $CPID
            exit 1
        fi

    cd ..
        # Tue le programme si la compilation ne s'est pas bien terminée
        if [ $? -ne 0 ] ; then
            echo "Erreur : Le RM a échoué. Sortie du programme."
            kill -SIGTERM $CPID
            exit 1
        fi
    head -n 50 "temp/gnuplot_data_S.txt" > "temp/gnu_data_S.txt"
        # Tue le programme si la compilation ne s'est pas bien terminée
        if [ $? -ne 0 ] ; then
            echo "Erreur : La compilation a échoué. Sortie du programme."
            kill -SIGTERM $CPID
            exit 1
        fi

# Mesurer le temps après l'exécution du processus
temps_fin=$(date +%s.%N)
    # Tue le programme si la compilation ne s'est pas bien terminée
    if [ $? -ne 0 ] ; then
        echo "Erreur : Le RM a échoué. Sortie du programme."
        kill -SIGTERM $CPID
        exit 1
    fi

# Calculer la différence de temps
temps_total=$(echo "$temps_fin - $temps_debut" | bc)
    # Tue le programme si la compilation ne s'est pas bien terminée
    if [ $? -ne 0 ] ; then
        echo "Erreur : Le RM a échoué. Sortie du programme."
        kill -SIGTERM $CPID
        exit 1
    fi

# vide le temp pour mettre seulement gnu_data_S.txt
    rm -f "temp/c_data.txt"
        # Tue le programme si la compilation ne s'est pas bien terminée
        if [ $? -ne 0 ] ; then
            echo "Erreur : Le RM a échoué. Sortie du programme."
            kill -SIGTERM $CPID
            exit 1
        fi
    rm -f "temp/gnuplot_data_S.txt" 
        # Tue le programme si la compilation ne s'est pas bien terminée
        if [ $? -ne 0 ] ; then
            echo "Erreur : Le RM a échoué. Sortie du programme."
            kill -SIGTERM $CPID
            exit 1
        fi

# Exécution du script Gnuplot
    file="gnu_script_S.sh"
        # Tue le programme si la compilation ne s'est pas bien terminée
        if [ $? -ne 0 ] ; then
            echo "Erreur : Le RM a échoué. Sortie du programme."
            kill -SIGTERM $CPID
            exit 1
        fi
    if [ ! -x "$file" ] ; then
        chmod +x gnu_script_S.sh
            # Tue le programme si la compilation ne s'est pas bien terminée
            if [ $? -ne 0 ] ; then
                echo "Erreur : Le RM a échoué. Sortie du programme."
                kill -SIGTERM $CPID
                exit 1
            fi
        ./gnu_script_S.sh
            # Tue le programme si la compilation ne s'est pas bien terminée
            if [ $? -ne 0 ] ; then
                echo "Erreur : Le RM a échoué. Sortie du programme."
                kill -SIGTERM $CPID
                exit 1
            fi
    else
        ./gnu_script_S.sh
            # Tue le programme si la compilation ne s'est pas bien terminée
            if [ $? -ne 0 ] ; then
                echo "Erreur : Le RM a échoué. Sortie du programme."
                kill -SIGTERM $CPID
                exit 1
            fi
    fi


kill -SIGUSR1 $CPID
echo #saut de ligne
echo "arret du compte à rebour => TRAITEMENT FINIE" 
echo #saut de ligne

echo "Le traitement S a mis $temps_total s" 
