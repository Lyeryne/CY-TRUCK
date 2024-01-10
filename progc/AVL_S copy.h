#ifndef AVL_S_H
#define AVL_S_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define SIZE1 4
#define SIZE2 50
#define SIZE3 5
#define ALLOC_ERROR 77


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

pArbre creerArbre(int trajet, float distance);

pArbre creationArbreFinal(pArbre a, pArbre b);

void infixeInverse(FILE* chemin, pArbre a, int *i);

pArbre insertionAVLTrajet(pArbre a, int idtrajet, float distance, int *h);

void libererArbre(pArbre a);

pArbre creerArbreEntier(int trajet, float distance, float min, float max, int compteur);

int min(int a, int b);

int max(int a, int b);

float max_f(float a,float b);

float min_f(float a, float b);

int existeFilsDroit(pArbre a);

pArbre insertionAVL(pArbre a, int trajet, float distance, float min, float max, int compteur, int *h);

pArbre rotationGauche(pArbre a);

pArbre rotationDroit(pArbre a);

pArbre doubleRotationGauche(pArbre a);

pArbre doubleRotationDroit(pArbre a);

pArbre equilibrerAVL(pArbre a);

#endif





