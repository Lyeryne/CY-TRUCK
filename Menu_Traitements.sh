#!/bin/bash

# PRINTF DE BIENVENUE
file1="Bonus/DisplayTxt_Menu.sh"
if [ ! -x "$file1" ] ; then # verifie si le fichier a la permission d'exécution
    chmod +x 'Bonus/DisplayTxt_Menu.sh'
    source Bonus/DisplayTxt_Menu.sh
else
    source Bonus/DisplayTxt_Menu.sh
fi

# ROBUSTESSE PARTIE [ DOSSIERS ]
    # si le dossier 'data' n'existe pas alors on le mkdir puis on mv le .csv
    if [ ! -e data ] ; then 
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


    # si le dossier 'temp' n'existe pas alors on le mkdir
    if [ ! -e temp ] ; then 
        mkdir temp
        else # si le dossier 'temp' contient des elements alors on rm récursivement 
            if [ ! -z "$(ls -A temp/)" ] ; then
                rm -r temp/*
            fi
    fi
    # si le dossier 'images' n'existe pas alors on le mkdir
    if [ ! -e images ] ; then 
        mkdir images
    else # si le dossier 'images' contient des elements alors on rm récursivement 
        if [ ! -z "$(ls -A images/)" ] ; then
            rm -r images/*
        fi
    fi
    # si le dossier 'demo' n'existe pas alors on le mkdir
    if [ ! -e demo ] ; then 
        mkdir demo
    fi



# CHOIX DE TRAITEMENTS (D1, D2, L, T, S)
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
        #"-h") message d’aide expliquant les options ;; 
    esac
done




