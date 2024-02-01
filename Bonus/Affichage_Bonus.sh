#!/bin/bash

# Fonction pour calculer les émissions de CO2
calcul_ges() {
  local consommation_moyenne=8          # Supposons que chaque camion consomme en moyenne 8 litres de diesel par 100 kilomètres
  local taux_emission_co2_par_litre=2.7 # Supposons un taux d'émission moyen de 2,7 kg de CO2 par litre de diesel
  local nombre_trajets=$(head -1 temp/gnu_data_D1.txt | cut -f2 -d';')  # Recuperer la ligne 1 et prendre le nombre de trajets effectués

  # Supposons que chaque trajet a une distance moyenne de 50 kilomètres
  local distance_moyenne=50

  # Calculer la distance totale parcourue
  local distance_totale=$((nombre_trajets * distance_moyenne))

  # Calculer les émissions de CO2
  local emissions_co2=$((distance_totale * consommation_moyenne * taux_emission_co2_par_litre / 100))

  echo "Le premier conducteur pour $nombre_trajets trajets a un taux de $emissions_co2 kg de CO2"
  echo "Il faudrait réduire les déplacements !"
}

# Appeler la fonction
calcul_ges
