#include <stdio.h>

// EXO 24

// QUESTION 1

int iterative(char *s1, char *s2)
{
    // Renvoie 1 si les chaines sont identiques, 0 sinon
    int i = 0;
    int res;
    while ((s1[i] != '\0') && (s2[i] != '\0'))
    {
        ++i;
        if (s1[i] == s2[i]) res = 1; 
        else res = 0; 
    } 
    return res;
}

// QUESTION 4

int recursive(char *s1, char *s2)
{
    // Version récursive de la fonction iterative 
    if ((*s1 == '\0') && (*s2 == '\0')) return 1; 
    else if (*s1 != *s2) return 0;
    return recursive(s1 + 1, s2 + 1);
}
/*
int main(void)
{
    char *h1 = "Bonjour";
    char *h2 = "Bonjour";

    printf("%d\n",recursive(h1,h2));
    return 0; 
}
*/
// EXO 25

// QUESTION 1

int dichotomy(int tab[], int taille, int elem)
{
    // Déterminer si l'élément appartient à ce tableau trié
    int g = 0, d = taille - 1, m;
    while (g <= d)
    {
        m = (g + d)/2;
        if (tab[m] == elem) return 1;
        else if (tab[m] < elem) g = m + 1;
        else d = m - 1;
    }
    return 0; 
}

// QUESTION 2

int dicho_rec(int tab[], int taille, int elem)
{
    int m;
    if (taille == 0) return 0;
    m = taille/2;
    if (elem == tab[m]) return 1;
    if (elem < tab[m]) return dicho_rec(tab, m, elem);
    return dicho_rec(tab+m+1, taille-(m+1),elem);
}
int main(void)
{
    int arr[] = {1,5,6,7};
    printf("%d\n", dicho_rec(arr,4,6));

    return 0; 
}
// Hard to understand but okay
