#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

// Note : Chaine de caractères = Un tableau de caractères dont le dernier caractère a la valeur "\0".
// EXO 20

// QUESTION 1

int compte(char chain[], char cr)
{
    // Compte le nombre d'occurences d'un caractère cr dans une chaine entrée
    int count = 0;
    int taille = strlen(chain);

    for (unsigned i = 0; i < taille; ++i) if (chain[i] == cr) count ++;
    return count; 
}
/*
int main(void)
{
    printf("%d\n", compte("Bonjour", 'o'));

    return 0; 
}
// Note : nếu chỉ có 1 chữ, dùng '', còn lại dùng ""
*/

void affiche_occur(char chain[])
{
    // Affiche le nombre d'occurences de chaque caractère d'une chaine
    int taille = strlen(chain);
    unsigned count = 0;

    for (unsigned i = 0; i < taille; ++i)
    {
        count = compte(chain, chain[i]);
        
        printf("Number of %c : %d\n", chain[i], count); 
    }
}
// Tester la fonction ci-dessus
/*
int main(void)
{
    char chaine[] = "Bonjour"; 
    affiche_occur(chaine);

    return 0; 
}
*/
// Phần còn lại chưa nghĩ ra nên sẽ làm sau

// EXO 21

#define NB_VILLES 5
int distances[NB_VILLES][NB_VILLES + 1] = 
{ 
    {29, 0, 598, 900, 504, 995}, 
    {59, 598, 0, 407, 203, 861}, 
    {67, 900, 407, 0, 397, 621}, 
    {75, 504, 203, 397, 0, 694}, 
    {83, 995, 861, 621, 694, 0},
};
void affiche_distances(int dist[NB_VILLES][NB_VILLES + 1])
{
    // Affiche les distances entre les ville 
    int *km;
    km = malloc(NB_VILLES * sizeof(int)); 
    
    printf("%s\t", "km");
    for (unsigned i = 0; i < NB_VILLES; ++i)
    {
        km[i] = distances[i][0];
        printf("%d\t", km[i]);
    }        
    printf("\n");

    for (unsigned j = 0; j < NB_VILLES; ++j)
    {
        for (unsigned k = 0; k <= NB_VILLES; ++k)
        {
            if (dist[j][k] == 0) printf("%s\t", "-"); 
            else printf("%d\t", dist[j][k]);
        }
        printf("\n");
    }
}
/* Tester la fonction ci-dessus
int main(void)
{
    affiche_distances(distances);

    return 0; 
}
*/
int plus_proche(int ville, int dist[NB_VILLES][NB_VILLES + 1])
{
    // Utiliser le tableau distances pour calculer la ville la plus proche de celle dont le code correspond au paramètre ville
    int *km;
    km = malloc(NB_VILLES * sizeof(int)); 
    
    for (unsigned i = 0; i < NB_VILLES; ++i) km[i] = distances[i][0];

    int *arr;
    arr = malloc((NB_VILLES + 1) * sizeof(int));
    for (unsigned j = 0; j < NB_VILLES; ++j)
    {
        if (km[j] == ville)
        {
            for (unsigned k = 0; k <= NB_VILLES; ++k) if (dist[j][k] != 0) arr[k] = dist[j][k];
        }
    }

    int min = arr[NB_VILLES];
    for (unsigned m = 1; m <= NB_VILLES; ++m) if ((arr[m] > 0) && (arr[m] < min)) min = arr[m];
    return min;
}
// Tự hào về bài này nhất này :))))
/*
int main(void)
{
    printf("%d\n", plus_proche(83, distances));

    return 0; 
}
*/

// EXO 22

char *int_to_str(int number)
{
    int s = 0;
    int N = 1; 
    // Count the number of number in an integer
    if (number == 0) N = 0;
    else if (number != 0)
    {
        s = number/10;
        while (s != 0)
        {
            s = s/10;
            N += 1;
        }
    }
    char *tab;
    tab = malloc(N * sizeof(int));
    int nb = number;
    int res = 0; 
    int tmp = N;
    for (unsigned i = 0; i < N; ++i)
    {
        res = nb/pow(10,tmp-1);
        tab[i] = res + 48;
        nb -= res * pow(10,tmp-1);
        tmp -= 1; 
    }
    return tab; 
}
int main(void)
{
    printf("%s\n",int_to_str(100));
    return 0; 
}

// EXO 23

// QUESTION 1

int indice_min(int tab[], int taille)
{
    // Renvoie la position de la valeur minimum 
    int min = tab[0];
    for (unsigned i = 0; i < taille; ++i) if (tab[i] < min) min = tab[i];
    int val; 
    for (unsigned j = 0; j < taille; ++j) if (tab[j] == min) val = j;
    return val; 
}
int indice_min_pos_nul(int tab[], int taille)
{
    // Renvoie la valeur min des valeurs positives ou nulles de tab[]
    int pos_nul = 0;
    for (unsigned i = 0; i < taille; ++i) if (tab[i] >= 0) pos_nul += 1;
    // if (pos_nul == 0) return 0;
    int *arr;
    arr = malloc(taille);
    int res = 0; 
    if (pos_nul == 0) res = 0;
    for (unsigned j = 0; j < taille; ++j)
    {
        if (tab[j] >= 0) for (unsigned k = 0; k < pos_nul; ++k) arr[k] = tab[j];
    }
    res = indice_min(arr,taille);
    return res;
}
/*
int main(void)
{
    int arr[] = {-3,-2,-1,-1};
    printf("%d\n",indice_min(arr,3));
    printf("%d\n",arr[indice_min_pos_nul(arr,3)]);

    return 0; 
}
*/