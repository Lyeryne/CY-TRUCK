# Définition du style de sortie
set terminal pngcairo enhanced font 'arial,15' size 900,700
set output 'images/output_L.png'

# Titre du graphique
set title 'Option -l : Distance = f(Route)'

# Style de la barre
set style data histograms
set style fill solid border -1

# Ajustement de la largeur des colonnes
set boxwidth 2.0

# Axe X
set xtics rotate by -0
set xlabel 'ROUTE ID'
set ylabel 'DISTANCE(km)'

# Ajustement de l'intervalle de l'axe y
set yrange [0:3000] 

# Charger les données depuis le fichier temporaire
plot 'demo/gnuplot_data_L.txt' using 2:xtic(1) with histograms title 'Distance'
