#!/bin/bash

# ROBUSTESSE PARTIE [ DOSSIERS ]
    # si le dossier 'data' n'existe pas alors on le mkdir puis on mv le .csv
    if [ -e "$1" ] ; then
        if [ ! -e "data" ] ; then 
            mkdir data #etape 1
            
            # ROBUSTESSE
            if [[ "$1" != *.csv ]] ; then # verifie si $1 est un .CSV 
                echo "Ce n'est pas un fichier csv" 
                exit 1
            elif [ ! -f "$1" ]  ; then
                echo "$1 n'est pas un fichier" #verifie si c'est un fichier
                exit 2
            fi
            
            mv $1 data/ #etape 2
            
            # ROBUSTESSE
            if  [ ! -e "data/$1" ] ; then # verifie si $1 existe dans data/
                echo "data/$1 n'existe pas"
                exit 3
            fi

        else
            if [[ "data/$1" != *.csv ]] || [ ! -e "data/$1" ] ; then  # mv le .csv dans data/ s'il n'y est pas ou s'il n'existe pas
                mv $1 data/
            fi
        fi

    fi
    # si le dossier 'temp' n'existe pas ou 'temp' n'est pas un dossier alors on rm puis mkdir
    if [ ! -e "temp" ] || [ ! -d "temp" ] ; then 
        mkdir temp
        else # si le dossier 'temp' contient des elements alors on rm récursivement 
            if [ ! -z "$(ls -A temp/)" ] ; then
                rm -r temp/*
            fi
    fi
    # si le dossier 'images' n'existe pas ou 'images' n'est pas un dossier alors on rm puis mkdir
    if [ ! -e "images" ] || [ ! -d "images" ] ; then 
        mkdir images
    else # si le dossier 'images' contient des elements alors on rm récursivement 
        if [ ! -z "$(ls -A images/)" ] ; then
            rm -r images/*
        fi
    fi


# CHOIX DE TRAITEMENTS (D1, D2, L, T, S)
    # si le fichier csv existe ou s'il existe dans data/ 
    if [ -e "$1" ] || [ -e "data/$1" ] ; then # Alors
        # PRINTF DE BIENVENUE
        if [ ! -x "Bonus/Affichage_Menu.sh" ] ; then # verifie si le fichier a la permission d'exécution
            chmod +x 'Bonus/Affichage_Menu.sh'
            source Bonus/Affichage_Menu.sh
            echo
        else
            source Bonus/Affichage_Menu.sh
            echo
        fi
        # PRINTF COMPTE A REBOURS
        if [ ! -x "Bonus/Affichage_Temps.sh" ] ; then # verifie si le fichier a la permission d'exécution
            chmod +x 'Bonus/Affichage_Temps.sh'
            echo
        fi       

    # si jamais il voit -h, il affiche l'aide et ne fais pas les autres traitements
        for i in "$@" ; do
            if [ "$i" = "-h" ] ; then
                cat H.txt
                exit 0
            fi
        done
    # Sinon il fais les traitements
        for i in "$@" ; do
            case $i in 
                "-d1")
                    if [ ! -x "D1.sh" ] ; then # verifie si le fichier a la permission d'exécution
                        chmod +x D1.sh
                        ./D1.sh $1 # on lance le script
                    else
                        ./D1.sh $1 
                    fi 
                    ;;
                "-d2")
                    if [ ! -x "D2.sh" ] ; then # verifie si le fichier a la permission d'exécution
                        chmod +x D2.sh
                        ./D2.sh $1 # on lance le script
                    else
                        ./D2.sh $1 
                    fi 
                    ;;
                "-l")
                    if [ ! -x "L.sh" ] ; then # verifie si le fichier a la permission d'exécution
                        chmod +x L.sh
                        ./L.sh $1 # on lance le script
                    else
                        ./L.sh $1 
                    fi 
                    ;;
                #"-t") 
                #    if [ ! -x "T.sh" ] ; then # verifie si le fichier a la permission d'exécution
                #        chmod +x T.sh
                #        ./T.sh $1 # on lance le script
                #    else
                #        ./T.sh $1 
                #    fi 
                #    ;;
                "-s")
                    if [ ! -x "S.sh" ] ; then # verifie si le fichier a la permission d'exécution
                        chmod +x S.sh
                        ./S.sh $1 # on lance le script
                    else
                        ./S.sh $1 
                    fi 
                    ;;
            esac
        done
    # si le fichier csv n'existe pas     
    else
        echo "!!! Ton fichier CSV ne se trouve pas à la racine du projet ou dans le dossier 'data' !!!"
    fi



