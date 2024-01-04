#include "AVL.h"

pArbre rotationGauche(pArbre a);
pArbre rotationDroit(pArbre a);
pArbre doubleRotationGauche(pArbre a);
pArbre doubleRotationDroit(pArbre a);
pArbre insertionAVL(pArbre a, int trajet, float distance, float min, float max,int compteur, int *h);
float min_f(float a, float b);
float max_f(float a, float b);

pArbre equilibrerAVL(pArbre a)
{
    if (a == NULL)
    {
        exit(9);
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

pArbre creerArbre(int trajet, float distance)
{
    pArbre a = malloc(sizeof(Arbre));
    if (a == NULL)
    {
        exit(1);
    }
    a->fg = NULL;
    a->fd = NULL;
    a->equilibre = 0;
    a->ID_route = trajet;
    a->distance = distance;
    a->min = distance;
    a->max = distance;
    a->compteur = 1;
    return a;
}



pArbre creationArbreFinal(pArbre a, pArbre b)
{
    if (a != NULL)
    {
        int h = 0;
        b = insertionAVL(b, a->ID_route, a->distance, a->min, a->max, a->compteur, &h);
        b = creationArbreFinal(a->fg, b);
        b = creationArbreFinal(a->fd, b);
    }
    return b;
}

void infixeInverse(FILE *chemin, pArbre a)
{
    if (a != NULL)
    {
        infixeInverse(chemin, a->fd);
        fprintf(chemin, "%d;%f;%f;%f\n", a->ID_route, a->min, a->max, a->distance / a->compteur);
        infixeInverse(chemin, a->fg);
    }
}

pArbre insertionAVLTrajet(pArbre a, int idtrajet, float distance, int *h)
{
    if (h == NULL)
    {
        exit(2);
    }
    if (a == NULL)
    {
        *h = 1;
        return creerArbre(idtrajet, distance);
    }
    else if (idtrajet < a->ID_route)
    {
        a->fg = insertionAVLTrajet(a->fg, idtrajet, distance, h);
        *h = -*h;
    }
    else if (idtrajet > a->ID_route)
    {
        *h = 0;
        a->fd = insertionAVLTrajet(a->fd, idtrajet, distance, h);
    }
    else
    {
        a->min = min_f(a->min, distance);
        a->max = max_f(a->max, distance);
        a->compteur += 1;
        a->distance += distance;
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
    if (a != NULL)
    {
        libererArbre(a->fg);
        libererArbre(a->fd);
        free(a);
    }
}

pArbre creerArbreEntier(int trajet, float distance, float min, float max, int compteur)
{
    pArbre c = malloc(sizeof(Arbre));
    if (c == NULL)
    {
        printf("Erreur d'allocation");
        exit(1);
    }
    c->distance = distance;
    c->ID_route = trajet;
    c->max = max;
    c->min = min;
    c->compteur = compteur;
    c->fg = NULL;
    c->fd = NULL;
    c->equilibre = 0;
    return c;
}

int min(int a, int b)
{
    if (a < b)
    {
        return a;
    }
    return b;
}
int max(int a, int b)
{
    if (a < b)
    {
        return b;
    }
    return a;
}

float min_f(float a, float b)
{
    if (a < b)
    {
        return a;
    }
    return b;
}
float max_f(float a, float b)
{
    if (a < b)
    {
        return b;
    }
    return a;
}

int existeFilsDroit(pArbre a)
{
    if (a != NULL)
    {
        return a->fg == NULL;
    }
    return 0;
}

pArbre insertionAVL(pArbre a, int trajet, float distance, float min, float max,int compteur, int *h)
{
    if (h == NULL)
    {
        exit(2);
    }
    if (a == NULL)
    {
        *h = 1;
        return creerArbreEntier(trajet, distance, min, max, compteur);
    }
    else if (max - min < a->max - a->min)
    {
        a->fg = insertionAVL(a->fg, trajet, distance, min, max, compteur, h);
        *h = -*h;
    }
    else if (max - min > a->max - a->min)
    {
        *h = 0;
        a->fd = insertionAVL(a->fd, trajet, distance, min, max, compteur, h);
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
    if (a == NULL)
    {
        exit(5);
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
    if (a == NULL)
    {
        exit(6);
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
    if (a == NULL)
    {
        exit(7);
    }
    a->fd = rotationDroit(a->fd);
    return rotationGauche(a);
}

pArbre doubleRotationDroit(pArbre a)
{
    if (a == NULL)
    {
        exit(8);
    }
    a->fg = rotationGauche(a->fg);
    return rotationDroit(a);
}
