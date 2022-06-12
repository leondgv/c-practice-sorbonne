#include <stdio.h>
#include <stdlib.h>

// EXO 11

int diff(int a, int b)
{
    int x = a - b;
    return x;
}
int calcul(int a, int b)
{
    int x;
    if (a > b) x = diff(a,b);
    else x = diff(b,a);
    return x;
}

// EXO 12

void ma_fonction(int a, int b)
{
    int c1, c2;
    int *d;
    c1 = a + b;
    d = &a;
    *d += 2;
    c2 = a + b;
    printf("a = %d, b = %d\n, c1 = %d, c2 = %d\n, *d = %d\n", a, b, c1, c2, *d);
}
/*
int main(void)
{
    int a = 7, b = 10;

    printf("Avant appel : a = %d, b = %d\n", a, b);

    ma_fonction(a,b);
    printf("Après appel : a = %d, b = %d\n", a, b);

    return 0;
}
*/
// RMK : Les valeurs de a et b restent les mêmes après appel (car ma_fonction est un void!)

// EXO 13

void my_function(int *param1, int param2)
{
    int var_loc = 3;
    *param1 = var_loc * param2;
    param2 = var_loc + 1;
}
/* Teste la fonction ci-dessus
int main(void)
{
    int v1, v2;

    v1 = 10;
    v2 = 3;

    my_function(&v2, v1);
    return 0;
}
*/
// RMK : only the v2 that have the pointeur *param1 changed, the other stays the same. The input (v1, v2) is (10, 3), and its output is (10, 30).

// EXO 14

// QUESTION 1

#define NB_VALEURS 1000
#define VMIN 0
#define VMAX 32000

int valeur_aleatoire(int min, int max)
{
    // Renvoie une valeur choisie aleatoirement entre min et max
    int num = 0;
    for (int i = 0; i < 1; ++i) num = (rand() % (max - min + 1)) + min;
    return num;
}
// RMK : Without srand(time(0)) the function still work normally

int minimum(int val, int valMin)
{
    // Renvoie la plus petite valeur entre val et valMin

    if (val < valMin) return val;
    return valMin;
}
int maximum(int val, int valMax)
{
    if (val > valMax) return val;
    return valMax;
}
/* Tester la fonction ci-dessus
int main(void)
{
    int i, val;
    int min = VMAX, max = VMIN;

    for (i = 0; i < NB_VALEURS; ++i)
    {
        val = valeur_aleatoire(VMIN, VMAX);
        
        min = minimum(val, min);
        max = maximum(val, max);
    }
    printf("MIN = %d, MAX = %d\n", min, max);

    return 0; 
}
*/

// QUESTION 2

void minimum_maximum(int value, int *valMin, int *valMax, int min, int max)
{
    *valMin = minimum(value, min);
    *valMax = maximum(value, max);
}
/* Tester la fonction ci-dessus
int main(void)
{
    int i, val;
    int v_min, v_max; 
    int min = VMAX, max = VMIN;

    for (i = 0; i < NB_VALEURS; ++i)
    {
        val = valeur_aleatoire(VMIN, VMAX);
        
        minimum_maximum(val, &v_min, &v_max, VMIN, VMAX);
    }
    printf("MIN = %d, MAX = %d\n", v_min, v_max);

    return 0; 
}
*/
// RMK : I really don't get this one, but a little progress is considerable :))

// EXO 15

// QUESTION 1

void permute(int *a, int *b)
{
    // Permuter les valeurs des variables
    int diff = *a; 

    *a = *b;
    *b = diff;
} // relire cette fonction dans le livre

int main(void)
{   int q = -20;
    int r = 10;

    permute(&q,&r);
    printf("a = %d,\nb = %d\n", q, r);
    return 0; 
}

// RMK : Kinda stupid method but it works :))

// QUESTION 2

void permute_circulaire(int *a, int *b, int *c)
{
    // Permute circulairement en faisant appel à la fonction permute
    permute(a, b);
    permute(b, c);

    printf("%d %d %d", *a, *b, *c);
}
/*
int main(void)
{
    int q = 10;
    int r = 20; 
    int s = 30;
    permute_circulaire(&q, &r, &s);

    return 0; 
}
*/
// Still don't know why it worked 