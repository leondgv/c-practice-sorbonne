#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

// fr. 22 March .22

typedef struct _cellule_t cellule_t;
struct _cellule_t {
    int donnee;
    cellule_t *suivant;
};

cellule_t *Creer_cellule(int d)
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

int len(cellule_t *liste)
{
    int cpt = 0;
    while (liste != NULL)
    {
        cpt++;
        liste = liste->suivant;
    }
    return cpt;
}
int existe(cellule_t *liste, int val)
{
    // Renvoie 0 si val ne dépend pas de liste et 1 sinon
    while (liste != NULL)
    {
        if (liste->donnee == val) return 1;

        liste = liste->suivant;
    }
    return 0;
}
cellule_t *Renvoie_element_debut(int val, cellule_t *liste)
{
    while (liste != NULL)
    {
        if (liste->donnee == val) return liste;
        liste = liste->suivant;
    }
    return NULL;
}
cellule_t *Renvoie_element_fin(int val, cellule_t *liste)
{
    cellule_t *retour = NULL;
    while (liste != NULL)
    {
        if (liste->donnee == val) retour = liste;

        liste = liste->suivant;
    }
    return retour;
}
cellule_t *Renvoie_dernier_element(cellule_t *liste)
{
    if (liste != NULL) return NULL;
    while (liste->suivant != NULL) liste = liste->suivant;
    return liste;
}
cellule_t *Modifier_element(int val, int pos, cellule_t *liste)
{
    while (liste != NULL && pos > 0)
    {
        liste = liste->suivant;
        pos--;
    }
    if (liste != NULL) liste->donnee = val;
    return liste;
}

// 29 March .22

cellule_t *Inserer_tete(int d, cellule_t *liste)
{
    // Renvoie la liste à laquelle un élément de valeur d a été ajouté en tête de la liste *
    cellule_t *new;
    new = Creer_cellule(d);

    new->suivant = liste;
    return new;
}
cellule_t *Inserer_fin_it(int d, cellule_t *liste)
{
    cellule_t *new, *dernier;
    new = Creer_cellule(d);

    if (liste == NULL) return new;
    
    dernier = liste;
    while (dernier->suivant != NULL) dernier->suivant = new;
    dernier->suivant = new;

    return liste;
}
cellule_t *Inserer_liste_pos_it(int d, int pos, cellule_t *liste)
{
    cellule_t *new, *tmp;
    new = Creer_cellule(d);

    if (liste == NULL || pos == 0)
    {
        new->suivant = liste;
        return new;
    }
    tmp = liste;
    
    while (tmp->suivant != NULL)
    {
        tmp = tmp->suivant;
        pos--;
    }
    new->suivant = tmp->suivant;
    tmp->suivant = new;

    return liste;
}
cellule_t *Liberer_liste(cellule_t *liste)
{
    // Déalloue toutes les cellules de liste dans le TAS
    cellule_t *tmp;
    while (liste != NULL)
    {
        tmp = liste; 
        liste = liste->suivant;
        free(tmp);
    }
    return NULL;
}
cellule_t *Supprimer_en_pos_it(int pos, cellule_t *liste)
{
    cellule_t *tmp, *p;

    if (liste == NULL) return NULL;
    if (pos == 0)
    {
        tmp = liste;
        liste = liste->suivant;
        free(tmp);
        return liste;
    }
    p = liste;

    while (p->suivant != NULL && pos > 1)
    {
        p = p->suivant;
        p->suivant = tmp->suivant;
        free(tmp);
    }
    return liste;
}
int liste_identiques(cellule_t *l1, cellule_t *l2)
{
    while (l1 != NULL && l2 != NULL)
    {
        if (l1->donnee != l2->donnee) return 0;
        l1 = l1->suivant;
        l2 = l2->suivant;
    }
    return (l1 == NULL && l2 == NULL);
}

// Le reste

int main(void)
{
    cellule_t *tete;
    tete = Creer_cellule(1);
    tete->suivant = Creer_cellule(2);
    tete->suivant->suivant = Creer_cellule(3);

    Affiche_int_liste(tete);
    cellule_t *celle1 = NULL, *celle2 = NULL, *celle3 = NULL;
    celle1 = Creer_cellule(1);
    celle2 = Creer_cellule(2);
    celle3 = Creer_cellule(3);

    celle1->suivant = celle2;
    celle2->suivant = celle3;
    Affiche_int_liste(celle1);
    Affiche_int_liste(celle2);
    Affiche_int_liste(celle3);
    printf("celle1 = %d\n",celle1[2].donnee);

    return 0; 
}

// 14 April 2022

cellule_t *Renvoyer_element_debut_rec(int val, cellule_t *liste)
{
    if (liste == NULL) return NULL;
    else if (liste->donnee == val) return liste;

    return Renvoyer_element_debut_rec(val,liste->suivant);
}
cellule_t *Inserer_fin_rec(int d, cellule_t *liste)
{
    if (liste == NULL) return Creer_cellule(d);
    liste->suivant = Inserer_fin_rec(d, liste->suivant);
    return liste;
}
cellule_t *Supprimer_en_pos_rec(cellule_t *liste, int pos)
{
    cellule_t *tmp;
    if (liste == NULL) return NULL;
    else if (pos == 0)
    {
        tmp = liste->suivant;
        free(liste);
        return tmp;
    }
    liste->suivant = Supprimer_en_pos_rec(liste->suivant,pos-1);
    return liste;
}
cellule_t *Creer_liste_positifs(cellule_t *liste)
{
    cellule_t *resultat = NULL;
    while (liste != NULL)
    {
        if (liste->donnee >= 0) resultat = Inserer_tete(liste->donnee, resultat);
        liste = liste->suivant;
    }
    return resultat;
}
// RMK : Nếu sử dụng récursif thì KHÔNG dùng while. Nếu dùng itératif thì dùng if trước và while sau đó
cellule_t *Creer_liste_positifs_rec(cellule_t *liste)
{
    if (liste == NULL) return NULL;
    else if (liste->donnee >= 0) return Inserer_tete(liste->donnee, Creer_liste_positifs_rec(liste->suivant));

    return Creer_liste_positifs_rec(liste->suivant);
}

// This one is the most complicate for me to understand

cellule_t *Garder_positifs(cellule_t *liste)
{
    cellule_t *pred = NULL, *ptr = liste;
    while (ptr != NULL)
    {
        if (ptr->donnee < 0)
        {
            if (pred == NULL)
            {
                liste = ptr->suivant;
                free(ptr);
                ptr = liste;
            }
            else 
            {
                pred->suivant = ptr->suivant;
                free(ptr);
                ptr = pred->suivant;
            }
        }
        else 
        {
            pred = ptr;
            ptr = ptr->suivant;
        }
    }
    return liste;
}

// Last TD

typedef struct _element_t element_t;
struct _element_t {
    int valeur;
    int frequence;
    element_t *suivant;
};

// This one is a lot more complicate than the other one

element_t *Creer_multi_ensemble_liste(cellule_t *liste)
{
    element_t *res = NULL, *l_multi;
    cellule_t *ptr = liste;

    if (ptr != NULL)
    {
        res = (element_t *)malloc(sizeof(element_t));
        res->valeur = ptr->donnee;
        res->frequence = 1;
        res->suivant = NULL;

        l_multi = res;
        ptr = ptr->suivant;
    }
    while (ptr != NULL)
    {
        if (ptr->donnee == l_multi->valeur) l_multi->frequence++;
        else 
        {
            l_multi->suivant = (element_t *)malloc(sizeof(element_t));
            l_multi->suivant->valeur = ptr->donnee;
            l_multi->suivant->frequence = 1;
            l_multi->suivant->suivant = NULL;
            
            l_multi = l_multi->suivant;
        }
        ptr = ptr->suivant;
    }
    return res;
}