#ifndef AVL_T_H
#define AVL_T_H

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


typedef struct _b
{
    int ID_route;
    struct _b *fg;
    struct _b *fd;
    int equilibre;
    char nomVille;
    int tab[SIZE 4];
    int compte;
} Arbre;


typedef struct {
    int ID_route;
    char nomVille;
} insertVille;


typedef Arbre* pArbre;

pArbre creerArbre(int ID_route, char nomVille, int compte, int tab);

pArbre creationArbreFinal(pArbre a, pArbre b);

void infixeInverse(FILE* chemin, pArbre a, int *i);

pArbre insertionAVLDEBUT(pArbre a, int ID_route, char nomVille, int compte ,int tab, int *h);

void libererArbre(pArbre a);

pArbre creationArbreDebut(int ID_route, char nomVille, int compte, int tab);

int min(int a, int b);

int max(int a, int b);

float max_f(float a,float b);

float min_f(float a, float b);

int existeFilsDroit(pArbre a);

pArbre insertionAVLFINAL(pArbre a, int ID_route, char nomVille, int compte, int tab, int *h);

pArbre rotationGauche(pArbre a);

pArbre rotationDroit(pArbre a);

pArbre doubleRotationGauche(pArbre a);

pArbre doubleRotationDroit(pArbre a);

pArbre equilibrerAVL(pArbre a);

#endif





