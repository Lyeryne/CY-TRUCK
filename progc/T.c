#include "T.h"
int main() {
    FILE *chemin;

    creerVille *racine = NULL;

    chemin = fopen("../roman/c2_data.txt", "r");
    if (chemin == NULL) {
        printf("Erreur d'ouverture de data C2");
        exit(1);
    }
    
    int IDR = 0;
    int dbt = 0;
    char *villeDepart = malloc(sizeof(char)*150);
    if(villeDepart == NULL){
        exit(66);
    }
    char *villeArrivee = malloc(sizeof(char)*150);
    if(villeArrivee == NULL){
        exit(67);
    }
    
    while (fscanf(chemin, "%d;%d;%49[^;];%49[^\n]\n", &IDR, &dbt, villeDepart, villeArrivee) == 4)
    {
        if(villeDepart == NULL || villeArrivee == NULL){
            printf("constant error");
            exit(2);
        }
        int h1 = 0;
        int h2 = 0;
        racine = insertionAVLDebut(racine, villeDepart, dbt, IDR, &h1);
        racine = insertionAVLDebut(racine, villeArrivee, 2, IDR, &h2);
    }
    
    
    creerVille* b = NULL;
    b = creationArbreFinal2(racine ,b);  

    fclose(chemin);
    
    char* nom = malloc(sizeof(150));
    if(nom == NULL){
        exit(66);
    }
    char* nom2 = malloc(150);
    if(nom2 == NULL){
        exit(66);
    }
    int debut, debut2;
    int CompteurVille, CompteurVille2;
    creerVille *c = NULL;
    for(int i = 0; i<10; i++){
        b = suppression(b, &nom, &CompteurVille, &debut, &nom2, &CompteurVille2, &debut2);
        int h = 0;
        c = insertionABRVraimentFinal(c, nom2, CompteurVille2, debut2);
    }
    infixe(c);
    return 0;
    
}