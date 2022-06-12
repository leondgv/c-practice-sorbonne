#include <stdio.h>
#include <stdlib.h>

// EXO 16

// QUESTION 1

void afficheTab(float *tab, unsigned taille)
{    
    for (unsigned i = 0; i < taille; ++i) printf("%.1f\n", tab[i]); 
}
/* Tester la fonction ci-dessus
int main(void)
{
    float tableau[] = {1, 2, 3};
    afficheTab(tableau, 3);

    return 0; 
}
*/

// QUESTION 2 : I don't really understand what it wanted

// QUESTION 3

void echangeTab(float *tab, int a, int b, unsigned taille)
{
    for (unsigned i = 0; i < taille; ++i)
    {            
        int val_a = tab[a];
        if (i == a)
        {
            tab[i] = tab[b];
            tab[b] = val_a;
        }
        printf("%.1f\n", tab[i]);
    }
}
/* Tester la fonction ci-dessus
int main(void)
{
    float hihi[] = {1, 5, 4, 3, 6};
    echangeTab(hihi,1,2,5);
    return 0; 
}
*/

// EXO 17

// QUESTION 1

#define N 4
/*
int main(void)
{
    int i; 
    int tab[N];

    for (i = 0; i < N; ++i)
    {
        tab[i] = 2 * i + 1;
        printf("%d\t", tab[i]);
    }
    printf("\n");

    return 0; 
}
*/

// QUESTION 2
/*
int main(void)
{
    int i; 
    int *tab;
    tab = malloc(N * sizeof(int)); 

    for (i = 0; i < N; ++i)
    {
        tab[i] = 2 * i + 1;
        printf("%d\t", tab[i]);
    }
    printf("\n");

    return 0; 
}
*/
// QUESTION 3

// Ce code ne fonctionne pas car étant donné qu’il n’y a plus de pointeur alloué, la copie de structures s’en trouve simplifiée et peut être réalisée sans opération particulière (ce qui était l’objectif recherché).vToutefois, cela entraîne une autre conséquence: il n’est plus possible d’assigner une valeur à une variable de type tableau, seuls ses éléments peuvent se voir affecter une valeur. Ainsi, le code suivant est incorrect puisqu’il n’y a aucun pointeur pour recevoir l’adresse du premier élément du tableau tab2.

// EXO 18

// QUESTION 1

void tabStatique(int n)
{
    // Déclarer un tableau statique de N entiers, l'initialise avec les valeurs de 1 à N et l'affiche

    int *tab;
    tab = malloc(n * sizeof(int));

    for (unsigned i = 0; i < n; ++i)
    {
        tab[i] = i + 1;
        printf("%d\t", tab[i]);
    }
    printf("\n");
}
/* Tester la fonction ci-dessus
int main(void)
{
    tabStatique(6);
    return 0; 
}
*/

// QUESTION 2

void init_alea(int n, int min, int max)
{
    // Initialiser un tableau d'entiers avec des valeurs tirées aléatoirement entre deux entiers min et max

    int num = 0;
    int *tab = malloc(n * sizeof(int));

    for (int i = 0; i < n; ++i)
    {
        num = (rand() % (max - min + 1)) + min;
        tab[i] = num;
        printf("%d\t", tab[i]);
    }
    printf("\n");
}
/*
int main(void)
{
    init_alea(7, 1, 8);
    
    return 0;
}
*/

// EXO 19

#include <time.h>
/*
int *tirage(int max, int chance_max)
{
    // Renvoie le tirage de 5 numeros + numero chance
    int i; 
    int res[6];

    for (i = 0; i < 5; ++i)
    {
        res[i] = 1 + (rand() % max);
    }
    res[5] = 1 + (rand() % chance_max);

    return res;
}
int main(void)
{
    int i;
    int *loto;

    srand(time(0));
    loto = tirage(49, 10);

    printf("Tirage du jour : ");

    for(i = 0; i < 5; ++i)
    {
        printf("%d\t", loto[i]);
    }
    printf("\nNumero chance : %d\n", loto[5]);

    return 0; 
}
*/
// Cette fonction est généralement erronnée. La pile a été arrêtée dès l'initialisation de la variable "loto = tirage(49,10)" (comme a expliqué à la 3è question de l'exo 17) 