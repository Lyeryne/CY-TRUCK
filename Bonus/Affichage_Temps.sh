#!/bin/bash

# Variable pour indiquer si le compte à rebours doit être arrêté
STOP_COMPTEUR=false

# Fonction pour arrêter le compte à rebours
stop_compteur() {
    STOP_COMPTEUR=true
    exit 0
}

# Capture du signal SIGUSR1 pour arrêter le compte à rebours
# -SIGUSR1 : Argument utilisé avec la commande kill/trap pour spécifier le signal que nous souhaitons envoyer, 
# Ici, -SIGUSR1 signifie "envoyer le signal SIGUSR1" qui sera capturé par la fonction trap, 
# puis ira à la fonction 'stop_compteur' et provoquera l'arrêt. 
# Conclusion : Lorsqu'un signal SIGUSR1 est reçu, la fonction stop_compteur doit être exécutée
trap 'stop_compteur' SIGUSR1

# Affichage du compte à rebours
AffichageTemps() {
    for ((i = 0; i <= 100; i++)) ; do
        printf "LANCEMENT DES TRAITEMENTS (PENSEZ À JETER UN COUP D'ŒIL SI L'UN DES TRAITEMENTS EST FINI) %d%%\r" $i # (\r) permet de revenir en début de ligne
        if [ $i -eq 100 ] || [ "$STOP_COMPTEUR" = true ] ; then
            break
        fi
        sleep 0.3  # suspend l'exécution du programme pendant 0.3 s pour l'effet
    done
}

# Lancement de la fonction 
AffichageTemps 
