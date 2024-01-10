#!/bin/bash

clear

# Affichage
echo "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ CY TRUCK ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"

# si jamais il voit -h, il affiche l'aide et s'arrete 
    for i in "$@" ; do
        if [ "$i" = "-h" ] || [ "$i" = "-H" ] || [ "$i" = "_h" ] || [ "$i" = "_H" ] ; then
            cat H.txt
            exit 15
        fi
    done
    
# ROBUSTESSE PARTIE [ DOSSIERS ]   
    # si le dossier 'data' n'existe pas alors on le mkdir puis on mv le .csv
    if [ -e "$1" ] ; then
        if [ ! -e "data" ] ; then 
            mkdir data #etape 1
                # Tue le programme si la commande ne s'est pas bien terminée
                if [ $? -ne 0 ] ; then
                    echo "Erreur : Le mkdir a échoué. Sortie du programme."
                    exit 1
                fi
            
            # ROBUSTESSE
            if [[ "$1" != *.csv ]] ; then # verifie si $1 est un .CSV 
                echo "Ce n'est pas un fichier csv" 
                exit 2
            elif [ ! -f "$1" ]  ; then
                echo "$1 n'est pas un fichier" #verifie si c'est un fichier
                exit 3
            fi
            
            mv $1 data/ #etape 2
                # Tue le programme si la commande ne s'est pas bien terminée
                if [ $? -ne 0 ] ; then
                    echo "Erreur : Le MV a échoué. Sortie du programme."
                    exit 4
                fi
            
            # ROBUSTESSE
            if  [ ! -e "data/$1" ] ; then # verifie si $1 existe dans data/
                echo "data/$1 n'existe pas"
                exit 5
            fi

        else
            if [[ "data/$1" != *.csv ]] || [ ! -e "data/$1" ] ; then  # mv le .csv dans data/ s'il n'y est pas ou s'il n'existe pas
                mv $1 data/
                    # Tue le programme si la commande ne s'est pas bien terminée
                    if [ $? -ne 0 ] ; then
                        echo "Erreur : Le MV a échoué. Sortie du programme."
                        exit 6
                    fi
            fi
        fi

    fi
    # si le dossier 'temp' n'existe pas ou 'temp' n'est pas un dossier alors on rm puis mkdir
    if [ ! -e "temp" ] || [ ! -d "temp" ] ; then 
        mkdir temp
            # Tue le programme si la commande ne s'est pas bien terminée
            if [ $? -ne 0 ] ; then
                echo "Erreur : Le MKDIR a échoué. Sortie du programme."
                exit 7
            fi
        else # si le dossier 'temp' contient des elements alors on rm récursivement 
            if [ ! -z "$(ls -A temp/)" ] ; then
                rm -r temp/*
                    # Tue le programme si la commande ne s'est pas bien terminée
                    if [ $? -ne 0 ] ; then
                        echo "Erreur : Le RM a échoué. Sortie du programme."
                        exit 8
                    fi
            fi
    fi
    # si le dossier 'images' n'existe pas ou 'images' n'est pas un dossier alors on rm puis mkdir
    if [ ! -e "images" ] || [ ! -d "images" ] ; then 
        mkdir images
            # Tue le programme si la commande ne s'est pas bien terminée
            if [ $? -ne 0 ] ; then
                echo "Erreur : Le MKDIR a échoué. Sortie du programme."
                exit 9
            fi
    else # si le dossier 'images' contient des elements alors on rm récursivement 
        if [ ! -z "$(ls -A images/)" ] ; then
            rm -r images/*
                # Tue le programme si la commande ne s'est pas bien terminée
                if [ $? -ne 0 ] ; then
                    echo "Erreur : Le RM a échoué. Sortie du programme."
            
                    exit 10
                fi
        fi
    fi


# CHOIX DE TRAITEMENTS (D1, D2, L, T, S)
    # si le fichier csv existe ou s'il existe dans data/ 
    if [ -e "$1" ] || [ -e "data/$1" ] ; then # Alors
        # PRINTF DE BIENVENUE
        if [ ! -x "Bonus/Affichage_Menu.sh" ] ; then # verifie si le fichier a la permission d'exécution
            chmod +x 'Bonus/Affichage_Menu.sh'
                # Tue le programme si la commande ne s'est pas bien terminée
                if [ $? -ne 0 ] ; then
                    echo "Erreur : Le CHMOD a échoué. Sortie du programme."
                    exit 11
                fi
            source 'Bonus/Affichage_Menu.sh'
                # Tue le programme si la commande ne s'est pas bien terminée
                if [ $? -ne 0 ] ; then
                    echo "Erreur : Le SOURCE a échoué. Sortie du programme."
                    exit 12
                fi
            echo
        else
            source 'Bonus/Affichage_Menu.sh'
                # Tue le programme si la commande ne s'est pas bien terminée
                if [ $? -ne 0 ] ; then
                    echo "Erreur : Le SOURCE a échoué. Sortie du programme."

                    exit 13
                fi
            echo
        fi
        # PRINTF COMPTE A REBOURS
        if [ ! -x "Bonus/Affichage_Temps.sh" ] ; then # verifie si le fichier a la permission d'exécution
            chmod +x 'Bonus/Affichage_Temps.sh'
                # Tue le programme si la commande ne s'est pas bien terminée
                if [ $? -ne 0 ] ; then
                    echo "Erreur : Le CHMOD a échoué. Sortie du programme."
                    exit 14
                fi
            echo
        fi       


    # si jamais il voit -h, il affiche l'aide et ne fais pas les autres traitements
        for i in "$@" ; do
            if [ "$i" = "-h" ] ; then
                cat H.txt
                exit 15
            fi
        done
    # Sinon il fais les traitements
        #creer une variable pour stocker le data.csv
        fichier_csv=""

        for i in "$@" ; do
            if [ -z "$fichier_csv" ] ; then
            # Si le fichier (-z) n'a pas encore établi, on considère alors l'arg actuel comme fichier_csv
            fichier_csv="$i"
                else
                    case $i in 
                        "-d1" | "-D1" | "_d1" | "_D1")
                            if [ ! -x "D1.sh" ] ; then # verifie si le fichier a la permission d'exécution
                                chmod +x D1.sh
                                    # Tue le programme si la commande ne s'est pas bien terminée
                                    if [ $? -ne 0 ] ; then
                                        echo "Erreur : Le CHMOD de D1.sh a échoué. Sortie du programme."                                
                                        exit 16
                                    fi
                                fi
                                ./D1.sh $1 # on lance le script
                                    # Tue le programme si la commande ne s'est pas bien terminée
                                    if [ $? -ne 0 ] ; then
                                        echo "Erreur : L'execution D1.sh a échoué. Sortie du programme."
                                        exit 17
                                    fi
                            ;;
                        "-d2" | "-D2" | "_d2" | "_D2")
                            if [ ! -x "D2.sh" ] ; then # verifie si le fichier a la permission d'exécution
                                chmod +x D2.sh
                                    # Tue le programme si la commande ne s'est pas bien terminée
                                    if [ $? -ne 0 ] ; then
                                        echo "Erreur : Le CHMOD de D2.sh a échoué. Sortie du programme."
                                        exit 19
                                    fi
                                fi
                                ./D2.sh $1 # on lance le script
                                    # Tue le programme si la commande ne s'est pas bien terminée
                                    if [ $? -ne 0 ] ; then
                                        echo "Erreur : L'execution D2.sh a échoué. Sortie du programme."
                                        exit 20
                                    fi
                            ;;
                        "-l" | "-L" | "_l" | "_L")
                            if [ ! -x "L.sh" ] ; then # verifie si le fichier a la permission d'exécution
                                chmod +x L.sh
                                    # Tue le programme si la commande ne s'est pas bien terminée
                                    if [ $? -ne 0 ] ; then
                                        echo "Erreur : Le CHMOD de L.sh a échoué. Sortie du programme."
                                        exit 22
                                    fi
                                fi
                                ./L.sh $1 # on lance le script
                                    # Tue le programme si la commande ne s'est pas bien terminée
                                    if [ $? -ne 0 ] ; then
                                        echo "Erreur : L'execution L.sh a échoué. Sortie du programme."
                                        exit 23
                                    fi
                            ;;
                        #"-t" | "-T" | "_t" | "_T") 
                        #    if [ ! -x "T.sh" ] ; then # verifie si le fichier a la permission d'exécution
                        #        chmod +x T.sh
                        #        ./T.sh $1 # on lance le script
                        #    else
                        #        ./T.sh $1 
                        #    fi 
                        #    ;;
                        "-s" | "-S" | "_s" | "_S")
                            if [ ! -x "S.sh" ] ; then # verifie si le fichier a la permission d'exécution
                                chmod +x S.sh
                                    # Tue le programme si la commande ne s'est pas bien terminée
                                    if [ $? -ne 0 ] ; then
                                        echo "Erreur : Le CHMOD de S.sh a échoué. Sortie du programme."
                                        exit 25
                                    fi
                                fi
                            ./S.sh $1 
                                # Tue le programme si la commande ne s'est pas bien terminée
                                if [ $? -ne 0 ] ; then
                                    echo "Erreur : L'execution S.sh a échoué. Sortie du programme."
                                    exit 27
                                fi
                            ;;
                        # Aucun des autres cas 
                        *)
                            echo "Traitement inconnue détectée : '$i' => RESPECTEZ LE FORMAT (revoir readme ou -h '_')"
                            exit 1000
                        ;;
                    esac
            fi
        done
    # si le fichier csv n'existe pas     
    else
        echo "!!! [Ton fichier CSV ne se trouve pas à la racine du projet ou dans le dossier 'data'] !!!"
        exit 100
    fi



