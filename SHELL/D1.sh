#!/bin/bash

if [ $# -ne 1 ] ; then
    echo "Tu dois utiliser qu'un argument" >&2
    exit 1
<<<<<<< HEAD
   
    elif [ $1 -ne 'data.csv' ] || [ ! -f $1 ] || [ ! -e $1 ]; then #question : est ce que le fichier .csv se nommera data.csv
        echo "Ce n'est pas le fichier qu'on attend" >&2
        exit 2
fi

#question : Pourquoi utiliser cut si on a AWK

colonne

=======
elif [ $1 -ne "data.csv" ] || [ ! -f $1 ] || [ ! -e $1 ]; then
    echo "Ce n'est pas le fichier qu'on attend" >&2
    exit 2
fi

trajets=`awk -F';' '{if(NR>1) count[$6]++} END {for (person in count) print person, count[person]}' data.csv`
echo "$trajets"
>>>>>>> 71e112d (oui)
