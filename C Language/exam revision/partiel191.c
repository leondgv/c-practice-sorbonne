#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int* creer_tab(int len)
{
    int *tab;
    tab = malloc(sizeof(int) * len);
    for (unsigned i = 0; i < len; ++i) *(tab + i) = i;  // or tab[i] = i;
    return tab;
}
void deplacer(int i, int t[])
{
    int x = t[0];
    for (unsigned j = 0; j < i; ++j) t[j] = t[j + i];
    t[i] = x;
}
void coupe(int c, int t[], int tt[], int len)
{
    int i, ii = 0;
    for (i = c; i < len; ++i) 
    {
        tt[ii] = t[i];
        ++ii;
    }
    for (i = 0; i < c; ++i)
    {
        tt[ii] = t[i];
        ++ii;
    }
}
void intercale(int c,int t[],int tt[],int len)
{
    int i1 = 0, i2 = c, ii = 0;
    while (ii < len)
    {
        if (i2 < len)
        {
            tt[ii] = t[i2];
            ++i2;
            ++ii;
        }
        if (i1 < c)
        {
            tt[ii] = t[i1];
            ++i1;
            ++ii;
        }
    }
}
int randb(int i1, int i2)
{
    return i1 + rand()%(i2 - i1 + 1);
}
int* battre(int len)
{
    int *t1 = creer_tab(len);
    int t2[len];
    int d = randb(1,len - 1);
    deplacer(d,t1);
    d = (len / 2) - 1;
    for (unsigned i = 0; i < 42; ++i)
    {
        coupe(d,t1,t2,len);
        intercale(d,t2,t1,len);
    }
    return t1;
}


struct s_carte {
    char* figure;
    char* couleur;
    struct s_carte *suivant;
};
typedef struct s_carte carte;

// This one is hard af dude :)))))))