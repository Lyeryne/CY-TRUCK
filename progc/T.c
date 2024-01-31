#include "T.h"

int main() {
    FILE *chemin;
    char ligne[1024];

    creerVille *racine = NULL;

    chemin = fopen("data.csv", "r");
    if (chemin == NULL) {
        printf("Erreur d'ouverture de data");
        exit(24);
    }

    while (fgets(ligne, sizeof(ligne), chemin)) {
        char *sep;
        char *Colonnes[5];

        int colonne = 0;
        sep = strtok(ligne, ";");
        while (sep != NULL && colonne < 5) {
            Colonnes[colonne++] = sep;
            sep = strtok(NULL, ";");
        }

        if (colonne >= 4) {
            char *ville = Colonnes[3];

            if (strlen(ville) < NOMVILLE) {
                racine = ajouterVille(racine, ville);
            }
        }

        if (colonne >= 2 && atoi(Colonnes[1]) == 1 && colonne >= 3) {
            char *villeDepart = Colonnes[2];

            if (strlen(villeDepart) < NOMVILLE) {
                racine = ajouterVille(racine, villeDepart);
            }
        }
    }


    fclose(chemin);

    creerVille *maxVilles[NBR_VILLE];
    unsigned long int nbVillesMAX = 0;

    Prefixe(racine, maxVilles, &nbVillesMAX);

    qsort(maxVilles, nbVillesMAX, sizeof(creerVille *), compareTrajet);

    printf("Les villes les plus traversées sont : \n");
    for (unsigned long int i = 0; i < nbVillesMAX && i < NBR_VILLE; i++) {
        printf("%s : Traversée - %d fois \n", maxVilles[i]->nom, maxVilles[i]->CmptVille);
    }

    return 0;
    
}