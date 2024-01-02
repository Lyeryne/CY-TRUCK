#!/bin/bash
  
# Explication :
  # - "${text:i:1}" : Cela extrait le caractère à la position actuelle 'i' dans la variable 'text'.
  #                   - 'i' est l'indice courant dans la boucle, donc cela récupère la lettre courante.
  #                   - ':1' spécifie la longueur de la sous-chaîne extraite, ici un seul caractère.
  # - 'local' est utilisé pour déclarer une variable locale, limitant sa portée à la fonction actuelle.
  # - 'tput setaf' pour définir la couleur du texte.
  # - L'option '-n' d'echo est utilisée pour empêcher l'ajout automatique d'un saut de ligne.
  # Cela permet d'afficher chaque lettre sur la même ligne pendant l'animation.

# Utilisation du format "${variable:start:length}" pour extraire une sous-chaîne.
# C'est une fonctionnalité de paramétrage de chaîne dans Bash.

# Fonction pour afficher le texte lettre par lettre avec un délai
AffichageTxt() {
  local text="$1" # Texte à afficher
  local delay1=100  # Délai entre chaque lettre en millisecondes

  # Codes d'échappement pour les couleurs
  local blue=$(tput setaf 4) # Bleu
  local violet=$(tput setaf 5) # Violet
  local reset=$(tput sgr0) # Réinitialisation de la couleur

  for ((i=0; i<${#text}; i++)); do
    # Vérifier si le texte contient "GROMU" et afficher en bleu
    if [[ ${text:i:5} == "GROMU" ]]; then
      echo -n -e "${blue}${text:i:5}${reset}"
      ((i+=4)) # Avancer de 4 caractères après "GROMU"
    # Vérifier si le texte contient "EVA QUEEN" et afficher en violet
    elif [[ ${text:i:9} == "EVA QUEEN" ]]; then
      echo -n -e "${violet}${text:i:9}${reset}"
      ((i+=8)) # Avancer de 8 caractères après "EVA QUEEN"
    else
      echo -n "${text:i:1}" # Afficher la lettre courante
    fi
    sleep 0.$delay1 # Délai en secondes
  done

  echo  # Retour à la ligne après l'affichage complet
}

