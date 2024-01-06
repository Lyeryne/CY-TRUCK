#ifndef AVL_T_H
#define AVL_T_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

struct AVLNode {
    char city[50];
    int totalTraversals;
    int departures;
    struct AVLNode* left;
    struct AVLNode* right;
    int height;
};

int max(int a, int b);

int height(struct AVLNode* node);

int getBalance(struct AVLNode* node);

struct AVLNode* newNode(char city[], int totalTraversals, int departures);

struct AVLNode* rightRotate(struct AVLNode* y);

struct AVLNode* leftRotate(struct AVLNode* x);

struct AVLNode* insert(struct AVLNode* node, char city[], int totalTraversals, int departures);

void processTopCities(FILE* inputFile, FILE* outputFile);

#endif 