#ifndef CELLULE_T
#define CELLULE_T

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct _cellule_t cellule_t;
struct _cellule_t {
    int donnee;
    cellule_t *suivant;
};
cellule_t *creerListe(int d)
{
    // Renvoie une cellule_t dont le champ donné est initialisé avec d
    cellule_t *nCell;
    nCell = (cellule_t *)malloc(sizeof(cellule_t));

    if (nCell == NULL)
    {
        printf("Dépassement de mémoire\n");
        exit(-1);   // exit(status)
    }
    nCell->donnee = d;
    nCell->suivant = NULL;

    return nCell;
}
void Affiche_int_liste(cellule_t *liste)
{
    cellule_t *celle = liste;

    while (celle != NULL)
    {
        printf("%d\t", celle->donnee);
        celle = celle->suivant;
    }
    printf("\n"); 
}
#endif