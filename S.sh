#!/bin/bash

if [ $# -ne 1 ] ; then # verifie de n'utiliser qu'un arg
    echo "Tu dois utiliser qu'un argument" 
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


gcc -o exe progc/S.c
res=$(cut -f1,5 "data/$1" > ./exe)



# si le dossier 'demo' n'existe pas alors on le mkdir
if [ ! -e demo ] ; then 
    mkdir demo
fi
# si le dossier 'images' n'existe pas alors on le mkdir
if [ ! -e images ] ; then 
    mkdir images
fi