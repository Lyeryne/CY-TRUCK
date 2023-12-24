# Gnuplot script (gnuplot_script_D2.gnu)

# Définition du style de sortie
set terminal pngcairo enhanced font 'arial,10' size 1000,600
set output 'images/output_D2.png'

# Titre du graphique
set title 'Option -d2 : Distance = f(Driver)'

# Style de la barre
set style data histograms
set style fill solid border -1

# Enlever la legende
unset key

# Ajustement de la largeur des colonnes
set boxwidth 2.0

# Axe X
set ytics rotate by -0
set xlabel 'DISTANCE (Km)'
set ylabel 'DRIVER NAMES'

# Ajustement de l'intervalle de l'axe y
set xrange [0:16000]

# separateur pour le using
set datafile separator ";"

# Charger les données depuis le fichier temporaire
plot 'demo/gnuplot_data_D2.txt' using (column(0)):2:ytic(1) with histograms title 'Distance', \
     '' using (column(0)):(0):(sprintf("%.6f", column(2))) with labels offset -1.5,0.5 notitle