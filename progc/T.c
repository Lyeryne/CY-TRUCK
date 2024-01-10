#include "T.h"


FILE *chemin1 = fopen("../temp/c_data.txt", "r");
    //vérification que l'allocation a bien été faite
    if (chemin1 == NULL)
    {
        printf("Erreur lors de l'ouverture du fichier 1\n");
        exit(1);
    }

    int RouteID;
    float distance;
    
