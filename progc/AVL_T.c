#include "AVL_T.h"

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

pVille creerVille(char nom, int num){
    pVille a = malloc(sizeof(Ville));
    if (a == NULL)
    {
        exit(ALLOC_ERROR_2);
    }
    a->nomVille = nom;
    a->Debut = num;
    return a;
}



pArbre creationArbreDebut(int ID_route, pVille nomVille, int compte, int tab[], int compteDebut)
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
    a->nomVille = nomVille->nomVille;
    for(int i=0;i<=SIZE4;i++){
        a->tab[i] = tab[i];
    }
    a->compte = compte;
    a->compteDebut = compteDebut + nomVille->Debut;
    int h = 0;
    return a;
}

pArbre TransfoArbreDebut(pArbre a, int ID_route, pVille nomVilleDepart, pVille nomVilleArrivee, int compte, int tab[], int compteDebut){
    if(a == NULL){
        a = creationArbreDebut(ID_route, nomVilleDepart, nomVilleArrivee, compte, tab, compteDebut);
        a = insertionAVLDEBUT(a, ID_route, nomVilleArrivee, compte, tab, compteDebut, &h)
    }
    else{
        int h = 0;
        a = insertionAVLDEBUT(a, ID_route, nomVilleDepart, compte, tab, compteDebut, &h);
        a = insertionAVLDEBUT(a, ID_route, nomVilleArrivee, compte, tab, compteDebut, &h);
    }
    return a;
}

pArbre creationArbreFinal(pArbre a, pArbre b)
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

void infixeInverse(FILE *chemin, pArbre a, int *i)
{
    //fonction récursive qui écris dans le fichier de données de sortie toutes les données nécessaires
    //Le compteur, l'id de la route, la ville
    //parcours de l'arbre infixe inverse pour parcourir dans le sens décroissant
    if (a != NULL)
    {
        infixeInverse(chemin, a->fd, i);
        (*i)++;
        fprintf(chemin, "%d;%d;%d;%d;%s\n", *i, a->ID_route, a->compte, a->compteDebut, a->nomVille->nomVille);
        infixeInverse(chemin, a->fg, i);
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
        a = creationArbreDebut(ID_route, pVille nomVille, compte, tab, compteDebut);
    }
    }
    else if (ID_route < a->ID_route)
    {
        //parcours d'AVL
        a->fd = insertionAVLDEBUT(a->fd, ID_route, nomVille, compte, tab, compteDebut,  h);
        *h = 0;
    }
    else if (ID_route > a->ID_route)
    {
        //parcours d'AVL
        *h = -*h;
        a->fg = insertionAVLDEBUT(a->fg, ID_route, nomVille, compte, tab, compteDebut, h);
    }
    else
    {
        int i;
        while(i<=500){
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
        int i;
        while(i<=500){
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

pArbre creerArbreFinal(int ID_route, char nomVille, int compte, int compteDebut)
{
    //crée un nouvel arbre avec les valeurs entrées
    pArbreF c = malloc(sizeof(ArbreF));
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

pArbre insertionAVLFINAL(pArbre a, int ID_route, char nomVille, int compte, int compteDebut, int *h)
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
        return creerArbreFinal(ID_route, nomVille, compte, compteDebut);
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

