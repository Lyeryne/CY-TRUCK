#!/bin/bash

# Compilation du programme C

make -C progc

# Exécution du programme C avec le fichier en argument
cut -d";" -f1,5 "data/$1" | tail -n +2 > temp/c_data.txt
./Projet
cat "temp/gnuplot_data_S.txt" | head -50

# Exécution du script Gnuplot
file="gnuplot_script_S.sh"
if [ ! -x "$file" ] ; then
    chmod +x gnuplot_script_S.sh
    ./gnuplot_script_S.sh
else
    ./gnuplot_script_S.sh
fi

