#include "T.h"


int main()
{

    pArbre a = NULL;
    pArbre b = NULL;

    //chemin pour accéder aux données principales
    FILE *chemin1 = fopen("../temp/c2_data.txt", "r");
    //vérification que l'allocation a bien été faite
    if (chemin1 == NULL){
        printf("Erreur lors de l'ouverture du fichier 1\n");
        exit(1);
    }

    int ID_route;
    char nomVille;
    //on récupere les données ligne par ligne du fichier data et on conserve les valeurs récupérées dans deux variables
    //routeID et distance
    while (fscanf(chemin1, "%d;%f\n", &ID_route, &nomVille) == 2)
    {
        //Verification de l'intégrité des données
        if(nomVille == NULL || nomVille[0] =='\O' || ID_route < 0){
            printf("Données Corrompues");
            exit(66);
        }
        for(int i = 0; nomVille[i]!= '\0'; i++ ){
            if(isdigit(nomVille[i])){
                printf("Données corrompues, il y a un chiffre dans le nom de la ville");
                exit(67);
            }
        }
        //on crée un AVL petit a petit avec les valeurs de RouteId et de distance
        int h = 0;
        a = insertionAVLDEBUT(a, RouteID, distance, compte, tab[], &h);
    }
    //fermeture du fichier pour libérer des ressources
    fclose(chemin1);
    //parcours l'arbre a et ajoute ses valeurs dans l'arbre b qui contiendra toutes les valeurs triées par distance max - distance min
    b = creationArbreFinal(a, b);
    //désallocation récursive de tout l'arbre manuellement
    libererArbre(a);
    //chemin pour accéder au fichier de sortie dans lequel on mettra les données utiles pour le script gnuplot
    FILE *chemin2 = fopen("../temp/gnuplot_data_S.txt", "w");
    //verification que l'allocation a bien été faite
    if (chemin2 == NULL)
    {
        printf("Erreur lors de l'ouverture du fichier 2\n");
        exit(1);
    }
    int i=0;
    //on parcours l'arbre dans l'ordre décroissant 
    infixeInverse(chemin2, b, &i);
    //fermeture du fichier
    fclose(chemin2);
    //désallocation récursive de l'arbre manuellement
    libererArbre(b);

    return 0;
}