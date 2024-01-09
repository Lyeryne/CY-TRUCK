#!/bin/bash

# Exécution du compte à rebours
echo "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ CY TRUCK ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
STOP_TEMPS=false
source "Bonus/Affichage_Temps.sh" &
CPID=$! # Cela prend le PID du processus ($!) qui vient d'être mis en arrière-plan (&) par la commande précédente, et le stocke dans la variable 'CPID'.
# Conclusion : Cela permet de manipuler le processus (la 'source') pour envoyer des signaux et pleins d'autres opérations
    
    # Tue le programme si la commande ne s'est pas bien terminée
    if [ $? -ne 0 ] ; then
        echo "Erreur : Le commande a échoué. Sortie du programme."
        echo "Le traitement D1 a mis 0.000000000 s" 
        kill -SIGTERM $CPID
        exit 28
    fi

    #debut compteur temps
    temps_debut=$(date +%s.%N)
        # Tue le programme si la commande ne s'est pas bien terminée
        if [ $? -ne 0 ] ; then
            echo "Erreur : la durée du traitement ne peut pas être affichée."            
            echo "Le traitement D1 a mis 0.000000000 s" 
            kill -SIGTERM $CPID
            exit 29
        fi

# Ligne de code permettant : 
# - (LC_NUMERIC=C) : evite les problèmes de formatage numérateur lors de l'executable de la commande dans un script.
# - cut (route ID,Driver name) (f1,6) du fichier csv (dans data/s) : f1 = $1 et f6 = $2 (dans le awk)
# - !routes[$1]++ : ne compte qu'une fois chaque route ID
# - compteur[$2]++ : compte le nombre de trajets pour chaque conducteur
# - À la fin (END) avec la boucle : on parcours le tableau compteur et on print le résultat sous forme "%s;%d\n" puis on redirige la sortie vers sort
# - sort : trie de manière numérique (-n) par ordre décroissant (-r) la 2e colonne (%d) puis on redirige la sortie vers head
# - head : on conserve que les 10 premieres lignes
trajets=$(LC_NUMERIC=C cut -d';' -f1,6 < "data/$1" | awk -F';' '!routes[$1]++ {compteur[$2]++} END {for (conducteur in compteur) printf "%s;%d\n", conducteur, compteur[conducteur]}' | sort -t';' -k2 -n -r | head -10)
    # Tue le programme si la commande ne s'est pas bien terminée
    if [ $? -ne 0 ] ; then
        echo "Erreur : La commande de traitement des données a échoué. Sortie du programme."
        kill -SIGTERM $CPID
        temps_fin=$(date +%s.%N)
            # Tue le programme si la compilation ne s'est pas bien terminée
            if [ $? -ne 0 ] ; then
                echo "Erreur : la durée du traitement ne peut pas être affichée."            
                echo "Le traitement D1 a mis 0.000000000 s"
                exit 101
            fi
        temps_total=$(echo "$temps_fin - $temps_debut" | bc)
            # Tue le programme si la compilation ne s'est pas bien terminée
            if [ $? -ne 0 ] ; then
                echo "Erreur : la durée du traitement ne peut pas être affichée."            
                echo "Le traitement D1 a mis 0.000000000 s"
                exit 102
            fi
        echo "Le traitement D1 a mis $temps_total s" 
        exit 30
    fi

# Envoie des résultats d’exécutions précédentes(echo) dans le dossier temp' 
echo "$trajets" > temp/gnu_data_D1.txt
    # Tue le programme si la compilation ne s'est pas bien terminée
    if [ $? -ne 0 ] ; then
        echo "Erreur : La commande a échoué. Sortie du programme."
        kill -SIGTERM $CPID
        temps_fin=$(date +%s.%N)
            # Tue le programme si la compilation ne s'est pas bien terminée
            if [ $? -ne 0 ] ; then
                echo "Erreur : la durée du traitement ne peut pas être affichée."            
                echo "Le traitement D1 a mis 0.000000000 s"
                exit 103
            fi
        # Calculer la différence de temps
        temps_total=$(echo "$temps_fin - $temps_debut" | bc)
            # Tue le programme si la compilation ne s'est pas bien terminée
            if [ $? -ne 0 ] ; then
                echo "Erreur : La commande a échoué. Sortie du programme."
                echo "Le traitement D1 a mis 0.000000000 s"
                exit 104
            fi
        echo "Le traitement D1 a mis $temps_total s"
        exit 31
    fi


# Mesurer le temps après l'exécution du processus
temps_fin=$(date +%s.%N)
    # Tue le programme si la compilation ne s'est pas bien terminée
    if [ $? -ne 0 ] ; then
        echo "Erreur : la durée du traitement ne peut pas être affichée."
        echo "Le traitement D1 a mis 0.000000000 s"
        kill -SIGTERM $CPID
        exit 32
    fi

# Calculer la différence de temps
temps_total=$(echo "$temps_fin - $temps_debut" | bc)
    # Tue le programme si la compilation ne s'est pas bien terminée
    if [ $? -ne 0 ] ; then
        echo "Erreur : La commande a échoué. Sortie du programme."
        echo "Le traitement D1 a mis 0.000000000 s"  
        kill -SIGTERM $CPID
        exit 33
    fi

# Exécution du script Gnuplot
    file="gnu_script_D1.sh"
        # Tue le programme si la compilation ne s'est pas bien terminée
        if [ $? -ne 0 ] ; then
            echo "Erreur : La commande a échoué. Sortie du programme."
            echo "Le traitement D1 n'a pu que mettre $temps_total s"
            kill -SIGTERM $CPID
            exit 34
        fi
        
    if [ ! -x "$file" ] ; then # verifie si le fichier a la permission d'exécution
        chmod +x gnu_script_D1.sh
            # Tue le programme si la compilation ne s'est pas bien terminée
            if [ $? -ne 0 ] ; then
                echo "Erreur : La commande a échoué. Sortie du programme."
                echo "Le traitement D1 n'a pu que mettre $temps_total s"
                kill -SIGTERM $CPID
                exit 35
            fi
    else
        ./gnu_script_D1.sh
            # Tue le programme si la compilation ne s'est pas bien terminée
            if [ $? -ne 0 ] ; then
                echo "Erreur : La commande a échoué. Sortie du programme."
                echo "Le traitement D1 n'a pu que mettre $temps_total s"
                kill -SIGTERM $CPID
                exit 37
            fi
    fi

# Ligne de code : cela enverra le signal SIGUSR1(il se trouve dans Affichage_Temps.sh) au processus identifié par le PID stocké dans la variable $CPID, 
# déclenchant ainsi la fonction stop_compteur dans le script.
kill -SIGUSR1 $CPID
echo # Retour à la ligne
echo "arret du compte à rebour => TRAITEMENT FINIE" 
echo # Retour à la ligne

echo ">> Le traitement D1 a mis $temps_total s <<" 
