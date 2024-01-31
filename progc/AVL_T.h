#ifndef AVL_T_H
#define AVL_T_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NOMVILLE 35
#define NBR_VILLE 10

// Structure de base du programme, avec toutes les informations.
typedef struct creerVille {
    char nom[NOMVILLE];
    int CmptVille;
    struct creerVille *gauche;
    struct creerVille *droite;
    int hauteur;
} creerVille;

int max(int a, int b);

int min(int a, int b);

int hauteur(creerVille *N);

creerVille *nouvelleVille(char *nom);

creerVille * rotationDroite(creerVille *a);

creerVille * rotationGauche(creerVille *a);

int calculEQUILIBRE(creerVille *N);

creerVille *ajouterVille(creerVille *branche, char *nom);

void Prefixe(creerVille *arbre, creerVille *maxVilles[],unsigned long int *ville);

int compareTrajet(const void *a, const void *b);

#endif