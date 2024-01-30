#include "S.h"


int main()
{

    pArbre a = NULL;
    pArbre b = NULL;
    int RouteID;
    float distance;

    //chemin pour accéder aux données principales
    FILE *chemin1 = fopen("../temp/c1_data.txt", "r");
    //vérification que l'allocation a bien été faite
    if (chemin1 == NULL)
    {
        printf("Erreur lors de l'ouverture du fichier 1\n");
        exit(1);
    }


    //on récupere les données ligne par ligne du fichier data et on conserve les valeurs récupérées dans deux variables
    //routeID et distance
    while (fscanf(chemin1, "%d;%f\n", &RouteID, &distance) == 2)
    {
        //Verification de l'intégrité des données
        if(distance < 0.0 || distance > 1999.9 || RouteID < 0){
            printf("Données Corrompues");
            exit(66);
        }
        //on crée un AVL petit a petit avec les valeurs de RouteId et de distance
        int h = 0;
        a = insertionAVLTrajet(a, RouteID, distance, &h);
    }



    //fermeture du fichier pour libérer des ressources
    fclose(chemin1);
    //parcours l'arbre a et ajoute ses valeurs dans l'arbre b qui contiendra toutes les valeurs triées par distance max - distance min
    b = creationArbreFinal(a, b);
    //désallocation récursive de tout l'arbre manuellement
    libererArbre(a);
    
    int i=0;
    //on parcours l'arbre dans l'ordre décroissant 
    infixeInverse(b, &i);

    //désallocation récursive de l'arbre manuellement
    libererArbre(b);

    return 0;
}