#include <stdio.h>
#include <assert.h>

// EXO 6 

// QUESTION 1

int somme_carres(int val, int max) 
{
    /* 
    Hypo : val <= max
    Renvoie la somme des carrés des entiers dans l'intervalle [m,n]
    */

   // somme des carrés
    int res = 0;

    // int courant dans l'intervalle
    int i = val;

    while (i <= max)
    {
        res += i * i;
        i += 1;
    }
    return res; 
}

// QUESTION 2
/*
int main(void)
{
    assert(somme_carres(1,5) == 55); 

    return 0;
}
*/
// QUESTION 3

int somme_carres_for(int val, int max)
{
    // Reformulez somme_carres en remplacant while par for
    int somme = 0;
    int i;
    for (i = val; i <= max; ++i) somme += i * i;
    return somme;
}
// EXO 2

#define MAX 5

int premier(int number)
{
    // Renvoie 1 si number est un premier, et 0 sinon
    
    _Bool i_est_premier = 0;
    
    for (int i = 2; i <= number; ++i)
    {
        i_est_premier = 1;

        for (int j = 2; j <= i - 1; ++j) if (i%j == 0) i_est_premier = 0;
    }
    return i_est_premier;
}
void afficheNombresPremiers(int max)
{
    // Printf les nombres premiers inférieurs ou égaux à max

    for (int i = 0; i <= max; ++i) if (premier(i)) printf("%d\n", i);
}
/* Test la fontion afficheNombresPremiers ci-dessus
int main(void)
{
    afficheNombresPremiers(5);
    return 0;
}
*/

// EXO 8

void afficheBilletsPieces(int somme) 
{
    /* 
    Hyp : somme > 0. 
    Affiche la décomposition en billets ou pièces de 5,2,1 euro 
    */
    int nb_5, nb_2, nb_1;
    int somme_tmp = somme;
    
    nb_5 = somme_tmp / 5;
    somme_tmp = somme_tmp - (5 * nb_5);
    
    nb_2 = somme_tmp / 2;
    somme_tmp = somme_tmp - (2 * nb_2);
    
    nb_1 = somme_tmp;
    printf("%d = %d * 5 euros + %d * 2 euros + %d * 1 euros\n", somme,nb_5,nb_2,nb_1);
}

void afficheBilletPiecesMultiple(int somme) 
{
    /* 
    Hyp : somme > 0. 
    Affiche toutes les décompositions possibles de somme en billets pieces de 5,2,1 euro 
    */
    int nb_5, nb_2, nb_1, somme_tmp;
    somme_tmp = somme;
    nb_5 = somme_tmp / 5;
    
    while (nb_5 >= 0) 
    {
        somme_tmp = somme - (5 * nb_5);
        nb_2 = somme_tmp / 2;
        
        while (nb_2 >= 0) 
        {
            nb_1 = somme_tmp - (nb_2 * 2);

            printf("%d = %d * 5 euros + %d * 2 euros + %d * 1 euros\n", somme, nb_5, nb_2, nb_1);
            nb_2--;
        }
        nb_5--;
    }
}
/* Tester la fonction de l'exo 8
int main()
{
    afficheBilletPiecesMultiple(13);
    
    return 0 ; 
}
*/

// EXO 9

int sommeDiv(int n)
{
    int somme = 0;

    for (int i = 1; i < n; ++i) if (n % i == 0) somme += i;
    return somme;
}

int kParfait(int n, int k)
{
    int product = 1;
    int res = 0;

    for (int i = 1; i < n; ++i)
    {
        if (n % i == 0)
        {
            product *= i;
            res += 1;
        }
    }
    if ((product == sommeDiv(n)) && (res == k)) return 1;
    return 0;
}
/* Tester la fonction ci-dessus
int main(void)
{
    printf("%d\n", kParfait(6,3));
    
    return 0;
}
*/

// EXO 10

// Quest : Pourquoi est-il fortement déconseillé d'utiliser la fonction assert pour tester directement la fonction surface_float ?
/* 
=> Il est fortement déconseillé d'utiliser directement la fonction assert pour tester une fonction de type float car on ne peut pas savoir combien de valeurs existant après la virgule (ce n'est que une valeur près)
Il est conseillé d'utiliser son égale à epsilon près afin d'obtenir un meilleur résultat
*/

// QUESTION 2

float valeur_absolue(float val)
{
    // Renvoie la valeur absolue d'un input
    if (val > 0) return val;
    else return -val;
}
int main(void)
{
    printf("%.2f\n", valeur_absolue(-3.5));
    return 0;
}

// QUESTION 3 : Pas compris exactement :))
