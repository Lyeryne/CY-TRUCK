#include "T.h"
int main() {
    FILE *chemin;//création du fichier

    creerVille *racine = NULL;//création de l'arbre

    chemin = fopen("../temp/c2_data.txt", "r");//récupération des données dans le fichier
    if (chemin == NULL) {//robustesse : on vérifie que les données sont bien récupérées
        printf("Erreur d'ouverture de data C2");
        exit(1);
    }
    //on initialise l'IDroute, le valeur de début et les deux noms de ville avec de la robustesse
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
    
    while (fscanf(chemin, "%d;%d;%49[^;];%49[^\n]\n", &IDR, &dbt, villeDepart, villeArrivee) == 4)//remplissage des variables du dessus
    {
        if(villeDepart == NULL || villeArrivee == NULL){//robustesse : on vérifie si les villes sont bien remplies
            printf("constant error");
            exit(2);
        }
        int h1 = 0;//hauteur 1
        int h2 = 0;//hauteur 2
        racine = insertionAVLDebut(racine, villeDepart, dbt, IDR, &h1);//création de l'arbre avec ces valeurs insérées dans le noeud x2
        racine = insertionAVLDebut(racine, villeArrivee, 2, IDR, &h2);
    }
    
    
    creerVille* b = NULL;//création de l'arbre trié selon le nombre de trajets
    b = creationArbreFinal2(racine ,b);  
        
    //désallocation récursive de tout l'arbre manuellement
    libererArbre(racine);
    libererCompteID(racine->ID_ville);

    fclose(chemin);//fermeture du fichier
    //insertion des 10 plus grandes valeurs dans l'arbre final trié par ordre alphabétique
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
        b = suppression(b, &nom, &CompteurVille, &debut, &nom2, &CompteurVille2, &debut2);//suppression et ajout de l'arbre dans l'autre pour les 1à plus grandes valeurs
        int h = 0;
        c = insertionABRVraimentFinal(c, nom2, CompteurVille2, debut2);
    }

    //désallocation récursive de tout l'arbre manuellement
    libererArbre(b);
    libererCompteID(b->ID_ville);

    infixe(c);//parcours de l'arbre trié dans l'ordre alphabétique

    //désallocation récursive de tout l'arbre manuellement
    libererArbre(c);
    libererCompteID(c->ID_ville);

    return 0;
    
}