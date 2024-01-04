#include "S.h"


int main()
{

    pArbre a = NULL;
    pArbre b = NULL;

    FILE *chemin1 = fopen("../temp/c_data.txt", "r");
    if (chemin1 == NULL)
    {
        printf("Erreur lors de l'ouverture du fichier 1\n");
        exit(1);
    }

    int RouteID;
    float distance;
    while (fscanf(chemin1, "%d;%f\n", &RouteID, &distance) == 2)
    {
        int h = 0;
        a = insertionAVLTrajet(a, RouteID, distance, &h);
    }
    
    fclose(chemin1);
    b = creationArbreFinal(a, b);
    libererArbre(a);
    FILE *chemin2 = fopen("../temp/gnuplot_data_S.txt", "w");
    if (chemin2 == NULL)
    {
        printf("Erreur lors de l'ouverture du fichier 2\n");
        exit(1);
    }
    int i=0;
    infixeInverse(chemin2, b, &i);
    fclose(chemin2);
    libererArbre(b);

    return 0;
}