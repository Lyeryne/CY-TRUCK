#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <ctype.h>

#define SIZE1 4
#define SIZE2 50
#define SIZE3 5
#define SIZE4 500
#define ALLOC_ERROR 77
#define ALLOC_ERROR_2 78

typedef struct{
    char* nomVille;
    int Debut;
} Ville;


typedef struct _b{
    int ID_route;
    struct _b *fg;
    struct _b *fd;
    int equilibre;
    char* nomVille;
    int tab[SIZE4];
    int compte;
    int compteDebut;
} Arbre;

typedef struct _a{
    int ID_route;
    struct _a *fg;
    struct _a *fd;
    int equilibre;
    char* nomVille;
    int compte;
    int compteDebut;
} ArbreF;

typedef struct {
    int ID_route;
    char* nomVille;
} insertVille;

typedef ArbreF* pArbreF;
typedef Ville* pVille;
typedef Arbre* pArbre;

pArbreF creerArbreFinal(int ID_route, char* nomVille, int compte, int compteDebut);

pArbreF creationArbreFinal(pArbre a, pArbreF b);

void infixeInverse(FILE* chemin, pArbreF a, int *i);

pArbre insertionAVLDEBUT(pArbre a, int ID_route, pVille nomVille, int compte ,int tab[], int compteDebut, int *h);

void libererArbreF(pArbreF a);

void libererArbre(pArbre a);

pArbre TransfoArbreDebut(pArbre a, int ID_route, pVille nomVilleDepart, pVille nomVilleArrivee, int compte, int tab[], int compteDebut);

pArbre creationArbreDebut(int ID_route, pVille nomVille, int compte, int tab[], int compteDebut);

int min(int a, int b);

int max(int a, int b);

int existeFilsDroit(pArbre a);

pArbreF insertionAVLFINAL(pArbreF a, int ID_route, char* nomVille, int compte, int compteDebut, int *h);

pArbre rotationGauche(pArbre a);

pArbre rotationDroit(pArbre a);

pArbreF rotationGaucheF(pArbreF a);

pArbreF rotationDroitF(pArbreF a);

pArbre doubleRotationGauche(pArbre a);

pArbre doubleRotationDroit(pArbre a);

pArbreF doubleRotationGaucheF(pArbreF a);

pArbreF doubleRotationDroitF(pArbreF a);

pArbre equilibrerAVL(pArbre a);

pArbreF equilibrerAVLF(pArbreF a);

pArbre equilibrerAVL(pArbre a)
{
    //fonction pour équilibrer l'AVL en fonction du facteur d'equilibrage 
    if (a == NULL)
    {
        exit(ALLOC_ERROR);
    }
    if (a->equilibre >= 2)
    {
        if (a->fd->equilibre >= 0)
        {
            return rotationGauche(a);
        }
        else
        {
            return doubleRotationGauche(a);
        }
    }
    else if (a->equilibre <= -2)
    {
        if (a->fg->equilibre <= 0)
        {
            return rotationDroit(a);
        }
        else
        {
            return doubleRotationDroit(a);
        }
    }
    return a;
}


pArbreF equilibrerAVLF(pArbreF a)
{
    //fonction pour équilibrer l'AVL en fonction du facteur d'equilibrage 
    if (a == NULL)
    {
        exit(ALLOC_ERROR);
    }
    if (a->equilibre >= 2)
    {
        if (a->fd->equilibre >= 0)
        {
            return rotationGaucheF(a);
        }
        else
        {
            return doubleRotationGaucheF(a);
        }
    }
    else if (a->equilibre <= -2)
    {
        if (a->fg->equilibre <= 0)
        {
            return rotationDroitF(a);
        }
        else
        {
            return doubleRotationDroitF(a);
        }
    }
    return a;
}

pVille creerVille(char* nom, int num){
    pVille a = malloc(sizeof(Ville));
    if (a == NULL)
    {
        exit(ALLOC_ERROR_2);
    }
    a->nomVille = nom;
    a->Debut = num;
    return a;
}

pArbre creationArbreDebut(int ID_route, pVille nVille, int compte, int tab[], int compteDebut)
{
    //crée l'arbre pour le premier AVL, distance, min et max prendront la valeur de distance, et le retourne
    pArbre a = malloc(sizeof(Arbre));
    if (a == NULL)
    {
        exit(ALLOC_ERROR);
    }
    a->fg = NULL;
    a->fd = NULL;
    a->equilibre = 0;
    a->ID_route = ID_route;
    a->nomVille = nVille->nomVille;
    for(int i=0;i<=SIZE4;i++){
        a->tab[i] = tab[i];
    }
    a->compte = compte;
    a->compteDebut = compteDebut + nVille->Debut;
    return a;
}

pArbre TransfoArbreDebut(pArbre a, int ID_route, pVille nomVilleDepart, pVille nomVilleArrivee, int compte, int tab[], int compteDebut){
    if(a == NULL){
        int h = 0;
        a = creationArbreDebut(ID_route, nomVilleDepart, compte, tab, compteDebut);
        a = insertionAVLDEBUT(a, ID_route, nomVilleArrivee, compte, tab, compteDebut, &h);
    }
    else{
        int h = 0;
        a = insertionAVLDEBUT(a, ID_route, nomVilleDepart, compte, tab, compteDebut, &h);
        a = insertionAVLDEBUT(a, ID_route, nomVilleArrivee, compte, tab, compteDebut, &h);
    }
    return a;
}

pArbreF creationArbreFinal(pArbre a, pArbreF b)
{
    //fonction récursive pour créer l'arbre final
    //la fonction va parcourir tout l'arbre a et ajouter les valeurs dans 
    //l'arbre b initialement nul, en les triants par nombre de traversées
    if (a != NULL)
    {
        //facteur d'equilibrage toujours initialisé a 0
        int h = 0;
        b = insertionAVLFINAL(b, a->ID_route, a->nomVille, a->compte, a->compteDebut, &h);
        b = creationArbreFinal(a->fg, b);
        b = creationArbreFinal(a->fd, b);
    }
    return b;
}

void infixeInverse(FILE *chemin, pArbreF a, int *i)
{
    //fonction récursive qui écris dans le fichier de données de sortie toutes les données nécessaires
    //Le compteur, l'id de la route, la ville
    //parcours de l'arbre infixe inverse pour parcourir dans le sens décroissant
    if (a != NULL)
    {
        infixeInverse(chemin, a->fd, i);
        (*i)++;
        fprintf(chemin, "%d;%d;%d;%s\n", *i, a->compte, a->compteDebut, a->nomVille);
        infixeInverse(chemin, a->fg, i);
    }
    else
    {
        exit(2);
    }
}

pArbre insertionAVLDEBUT(pArbre a, int ID_route, pVille nomVille, int compte, int tab[], int compteDebut, int *h)
{
    //fonction d'insertion d'AVL 
    if (h == NULL)
    {
        exit(ALLOC_ERROR);
    }
    if (a == NULL)
    {
        *h = 1;
        a = creationArbreDebut(ID_route, nomVille, compte, tab, compteDebut);
        return a;
    }
    //resultat = strcmp(nomVille, a->nomville)
    //resultat < 0 nomville < a->nomville
    //resultat > 0 nomville > a->nomville
    else if (strcmp(nomVille->nomVille, a->nomVille) < 0)
    {
        //parcours d'AVL
        a->fd = insertionAVLDEBUT(a->fd, ID_route, nomVille, compte, tab, compteDebut,  h);
        *h = 0;
    }
    else if (strcmp(nomVille->nomVille, a->nomVille) > 0)
    {
        //parcours d'AVL
        a->fg = insertionAVLDEBUT(a->fg, ID_route, nomVille, compte, tab, compteDebut, h);
           
    }
    else
    {
        int i = 0;
        while(tab[i] != '\0'){
            if(tab[i] != ID_route){
                i++;
            }
            else{
                *h = 0;
                return a;
            }
        }

        int j;
        while(j != '\0'){
            j++;
        }
            tab[j] = ID_route;
        *h = 0;
        return a;
    }

    if (*h != 0)
    {
        a->equilibre = a->equilibre + *h;
        a = equilibrerAVL(a);
        if (a->equilibre == 0)
        {
            *h = 0;
        }
        else
        {
            *h = 1;
        }
    }
    return a;
}

void libererArbre(pArbre a)
{
    //libère tout l'arbre de manière récursive
    if (a != NULL)
    {
        libererArbre(a->fg);
        libererArbre(a->fd);
        free(a);
    }
}

void libererArbreF(pArbreF a)
{
    //libère tout l'arbre de manière récursive
    if (a != NULL)
    {
        libererArbreF(a->fg);
        libererArbreF(a->fd);
        free(a);
    }
}

pArbreF creerArbreFinal(int ID_route, char* nomVille, int compte, int compteDebut)
{
    //crée un nouvel arbre avec les valeurs entrées
    pArbreF c = (pArbreF)(malloc(sizeof(ArbreF)));
    if (c == NULL)
    {
        exit(ALLOC_ERROR);
    }
    c->ID_route = ID_route;
    c->nomVille = nomVille;
    c->compteDebut = compteDebut;
    c->compte = compte;
    c->fg = NULL;
    c->fd = NULL;
    c->equilibre = 0;
    return c;
}

int min(int a, int b)
{
    //retourne la valeur minimale entre a et b
    if (a < b)
    {
        return a;
    }
    return b;
}
int max(int a, int b)
{
    //retourne la valeur maximale entre a et b
    if (a < b)
    {
        return b;
    }
    return a;
}

float min_f(float a, float b)
{
    //retourne la valeur minimale entre a et b et prenant des float en argument
    if (a < b)
    {
        return a;
    }
    return b;
}
float max_f(float a, float b)
{
    //retourne la valeur maximale entre a et b et prenant des float en argument
    if (a < b)
    {
        return b;
    }
    return a;
}

int existeFilsDroit(pArbre a)
{
    //renvoie True si l'arbre est vide, False sinon
    //renvoie 0 en cas d'erreur
    if (a != NULL)
    {
        return a->fg == NULL;
    }
    return 0;
}

pArbreF insertionAVLFINAL(pArbreF a, int ID_route, char* nomVille, int compte, int compteDebut, int *h)
{
    //fonction d'insertion d'AVL récursive
    if (h == NULL)
    {
        exit(ALLOC_ERROR);
    }
    if (a == NULL)
    {
        //on est au bon endroit dans l'AVL, on cré un nouveau noeud et le retourne 
        *h = 1;
        a = creerArbreFinal(ID_route, nomVille, compte, compteDebut);
        return a;
    }
    else if (compte > a->compte)
    {
        //on veut trier les valeurs en fonction de valeur min - valeur max donc on parcours l'arbre de cette manière
        a->fd = insertionAVLFINAL(a->fd, ID_route, nomVille, compte, compteDebut, h);
        *h = 0;
    }
    else if (compte < a->compte)
    {
        *h = -*h;
        a->fd = insertionAVLFINAL(a->fd, ID_route, nomVille, compte, compteDebut, h);
    }
    else
    {
        *h = 0;
        return a;
    }
    if (*h != 0)
    {
        a->equilibre = a->equilibre + *h;
        a = equilibrerAVLF(a);
        if (a->equilibre == 0)
        {
            *h = 0;
        }
        else
        {
            *h = 1;
        }
    }
    return a;
}

pArbre rotationGauche(pArbre a)
{
    //permet de faire une simple rotation a gauche de l'AVL 
    if (a == NULL)
    {
        exit(ALLOC_ERROR);
    }
    pArbre pivot;
    int eq_a, eq_p;
    pivot = a->fd;
    a->fd = pivot->fg;
    pivot->fg = a;
    eq_a = a->equilibre;
    eq_p = pivot->equilibre;
    a->equilibre = eq_a - max(eq_p, 0) - 1;
    pivot->equilibre = min(eq_a - 2, eq_a + eq_p - 2);
    pivot->equilibre = min(pivot->equilibre, eq_p - 1);
    a = pivot;
    return a;
}

pArbreF rotationGaucheF(pArbreF a)
{
    //permet de faire une simple rotation a gauche de l'AVLFinal 
    if (a == NULL)
    {
        exit(ALLOC_ERROR);
    }
    pArbreF pivot;
    int eq_a, eq_p;
    pivot = a->fd;
    a->fd = pivot->fg;
    pivot->fg = a;
    eq_a = a->equilibre;
    eq_p = pivot->equilibre;
    a->equilibre = eq_a - max(eq_p, 0) - 1;
    pivot->equilibre = min(eq_a - 2, eq_a + eq_p - 2);
    pivot->equilibre = min(pivot->equilibre, eq_p - 1);
    a = pivot;
    return a;
}

pArbre rotationDroit(pArbre a)
{
    //permet de faire une simple rotation a droite de l'AVL 
    if (a == NULL)
    {
        exit(ALLOC_ERROR);
    }
    pArbre pivot;
    int eq_a, eq_p;
    pivot = a->fg;
    a->fg = pivot->fd;
    pivot->fd = a;
    eq_a = a->equilibre;
    eq_p = pivot->equilibre;
    a->equilibre = eq_a - min(eq_p, 0) + 1;
    pivot->equilibre = max(eq_a + 2, eq_a + eq_p + 2);
    pivot->equilibre = max(pivot->equilibre, eq_a + 1);
    a = pivot;
    return a;
}

pArbre doubleRotationGauche(pArbre a)
{
    //permet de faire une double rotation a gauche de l'AVL 
    //donc rotation simple droite puis rotation simple gauche
    if (a == NULL)
    {
        exit(ALLOC_ERROR);
    }
    a->fd = rotationDroit(a->fd);
    return rotationGauche(a);
}

pArbre doubleRotationDroit(pArbre a)
{
    //permet de faire une double rotation a droite de l'AVL 
    //donc rotation simple gauche puis rotation simple droite
    if (a == NULL)
    {
        exit(ALLOC_ERROR);
    }
    a->fg = rotationGauche(a->fg);
    return rotationDroit(a);
}
pArbreF rotationDroitF(pArbreF a)
{
    //permet de faire une simple rotation a droite de l'AVL 
    if (a == NULL)
    {
        exit(ALLOC_ERROR);
    }
    pArbreF pivot;
    int eq_a, eq_p;
    pivot = a->fg;
    a->fg = pivot->fd;
    pivot->fd = a;
    eq_a = a->equilibre;
    eq_p = pivot->equilibre;
    a->equilibre = eq_a - min(eq_p, 0) + 1;
    pivot->equilibre = max(eq_a + 2, eq_a + eq_p + 2);
    pivot->equilibre = max(pivot->equilibre, eq_a + 1);
    a = pivot;
    return a;
}

pArbreF doubleRotationGaucheF(pArbreF a)
{
    //permet de faire une double rotation a gauche de l'AVL 
    //donc rotation simple droite puis rotation simple gauche
    if (a == NULL)
    {
        exit(ALLOC_ERROR);
    }
    a->fd = rotationDroitF(a->fd);
    return rotationGaucheF(a);
}

pArbreF doubleRotationDroitF(pArbreF a)
{
    //permet de faire une double rotation a droite de l'AVL 
    //donc rotation simple gauche puis rotation simple droite
    if (a == NULL)
    {
        exit(ALLOC_ERROR);
    }
    a->fg = rotationGaucheF(a->fg);
    return rotationDroitF(a);
}

int main()
{

    pArbre a = NULL;
    pArbreF b = NULL;

    //chemin pour accéder aux données principales
    FILE *chemin1 = fopen("../roman/c2_data.txt", "r");
    //vérification que l'allocation a bien été faite
    if (chemin1 == NULL){
        printf("Erreur lors de l'ouverture du fichier 1\n");
        exit(1);
    }

    int ID_route;
    char* nomVilleDepart;
    nomVilleDepart = malloc(sizeof(char)*50);
    if(nomVilleDepart == NULL)
    {
        printf("Erreur d'allocation\n");
    }
    char* nomVilleArrivee;
    nomVilleArrivee = malloc(sizeof(char)*50);
    if(nomVilleArrivee == NULL)
    {
        printf("Erreur d'allocation\n");
    }
    
    //on récupere les données ligne par ligne du fichier data et on conserve les valeurs récupérées dans deux variables
    //routeID et distance
    while (fscanf(chemin1, "%d;%49[^;];%49[^\n]\n", &ID_route, nomVilleDepart, nomVilleArrivee) == 3)
    {
        //Verification de l'intégrité des données
        if (nomVilleDepart[0] == '\0' || nomVilleArrivee[0] == '\0' || ID_route < 0) {

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
    fclose(chemin1);
    //parcours l'arbre a et ajoute ses valeurs dans l'arbre b qui contiendra toutes les valeurs triées par traversées
    b = creationArbreFinal(a, b);
    //désallocation récursive de tout l'arbre manuellement
    
    //chemin pour accéder au fichier de sortie dans lequel on mettra les données utiles pour le script gnuplot
    libererArbre(a);    
    FILE *chemin2 = fopen("../roman/gnuplot_data_T.txt", "w");
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
    libererArbreF(b);
    libererArbre(a);

    return 0;
}