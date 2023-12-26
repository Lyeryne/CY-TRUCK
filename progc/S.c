#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
    float distance_min;
    float distance_max;
    float distance_moyenne;
    int Route_ID;
}Données;






int main(){



    int routeID;
    float distance;
    while(scanf("%d;%f", &routeID, &distance) == 2){
        while(a == NULL){
            if(routeID < a->arbre->route_ID){
                a = a->fg;
            }
            else if(routeID > a->arbre->routeID){
                a = a->fd;
            }
            else{
                if(a == NULL){
                    a = creerArbre()
                }
            }
        }
    }






    return 0;
}