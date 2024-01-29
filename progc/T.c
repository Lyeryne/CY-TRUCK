#include "T.h"


int main()
{

    pArbre a = NULL;
    pArbreF b = NULL;

    //chemin pour accéder aux données principales
    FILE *chemin1T = fopen("../temp/c2_data.txt", "r");
    //vérification que l'allocation a bien été faite
    if (chemin1T == NULL){
        printf("Erreur lors de l'ouverture du fichier 1\n");
        exit(1);
    }

    int ID_route;
    char* nomVilleDepart;
    char* nomVilleArrivee;
    //on récupere les données ligne par ligne du fichier data et on conserve les valeurs récupérées dans deux variables
    //routeID et distance
<<<<<<< HEAD
    while (fscanf(chemin1T, "%d;%s;%s\n", &ID_route, nomVilleDepart, nomVilleArrivee) == 3)
=======
    while (fscanf(chemin1T, "%d;%49[^;];%49[^\n]\n", &ID_route, nomVilleDepart, nomVilleArrivee) == 3)
>>>>>>> f346c4f9972cc509897c45aa28c5876c8d6a037a
    {
        //Verification de l'intégrité des données
        if (nomVilleDepart == NULL || nomVilleDepart[0] == '\0' || nomVilleArrivee == NULL || nomVilleArrivee[0] == '\0' || ID_route < 0) {

            printf("Données Corrompues");
            exit(66);
        }
        for(int i = 0; nomVilleDepart[i]!= '\0'; i++ ){
            if(isdigit(nomVilleDepart[i])){
                printf("Données corrompues, il y a un chiffre dans le nom de la ville de départ");
                exit(67);
            }
        }
        for(int i = 0; nomVilleArrivee[i]!= '\0'; i++ ){
            if(isdigit(nomVilleArrivee[i])){
                printf("Données corrompues, il y a un chiffre dans le nom de la ville d'arrivée");
                exit(68);
            }
        }
        //on crée un AVL petit a petit avec les valeurs de RouteId et des villes
        
        pVille VilleDepart = creerVille(nomVilleDepart, 1);
        pVille VilleArrivee = creerVille(nomVilleArrivee, 0);
        int compte = 0;

        int tab[SIZE4];
        for(int i = 0; i<= SIZE4;i++){
            tab[i] = 0;
        }
        int compteDebut = 0;
        a = TransfoArbreDebut(a, ID_route, VilleDepart, VilleArrivee, compte, tab, compteDebut);
    }
    //fermeture du fichier pour libérer des ressources
    fclose(chemin1T);
    //parcours l'arbre a et ajoute ses valeurs dans l'arbre b qui contiendra toutes les valeurs triées par traversées
    b = creationArbreFinal(a, b);
    //désallocation récursive de tout l'arbre manuellement
    libererArbre(a);
    //chemin pour accéder au fichier de sortie dans lequel on mettra les données utiles pour le script gnuplot
    FILE *chemin2T = fopen("../temp/gnuplot_data_T.txt", "w");
    //verification que l'allocation a bien été faite
    if (chemin2T == NULL)
    {
        printf("Erreur lors de l'ouverture du fichier 2\n");
        exit(1);
    }
    int i=0;
    //on parcours l'arbre dans l'ordre décroissant 
    infixeInverse(chemin2T, b, &i);
    //fermeture du fichier
    fclose(chemin2T);
    //désallocation récursive de l'arbre manuellement
    libererArbreF(b);

    return 0;
}