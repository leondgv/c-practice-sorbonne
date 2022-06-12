#ifndef MULTI_ENSEMBLES
#define MULTI_ENSEMBLES

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _element_t element_t;
struct _element_t {
    int valeur;
    int frequence;
    element_t *suivant;
};


element_t *Recherche_val(element_t *ensemble, int val) 
{
    element_t *ens = NULL;
    while (ensemble != NULL)
    {
        if (ensemble->valeur == val) ens = ensemble;
        ensemble = ensemble->suivant;
    }
    if (ens == NULL) return NULL;
    else return ens;
}
element_t * Ajout_tete_ensemble(element_t *ens, int val, int freq)
{
    element_t * new, * tmp = ens;
    new = (element_t *)malloc(sizeof(element_t));
    if (Recherche_val(tmp, val) != NULL)
    {
        while (tmp != NULL)
        {
            if (tmp->valeur == val) 
            {
                tmp->frequence += freq;
            }
            tmp = tmp->suivant;
        }
        return ens;
    }
    new->valeur = val;
    new->frequence = freq;
    new->suivant = ens;
    return new;
}
element_t * Creation_ensemble(int n) 
{
    element_t *ensemble=NULL;
    for (unsigned i = 1; i <= n; ++i) ensemble=Ajout_tete_ensemble(ensemble,i,1);
    return ensemble;
}

void affiche_ensemble(element_t* multi)
{
    while (multi != NULL)
    {
        printf("freq = %d\t",multi->frequence);
        printf("val = %d\n",multi->valeur);
        multi = multi->suivant;
    }
}
#endif