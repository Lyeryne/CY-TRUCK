#!/bin/bash

gnuplot << EOF
# Determination du style de sortie
set terminal pngcairo enhanced font 'arial,10' size 1100,700
set output 'images/output_T.png'

# Titre du graphique 
set title 'Histogramme des trajets par ville'

# Axe X
set xlabel 'Villes'

# Axe Y
set ylabel 'Nombre de trajets'

# Graduation de l'axe Y tous les 10
set ytics 10

# Rotation des numéros de l'axe x de 45 degrés
set xtics rotate by 45 right

# Ajustement de l'intervalle de l'axe Y
set yrange [0:*]

# separateur pour le using
set datafile separator ";"

# Définition du style des barres
set style data histogram
set style histogram clustered
set style fill solid border -1

# Chargement des données depuis le fichier CSV
#stats datafile using 1 nooutput
#stats datafile using 2 nooutput

# Affichage des 10 premières lignes du fichier pour débogage
#print "Contenu du fichier :"
#system("head -n 10 gnu_data_T.txt.csv")

# Tracé de l'histogramme
plot 'temp/gnu_data_T.txt' using 3:xticlabels(4) title 'Trajets totaux', \
     '' using 3:xticlabels(4) title 'Trajets de départ'
EOF
