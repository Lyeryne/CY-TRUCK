# Gnuplot script (gnuplot_script_D1.gnu)

# Définition du style de sortie
set terminal pngcairo enhanced font 'arial,10' size 1000,600
set output 'images/output_D1.png'

# Séparateur pour le using
set datafile separator ";"

# Titre du graphique
set title 'Option -d1 : Nb routes = f(Driver)'

# Style de la barre 
set style data histograms 
set style fill solid border -1

# Enlever la légende
unset key

# Ajustement de la largeur des colonnes et positionnement à gauche
set boxwidth 1.0 absolute
set style histogram cluster gap 1

# Axe X
set xlabel 'DISTANCE (Km)'
set ylabel 'DRIVER NAMES'

# Ajustement de l'intervalle de l'axe y
set xrange [0:250]

# Ajustement des xtics
set xtics rotate by 0
set ytics rotate by 0

# Utilisation de l'axe x1 pour les étiquettes (colonne 1)
set x2tics rotate by 0
set format x2""

# Utilisation de l'axe x2 pour les étiquettes (colonne 1)
set y2tics rotate by 0
set format y2 ""

# Charger les données depuis le fichier temporaire
plot 'demo/gnuplot_data_D1.txt' using ytic(1):2 with boxes title 'Distance' axes x2y2
