#ifndef AVL_H
#define AVL_H

#include <stdio.h>
#include <math.h>

#define SIZE1 4
#define SIZE2 50
#define SIZE3 5


typedef struct _b
{
    int elt;
    struct _b *fg;
    struct _b *fd;
    int equilibre;
    float tab_distance[SIZE1];
} Arbre;

typedef Arbre* pArbre;

pArbre creerArbre(int e);

int existeFilsDroit(pArbre a);

pArbre insertionAVL(pArbre a, int e, int *h);

pArbre supprAVL(pArbre a, int e, int *h);

pArbre suppMinAVL(pArbre a, int *h, int *pe);

pArbre rotationGauche(pArbre a);

pArbre rotationDroit(pArbre a);

pArbre doubleRotationGauche(pArbre a);

pArbre doubleRotationDroit(pArbre a);

pArbre equilibrerAVL(pArbre a);

#endif





