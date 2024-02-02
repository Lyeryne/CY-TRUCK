#include "AVL_T.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Fonction qui retourne le min entre 2 entiers
int min(int a, int b) {
    if(a > b){
        return b;//si a est inférieur à b on retourne a
    }
    else{
        return a;//sinon on retourne b
    }
}
// Fonction qui retourne le max entre 2 entiers
int max(int a, int b) {
    if(a > b){
        return a;//si a est plus grand que b on retourne a
    }
    else{
        return b;//sinon on retourne b
    }
    
}
creerVille* rotationGauche(creerVille* a)
{
    // permet de faire une simple rotation a gauche de l'AVL
    if (a == NULL)
    {
        exit(66);
    }
    creerVille* pivot;//on créée le pivot de notre rotation
    int eq_a, eq_p;
    pivot = a->droite;//le fils droit est choisi comme pivot
    a->droite = pivot->gauche;//on fait la rotation
    pivot->gauche = a;//on termine la rotation
    eq_a = a->equilibre;//on vérifie l'équilibre de l'arbre
    eq_p = pivot->equilibre;//et on réajuste en conséquence
    a->equilibre = eq_a - max(eq_p, 0) - 1;
    pivot->equilibre = min(eq_a - 2, eq_a + eq_p - 2);
    pivot->equilibre = min(pivot->equilibre, eq_p - 1);
    a = pivot;//on remet la base de l'arbre au pivot
    return a;// on retourne notre arbre
}

creerVille* rotationDroit(creerVille* a)
{
    // permet de faire une simple rotation a droite de l'AVL
    if (a == NULL)
    {
        exit(66);
    }
    creerVille* pivot;//on créée le pivot de notre rotation
    int eq_a, eq_p;
    pivot = a->gauche;//le fils gauche est choisi comme pivot
    a->gauche = pivot->droite;//on fait la rotation
    pivot->droite = a;//on termine la rotation
    eq_a = a->equilibre;//on vérifie l'équilibre de l'arbre
    eq_p = pivot->equilibre;//et on réajuste en conséquence
    a->equilibre = eq_a - min(eq_p, 0) + 1;
    pivot->equilibre = max(eq_a + 2, eq_a + eq_p + 2);
    pivot->equilibre = max(pivot->equilibre, eq_a + 1);
    a = pivot;//on remet la base de l'arbre au pivot
    return a;// on retourne notre arbre
}

compteID* rotationDroit2(compteID* a)
{
    // permet de faire une simple rotation a droite de l'AVL
    if (a == NULL)
    {
        exit(66);
    }
    compteID* pivot;//se référer à rotationDroit, 
    int eq_a, eq_p;//elle fait la même chose mais avec un type d'arbre différent
    pivot = a->fg;
    a->fg = pivot->fd;
    pivot->fd = a;
    eq_a = a->equilibre;
    eq_p = pivot->equilibre;
    a->equilibre = eq_a - min(eq_p, 0) + 1;
    pivot->equilibre = max(eq_a + 2, eq_a + eq_p + 2);
    pivot->equilibre = max(pivot->equilibre, eq_p + 1);
    a = pivot;
    return a;
}

compteID* rotationGauche2(compteID* a)
{
    // permet de faire une simple rotation a gauche de l'AVL
    if (a == NULL)
    {
        exit(66);
    }
    compteID* pivot;//se référer à rotationGauche
    int eq_a, eq_p;//elle fait la même chose mais avec un type d'arbre différent
    pivot = a->fd;
    a->fd = pivot->fg;
    pivot->fg = a;
    eq_a = a->equilibre;
    eq_p = pivot->equilibre;
    a->equilibre = eq_a - max(eq_p, 0) - 1;
    pivot->equilibre = min(eq_a - 2, eq_a + eq_p - 2);
    pivot->equilibre = min(pivot->equilibre, eq_p - 1);
    a = pivot;
    return a;
}


creerVille* doubleRotationGauche(creerVille* a)
{
    // permet de faire une double rotation a gauche de l'AVL
    // donc rotation simple droite puis rotation simple gauche
    if (a == NULL)
    {
        exit(66);
    }
    a->droite = rotationDroit(a->droite);
    return rotationGauche(a);
}

compteID* doubleRotationGauche2(compteID* a)
{
    // permet de faire une double rotation a gauche de l'AVL
    // donc rotation simple droite puis rotation simple gauche
    if (a == NULL)
    {
        exit(66);
    }
    a->fd = rotationDroit2(a->fd);
    return rotationGauche2(a);
}

creerVille* doubleRotationDroit(creerVille* a)
{
    // permet de faire une double rotation a droite de l'AVL
    // donc rotation simple gauche puis rotation simple droite
    if (a == NULL)
    {
        exit(66);
    }
    a->gauche = rotationGauche(a->gauche);
    return rotationDroit(a);
}

compteID* doubleRotationDroit2(compteID* a)
{
    // permet de faire une double rotation a droite de l'AVL
    // donc rotation simple gauche puis rotation simple droite
    if (a == NULL)
    {
        exit(66);
    }
    a->fg = rotationGauche2(a->fg);
    return rotationDroit2(a);
}

creerVille* equilibrerAVL(creerVille* a)
{
    // fonction pour équilibrer l'AVL en fonction du facteur d'equilibrage
    if (a == NULL)
    {
        exit(66);
    }
    if (a->equilibre >= 2)//vérifie les facteurs d'équilibre pour déterminer le type de rotation
    {
        if (a->droite->equilibre >= 0)//vérifie les facteurs d'équilibre pour déterminer le type de rotation
        {
            return rotationGauche(a);
        }
        else
        {
            return doubleRotationGauche(a);
        }
    }
    else if (a->equilibre <= -2)//vérifie les facteurs d'équilibre pour déterminer le type de rotation
    {
        if (a->gauche->equilibre <= 0)//vérifie les facteurs d'équilibre pour déterminer le type de rotation
        {
            return rotationDroit(a);
        }
        else
        {
            return doubleRotationDroit(a);
        }
    }
    return a;
}

compteID* equilibrerAVL2(compteID* a)
{
    // fonction pour équilibrer l'AVL en fonction du facteur d'equilibrage
    if (a == NULL)
    {
        exit(66);
    }
    if (a->equilibre >= 2)//vérifie les facteurs d'équilibre pour déterminer le type de rotation
    {
        if (a->fd->equilibre >= 0)//vérifie les facteurs d'équilibre pour déterminer le type de rotation
        {
            return rotationGauche2(a);
        }
        else
        {
            return doubleRotationGauche2(a);
        }
    }
    else if (a->equilibre <= -2)//vérifie les facteurs d'équilibre pour déterminer le type de rotation
    {
        if (a->fg->equilibre <= 0)//vérifie les facteurs d'équilibre pour déterminer le type de rotation
        {
            return rotationDroit2(a);
        }
        else
        {
            return doubleRotationDroit2(a);
        }
    }
    return a;
}

void libererArbre(creerVille* a)
{
    // libère tout l'arbre de manière récursive
    if (a != NULL)
    {
        libererArbre(a->gauche);
        libererArbre(a->droite);

        // Libérer la mémoire allouée pour le nom
        free(a->nom);

        // libère le noeud
        free(a);
    }
}

void libererCompteID(compteID* id)
{
    // libère la mémoire pour la structure compteID de manière récursive
    if (id != NULL)
    {
        libererCompteID(id->fg);
        libererCompteID(id->fd);

        // libère le nœud compteID 
        free(id);
    }
}

//fonction qui créée l'arbre contenant les routes ID
compteID *creerAVL3(int IDRoute){
    compteID *route_ID = (compteID *)malloc(sizeof(compteID));
    route_ID->ID_route = IDRoute;//ajout du route ID de ce noeud de l'arbre
    route_ID->equilibre = 0;//equilibre mis a 0
    route_ID->fg = NULL;//noeud unique donc pas de fils
    route_ID->fd = NULL;
    return route_ID;
}

// Initialise la première ville de l'arbre 
creerVille *nouvelleVille(char *nom, int debutTraj, int IDRoute) {
    creerVille *ville = (creerVille *)malloc(sizeof(creerVille));//allocation dynamique de mémoire
    if(ville == NULL){//robustesse : vérification de l'allocation
        exit(66);
    }
    ville->nom = malloc(sizeof(char)*150);//allocation dynamique de mémoire
    if(ville->nom == NULL){//robustesse : vérification de l'allocation
        exit(66);
    }
    strcpy(ville->nom, nom);//copie le nom
    ville->CmptVille = 1;//compte ville est initialisé à 1
    ville->nbrID = IDRoute;//copie ID route actuel
    ville->ID_ville = creerAVL3(ville->nbrID);//créée un arbre de routes ID avec l'ID route actuel
    ville->debutTrajet = 0;//vérification si la ville est une ville de départ de
    if(debutTraj == 1){//si elle est une ville de départ, debutTraj vaut 1, sinon 0
        ville->debutTrajet ++;
    }
    
    ville->gauche = NULL;//création d'1 noeud donc pas de fils
    ville->droite = NULL;
    ville->equilibre = 0;//équilibre initialisé à 0
    return ville;
}

//initialise une des 10 dernieres villes
creerVille* nouvelleVilleFinale(char* nom, int CmptVille, int debut){
    creerVille* ville = malloc(sizeof(creerVille));//se référer à nouvelleVille, où on ne s'intéresse pas à toutes les valeurs
    if(ville == NULL){
        exit(66);
    }
    ville->CmptVille = CmptVille;
    ville->nom = malloc(strlen(nom+1));
    if(ville->nom == NULL){
        exit(66);
    }
    strcpy(ville->nom, nom);
    ville->debutTrajet = debut;
    ville->droite = NULL;
    ville->gauche = NULL;
    return ville;
}

creerVille *creerAVL2(creerVille* ville, int IDRoute) {
    compteID *route_ID = (compteID *)malloc(sizeof(compteID));//se référer à creerAVL3
    route_ID->ID_route = IDRoute;
    route_ID->equilibre = 0;
    route_ID->fg = NULL;
    route_ID->fd = NULL;
    ville->ID_ville = creerAVL3(ville->nbrID);
    return ville;
}


compteID* insertionAVLMilieu(compteID *a, int IDRoute, int *b, int* h)
{
    // fonction d'insertion d'AVL
    if (h == NULL)
    {
        exit(66);
    }
    if (a == NULL)
    {
        // si l'id trajet est nouveau, on crée un AVL
        *h = 1;
        *b = 1;
        return creerAVL3(IDRoute);
    }
    else if (IDRoute < a->ID_route)
    {
        // parcours d'AVL
        a->fg = insertionAVLMilieu(a->fg, IDRoute, b, h);
        *h = -*h;
    }
    else if (IDRoute > a->ID_route)
    {
        // parcours d'AVL
        *h = 0;
        a->fd = insertionAVLMilieu(a->fd, IDRoute, b, h);
        
    }
    else
    {//si le trajet existe déjà rien ne se passe
        *h = 0;
        return a;
    }

    if (*h != 0)//vérif de l'équilibre
    {
        a->equilibre = a->equilibre + *h;
        a = equilibrerAVL2(a);
        if (a->equilibre == 0)
        {
            *h = 0;
        }
        else
        {
            *h = 1;
        }
    }
    return a;
}


creerVille* insertionAVLDebut(creerVille *a, char *nom, int debut, int IDRoute, int* h)
{
    // fonction d'insertion d'AVL
    if (h == NULL)
    {
        exit(66);
    }
    if (a == NULL)
    {
        // si l'id trajet est nouveau, on crée un AVL
        *h = 1;
        return nouvelleVille(nom, debut, IDRoute);
    }
    else if (strcmp(nom, a->nom) < 0)
    {
        // parcours d'AVL
        a->gauche = insertionAVLDebut(a->gauche, nom, debut, IDRoute, h);
        *h = -*h;
    }
    else if (strcmp(nom, a->nom) > 0)
    {
        // parcours d'AVL
        *h = 0;
        a->droite = insertionAVLDebut(a->droite, nom, debut, IDRoute, h);
    }
    else
    {
        // si la valeur d'id est déjà présente
        // rien ne se passe 
        
        
        int* b;
        b = malloc(sizeof(int));//créée un pointeur qui pourra vérifier si un id a été ajouté
        if(b == NULL){
            exit(66);
        }
        *b = 0;
        a->ID_ville = insertionAVLMilieu(a->ID_ville,IDRoute, b, h);
        if(*b == 1){//si un ID a ete ajoute on augmente le compte d'IDs
        (a->CmptVille)++;
        }
        *h = 0;
        if(debut == 1){//on vérifie si la ville est une ville de début de trajet 
            a->debutTrajet ++;
    }
        return a;
    }
    if (*h != 0)//vérification de l'équilibre et ajusteents éventuels
    {
        a->equilibre = a->equilibre + *h;
        a = equilibrerAVL(a);
        if (a->equilibre == 0)
        {
            *h = 0;
        }
        else
        {
            *h = 1;
        }
    }
    return a;
}

creerVille* creerArbreFinal(int CpVille, int dbT, char* nomination){
    creerVille *b = malloc(sizeof(creerVille));//se référer à nouvelleVille
    if(b == NULL){//on prend seulement les informations importantes à l'arbre final(nom, compteur d'ID, compteur de Debuts)
        exit(66);
    }
    b->CmptVille = CpVille;
    b->nom = malloc(sizeof(char)*150);
    if(b->nom == NULL){
        exit(66);
    }
    b->nom = strcpy(b->nom, nomination);
    b->debutTrajet = dbT;
    b->equilibre=0;
    return b;
}

creerVille* insertionAVLFinal(creerVille *a, int CmptVille, int debutTrajet, char* nom, int* h)
{//a=b b= racine
    // fonction d'insertion d'AVL
    if (h == NULL)
    {
        exit(66);
    }
    if (a == NULL)
    {
        // si l'id trajet est nouveau, on crée un AVL
        *h = 1;
        return creerArbreFinal(CmptVille, debutTrajet, nom);
    }
    else if (CmptVille < a->CmptVille)
    {
        // parcours d'AVL
        a->gauche = insertionAVLFinal(a->gauche, CmptVille, debutTrajet, nom, h);
        *h = -*h;
    }
    else if (CmptVille > a->CmptVille)
    {
        // parcours d'AVL
        *h = 0;
        a->droite = insertionAVLFinal(a->droite, CmptVille, debutTrajet, nom, h);
    }
    else{
        *h = 0;
        return a;
    }

    if (*h != 0)//verif d'équilibrage et ajustements en fonction
    {
        a->equilibre = a->equilibre + *h;
        a = equilibrerAVL(a);
        if (a->equilibre == 0)
        {
            *h = 0;
        }
        else
        {
            *h = 1;
        }
    }
    return a;
}

creerVille* insertionABRVraimentFinal(creerVille *a, char *nom, int compteurV, int debut)
{//insertion d'un arbre VRAIMENT TRES TRES final

    if (a == NULL)
    {
        return nouvelleVilleFinale(nom, compteurV, debut);//premier élément de l'arbre
    }
    else if (strcmp(nom, a->nom) < 0)
    {
        a->gauche = insertionABRVraimentFinal(a->gauche, nom, compteurV, debut);//insertion dans l'ordre alphabétique
    }
    else if (strcmp(nom, a->nom) > 0)
    {
        a->droite = insertionABRVraimentFinal(a->droite, nom, compteurV, debut);
    }
    return a;
}

void infixeInverse(creerVille *a)
{
    // fonction récursive qui écris dans le fichier de données de sortie toutes les données nécessaires
    // Le compteur du d'id de la ville, celui du nombre de fois qu'elle est ville de depart
    // parcours de l'arbre infixe inverse pour parcourir dans le sens décroissant
    if (a != NULL)
    {
        infixeInverse(a->droite);
        printf("%s;%d;%d\n", a->nom, a->CmptVille, a->debutTrajet);
        infixeInverse(a->gauche);
    }
}

void infixe(creerVille *a)
{
    // fonction récursive qui écris dans le fichier de données de sortie toutes les données nécessaires
    // Le compteur du d'id de la ville, celui du nombre de fois qu'elle est ville de depart
    // parcours de l'arbre infixe  pour parcourir dans le sens croissant
    if (a != NULL)
    {
        infixe(a->gauche);
        printf("%s;%d;%d\n", a->nom, a->CmptVille, a->debutTrajet);
        infixe(a->droite);
    }
}


creerVille* suppMax(creerVille* a, char** pnom, int* CmptVille, int* DebutTrajet) {
    creerVille* tmp;

    // On rappelle la fonction avec le fils droit
    if (a->droite != NULL) {
        a->droite = suppMax(a->droite, pnom, CmptVille, DebutTrajet);
    } else {
        // Si plus de fils droit, on a le successeur
        //on récupère les données importantes
        *pnom = strcpy(*pnom, a->nom);
        *CmptVille = a->CmptVille;
        *DebutTrajet = a->debutTrajet;
        tmp = a;//on créée un tampon
        a = a->gauche;//on remplace a par son éventuel fils gauche
        free(tmp->nom);//on libére le tampon et le pointeur de charactères nom
        free(tmp);
    }
    return a;//on renvoie les d noeud supprimé
}

creerVille* suppression(creerVille* a, char** pnom, int* CmptVille, int* DebutTrajet, char** pnom2, int* CmptVille2, int* DebutTrajet2) {
    creerVille* tmp;

    // Element non présent dans l'arbre
    if (a == NULL) {
        return a;
    }

    // Parcours récursif de l'arbre
    if (a->droite != NULL) {
        a->droite = suppression(a->droite, pnom, CmptVille, DebutTrajet, pnom2, CmptVille2, DebutTrajet2);
    }
    else if (a->gauche == NULL) {//on vérifie comme dans supMax
            tmp = a;
            *pnom2 = strcpy(*pnom2, tmp->nom);
            *CmptVille2 = tmp->CmptVille;
            *DebutTrajet2 = tmp->debutTrajet;
            a = a->droite;
            free(tmp->nom);
            free(tmp);
    }
    else {
        // Élément trouvé : remplacement par le fils gauche éventuel
        *pnom2 = strcpy(*pnom2,a->nom);
        *CmptVille2 = a->CmptVille;
        *DebutTrajet2 = a->debutTrajet;
        a->gauche = suppMax(a->gauche, &a->nom, &a->CmptVille, &a->debutTrajet);

    }
    return a;
}

creerVille* creationArbreFinal2(creerVille* a, creerVille* b)
{
    // fonction récursive pour créer l'arbre final
    // la fonction va parcourir tout l'arbre a et ajouter les valeurs dans l'arbre b initialement nul
    if (a != NULL)
    {
        // facteur d'equilibrage toujours initialisé a 0
        int h = 0;
        b = insertionAVLFinal(b, a->CmptVille, a->debutTrajet, a->nom, &h);
        b = creationArbreFinal2(a->gauche, b);
        b = creationArbreFinal2(a->droite, b);
    }
    return b;
}