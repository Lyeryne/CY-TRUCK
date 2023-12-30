#include"avl.h"

pArbre creerArbre(int e)
{
    pArbre a = malloc(sizeof(Arbre));
    if (a == NULL)
    {
        exit(1);
    }
    a->fg = NULL;
    a->fd = NULL;
    a->equilibre = 0;
    a->elt = e;
    for(int i=0; i<SIZE1; i++)
    {
        a->tab_distance[i] = 0;
    }
 /* i=0 //distance maxi
    i=1;//distance mini
    i=2;//distance totale
    i=3;//compteur       */
    return a;
}

int existeFilsDroit(pArbre a)
{
    if (a != NULL)
    {
        return a->fg == NULL;
    }
    return 0;
}

pArbre insertionAVL(pArbre a, int e, int *h)
{
    if (h == NULL)
    {
        exit(2);
    }
    if (a == NULL)
    {
        *h = 1;
        return creerArbre(e);
    }
    else if (e < a->elt)
    {
        a->fg = insertionAVL(a->fg, e, h);
        *h = -*h;
    }
    else if (e > a->elt)
    {
        a->fd = insertionAVL(a->fd, e, h);
    }
    else
    {
        *h = 0;
        return a;
    }
    if (*h != 0)
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

pArbre supprAVL(pArbre a, int e, int *h)
{
    if (h == NULL)
    {
        exit(3);
    }
    if (a == NULL)
    {
        *h = 1;
        return a;
    }
    else if (e > a->elt)
    {
        a->fd = supprAVL(a->fd, e, h);
    }
    else if (e < a->elt)
    {
        a->fg = supprAVL(a->fg, e, h);
    }
    else if (existeFilsDroit(a))
    {
        a->fg = suppMinAVL(a->fd, h, &a->elt);
    }
    else
    {
        pArbre tmp = a;
        a = a->fg;
        free(tmp);
        *h = -1;
    }
    if (a == NULL)
    {
        *h = 0;
    }
    if (*h != 0)
    {
        a->equilibre = a->equilibre + *h;
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

pArbre suppMinAVL(pArbre a, int *h, int *pe)
{
    if (h == NULL || pe == NULL)
    {
        exit(4);
    }
    if (a->fg == NULL)
    {
        *pe = a->elt;
        *h = -1;
        pArbre tmp = a;
        a = a->fd;
        free(tmp);
        return a;
    }
    else
    {
        a->fg = suppMinAVL(a->fg, h, pe);
        *h = -*h;
    }
    if (*h != 0)
    {
        a->equilibre = a->equilibre + *h;
        if (a->equilibre == 0)
        {
            *h = -1;
        }
        else
        {
            *h = 0;
        }
    }
    return a;
}

pArbre rotationGauche(pArbre a)
{
    if (a == NULL)
    {
        exit(5);
    }
    pArbre pivot;
    int eq_a, eq_p;
    pivot = a->fd;
    a->fd = pivot->fg;
    pivot->fg = a;
    eq_a = a->equilibre;
    eq_p = pivot->equilibre;
    a->equilibre = eq_a - fmax(eq_p, 0) - 1;
    pivot->equilibre = fmin(eq_a - 2, eq_a + eq_p - 2);
    pivot->equilibre = fmin(pivot->equilibre, eq_p - 1);
    a = pivot;
    return a;
}

pArbre rotationDroit(pArbre a)
{
    if (a == NULL)
    {
        exit(6);
    }
    pArbre pivot;
    int eq_a, eq_p;
    pivot = a->fg;
    a->fg = pivot->fd;
    pivot->fd = a;
    eq_a = a->equilibre;
    eq_p = pivot->equilibre;
    a->equilibre = eq_a - fmax(eq_p, 0) - 1;
    pivot->equilibre = fmin(eq_a - 2, eq_a + eq_p - 2);
    pivot->equilibre = fmin(pivot->equilibre, eq_p - 1);
    a = pivot;
    return a;
}

pArbre doubleRotationGauche(pArbre a)
{
    if (a == NULL)
    {
        exit(7);
    }
    a->fd = rotationDroit(a->fd);
    return rotationGauche(a);
}

pArbre doubleRotationDroit(pArbre a)
{
    if (a == NULL)
    {
        exit(8);
    }
    a->fg = rotationGauche(a->fg);
    return rotationDroit(a);
}

pArbre equilibrerAVL(pArbre a)
{
    if (a == NULL)
    {
        exit(9);
    }
    if (a->equilibre >= 2)
    {
        if (a->fd->equilibre >= 0)
        {
            return rotationGauche(a);
        }
        else
        {
            return doubleRotationGauche(a);
        }
    }
    else if (a->equilibre <= -2)
    {
        if (a->fg->equilibre <= 0)
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