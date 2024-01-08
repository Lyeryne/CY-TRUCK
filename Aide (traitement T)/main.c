#include "AVLt.h"
#include "AVLt.c"
#include <stdio.h>
#include <stdlib.h>

// Fonction pour lire le fichier et insérer les données dans l'arbre1
  void insererDepuisFichier(pArbre arbre, const char *nomFichier) {
      FILE *fichier = fopen(nomFichier, "r");

      if (fichier == NULL) {
          perror("Erreur lors de l'ouverture du fichier");
          exit(EXIT_FAILURE);
      }

      int idtrajet;
      float distance;

      // Lecture des données du fichier et insertion dans l'arbre1
      while (fscanf(fichier, "%d;%f", &idtrajet, &distance) == 2) {
          int h = 0;
          arbre = insertionT(arbre, idtrajet, distance, &h);
      }

      // Fermeture du fichier
      fclose(fichier);
  }


int main() {
    pArbre ArbreT = NULL;  // Initialisation de l'arbre
    pArbre ArbreD = NULL;  // Initialisation de l'arbre

    // Remplacez "nom_du_fichier.txt" par le nom réel de votre fichier texte
    insererDepuisFichier(ArbreT, "test.txt");
    CopieEtInsertionD(ArbreT, ArbreD);
    afficherArbre(ArbreT);
    afficherArbre2(ArbreD);


  
    return 0;
}
