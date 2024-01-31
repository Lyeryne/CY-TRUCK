#include "AVL_T.h"
// Fonction qui retourne le max entre 2 entiers
int max(int a, int b) {
    if(a > b){
        return a;
    }
    else{
        return b;
    }
    
}

//Fonction qui retourne le min entre 2 entiers
int min(int a, int b) {
    if(a > b){
        return b;
    }
    else{
        return a;
    }
}

// Fonction qui retourne la hauteur du noeud N
int hauteur(creerVille *N) {
    if (N == NULL)
        return 0;
    return N->hauteur;
}

// Initialise la première ville de l'arbre
creerVille *nouvelleVille(char *nom) {
    creerVille *ville = (creerVille *)malloc(sizeof(creerVille));
    strcpy(ville->nom, nom);
    ville->CmptVille = 1;
    ville->hauteur = 1;
    ville->gauche = NULL;
    ville->droite = NULL;
    return ville;
}

// Fonctions des rotations pour équilibrer l'arbre

creerVille * rotationDroite(creerVille *a)
{
    //permet de faire une simple rotation a gauche de l'AVL 
    if (a == NULL)
    {
        exit(30);
    }
    creerVille *pivot;
    int eq_a, eq_p;
    pivot = a->gauche;
    a->gauche = pivot->droite;
    pivot->droite = a;
    eq_a = a->hauteur;
    eq_p = pivot->hauteur;
    a->hauteur = eq_a - max(eq_p, 0) - 1;
    pivot->hauteur = min(eq_a - 2, eq_a + eq_p - 2);
    pivot->hauteur = min(pivot->hauteur, eq_p - 1);
    a = pivot;
    return a;
}

creerVille * rotationGauche(creerVille *a)
{
    //permet de faire une simple rotation a gauche de l'AVL 
    if (a == NULL)
    {
        exit(30);
    }
    creerVille *pivot;
    int eq_a, eq_p;
    pivot = a->droite;
    a->droite = pivot->gauche;
    pivot->gauche = a;
    eq_a = a->hauteur;
    eq_p = pivot->hauteur;
    a->hauteur = eq_a - max(eq_p, 0) - 1;
    pivot->hauteur = min(eq_a - 2, eq_a + eq_p - 2);
    pivot->hauteur = min(pivot->hauteur, eq_p - 1);
    a = pivot;
    return a;
}

// Fonction pour obtenir l'équilibre d'un nœud dans l'arbre
int calculEQUILIBRE(creerVille *N) {
    if (N == NULL)
        return 0;
    return hauteur(N->gauche) - hauteur(N->droite);
}

// Fonction pour ajouter une ville dans l'arbre
creerVille *ajouterVille(creerVille *branche, char *nom) {
    if (branche == NULL)
        return nouvelleVille(nom); //si pas d'arbre le créée

    if (strcmp(nom, branche->nom) < 0)
        branche->gauche = ajouterVille(branche->gauche, nom);//ajoute en fonction de l'ordre alphabétique à gauche
    else if (strcmp(nom, branche->nom) > 0)
        branche->droite = ajouterVille(branche->droite, nom);//ajoute en fonction de l'ordre alphabétique à droite
    else {
        (branche->CmptVille)++;
        return branche;
    }

    // Mettre à jour la hauteur de la branche
    branche->hauteur = 1 + max(hauteur(branche->gauche), hauteur(branche->droite));
    // Vérifie l'équilibre de la branche et effectue les rotations nécessaires
    int balance = calculEQUILIBRE(branche);

    if (balance > 1 && strcmp(nom, branche->gauche->nom) < 0)
        return rotationDroite(branche);

    if (balance < -1 && strcmp(nom, branche->droite->nom) > 0)
        return rotationGauche(branche);

    if (balance > 1 && strcmp(nom, branche->gauche->nom) > 0) {
        branche->gauche = rotationGauche(branche->gauche);
        return rotationDroite(branche);
    }

    if (balance < -1 && strcmp(nom, branche->droite->nom) < 0) {
        branche->droite = rotationDroite(branche->droite);
        return rotationGauche(branche);
    }

    return branche;
}

// Parcours l'arbre et affiche les 10 villes les plus visitées
void Prefixe(creerVille *arbre, creerVille *maxVilles[],unsigned long int *ville) {
    if (arbre != NULL) {
        Prefixe(arbre->gauche, maxVilles, ville);

        if (*ville < NBR_VILLE) {
            maxVilles[(*ville)++] = arbre;
        } else {
            int minVisite = maxVilles[0]->CmptVille;
            int min = 0;

            for (int i = 1; i < NBR_VILLE; i++) {
                if (maxVilles[i]->CmptVille < minVisite) {
                    minVisite = maxVilles[i]->CmptVille;
                    min = i;
                }
            }

            if (arbre->CmptVille > minVisite) {
                maxVilles[min] = arbre;
            }
        }

        Prefixe(arbre->droite, maxVilles, ville);
    }
}
//Fonction qui compare le nombre de trajets de deux villes
int compareTrajet(const void *a, const void *b) {
    const creerVille *villeA = *(const creerVille **)a;
    const creerVille *villeB = *(const creerVille **)b;
    return (villeB->CmptVille - villeA->CmptVille);
}
