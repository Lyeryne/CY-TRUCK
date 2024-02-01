#!/bin/bash


# Exécution du compte à rebours
echo "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ CY TRUCK ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
STOP_TEMPS=false
source "Bonus/Affichage_Temps.sh" &
CPID=$! # Cela prend le PID du processus ($!) qui vient d'être mis en arrière-plan (&) par la commande précédente, et le stocke dans la variable 'CPID'.
# Conclusion : Cela permet de manipuler le processus (la 'source') pour envoyer des signaux et pleins d'autres opérations

    # Tue le programme si la compilation ne s'est pas bien terminée
    if [ $? -ne 0 ] ; then
        echo "Erreur : Le commande a échoué. Sortie du programme."
        echo "Le traitement D2 a mis 0.000000000 s" 
        kill -SIGTERM $CPID
        exit 38
    fi

    #debut compteur temps
    temps_debut=$(date +%s.%N)
        # Tue le programme si la compilation ne s'est pas bien terminée
        if [ $? -ne 0 ] ; then
            echo "Erreur : la durée du traitement ne peut pas être affichée."            
            echo "Le traitement D2 a mis 0.000000000 s" 
            kill -SIGTERM $CPID
            exit 39
        fi
        
# Ligne de code permettant : 
# - cut (Distance,Driver name) (f5,6) du fichier csv (dans data/s) : f5 = $1 et f6 = $2 (dans le awk)
# - on fait alors la somme des distances de toutes les étapes qui leurs sont associées (...[$2]+= $1)
# - (NR>1) exclut la première ligne et (LC_NUMERIC=en_US.UTF-8) evite les problèmes de formatage numérateur en spécifiant le format (.)
# - À la fin (END) avec la boucle : on parcours le tableau distance et on print le résultat sous forme "%s;%f\n" puis on redirige la sortie vers sort
# - sort : trie de manière numérique (-n) par ordre décroissant (-r) la 2e colonne (%d) puis on redirige la sortie vers head
# - head : on conserve que les 10 premieres lignes
distance_conducteur=$(cut -d';' -f5,6 < "data/$1" | LC_NUMERIC=en_US.UTF-8 awk -F';' 'NR>1 {distance[$2] += $1} END {for (conducteur in distance) printf "%s;%f\n", conducteur, distance[conducteur]}' | sort -t';' -k2 -r -n | head -10)
    # Tue le programme si la commande ne s'est pas bien terminée
    if [ $? -ne 0 ] ; then
        echo "Erreur : La commande de traitement des donnnées a échoué. Sortie du programme."
        kill -SIGTERM $CPID
        temps_fin=$(date +%s.%N)
            # Tue le programme si la compilation ne s'est pas bien terminée
            if [ $? -ne 0 ] ; then
                echo "Erreur : la durée du traitement ne peut pas être affichée."            
                echo "Le traitement D2 a mis 0.000000000 s"             
                exit 52
            fi
        # Calculer la différence de temps
        temps_total=$(echo "$temps_fin - $temps_debut" | bc)
            # Tue le programme si la compilation ne s'est pas bien terminée
            if [ $? -ne 0 ] ; then
                echo "Erreur : la durée du traitement ne peut pas être affichée."            
                echo "Le traitement D2 a mis 0.000000000 s"             
                exit 53
            fi
        echo "Le traitement L a mis $temps_total s"
        exit 40
    fi

# Envoie des résultats d’exécutions précédentes(echo) dans le dossier temp' 
echo "$distance_conducteur" > temp/gnu_data_D2.txt
    # Tue le programme si la compilation ne s'est pas bien terminée
    if [ $? -ne 0 ] ; then
        echo "Erreur : La commande a échoué. Sortie du programme."
        kill -SIGTERM $CPID
        temps_fin=$(date +%s.%N)
            # Tue le programme si la compilation ne s'est pas bien terminée
            if [ $? -ne 0 ] ; then
                echo "Erreur : la durée du traitement ne peut pas être affichée."            
                echo "Le traitement D2 a mis 0.000000000 s"             
                exit 53
            fi
        # Calculer la différence de temps
        temps_total=$(echo "$temps_fin - $temps_debut" | bc)
            # Tue le programme si la compilation ne s'est pas bien terminée
            if [ $? -ne 0 ] ; then
                echo "Erreur : la durée du traitement ne peut pas être affichée."            
                echo "Le traitement D2 a mis 0.000000000 s"             
                exit 54
            fi
        echo "Le traitement L a mis $temps_total s"
        exit 41
    fi

# Mesurer le temps après l'exécution du processus
temps_fin=$(date +%s.%N)
    # Tue le programme si la compilation ne s'est pas bien terminée
    if [ $? -ne 0 ] ; then
        echo "Erreur : la durée du traitement ne peut pas être affichée."            
        echo "Le traitement D2 a mis 0.000000000 s"             
        kill -SIGTERM $CPID
        exit 42
    fi

# Calculer la différence de temps
temps_total=$(echo "$temps_fin - $temps_debut" | bc)
    # Tue le programme si la compilation ne s'est pas bien terminée
    if [ $? -ne 0 ] ; then
        echo "Erreur : la durée du traitement ne peut pas être affichée."            
        echo "Le traitement D2 a mis 0.000000000 s"             
        kill -SIGTERM $CPID
        exit 43
    fi

# Exécution du script Gnuplot
    file="gnu_script_D2.sh"
        # Tue le programme si la compilation ne s'est pas bien terminée
        if [ $? -ne 0 ] ; then
            echo "Erreur : La commande a échoué. Sortie du programme."
            echo "Le traitement D2 n'a pu mettre que $temps_total s"
            kill -SIGTERM $CPID
            exit 44
        fi
        
    if [ ! -x "$file" ] ; then # verifie si le fichier a la permission d'exécution
        chmod +x gnu_script_D2.sh
            # Tue le programme si la compilation ne s'est pas bien terminée
            if [ $? -ne 0 ] ; then
                echo "Erreur : La commande a échoué. Sortie du programme."
                echo "Le traitement D2 n'a pu mettre que $temps_total s"
                kill -SIGTERM $CPID
                exit 45
            fi
    else
        ./gnu_script_D2.sh
            # Tue le programme si la compilation ne s'est pas bien terminée
            if [ $? -ne 0 ] ; then
                echo "Erreur : La commande a échoué. Sortie du programme."
                echo "Le traitement D2 n'a pu mettre que $temps_total s"
                kill -SIGTERM $CPID
                exit 47
            fi
    fi
    #display images/output_D2.png

# Ligne de code : cela enverra le signal SIGUSR1(il se trouve dans Affichage_Temps.sh) au processus identifié par le PID stocké dans la variable $CPID, 
# déclenchant ainsi la fonction stop_compteur dans le script.
kill -SIGUSR1 $CPID
echo # Retour à la ligne
echo "arret du compte à rebour => TRAITEMENT FINIE" 
echo # Retour à la ligne

echo ">> Le traitement D2 a mis $temps_total s <<" 

cd Bonus
./Affichage_Bonus.sh calcul_temps
cd ..
