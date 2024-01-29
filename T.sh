#!/bin/bash

# Affichage
echo "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ CY TRUCK ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"

    # Tue le programme si le fichiers .C ou .h ou le makefile n'existe pas     
    if [ ! -e "progc/T.c" ] || [ ! -e "progc/AVL_T.c" ] || [ ! -e "progc/AVL_T.h" ] || [ ! -e "progc/T.h" ] ; then
        echo "Il vous manque un fichier .c ou .h"
        echo "Le traitement S a mis 0.000000000 s"
        exit 59
    fi
    if [ ! -e "progc/makefile" ] ; then
        echo "Il vous manque le makefile"
        echo "Le traitement T a mis 0.000000000 s"
        exit 60
    fi

# Compilation du programme C
    make -C progc Projet_T
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
    cut -d';' -f1,3,4 < "data/$1" | LC_NUMERIC=en_US.UTF-8 tail -n +2 > temp/c2_data.txt
    # Tue le programme si la commande ne s'est pas bien terminée
    if [ $? -ne 0 ] ; then
        echo "Erreur : La commande de traitement des données a échoué. Sortie du programme."
        kill -SIGTERM $CPID
        temps_fin=$(date +%s.%N)
            # Tue le programme si la compilation ne s'est pas bien terminée
            if [ $? -ne 0 ] ; then
                echo "Erreur : la durée du traitement ne peut pas être affichée."            
                echo "Le traitement T a mis 0.000000000 s" 
                exit 63
            fi
        temps_total=$(echo "$temps_fin - $temps_debut" | bc)
            # Tue le programme si la compilation ne s'est pas bien terminée
            if [ $? -ne 0 ] ; then
                echo "Erreur : La durée du traitement ne peut être affichée. Sortie du programme."
                exit 63
            fi
        echo "Le traitement T a mis $temps_total s"
        exit 67
    fi
    cd progc
        # Tue le programme si la compilation ne s'est pas bien terminée
        if [ $? -ne 0 ] ; then
            echo "Erreur : La commande a échoué. Sortie du programme."
            kill -SIGTERM $CPID
            temps_fin=$(date +%s.%N)
                # Tue le programme si la compilation ne s'est pas bien terminée
                if [ $? -ne 0 ] ; then
                    echo "Erreur : La durée du traitement ne peut être affichée. Sortie du programme."
                    exit 63
                fi
            temps_total=$(echo "$temps_fin - $temps_debut" | bc)
                # Tue le programme si la compilation ne s'est pas bien terminée
                if [ $? -ne 0 ] ; then
                    echo "Erreur : la durée du traitement ne peut pas être affichée."            
                    echo "Le traitement T a mis 0.000000000 s" 
                    exit 65
                fi
            echo "Le traitement T a mis $temps_total s"
            exit 68
        fi
    ./Projet_T
        # Tue le programme si l'execution ne s'est pas bien terminée
        if [ $? -ne 0 ] ; then
            echo "Erreur : L'exécution du programme C a échoué. Sortie du programme."
            kill -SIGTERM $CPID
            temps_fin=$(date +%s.%N)
                # Tue le programme si la compilation ne s'est pas bien terminée
                if [ $? -ne 0 ] ; then
                    echo "Erreur : la durée du traitement ne peut pas être affichée."            
                    echo "Le traitement T a mis 0.000000000 s" 
                    exit 65
                fi
            temps_total=$(echo "$temps_fin - $temps_debut" | bc)
                # Tue le programme si la compilation ne s'est pas bien terminée
                if [ $? -ne 0 ] ; then
                    echo "Erreur : la durée du traitement ne peut pas être affichée."            
                    echo "Le traitement T a mis 0.000000000 s" 
                    exit 65
                fi
            echo "Le traitement T a mis $temps_total s"
            exit 70
        fi

    cd ..
        # Tue le programme si la compilation ne s'est pas bien terminée
        if [ $? -ne 0 ] ; then
            echo "Erreur : La commande a échoué. Sortie du programme."
            kill -SIGTERM $CPID
            temps_fin=$(date +%s.%N)
                # Tue le programme si la compilation ne s'est pas bien terminée
                if [ $? -ne 0 ] ; then
                    echo "Erreur : la durée du traitement ne peut pas être affichée."            
                    echo "Le traitement T a mis 0.000000000 s" 
                    exit 65
                fi
            temps_total=$(echo "$temps_fin - $temps_debut" | bc)
                # Tue le programme si la compilation ne s'est pas bien terminée
                if [ $? -ne 0 ] ; then
                    echo "Erreur : la durée du traitement ne peut pas être affichée."            
                    echo "Le traitement T a mis 0.000000000 s" 
                    exit 65
                fi
            echo "Le traitement T a mis $temps_total s"
            exit 72
        fi
    head -n 10 "temp/gnuplot_data_T.txt" > "temp/gnu_data_T.txt"
        # Tue le programme si la compilation ne s'est pas bien terminée
        if [ $? -ne 0 ] ; then
            echo "Erreur : La compilation a échoué. Sortie du programme."
            kill -SIGTERM $CPID
            temps_fin=$(date +%s.%N)
                # Tue le programme si la compilation ne s'est pas bien terminée
                if [ $? -ne 0 ] ; then
                    echo "Erreur : la durée du traitement ne peut pas être affichée."            
                    echo "Le traitement T a mis 0.000000000 s" 
                    exit 65
                fi
            temps_total=$(echo "$temps_fin - $temps_debut" | bc)
                # Tue le programme si la compilation ne s'est pas bien terminée
                if [ $? -ne 0 ] ; then
                    echo "Erreur : la durée du traitement ne peut pas être affichée."            
                    echo "Le traitement T a mis 0.000000000 s" 
                    exit 65
                fi
            echo "Le traitement T a mis $temps_total s"
            exit 74
        fi

# Mesurer le temps après l'exécution du processus
temps_fin=$(date +%s.%N)
    # Tue le programme si la commande ne s'est pas bien terminée
    if [ $? -ne 0 ] ; then
        echo "Erreur : la durée du traitement ne peut pas être affichée."            
        echo "Le traitement T a mis 0.000000000 s" 
        kill -SIGTERM $CPID
        exit 75
    fi

# Calculer la différence de temps
temps_total=$(echo "$temps_fin - $temps_debut" | bc)
    # Tue le programme si la compilation ne s'est pas bien terminée
    if [ $? -ne 0 ] ; then
        echo "Erreur : la durée du traitement ne peut pas être affichée."            
        echo "Le traitement T a mis 0.000000000 s" 
        kill -SIGTERM $CPID
        exit 76
    fi

# vide le temp pour mettre seulement gnu_data_S.txt
    rm -f "temp/c2_data.txt"
        # Tue le programme si la compilation ne s'est pas bien terminée
        if [ $? -ne 0 ] ; then
            echo "Erreur : La commande a échoué. Sortie du programme."
            echo "Le traitement T n'a pu que mettre $temps_total s"
            kill -SIGTERM $CPID
            exit 76    
        fi
    rm -f "temp/gnuplot_data_T.txt" 
        # Tue le programme si la compilation ne s'est pas bien terminée
        if [ $? -ne 0 ] ; then
            echo "Erreur : Le RM a échoué. Sortie du programme."
            echo "Le traitement T n'a pu que mettre $temps_total s" 
            kill -SIGTERM $CPID
            exit 78
        fi

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
