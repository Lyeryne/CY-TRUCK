#!/bin/bash



gcc -o exe progc/t.c -lm
#$(cut -f1,5 "data/$1" > ./exe) > temp/gnuplot_data_T.txt

# Exécution du script Gnuplot
file="gnuplot_script_T.sh"
if [ ! -x "$file" ] ; then # verifie si le fichier a la permission d'exécution
    chmod +x gnuplot_script_T.sh
    ./gnuplot_script_T.sh # on lance le script
else
    ./gnuplot_script_T.sh
fi