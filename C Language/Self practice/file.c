#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>

// Nếu không có dấu ! ở is_empty -> is_empty(xs) == 1 còn !empty(xs) == 0

// Pour les fifo
struct cell {
    int donnee;
    struct cell *suivant;
};

// Paire de pointeurs vers des cellules chainables
struct s_fifo {
    struct cell *first;
    struct cell *last;
};
typedef struct s_fifo fifo;

/*
LA FILE VIDE
    Créer une file vide : on donne la valeur NULL aux 2 champs
*/
fifo new_fifo(void)
{
    fifo r;
    r.first = NULL;
    r.last = NULL;

    return r;
}

// Reconnaitre une file vide
int is_empty(fifo xs)
{
    return (xs.first == NULL && xs.last == NULL);
}
/*
AJOUT D'UNE VALEUR
    Le principe : 3 étapes
    1. créer une nouvelle cellule
    2. chainer la nouvelle cellule
    3. mettre à jour le champ last

    1 cas particulier : la première valeur dans une file vide
    1. créer une nouvelle cellule
    2. initialiser les champs first et last
*/
fifo add(int x, fifo xs)
{
    struct cell *c = malloc(sizeof(struct cell));
    c->donnee = x;
    c->suivant = NULL;

    if (is_empty(xs) == 1)
    {
        xs.first = c;
        xs.last = c;
    }
    else 
    {
        xs.last->suivant = c;
        xs.last = c;    // cho vào donnee chứ không cho vào suivant
    }
    return xs;
}

// Valeur de tête (la première ajoutée à la file) -> on obtient la valeur de tête avec le champ first
int peek(fifo xs)
{
    return xs.first->donnee;
}
/*
ATTENTION : fonction partielle, non définie sur les files vides.
*/
// Version défensive : échoue si la file est vide
int peekd(fifo xs)
{
    assert(is_empty(xs) == 0);
    return xs.first->donnee;
}
/*
RETRAIT D'UNE VALEUR
    Le principe : 1 étape -> modifier la valeur du champ first

    1 cas particulier : la dernière valeur
*/
fifo pop(fifo xs)
{
    if (is_empty(xs) == 0)
    {
        xs.first = xs.first->suivant;
        if (xs.first == NULL) xs.last = NULL;
    }
    return xs;
}
// La file est inchangée si elle est vide

/*
UTILITAIRE
    Afficher les valeurs de la file : du plus ancien au plus récent ~ afficher la liste chainée du champ first
*/
void print_fifo(fifo xs)
{
    struct cell *c = xs.first;
    printf("[");

    while (c != NULL)
    {
        printf("(%d)",c->donnee);
        c = c->suivant;
    }
    printf("]\n");
}
// EXEMPLE
/*
int main(void)
{
    fifo xs = new_fifo();
    print_fifo(xs);
    xs = add(1,xs); print_fifo(xs);
    xs = add(2,xs); print_fifo(xs);
    xs = add(3,xs); print_fifo(xs);
    xs = add(4,xs); print_fifo(xs);
    xs = pop(xs); print_fifo(xs);
    xs = pop(xs); print_fifo(xs);
    xs = pop(xs); print_fifo(xs);
    xs = pop(xs); print_fifo(xs);

    return 0; 
}
*/
// Add par effet de bord
void addq(int x, fifo *xs)
{
    struct cell *c = malloc(sizeof(struct cell));
    c->donnee = x;
    c->suivant = NULL;

    if (is_empty(*xs))
    {
        xs->first = c; 
        xs->last = c;
    }
    else 
    {
        xs->last->suivant = c;
        xs->last = c;
    }
}

// Pop par effet de bord
// Gestion de mémoire : libérer l'espace alloué à la cellule supprimée
int popq(fifo *xs)
{
    int x; 
    if (is_empty(*xs) == 0)
    {
        struct cell *d = xs->first;
        x = d->donnee;
        xs->first = xs->first->suivant;
        free(d);

        if (xs->first == NULL) xs->last = NULL;
    }
    return x;
}
int main() {
    fifo xs = new_fifo();
    print_fifo(xs);
    addq(1,&xs); print_fifo(xs);
    addq(2,&xs); print_fifo(xs);
    addq(3,&xs); print_fifo(xs);
    addq(4,&xs); print_fifo(xs);
    popq(&xs); print_fifo(xs);
    popq(&xs); print_fifo(xs);
    popq(&xs); print_fifo(xs);
    popq(&xs); print_fifo(xs);
}