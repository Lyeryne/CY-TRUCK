#!/bin/bash

# Copie du fichier de données dans le dossier 'data'
#cp data/datafile.txt data/

# Appel du programme C pour le traitement des 10 villes les plus traversées
#progc/process_data -t data/datafile.txt temp/top_cities.txt

# Génération du graphique à partir des résultats
gnuplot <<EOF
set terminal png
set output "images/output_T.png"
set style data histograms
set style histogram clustered
set style fill solid border -1
set boxwidth 0.8
set xtic scale 0
set ytic auto
plot "temp/gnu_data_T.txt" using 2:xticlabels(1) title 'Total Traversals', '' using 3 title 'Departures'
EOF