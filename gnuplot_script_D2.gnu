# Gnuplot script (gnuplot_script_D2.gnu)

# Définition du style de sortie
set terminal pngcairo enhanced font 'arial,10' size 800,600
set output 'images/output_D2.png'

# Titre du graphique
set title 'Option -d2 : Distance = f(Driver)'

# Style de la barre
set style data histograms
set style fill solid border -1

# Ajustement de la largeur des colonnes
set boxwidth 2.0

# Axe X
set xtics rotate by -45
set xlabel 'DISTANCE (Km)'
set ylabel 'DRIVER NAMES'

# Ajustement de l'intervalle de l'axe y
set xrange [0:1600]

# Charger les données depuis le fichier temporaire
plot 'demo/gnuplot_data_D2.txt' using ???:??? with histograms title 'Distance'