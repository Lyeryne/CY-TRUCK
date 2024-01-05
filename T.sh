#!/bin/bash

# Compilation du programme C
make -C progc

# Exécution du programme C avec le fichier en argument
cut -d";" -f1,5 "data/$1" | tail -n +2 > temp/c_data_T.txt
cd progc
./Projet

#aide
echo "Le répertoire actuel est : $(pwd)"
cd .. 
echo "Le répertoire actuel est : $(pwd)"

#head -n 50 "temp/gnuplot_data_T.txt" > "temp/gnu_data_T.txt"
rm -f "temp/c_data_T.txt"
rm -f "temp/gnuplot_data_T.txt" 

# Exécution du script Gnuplot
file="gnu_script_T.sh"
if [ ! -x "$file" ] ; then
    chmod +x gnu_script_T.sh
    ./gnu_script_T.sh
else
    ./gnu_script_T.sh
fi

