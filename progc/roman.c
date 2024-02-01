#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NOMVILLE 35
#define NBR_VILLE 10


//structure pour vérifier si le trajet s'est déjà déroulé
typedef struct _cntID {
    int ID_route;
    struct _cntID *fg;
    struct _cntID *fd;
    int equilibre;
} compteID;

// Structure de base du programme, avec toutes les informations.
typedef struct _creerVille {
    char *nom;
    int CmptVille;
    int debutTrajet;
    int nbrID;
    compteID *ID_ville;
    struct _creerVille *gauche;
    struct _creerVille *droite;
    int hauteur;
    int equilibre;
} creerVille;

// Fonction qui retourne le max entre 2 entiers
int max(int a, int b) {
    if(a > b){
        return a;
    }
    else{
        return b;
    }
    
}
//Fonction qui retourne le min entre 2 entiers
int min(int a, int b) {
    if(a > b){
        return b;
    }
    else{
        return a;
    }
}

creerVille* rotationGauche(creerVille* a)
{
    // permet de faire une simple rotation a gauche de l'AVL
    if (a == NULL)
    {
        exit(66);
    }
    creerVille* pivot;
    int eq_a, eq_p;
    pivot = a->droite;
    a->droite = pivot->gauche;
    pivot->gauche = a;
    eq_a = a->equilibre;
    eq_p = pivot->equilibre;
    a->equilibre = eq_a - max(eq_p, 0) - 1;
    pivot->equilibre = min(eq_a - 2, eq_a + eq_p - 2);
    pivot->equilibre = min(pivot->equilibre, eq_p - 1);
    a = pivot;
    free(pivot);
    return a;
}

creerVille* rotationDroit(creerVille* a)
{
    // permet de faire une simple rotation a droite de l'AVL
    if (a == NULL)
    {
        exit(66);
    }
    creerVille* pivot;
    int eq_a, eq_p;
    pivot = a->gauche;
    a->gauche = pivot->droite;
    pivot->droite = a;
    eq_a = a->equilibre;
    eq_p = pivot->equilibre;
    a->equilibre = eq_a - min(eq_p, 0) + 1;
    pivot->equilibre = max(eq_a + 2, eq_a + eq_p + 2);
    pivot->equilibre = max(pivot->equilibre, eq_a + 1);
    a = pivot;
    return a;
}

compteID* rotationDroit2(compteID* a)
{
    // permet de faire une simple rotation a droite de l'AVL
    if (a == NULL)
    {
        exit(66);
    }
    compteID* pivot;
    int eq_a, eq_p;
    pivot = a->fg;
    a->fg = pivot->fd;
    pivot->fd = a;
    eq_a = a->equilibre;
    eq_p = pivot->equilibre;
    a->equilibre = eq_a - min(eq_p, 0) + 1;
    pivot->equilibre = max(eq_a + 2, eq_a + eq_p + 2);
    pivot->equilibre = max(pivot->equilibre, eq_p + 1);
    a = pivot;
    return a;
}

compteID* rotationGauche2(compteID* a)
{
    // permet de faire une simple rotation a gauche de l'AVL
    if (a == NULL)
    {
        exit(66);
    }
    compteID* pivot;
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


creerVille* doubleRotationGauche(creerVille* a)
{
    // permet de faire une double rotation a gauche de l'AVL
    // donc rotation simple droite puis rotation simple gauche
    if (a == NULL)
    {
        exit(66);
    }
    a->droite = rotationDroit(a->droite);
    return rotationGauche(a);
}

compteID* doubleRotationGauche2(compteID* a)
{
    // permet de faire une double rotation a gauche de l'AVL
    // donc rotation simple droite puis rotation simple gauche
    if (a == NULL)
    {
        exit(66);
    }
    a->fd = rotationDroit2(a->fd);
    return rotationGauche2(a);
}

creerVille* doubleRotationDroit(creerVille* a)
{
    // permet de faire une double rotation a droite de l'AVL
    // donc rotation simple gauche puis rotation simple droite
    if (a == NULL)
    {
        exit(66);
    }
    a->gauche = rotationGauche(a->gauche);
    return rotationDroit(a);
}

compteID* doubleRotationDroit2(compteID* a)
{
    // permet de faire une double rotation a droite de l'AVL
    // donc rotation simple gauche puis rotation simple droite
    if (a == NULL)
    {
        exit(66);
    }
    a->fg = rotationGauche2(a->fg);
    return rotationDroit2(a);
}

creerVille* equilibrerAVL(creerVille* a)
{
    // fonction pour équilibrer l'AVL en fonction du facteur d'equilibrage
    if (a == NULL)
    {
        exit(66);
    }
    if (a->equilibre >= 2)
    {
        if (a->droite->equilibre >= 0)
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
        if (a->gauche->equilibre <= 0)
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
compteID* equilibrerAVL2(compteID* a)
{
    // fonction pour équilibrer l'AVL en fonction du facteur d'equilibrage
    if (a == NULL)
    {
        exit(66);
    }
    if (a->equilibre >= 2)
    {
        if (a->fd->equilibre >= 0)
        {
            return rotationGauche2(a);
        }
        else
        {
            return doubleRotationGauche2(a);
        }
    }
    else if (a->equilibre <= -2)
    {
        if (a->fg->equilibre <= 0)
        {
            return rotationDroit2(a);
        }
        else
        {
            return doubleRotationDroit2(a);
        }
    }
    return a;
}



compteID *creerAVL3(int IDRoute){
    compteID *route_ID = (compteID *)malloc(sizeof(compteID));
    route_ID->ID_route = IDRoute;
    route_ID->equilibre = 0;
    route_ID->fg = NULL;
    route_ID->fd = NULL;
    return route_ID;
}
// Initialise la première ville de l'arbre
creerVille *nouvelleVille(char *nom, int debutTraj, int IDRoute) {
    creerVille *ville = (creerVille *)malloc(sizeof(creerVille));
    if(ville == NULL){
        exit(66);
    }
    ville->nom = malloc(sizeof(char)*150);
    if(ville->nom == NULL){
        exit(66);
    }
    strcpy(ville->nom, nom);
    ville->CmptVille = 1;
    ville->hauteur = 1;
    ville->nbrID = IDRoute;
    ville->ID_ville = creerAVL3(ville->nbrID);
    if(debutTraj == 1){
    ville->debutTrajet ++;
    }
    else{
        ville->debutTrajet = 0;
    }
    ville->gauche = NULL;
    ville->droite = NULL;
    ville->equilibre = 0;
    return ville;
}

creerVille *creerAVL2(creerVille* ville, int IDRoute) {
    compteID *route_ID = (compteID *)malloc(sizeof(compteID));
    route_ID->ID_route = IDRoute;
    route_ID->equilibre = 0;
    route_ID->fg = NULL;
    route_ID->fd = NULL;
    ville->ID_ville = creerAVL3(ville->nbrID);
    return ville;
}







compteID* insertionAVLMilieu(compteID *a, int IDRoute, int *b, int* h)
{
    // fonction d'insertion d'AVL
    if (h == NULL)
    {
        exit(66);
    }
    if (a == NULL)
    {
        // si l'id trajet est nouveau, on crée un AVL
        *h = 1;
        *b = 1;
        return creerAVL3(IDRoute);
    }
    else if (IDRoute < a->ID_route)
    {
        // parcours d'AVL
        a->fg = insertionAVLMilieu(a->fg, IDRoute, b, h);
        *h = -*h;
    }
    else if (IDRoute > a->ID_route)
    {
        // parcours d'AVL
        *h = 0;
        a->fd = insertionAVLMilieu(a->fd, IDRoute, b, h);
        
    }
    else
    {
        *h = 0;
        return a;
    }

    if (*h != 0)
    {
        a->equilibre = a->equilibre + *h;
        a = equilibrerAVL2(a);
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



creerVille* insertionAVLDebut(creerVille *a, char *nom, int debut, int IDRoute, int* h)
{
    // fonction d'insertion d'AVL
    if (h == NULL)
    {
        exit(66);
    }
    if (a == NULL)
    {
        // si l'id trajet est nouveau, on crée un AVL
        *h = 1;
        return nouvelleVille(nom, debut, IDRoute);
    }
    else if (strcmp(nom, a->nom) < 0)
    {
        // parcours d'AVL
        a->gauche = insertionAVLDebut(a->gauche, nom, debut, IDRoute, h);
        *h = -*h;
    }
    else if (strcmp(nom, a->nom) > 0)
    {
        // parcours d'AVL
        *h = 0;
        a->droite = insertionAVLDebut(a->droite, nom, debut, IDRoute, h);
    }
    else
    {
        // si la valeur d'id est déjà présente
        // on modifie la valeur minimale et maximale au besoin du noeud
        // on augmente le compteur et on actualise la valeur de distance totale
        int* b;
        b = malloc(sizeof(int));
        if(b == NULL){
            exit(66);
        }
        *b = 0;
        a->ID_ville = insertionAVLMilieu(a->ID_ville,IDRoute, b, h);
        if(*b == 1){
        (a->CmptVille)++;
        }
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

creerVille* creerArbreFinal(int CpVille, int dbT, char* nomination, int* h){
    creerVille *b = malloc(sizeof(creerVille));
    if(b == NULL){
        exit(66);
    }
    b->CmptVille = CpVille;
    b->nom = malloc(sizeof(char)*150);
    if(b->nom == NULL){
        exit(66);
    }
    b->nom = strcpy(b->nom, nomination);
    b->debutTrajet = dbT;
    b->equilibre = *h;
    return b;
}



creerVille* insertionAVLFinal(creerVille *a, int CmptVille, int debutTrajet, char* nom, int* h)
{//a=b b= racine
    // fonction d'insertion d'AVL
    if (h == NULL)
    {
        exit(66);
    }
    if (a == NULL)
    {
        // si l'id trajet est nouveau, on crée un AVL
        *h = 1;
        return creerArbreFinal(CmptVille, debutTrajet, nom, h);
    }
    else if (CmptVille < a->CmptVille)
    {
        // parcours d'AVL
        a->gauche = insertionAVLFinal(a->gauche,CmptVille, debutTrajet, nom, h);
        *h = -*h;
    }
    else if (CmptVille >= a->CmptVille)
    {
        // parcours d'AVL
        *h = 0;
        a->droite = insertionAVLFinal(a->droite ,CmptVille, debutTrajet, nom, h);
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



creerVille* creationArbreFinal2(creerVille* a, creerVille* b)
{
    // fonction récursive pour créer l'arbre final
    // la fonction va parcourir tout l'arbre a et ajouter les valeurs dans l'arbre b initialement nul
    if (a != NULL)
    {
        // facteur d'equilibrage toujours initialisé a 0
        int h = 0;
        b = insertionAVLFinal(b, a->CmptVille, a->debutTrajet, a->nom, &h);
        b = creationArbreFinal2(a->gauche, b);
        b = creationArbreFinal2(a->droite, b);
    }
    return b;
}

void infixeInverse(creerVille *a)
{
    // fonction récursive qui écris dans le fichier de données de sortie toutes les données nécessaires
    // Le compteur, l'id de la route, la distance minimale du trajet, la moyenne de distance du trajet, la distance maximale du trajet
    // la différence entre distance maximale et minimale du trajet,
    // parcours de l'arbre infixe inverse pour parcourir dans le sens décroissant
    if (a != NULL)
    {
        infixeInverse(a->droite);
        printf("%s;%d;%d\n", a->nom, a->CmptVille, a->debutTrajet);
        infixeInverse(a->gauche);
    }
}
void infixe(creerVille *a)
{
    // fonction récursive qui écris dans le fichier de données de sortie toutes les données nécessaires
    // Le compteur, l'id de la route, la distance minimale du trajet, la moyenne de distance du trajet, la distance maximale du trajet
    // la différence entre distance maximale et minimale du trajet,
    // parcours de l'arbre infixe inverse pour parcourir dans le sens décroissant
    if (a != NULL)
    {
        infixeInverse(a->droite);
        printf("%s;%d;%d\n", a->nom, a->CmptVille, a->debutTrajet);
        infixeInverse(a->gauche);
    }
}

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
        racine = insertionAVLDebut(racine, villeArrivee, dbt, IDR, &h2);
    }
    
    
    creerVille* b = NULL;
    b = creationArbreFinal2(racine ,b);  

    fclose(chemin);


    infixe(b);

    return 0;
    
}