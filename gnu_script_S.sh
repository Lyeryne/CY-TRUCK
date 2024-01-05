#!/bin/bash

gnuplot << EOF
# Determination du style de sortie
set terminal pngcairo enhanced font 'arial,10' size 1100,700
set output 'images/output_S.png'

# Titre du graphique 
set title 'Option -s: Distance = f(Route)'

# Axe X
set xlabel 'ROUTE ID'

# Axe Y
set ylabel 'DISTANCE(Km)'

# Graduation de l'axe Y tous les 100
set ytics 100

# Rotation des numéros de l'axe x de 45 degrés
set xtics rotate by 45 right

# Ajustement de l'intervalle de l'axe Y
set yrange [0:1000]

# separateur pour le using
set datafile separator ";"


# Tracé de la zone entre Min et Max (remplissage en vert)
plot 'temp/gnu_data_S.txt' using 0:3:5:xticlabels(2) with filledcurves linecolor 2 lt 1 title 'Distances Max (Km))', \
     '' using 0:4 with lines linecolor 0 title 'Distance average (Km)'
EOF