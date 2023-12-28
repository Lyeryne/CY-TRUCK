#!/bin/bash

gnuplot << EOF
# Définition du style de sortie avec rotation
set terminal pngcairo enhanced font 'arial,15' size 1100,1000
set output 'images/output_D2.png'

# Séparateur pour le using
set datafile separator ";"

# Titre du graphique
set ylabel 'Option -d2 : Distance = f(Driver)'

# Style de la barre 
set style data histogram
set style fill solid border -1

# Enlever la légende
unset key

# Ajustement de la largeur des colonnes et positionnement à gauche
set style histogram cluster gap 1
set boxwidth 1.6

# Axe X
set xlabel 'DRIVER NAMES' rotate by 180
set y2label 'DISTANCE (Km)'

# Ajustement des xtics
set xtics rotate 
set y2range [0:160000]

# Ajustement des y2tics
set y2tics rotate 
unset ytics;set y2tics mirror

# Charger les données depuis le fichier temporaire
plot 'temp/gnuplot_data_D2.txt' using 2:xticlabels(1) axes x1y2 notitle linecolor 2 lt 1
EOF

convert -rotate 90 images/output_D2.png images/output_D2.png
