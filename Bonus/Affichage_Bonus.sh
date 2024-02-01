#!/bin/bash

# Fonction pour calculer les émissions de CO2
calcul_ges() {
  local consommation_moyenne=8          # Supposons que chaque camion consomme en moyenne 8 litres de diesel par 100 kilomètres
  local taux_emission_par_litre=3      # Supposons un taux d'émission moyen de 2,7 (arrondi à 3) kg de CO2 par litre de diesel
  local nombre_trajets=$(head -1 ../temp/gnu_data_D1.txt | cut -f2 -d';')  # Recuperer la ligne 1 et prendre le nombre de trajets effectués

  # Supposons que chaque trajet a une distance moyenne de 50 kilomètres
  local distance_moyenne=50

  # Calculer la distance totale parcourue
  local distance_totale=$((nombre_trajets * distance_moyenne))

  # Calculer les émissions de CO2
  local emissions_co2=$((distance_totale * consommation_moyenne * taux_emission_par_litre / 100))

  echo
  echo "Remarque :"
  echo "Le premier conducteur pour $nombre_trajets trajets a un taux de $emissions_co2 kg de CO2"
  echo "Il faudrait réduire les déplacements !"
}


# Fonction pour calculer le temps de conduite
calcul_temps() {
  LC_NUMERIC=en_US.UTF-8
  # Récupérer la distance totale parcourue (supposons que cela soit en kilomètres)
  local distance_totale=$(LC_NUMERIC=en_US.UTF-8 head -1 ../temp/gnu_data_D2.txt | cut -d';' -f2 | cut -d'.' -f1)

  # Estimer le temps de conduite en fonction d'une vitesse moyenne (supposons 60 km/h)
  local vitesse_moyenne=60
  local temps_de_conduite=$((distance_totale / vitesse_moyenne / 24))  # Convertir le temps de conduite en jours

  echo
  echo "Remarque :"
  echo "Le premier conducteur pour $distance_totale km parcourue, lui a fait un temps de conduite estimé à environ $temps_de_conduite jours"
  echo "J'espère qu'il a pu bien voyager..."
}

# Si le script est inclus dans un autre script, vérifier le paramètre pour déterminer quelle fonction appeler
  if [ "$1" == "calcul_ges" ]; then
    calcul_ges
  elif [ "$1" == "calcul_temps" ]; then
    calcul_temps
  fi

