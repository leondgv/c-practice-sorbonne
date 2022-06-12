#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <assert.h>
// STRUCTURE
typedef struct _planete {
    char nom[10];
    float densite;
    float distance;
    int nbsat;
} planete;

void affichePlanete(planete p)
{
    printf("%s : densite = %.2f, distance soleil = %.1f, nb satellites = %d",p.nom,p.densite,p.distance,p.nbsat);
}
// Afficher les carqacatères de toutes les planetes
void afficheToutesPlanetes(planete tab[], int taille)
{
    for (unsigned i = 0; i < taille; ++i) printf("%s : densite = %.2f, distance soleil = %.1f, nb satellites = %d\n",tab[i].nom,tab[i].densite,tab[i].distance,tab[i].nbsat);
}
// Modifier la densité des planètes
void modifieDensite(planete tab[], int taille, int number, float d)
{
    for (unsigned i = 0; i < taille; ++i)
    {
        if (i == number)
        {
            tab[i].densite = d;
            break;
        }
    }
}


// EXERCICES SUR LES PARCOURS SUR LES LISTES
#include "cellule.h"
// Calculer le nombre d'occurences d'un nombre à l'entrée
int nb_occurences(int val, cellule_t *liste)
{
    int occ = 0;
    cellule_t *nCell = liste;
    while (nCell != NULL)
    {
        if (nCell->donnee == val) 
        {
            ++occ;
            nCell = nCell->suivant;
        }
        else nCell = nCell->suivant;
    }
    return occ;
}
// qui renvoie 1 (vrai) si aucun élément de la liste n'est strictement inférieur à la valeur val, 0 (faux) sinon.
int tous_plus_grands(int val, cellule_t *liste)
{
    int v = 0;
    cellule_t *nCell = liste;
    while (nCell != NULL)
    {
        if (nCell->donnee < val) ++v;
        nCell = nCell->suivant;
    }
    if (v == 0) return 1;
    else return 0;
}
// renvoie un pointeur vers la première rencontrée. Si la liste est vide, la fonction renvoie NULL.
cellule_t *maximum(cellule_t *liste)
{
    cellule_t *nCell = liste,*new;
    int val = liste->donnee;
    while (nCell != NULL)
    {
        if (nCell->donnee > val) 
        {
            val = nCell->donnee;
            new = nCell;
        }
        nCell = nCell->suivant;
    }
    return new;
}   // well, at least it works =))))

// renvoie la valeur du champ donnee de l'élément en position pos de la liste (le premier élément est en position 0)
int renvoyer_val_element_pos(int pos, cellule_t* liste)
{
    int s = 0, val;
    cellule_t *nCell = liste;
    while (nCell != NULL)
    {
        if (s == pos) 
        {
            val = nCell->donnee;
            break;
        }
        ++s;
        nCell = nCell->suivant;
    }
    return val;
}


// MULTI_ENSEMBLES
#include "multi_ensembles.h"
// Supprimer totalement la multi-ensemble
element_t * Supprime_total_element(element_t * ensemble, int val)
{
    element_t * tmp;
    if (ensemble == NULL) return NULL;
    else if (ensemble->valeur == val)
    {
        tmp = ensemble->suivant;
        free(ensemble);
        ensemble = tmp;
    }
    else ensemble->suivant = Supprime_total_element(ensemble->suivant,val);
    return ensemble;
}
// Supprimer l'ensemble ayant la valeur à l'entrée
element_t * Supprime_element(element_t * ensemble, int val)
{
    element_t * tmp = ensemble;
    if (ensemble == NULL) return NULL;
    else if (ensemble->valeur == val) 
    {
        if (ensemble->frequence == 1) 
        {
            tmp = ensemble->suivant;
            free(ensemble);
            ensemble = tmp;
        }
        else tmp->frequence -= 1;
    }
    else ensemble->suivant = Supprime_element(ensemble->suivant,val);
    return ensemble;
}
// Ajouter à un ensemble trié
// This shit actually not even works =))))
element_t * Ajout_ensemble_trie(element_t *ensemble, int val, int freq) 
{
    element_t *ens = ensemble, *new;
    new = (element_t*)malloc(sizeof(element_t));
    if (ensemble == NULL)
    {
        new->valeur = val;
        new->frequence = freq;
        return new;
    }
    while (ens!= NULL)
    {
        if (Recherche_val(ensemble,val))
        {
            if (ens->valeur == val) ens->frequence += freq;
            ens = ens->suivant;
        }
        else 
        {
            new->valeur = val;
            new->frequence = freq;
            while (ensemble != NULL)
            {
                if (ensemble->valeur > val) 
                {
                    new->suivant = ensemble;
                    ens->suivant = new;
                }
                ens = ens->suivant;
            }
        }
    }
    return ens;
}
// Supprimer un ensemble trié
element_t *Supprime_total_element_ensemble_trie(element_t * ensemble, int val) 
{
    element_t *tete = ensemble;
    element_t *pre=NULL;
    while (ensemble != NULL && ensemble->valeur != val)
    {
        pre = ensemble;
        ensemble = ensemble->suivant;
    }
    if (ensemble)
    {
        if(pre) pre->suivant = ensemble->suivant; 
        else tete = ensemble->suivant;
        free(ensemble);
    }
    return tete;
}
// Supprimer un element d'un ensemble trié
element_t *Supprime_element_ensemble_trie(element_t * ensemble, int val) 
{
    element_t *cell;
    cell = Recherche_val(ensemble,val);
    if (cell)
    {
        if(cell->frequence==1) return Supprime_total_element_ensemble_trie(ensemble,val);
        else cell->frequence -= 1;
    }
    return ensemble;
}
// Renvoie le nombre d'élément d'un ensemble
int taille(element_t *ens)
{
    element_t *nEns;
    nEns = ens;
    int som = 0;
    while (nEns != NULL)
    {
        som = som + nEns->frequence;
        nEns = nEns->suivant;
    }
    return som;
}
// Supprimer un element dont la fréquence est inférieure au seuil entré
element_t* supprime_frequence_inf_seuil(element_t* ens, int seuil)
{
    element_t * tmp;
    if (ens == NULL) return NULL;
    else 
    {
        if (ens->frequence < seuil)
        {
            tmp = ens->suivant;
            free(ens);
            ens = tmp;
        } 
        else ens->suivant = supprime_frequence_inf_seuil(ens->suivant,seuil);
    }
    return ens;
}   // Cái này mình vẫn không hiểu sao nó không chạy :))
int inclus_rec(element_t* A, element_t* B)
{
    element_t *p, *q;
    int checker = 0;
    for(p = A; p != NULL; p = p->suivant)
    {
        for(q = B; q != NULL; q = q ->suivant)
        {
            if(q->valeur == p->valeur)
            {
                if (p->frequence <= q->frequence) checker = 1;
            }
            else if (q->valeur != p->valeur) break;
        }
    }
    if (A == NULL) checker = 1;
    else if (taille(A) > taille(B)) checker = 0;
    return checker;
}   // Finnally I cheated and it actually fucking works =))))

element_t* inverser(element_t* ens)
{
    element_t* prev = NULL, *current = ens, *next = NULL;
    while (current != NULL)
    {
        next = current->suivant;
        current->suivant = prev;
        prev = current;
        current = next;
    }
    ens = prev;
    return ens;
}