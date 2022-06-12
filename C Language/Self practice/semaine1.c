#include <stdio.h>
#include <assert.h>

// EXO 1

// QUESTION 1

unsigned surface(unsigned longueur, unsigned largeur)
{
    // Renvoie le surface d'un rectangle de longueur longueur et de largeur largeur
    return longueur * largeur;
}

int addition(int a, int b)
{
    // Renvoie la somme de 2 entiers input
    return a + b;
}

// QUESTION 2
/*
int main(void)
{
    assert(surface(3, 5) == 15);

    return 0;
}
*/      
// car on ne peut pas avoir plusieurs fonction main

// EXO 2

// QUESTION 1

float multi(int entier, float flottant)
{
    // Renvoie le produit de 2 variables pris en paramètre
    return entier * flottant;
}

// QUESTION 2
/* 
int main(void)
{
    int op1;
    float op2;

    op1 = 3;
    op2 = 2.7;
    printf("%d x %.2f = %.2f", op1, op2, multi(op1, op2));

    return 0;
}
*/

// EXO 3

// QUESTION 1

int plusGrand(int a, int b, int c)
{
    // Renvoie le plus grand des 3 nombres
    if ((b < a) && (c < a)) return a;
    else if ((a < b) && (c < b)) return b;
    else return c;
}

// QUESTION 2
/*
int main(void)
{
    printf("%d\n", plusGrand(3,6,5));

    return 0;
}
*/

// QUESTION 3

int plusGrand_cinq(int a1, int a2, int a3, int a4, int a5)
{
    // Renvoie le plus grand des 5 nombres
    int b1 = plusGrand(a1, a2, a3);
    int b2 = plusGrand(a2, a3, a4);
    int b3 = plusGrand(a3, a4, a5);

    return plusGrand(b1, b2, b3);
}

// EXO4

// QUESTION 1

int signeSomme(int a, int b)
{
    // Renvoie le signe  des sommes
    if (a + b == 0) return 0; 
    else if (a + b < 0) return -1;
    else return 1; 
}

// QUESTION 2
/*
int main(void){
    assert(signeSomme(-3, 4) == 1);

    return 0;
}
*/

// EXO 5

#define TNORMAL 11.40
#define TMOINS14 4.50
#define TMOINS26S 4.90
#define TMOINS26WE 7.90
#define TMATIN 7.10

float prixPlace(int age, int jour, float heure)
{
    float total = 0;
    if (age < 14) total = TMOINS14;
    else if ((14 <= age) && (age < 26))
    {
        if ((1 <= jour) && (jour <= 5)) total = TMOINS26S;
        else total = TMOINS26WE;
    }
    else if ((8 < heure) && (heure < 11)) total = TMATIN;
    else total = TNORMAL;
    return total; 
}
int main(void)
{
    printf("%.2f\n", prixPlace(15, 5, 9));

    return 0;
}