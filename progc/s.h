#ifndef S_H
#define S_H

#include "avl.h"
#include <string.h>

float **creation_tableau_final(pArbre a, float **tab);

void echanger(float **tableau, int a, int b);

int comparer(float a[], float b[]);

void trierTableau(float **tableau, int taille);

#endif
