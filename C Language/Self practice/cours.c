#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

/*
Listes vs. tableaux?
Un tableau correspond à une zone contigue de la mémoire, pour accéder au i-ème élément il suffit de connaitre l'adresse du premier -> accéder à la case i est immédiat

Limitations : 
- La mémoire réservée pour le tableau doit être contigue
- Les opérations d'insertion et suppression sont couteuses

De même que les tableaux, les listes chainées servent à stocker un ensemble d'éléments de même type

Sans les limitations des tableaux : 
- insérer un élément sans avoir à recopier la suite du tableau,
- retirer un élément sans avoir à recopier la suite du tableau, 
- ne pas nécessiter l'utilisation de mémoire contigue.
*/
typedef struct _cellule_t cellule_t;
struct _cellule_t {
    int donnee;
    cellule_t *suivant;
};
/*
Construire une liste : 
1. Parcours simples : 
- Afficher une liste 
- Fonction retournant un entier : retourner la somme des éléments d'une liste
- Fonction retournant une liste : retourner la liste ordonnée en sens inverse

2. Parcours pouvant être "interrompus" : 
- Rechercher un élément dans une liste

3. Parcours nécessitant de conserver l'élément précédent :
- Libérer un liste
- Supprimer un élément d'une liste
- Concaténer 2 listes

4. Autres parcours : 
- Parcourir 2 listes -> Fusions 2 listes ordonnées
- Retourner 2 listes
*/
cellule_t *cons(int val, cellule_t *pListe)
{
    cellule_t *el;

    el = malloc(sizeof(cellule_t));
    if (el == NULL) return NULL;
    el->donnee=val;
    el->suivant=pListe;

    return el;
}
void Afficher_liste_int(cellule_t *liste)
{
    cellule_t *cell = liste;
    while (cell != NULL)
    {
        fprintf(stderr, "%d\t", cell->donnee);
        cell=cell->suivant;
    }
    fprintf(stderr, "\n");
}
// Le même avec Afficher_liste_int mais récursive
void Afficher_liste_rec(cellule_t *liste)
{
    cellule_t *cell = liste;
    if (liste != NULL)
    {
        fprintf(stderr, "%d\t", cell->donnee);  // This one is important that I usually forgot
        Afficher_liste_rec(cell->suivant);
    }
    else fprintf(stderr, "\n");
}
int somme_list(cellule_t *cell)
{
    int r = 0;
    while (cell != NULL)
    {
        r += cell->donnee;
        cell=cell->suivant;
    }
    return r;
}
/*
int main(void)
{
    cellule_t *ns = NULL;
    ns = cons(3,ns);
    ns = cons(2,ns);
    ns = cons(1,ns);

    Afficher_liste_rec(ns);
    int x = somme_list(ns);
    printf("somme liste = %d\n",x);

    return 0; 
}
*/
/*
Méthode : Rechercher un élément dans une liste
1. Comment faire?
Pour chaque élément de la liste,
- Si c'est élément cherché, on a fini, retourner l'élément
- Sinon, on continue
Si à la fin on n'a pas trouvé, c'est qu'il n'y est pas

2. Quel est la signature de la fonction?
Plusieurs possibilités :
- chercher un élément selon sa valeur ou son adresse
- retourner un booléen ou un pointeur vers l'élément
*/
cellule_t *rechercher(cellule_t *liste, int val)
{
    while (liste != NULL)
    {
        if (liste->donnee == val) return liste;
        else liste=liste->suivant;
    }
    return NULL;
}
/*
int main(void)
{
    cellule_t *ns, elt;
    
    ns=cons(1,cons(2,cons(3,NULL)));
    assert(rechercher(ns, 1) != NULL);
    assert( rechercher(ns,2 ) != NULL);
    assert( rechercher(ns,3 ) != NULL);
    assert( rechercher(ns,4 ) == NULL);

    return 0;
}
*/
/*
Libérer une liste
Comment faire?
Pour chaque élément de la liste
- Le libérer (free)
- Passer au suivant
*/
cellule_t *Liberer_liste(cellule_t *liste)
{
    cellule_t *tmp;
    while (liste != NULL)
    {
        tmp=liste->suivant;
        free(liste);
        liste=tmp;
    }
    return NULL;
}
/*
int main(void)
{
    cellule_t *ns;
    ns = cons(1,cons(2,cons(3,NULL)));
    ns = Liberer_liste(ns);
    ns = Liberer_liste(ns);

    return 0; 
}
*/
/*
Supprimer un élément d'une liste
Comment faire?
Pour supprimer l'élémenet de valeur 2, il faut donc :
- Trouver l'élément
- Mettre à jour le chainage
- Libérer l'élément

Et si on supprime le premier élément?
-> Il faut donc modifier le pointeur vers la tête de liste

Plusieurs possibilités : 
- supprimer un élément dont on a la valeur ou l'adresse
    Comment faire?
    Version récursive plus simple

    Cas de base : 
    - Si le premier élément est celui que je cherche, alors,
        - On libère l'élément
        - On retourne le suivant de l'élément
    - Sinon,(cas général)
        - On applique la fonction sur le suivant
*/
cellule_t *Supprimer_el_rec(cellule_t *liste, int val)
{
    cellule_t *tmp;
    if (liste)
    {
        if (liste->donnee == val)
        {
            tmp=liste->suivant;
            free(liste);
            liste = tmp;
        }
        else liste->suivant=Supprimer_el_rec(liste->suivant,val);
    }
    return liste;
}
/*
int main(void)
{
    cellule_t *ns;
    ns = cons(1,cons(2,cons(3,NULL)));
    ns = Supprimer_el_rec(ns,2);

    return 0; 
}
*/
/*
Trouver le n-ième élément d'une liste
Comment faire?
On suppose que la numérotation commence à 0
*/
cellule_t *Trouver_elt_n(cellule_t *liste, int n)
{
    while (liste != NULL && n > 0)
    {
        n -= 1;
        liste=liste->suivant;
    }
    return liste;
}
/*
int main(void)
{
    cellule_t *ns, *elt;
    ns = cons(1,cons(2,cons(3,NULL)));
    elt = Trouver_elt_n(ns,1);

    return 0; 
}
*/
/*
Ajouter en fin de liste
Comment faire?
Créer un nouvel élément et l'ajouter après le premier
*/
cellule_t *Ajouter_queue(cellule_t *liste, int val)
{
    cellule_t *tmp = liste, *new;
    new = malloc(sizeof(cellule_t));
    new->donnee=val;
    new->suivant=NULL;  

    if (liste == NULL) return new;
    while (tmp->suivant) tmp = tmp->suivant;

    tmp->suivant = new;
    return liste; 
}
/*
Retourner une nouvelle liste contennant les carrés des éléments
Comment faire? 
Pour chaque élément de la liste courante, il faut créer un nouvel élément de liste contenant le carré de la valeur
Il faut créer une nouvelle liste -> on peut utiliser la foncion d'ajout
*/
cellule_t *liste_carree(cellule_t *pL)
{
    cellule_t *tmp = pL, *new_pL = NULL;
    while (tmp != NULL)
    {
        new_pL = cons(pL->donnee *pL->donnee, new_pL);
        pL=pL->suivant;
    }
    return new_pL;
}
/* Problem with memory acccess
int main(void)
{
    cellule_t *ns=NULL, *ns2;
    ns = cons(1,cons(2,cons(3,ns)));
    ns2 = liste_carree(ns);

    return 0; 
}
*/