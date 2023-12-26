#ifndef AVL_H
#define AVL_H

#include <stdio.h>

typedef struct _a
{
    int elt;
    struct _a *fg;
    struct _a *fd;
    int equilibre;
} Arbre;

typedef Arbre *pArbre;

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





