#!/bin/bash

gnuplot << EOF
# Determination du style de sortie
set terminal pngcairo enhanced font 'arial,10'
set output 'images/output_S.png'

# Titre du graphique 
set title 'Option -s: Distance = f(Route)'

# Axe X
set xlabel 'ROUTE ID'

# Axe Y
set ylabel 'DISTANCE(Km)'

# Ajustement de l'intervalle de l'axe Y
set yrange [0:1000]

# separateur pour le using
set datafile separator ";"

# Utilisation d'ID du trajet pour l'axe x et de la distance minimale, maximale et moyenne pour l'axe y
plot 'temp/gnu_data_S.txt' using 1:2:3:4:xticlabels(1) with yerrorbars title 'Distance Min', \
     '' using 1:4:4 with lines title 'Distance Moyenne', \
     '' using 1:5:5 with lines title 'Distance Max'
EOF