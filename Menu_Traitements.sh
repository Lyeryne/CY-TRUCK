#!/bin/bash

# PRINTF DE BIENVENUE
file1="Bonus/DisplayTxt_Menu.sh"
if [ ! -x "$file1" ] ; then # verifie si le fichier a la permission d'exécution
    chmod +x 'Bonus/DisplayTxt_Menu.sh'
    source Bonus/DisplayTxt_Menu.sh
else
    source Bonus/DisplayTxt_Menu.sh
fi

# ROBUSTESSE PARTIE DOSSIER
    # si le dossier 'data' n'existe pas alors on le mkdir
    if [ ! -e data ] ; then 
        mkdir data
        mv *.csv data/
    fi
    # si le dossier 'demo' n'existe pas alors on le mkdir
    if [ ! -e demo ] ; then 
        mkdir demo
    fi
    # si le dossier 'images' n'existe pas alors on le mkdir
    if [ ! -e images ] ; then 
        mkdir images
    fi
# ROBUSTESSE PARTIE DATA/FICHIER($1)
    if [ $# -ne 2 ] ; then # verifie de n'utiliser qu'un arg
        echo "Tu dois utiliser que 2 arguments" 
        exit 1
    elif  [ ! -e "data/$1" ] ; then # verifie si $1 existe
        echo "data/$1 n'existe pas"
        exit 2
    elif [[ "$1" != *.csv ]] ; then # verifie si $1 est un .CSV 
        echo "Ce n'est pas un fichier csv" 
        exit 3
    elif [ ! -f "data/$1" ]  ; then
        echo "data/$1 n'est pas un fichier" #verifie si c'est un fichier
        exit 4
    fi

# CHOIX DE TRAITEMENTS (D1, D2, L, T, S)
    #for i in `seq 1$#
    #varM=1
    #varC=1
    #for i in $@
    #do 
        #echo ${!i} affiche le nombre d'arguments
        #echo $i
        
        case $2 in 
            -D1)
                if [ ! -x D1.sh ] ; then
                    chmod +x D1.sh
                    ./D1.sh $1 
                else
                    ./D1.sh $1
                fi 
                ;;
            -D2)
                if [ ! -x $2 ] ; then
                    chmod +x $2
                    ./$2 $1 
                else
                    ./$2 $1
                fi 
                ;; #   $varM=1;; #equivalent du break
            -L)
                if [ ! -x $2 ] ; then
                    chmod +x $2
                    ./$2 $1 
                else
                    ./$2 $1
                fi 
                ;;  #    $1 $varC=1;;
            #-T) ... ;;
            #-S) ... ;;
            
           #if[ $varM -eq 1 ] ; then   
            #fi
        esac
    #done




