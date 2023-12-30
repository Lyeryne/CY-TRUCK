#include "avl.h"
#include "s.h"

float **creation_tableau_final(pArbre a, float **tab)
{
    if (tab == NULL)
    {
        printf("Tableau vide");
        exit(2);
    }
    if (a != NULL)
    {
        int i = 0;
        do
        {
            if (tab[i] == NULL)
            {
                printf("Tableau vide");
                exit(2);
            }
            i++;
        } while (a->tab_distance[0] < tab[i][0] && i < SIZE3);

        if (i != 50)
        {
            for (int j = 0; j < SIZE1; j++)
            {
                if (tab[i] == NULL)
                {
                    printf("Tableau vide");
                    exit(2);
                }
                tab[i][j] = a->tab_distance[j];
            }
            tab[i][4] = a->elt;
        }
        tab = creation_tableau_final(a->fd, tab);
        tab = creation_tableau_final(a->fg, tab);
    }
    return tab;
}

void echanger(float **tableau, int a, int b)
{
    float temp[SIZE3];
    if (tableau == NULL)
    {
        printf("Tableau vide");
        exit(2);
    }
    for (int i = 0; i < SIZE3; i++)
    {
        if (tableau[i] == NULL)
        {
            printf("Tableau vide");
            exit(2);
        }
        temp[i] = tableau[a][i];
    }
    for (int i = 0; i < SIZE3; i++)
    {
        tableau[a][i] = tableau[b][i];
    }
    for (int i = 0; i < SIZE3; i++)
    {
        tableau[b][i] = temp[i];
    }
}

int comparer(float a[], float b[])
{
    float diffA = a[0] - a[1];
    float diffB = b[0] - b[1];

    if (diffA > diffB)
    {
        return -1;
    }
    else if (diffA < diffB)
    {
        return 1;
    }
    return 0;
}

void trierTableau(float **tableau, int taille)
{
    if (tableau == NULL)
    {
        printf("Tableau vide");
        exit(2);
    }
    for (int i = 0; i < taille - 1; i++)
    {
        if (tableau[i] == NULL)
        {
            printf("Tableau vide");
            exit(2);
        }
        for (int j = 0; j < taille - i - 1; j++)
        {
            if (comparer(tableau[j], tableau[j + 1]) > 1)
            {
                echanger(tableau, j, j + 1);
            }
        }
    }
}

int main()
{

    pArbre a = NULL;
    pArbre b = a;

    int RouteID;
    float distance;
    while (scanf("%d;%f", &RouteID, &distance) == 2)
    {
        while (b != NULL || RouteID == b->elt)
        {
            if (RouteID < b->elt)
            {
                b = b->fg;
            }
            else if (RouteID > b->elt)
            {
                b = b->fd;
            }
        }
        // donc la mon reuf soit y'a groupe ID soit ya pas
        if (b == NULL)
        {
            a = insertionAVL(a, RouteID, &a->equilibre);
        }
        else
        {
            // distance maximale
            if (b->tab_distance[0] < distance)
            {
                b->tab_distance[0] = distance;
            }
            // distance minimale
            else if (b->tab_distance[1] > distance)
            {
                b->tab_distance[1] = distance;
            }
            // distance totale
            b->tab_distance[2] += distance;
            b->tab_distance[3] += 1;
        }
    }
    free(b);
    float **tab_final = creation_tableau_final(a, tab_final);

    trierTableau(tab_final, SIZE2);
    FILE *chemin = fopen("temp/gnuplot_data_S.txt", "w");

    if (chemin == NULL)
    {
        printf("Erreur lors de l'ouverture du fichier");
        exit(1);
    }
    for (int i = 0; i < SIZE2; i++)
    {
        int a = tab_final[i][4];
        fprintf(chemin, "%d;%d;%f;%f;%f", i, a, tab_final[i][0], tab_final[i][1], tab_final[i][2] / tab_final[i][3]);
        printf("%d;%d;%f;%f;%f", i, a, tab_final[i][0], tab_final[i][1], tab_final[i][2] / tab_final[i][3]);
    }

    for (int i = 0; i < SIZE1; i++)
    {
        free(tab_final[i]);
    }
    free(tab_final);

    return 0;
}