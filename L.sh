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
        echo "Le traitement L a mis 0.000000000 s" 
        kill -SIGTERM $CPID
        exit 28
    fi

    #debut compteur temps
    temps_debut=$(date +%s.%N)
        # Tue le programme si la commande ne s'est pas bien terminée
        if [ $? -ne 0 ] ; then
            echo "Erreur : Le commande a échoué. Sortie du programme."
            echo "Le traitement L a mis 0.000000000 s" 
            kill -SIGTERM $CPID
            exit 28
        fi

# Ligne de code permettant : 
# - cut (Route ID,Distance) (f1,5) du fichier csv (dans data/s) : f1 = $1 et f5 = $2 (dans le awk)
# - on fait alors la somme de chaque étape et ce, pour chaque trajet (...[$1]+= $2)
# - (NR>1) exclut la première ligne et (LC_NUMERIC=en_US.UTF-8) evite les problèmes de formatage numérateur en spécifiant le format (.)
# - À la fin (END) avec la boucle : on parcours le tableau distance et on print le résultat sous forme "%s;%f\n" puis on redirige la sortie vers sort
# - sort (1) : trie de manière numérique (-n) par ordre décroissant (-r) la 2e colonne (%d) puis on redirige la sortie vers head
# - head : on conserve que les 10 premieres lignes puis on redirige la sortie vers sort    
# - sort (2) : revient à trier le résultat (head) par numéro d’identifiant de trajet croissant ($1)
distance_trajet=$(cut -d';' -f1,5 < "data/$1" | LC_NUMERIC=en_US.UTF-8 awk -F';' 'NR>1 {distance[$1] += $2} END {for (conducteur in distance) printf "%s;%f\n", conducteur, distance[conducteur]}'| sort -t';' -k2 -r -n | head -10 | sort -t';' -k1 -n -r) 
    # Tue le programme si la commande ne s'est pas bien terminée
    if [ $? -ne 0 ] ; then
        echo "Erreur : La commande de traitement des données a échoué. Sortie du programme."
        kill -SIGTERM $CPID
        temps_fin=$(date +%s.%N)
            if [ $? -ne 0 ] ; then
                echo "Erreur : la durée du traitement ne peut pas être affichée."            
                echo "Le traitement L a mis 0.000000000 s"
                exit 101
            fi
        temps_total=$(echo "$temps_fin - $temps_debut" | bc)
            # Tue le programme si la compilation ne s'est pas bien terminée
            if [ $? -ne 0 ] ; then
                echo "Erreur : la durée du traitement ne peut pas être affichée."            
                echo "Le traitement L a mis 0.000000000 s"
                exit 102
            fi
        echo "Le traitement L a mis $temps_total s" 
        exit 30
    fi

# Envoie des résultats d’exécutions précédentes(echo) dans le dossier temp' 
echo "$distance_trajet" > temp/gnu_data_L.txt
    # Tue le programme si la compilation ne s'est pas bien terminée
    if [ $? -ne 0 ] ; then
        echo "Erreur : La commande a échoué. Sortie du programme."
        kill -SIGTERM $CPID
        temps_fin=$(date +%s.%N)
            # Tue le programme si la compilation ne s'est pas bien terminée
            if [ $? -ne 0 ] ; then
                echo "Erreur : la durée du traitement ne peut pas être affichée."            
                echo "Le traitement L a mis 0.000000000 s"
                exit 103
            fi
        # Calculer la différence de temps
        temps_total=$(echo "$temps_fin - $temps_debut" | bc)
            # Tue le programme si la compilation ne s'est pas bien terminée
            if [ $? -ne 0 ] ; then
                echo "Erreur : La commande a échoué. Sortie du programme."
                echo "Le traitement L a mis 0.000000000 s"
                exit 104
            fi
        echo "Le traitement L a mis $temps_total s"
        exit 31
    fi


# Mesurer le temps après l'exécution du processus
temps_fin=$(date +%s.%N)
    # Tue le programme si la compilation ne s'est pas bien terminée
    if [ $? -ne 0 ] ; then
        echo "Erreur : la durée du traitement ne peut pas être affichée."
        echo "Le traitement L a mis 0.000000000 s"
        kill -SIGTERM $CPID
        exit 32
    fi

# Calculer la différence de temps
temps_total=$(echo "$temps_fin - $temps_debut" | bc)
    # Tue le programme si la compilation ne s'est pas bien terminée
    if [ $? -ne 0 ] ; then
        echo "Erreur : La commande a échoué. Sortie du programme."
        echo "Le traitement L a mis 0.000000000 s"  
        kill -SIGTERM $CPID
        exit 33
    fi

# Exécution du script Gnuplot
    file="gnu_script_L.sh"
        # Tue le programme si la compilation ne s'est pas bien terminée
        if [ $? -ne 0 ] ; then
            echo "Erreur : La commande a échoué. Sortie du programme."
            echo "Le traitement L n'a pu mettre que $temps_total s"
            kill -SIGTERM $CPID
            exit 34
        fi
        
    if [ ! -x "$file" ] ; then # verifie si le fichier a la permission d'exécution
        chmod +x gnu_script_L.sh
            # Tue le programme si la compilation ne s'est pas bien terminée
            if [ $? -ne 0 ] ; then
                echo "Erreur : La commande a échoué. Sortie du programme."
                echo "Le traitement L n'a pu mettre que $temps_total s"
                kill -SIGTERM $CPID
                exit 35
            fi
    else
        ./gnu_script_L.sh
            # Tue le programme si la compilation ne s'est pas bien terminée
            if [ $? -ne 0 ] ; then
                echo "Erreur : La commande a échoué. Sortie du programme."
                echo "Le traitement L n'a pu mettre que $temps_total s"
                kill -SIGTERM $CPID
                exit 37
            fi
    fi
    display images/output_L.png &
        if [ $? -ne 0 ] ; then
            echo "Erreur : Affichage Impossible."
            exit 101
        fi

# Ligne de code : cela enverra le signal SIGUSR1(il se trouve dans Affichage_Temps.sh) au processus identifié par le PID stocké dans la variable $CPID, 
# déclenchant ainsi la fonction stop_compteur dans le script.
kill -SIGUSR1 $CPID
echo # Retour à la ligne
echo "arret du compte à rebour => TRAITEMENT FINIE" 
echo # Retour à la ligne

echo ">> Le traitement L a mis $temps_total s <<" 