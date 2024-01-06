#include "AVL_T.h"

// Fonctions auxiliaires
int max(int a, int b) {
    return (a > b) ? a : b;
}

int height(struct AVLNode* node) {
    if (node == NULL)
        return 0;
    return node->height;
}

int getBalance(struct AVLNode* node) {
    if (node == NULL)
        return 0;
    return height(node->left) - height(node->right);
}

// Fonctions pour les rotations
struct AVLNode* rightRotate(struct AVLNode* y) {
    struct AVLNode* x = y->left;
    struct AVLNode* T2 = x->right;

    // Perform rotation
    x->right = y;
    y->left = T2;

    // Update heights
    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    return x;
}

struct AVLNode* leftRotate(struct AVLNode* x) {
    struct AVLNode* y = x->right;
    struct AVLNode* T2 = y->left;

    // Perform rotation
    y->left = x;
    x->right = T2;

    // Update heights
    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    return y;
}

// Fonction pour créer un nouveau nœud AVL
struct AVLNode* newNode(char city[], int totalTraversals, int departures) {
    struct AVLNode* node = (struct AVLNode*)malloc(sizeof(struct AVLNode));
    strcpy(node->city, city);
    node->totalTraversals = totalTraversals;
    node->departures = departures;
    node->left = NULL;
    node->right = NULL;
    node->height = 1; // Nouveau nœud, donc la hauteur est 1
    return node;
}

// Fonction pour insérer un nœud dans l'arbre AVL
struct AVLNode* insert(struct AVLNode* node, char city[], int totalTraversals, int departures) {
    // Effectuer une insertion normale de l'arbre binaire de recherche
    if (node == NULL)
        return newNode(city, totalTraversals, departures);

    if (strcmp(city, node->city) < 0)
        node->left = insert(node->left, city, totalTraversals, departures);
    else if (strcmp(city, node->city) > 0)
        node->right = insert(node->right, city, totalTraversals, departures);
    else {
        // Si la ville existe déjà, mettre à jour les données
        node->totalTraversals += totalTraversals;
        node->departures += departures;
        return node;
    }

    // Mettre à jour la hauteur du nœud actuel
    node->height = 1 + max(height(node->left), height(node->right));

    // Rééquilibrer l'arbre
    int balance = getBalance(node);

    // Cas de déséquilibre à gauche
    if (balance > 1) {
        if (strcmp(city, node->left->city) < 0)
            return rightRotate(node);
        if (strcmp(city, node->left->city) > 0) {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }
    }

    // Cas de déséquilibre à droite
    if (balance < -1) {
        if (strcmp(city, node->right->city) > 0)
            return leftRotate(node);
        if (strcmp(city, node->right->city) < 0) {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }
    }

    return node;
}

void processTopCities(FILE* inputFile, FILE* outputFile) {
    struct AVLNode* root = NULL;

    char line[256];
    while (fgets(line, sizeof(line), inputFile) != NULL) {
        char departureCity[50], arrivalCity[50];

        // Utiliser sscanf pour extraire les données du CSV
        int fieldsRead = sscanf(line, "%d;%*d;%49[^;];%49[^;];%*f;%[^;]", departureCity, arrivalCity);

        // Vérifier que les deux champs ont été lus avec succès
        if (fieldsRead == 2) {
            // Insérer les données dans la structure AVL
            root = insert(root, departureCity, 1, 1); // 1 pour totalTraversals et les départs
            root = insert(root, arrivalCity, 1, 0);   // 1 pour totalTraversals seulement
        } else {
            printf("Error reading line: %s", line);
        }
    }

    // TODO: Extraire les 10 villes les plus traversées et les écrire dans le fichier de sortie
    // Vous devrez parcourir l'arbre AVL et effectuer le tri en fonction du nombre total de traversées

    // Libérer la mémoire utilisée par la structure AVL (à compléter selon les besoins)
}