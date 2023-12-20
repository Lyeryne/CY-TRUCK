#include<stdio.h>
#include<stdlib.h>

#define SIZE 15

typedef struct _abr
{
    int data;
    struct _abr* fg;
    struct _abr* fd;
}ABR;

typedef ABR* pArbre;
