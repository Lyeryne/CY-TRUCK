#!/bin/bash
  
# Afficher le texte lettre par lettre avec un délai
displayTxt() {
  local text="$1"
  local delay1=100  # Délai entre chaque lettre en millisecondes

  # Codes d'échappement pour les couleurs
  local blue=$(tput setaf 4)      # Bleu
  local violet=$(tput setaf 5)    # Violet
  local reset=$(tput sgr0)        # Réinitialisation de la couleur

  for ((i=0; i<${#text}; i++)); do
    if [[ ${text:i:5} == "GROMU" ]]; then
      echo -n -e "${blue}${text:i:5}${reset}"
      ((i+=4))  # Avancer de 4 caractères après "GROMU"
    elif [[ ${text:i:9} == "EVA QUEEN" ]]; then
      echo -n -e "${violet}${text:i:9}${reset}"
      ((i+=8))  # Avancer de 8 caractères après "EVA QUEEN"
    else
      echo -n "${text:i:1}"
    fi
    sleep 0.$delay1  # Délai en secondes
  done

  echo  # Retour à la ligne après l'affichage complet
}

displayTxt "BIENVENUE GROMU ET EVA QUEEN (;"
