#ifndef AVL_T_H
#define AVL_T_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NOMVILLE 35
#define NBR_VILLE 10

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
    int equilibre;
} creerVille;

int max(int a, int b);

int min(int a, int b);

creerVille* rotationGauche(creerVille* a);

creerVille* rotationDroit(creerVille* a);

compteID* rotationDroit2(compteID* a);

compteID* rotationGauche2(compteID* a);

creerVille* doubleRotationGauche(creerVille* a);

compteID* doubleRotationGauche2(compteID* a);

creerVille* doubleRotationDroit(creerVille* a);

compteID* doubleRotationDroit2(compteID* a);

creerVille* equilibrerAVL(creerVille* a);

compteID* equilibrerAVL2(compteID* a);

//void libererArbre(creerVille* a);

compteID *creerAVL3(int IDRoute);

creerVille *nouvelleVille(char *nom, int debutTraj, int IDRoute);

creerVille* nouvelleVilleFinale(char* nom, int CmptVille, int debut);

creerVille *creerAVL2(creerVille* ville, int IDRoute);

compteID* insertionAVLMilieu(compteID *a, int IDRoute, int *b, int* h);

creerVille* insertionAVLDebut(creerVille *a, char *nom, int debut, int IDRoute, int* h);

creerVille* creerArbreFinal(int CpVille, int dbT, char* nomination);

creerVille* insertionAVLFinal(creerVille *a, int CmptVille, int debutTrajet, char* nom, int* h);

creerVille* insertionABRVraimentFinal(creerVille *a, char *nom, int compteurV, int debut);

void infixeInverse(creerVille *a);

void infixe(creerVille *a);

creerVille* suppMax(creerVille* a, char** pnom, int* CmptVille, int* DebutTrajet);

creerVille* suppression(creerVille* a, char** pnom, int* CmptVille, int* DebutTrajet, char** pnom2, int* CmptVille2, int* DebutTrajet2);

creerVille* creationArbreFinal2(creerVille* a, creerVille* b);

#endif