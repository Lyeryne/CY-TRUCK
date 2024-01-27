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

pVille creerVille(char* nom, int num);

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


#endif