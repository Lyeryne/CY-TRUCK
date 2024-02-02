#!/bin/bash

gnuplot << EOF
# Determination du style de sortie
set terminal pngcairo enhanced font 'arial,10' size 1100,700
set output 'images/output_T.png'

# Titre du graphique 
set title 'set title "Option -t : Nb routes = f(Villes)"'

# Axe X
set xlabel 'Villes'

# Axe Y
set ylabel 'Nombre de trajets'

# Rotation des numéros de l'axe x de 45 degrés
set xtics rotate by -45 

# Ajustement de l'intervalle de l'axe Y
set autoscale y
set yrange [0:*]

# separateur
set datafile separator ";"

# Définition du style des barres
set style data histograms

# Ajustement de la largeur des colonnes
set boxwidth 3

# Style de la barre
set style histogram clustered gap 7
set style fill solid 1.00 border 0

# Tracé de l'histogramme
plot 'temp/gnu_data_T.txt' using 2:xtic(1) title 'Trajets totales', '' using 3 lc rgb "#207523" title 'Trajets de départ'
EOF