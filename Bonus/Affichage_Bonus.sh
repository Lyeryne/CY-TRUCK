#!/bin/bash

# Fonction permettant de calculer les émissions de CO2 avec le nombre de trajets
  calcul_ges() 
  {
    local consommation_moyenne=8 # On suppose que chaque camion consomme en moyenne 8L de diesel par 100 km
    local taux_emission_par_litre=3 # On suppose ensuite un taux d'émission moyen de 2,7 (arrondi à 3) kg de CO2 par L de diesel
    # On recupére le premier conducteur ayant fait le plus de trajets
    local nombre_trajets=$(head -1 ../temp/gnu_data_D1.txt | cut -f2 -d';')  

    # On suppose que chaque trajet a une distance moyenne de 100 km 
    local distance_moyenne=100

    # On calcule la distance totale parcourue
    local distance_totale=$((nombre_trajets * distance_moyenne))

    # Ensuite on calcul les émissions de CO2
    local emissions_co2=$((distance_totale * consommation_moyenne * taux_emission_par_litre / 100))

    echo
    echo "Remarque :"
    echo "Le premier conducteur pour $nombre_trajets trajets a consommé un taux de $emissions_co2 kg de CO2"
    echo "Il faudrait réduire les déplacements !"
  }

# Fonction permettant de calculer les émissions de CO2 avec la distance totale parcourue
  calcul_distance_ges() 
  {
    local consommation_moyenne=8 # En litres par 100 km
    local taux_emission_par_litre=3 # En kg de CO2 par litre de diesel
    
    # On récupère le premier conducteur ayant fait la plus grande distance
    local distance_totale=$(LC_NUMERIC=en_US.UTF-8 head -1 ../temp/gnu_data_L.txt | cut -f2 -d';' | cut -d'.' -f1)  
    local id_route=$(head -1 ../temp/gnu_data_L.txt | cut -f1 -d';')
    
    # Ensuite, on calcule les émissions de CO2
    local emissions_co2=$((distance_totale * consommation_moyenne * taux_emission_par_litre / 100))
    
    # Affichage du résultat
    echo
    echo "Remarque :"
    echo "L'ID route > $id_route pour une distance totale de $distance_totale km consommera $emissions_co2 kg de Co2."
    echo "Il faudra utiliser un camion qui consomme moins"
  }

# Fonction pour calculer le temps de conduite
  calcul_temps() 
  {
    # On recupére le premier conducteur ayant fait la plus grande distance parcourue
    local distance_totale=$(LC_NUMERIC=en_US.UTF-8 head -1 ../temp/gnu_data_D2.txt | cut -d';' -f2 | cut -d'.' -f1)

    # On suppose que le conducteur à une vitesse moyenne de 90 km/h
    local vitesse_moyenne=90
    local temps_de_conduite=$((distance_totale / vitesse_moyenne / 24))  # Conversion du temps de conduite en jours

    echo
    echo "Remarque :"
    echo "Le premier conducteur pour $distance_totale km parcourue, lui a fait un temps de conduite estimé à environ $temps_de_conduite jours"
    echo "Il a de la patience..."
  }

# Conditions pour déterminer quelle fonction appeler
  if [ "$1" == "calcul_ges" ]; then
    calcul_ges
  elif [ "$1" == "calcul_temps" ]; then
    calcul_temps
  elif [ "$1" == "calcul_distance_ges" ] ; then
    calcul_distance_ges
  fi

