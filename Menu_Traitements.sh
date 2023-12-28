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
        rm *temp*
        mkdir temp
        else # si le dossier 'temp' contient des elements alors on rm récursivement 
            if [ ! -z "$(ls -A temp/)" ] ; then
                rm -r temp/*
            fi
    fi
    # si le dossier 'images' n'existe pas ou 'images' n'est pas un dossier alors on rm puis mkdir
    if [ ! -e "images" ] || [ ! -d "images" ] ; then 
        rm *images*
        mkdir images
    else # si le dossier 'images' contient des elements alors on rm récursivement 
        if [ ! -z "$(ls -A images/)" ] ; then
            rm -r images/*
        fi
    fi


# CHOIX DE TRAITEMENTS (D1, D2, L, T, S)
if [ -e "$1" ] || [ -e "data/$1" ] ; then
    # PRINTF DE BIENVENUE
    if [ ! -x "Bonus/DisplayTxt_Menu.sh" ] ; then # verifie si le fichier a la permission d'exécution
        chmod +x 'Bonus/DisplayTxt_Menu.sh'
        source Bonus/DisplayTxt_Menu.sh
    else
        source Bonus/DisplayTxt_Menu.sh
    fi


    for i in $@
    do 
        case $i in 
            "-d1")
                if [ ! -x "D1.sh" ] ; then
                    chmod +x D1.sh
                    ./D1.sh $1 
                else
                    ./D1.sh $1
                fi 
                ;;
            "-d2")
                if [ ! -x "D2.sh" ] ; then
                    chmod +x D2.sh
                    ./D2.sh $1 
                else
                    ./D2.sh $1
                fi 
                ;;
            "-l")
                if [ ! -x "L.sh" ] ; then
                    chmod +x L.sh
                    ./L.sh $1 
                else
                    ./L.sh $1
                fi 
                ;;
            #"-t") ... ;;
            #"-s") ... ;;
            #"-h") message d’aide expliquant les options 
                    #exit 0
                    #;; 
               *)
                echo "Option non reconnue: $i"
                exit 1
                ;;
        esac
    done
    if [[ "$@" == *"-h"* ]]; then
        exit 0
    fi
else
    echo "Ton fichier CSV ne se trouve pas à la racine du projet"
fi



