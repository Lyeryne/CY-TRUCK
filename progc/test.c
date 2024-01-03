#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

#define SIZE1 4
#define SIZE2 50
#define SIZE3 5


typedef struct _b
{
    int ID_route;
    struct _b *fg;
    struct _b *fd;
    int equilibre;
    float distance;
    float min;
    float max;
    int compteur;
} Arbre;

typedef Arbre* pArbre;

pArbre rotationGauche(pArbre a);
pArbre rotationDroit(pArbre a);
pArbre doubleRotationGauche(pArbre a);
pArbre doubleRotationDroit(pArbre a);
pArbre insertionAVL(pArbre a, int trajet, float distance, float min, float max,int compteur, int *h);

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
        b = creationArbreFinal(a->fg, b);
        int h = 0;
        b = insertionAVL(b, a->ID_route, a->distance, a->min, a->max, a->compteur, &h);
        b = creationArbreFinal(a->fd, b);
    }
    return b;
}

void infixeInverse(FILE *chemin, pArbre a)
{
    if (a != NULL)
    {
        infixeInverse(chemin, a->fd);
        fprintf(chemin, "%d;%f;%f;%f;%f\n", a->ID_route, a->distance, a->min, a->max, a->distance / a->compteur);
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
        if (a->min > distance)
        {
            a->min = distance;
        }
        if (a->max < distance)
        {
            a->max = distance;
        }
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

pArbre creerArbreEntier(int trajet, float distance, int max, int min, int compteur)
{
    pArbre a = malloc(sizeof(Arbre));
    if (a == NULL)
    {
        printf("Erreur d'allocation");
        exit(1);
    }
    a->distance = distance;
    a->ID_route = trajet;
    a->max = max;
    a->min = min;
    a->compteur = compteur;
    a->fg = NULL;
    a->fd = NULL;
    a->equilibre = 0;
    return a;
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


int main()
{

    pArbre a = NULL;
    pArbre b = NULL;

    FILE *chemin = fopen("../temp/c_data.txt", "r");
    if (chemin == NULL)
    {
        printf("Erreur lors de l'ouverture du fichier 1\n");
        exit(1);
    }

    int RouteID;
    float distance;
    while (fscanf(chemin, "%d;%f\n", &RouteID, &distance) == 2)
    {
        int h = 0;
        a = insertionAVLTrajet(a, RouteID, distance, &h);
    }
    printf("\noui%d\n", a->ID_route);
    
    fclose(chemin);
    b = creationArbreFinal(a, b);
    FILE *chemin2 = fopen("../temp/gnuplot_data_S.txt", "w");
    if (chemin2 == NULL)
    {
        printf("Erreur lors de l'ouverture du fichier 2\n");
        exit(1);
    }
    infixeInverse(chemin2, b);
    fclose(chemin2);

    return 0;
}