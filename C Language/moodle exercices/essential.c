#include <stdio.h>
#include <math.h>
#include <stdlib.h>
// EXERCICES SUR LES ALTERNATIVES
int discriminant(int a, int b, int c) 
{
    return b*b - 4*a*c;
}
void afficheRacines(int a, int b, int c) {
/* Affiche les racines */
    float dis = discriminant(a,b,c);
    float x = -b / (2*a);

    float x1 = (-b + sqrt(dis)) / (2*a);
    float x2 = (-b - sqrt(dis)) / (2*a);

    if (dis == 0) printf("La racine double est %.2f\n", x);
    else 
    {
        if (dis > 0) printf("Les deux racines sont %.2f et %.2f\n",x1,x2);
        else printf("Pas de racine reelle\n");
    } 
}
int signeProduit(int a, int b)
{
    // Sans calculer le produit, renvoie 0 si le produit est nul, -1 s'il est négatif et 1 sinon
    if (((a < 0) && (b < 0)) || ((a > 0) && (b > 0))) return 1;
    else if ((a == 0) || (b == 0)) return 0;
    else return -1;
}
#define TFAMILLE 57.8
#define TADULTE 22.7
#define TENFANT 10.75

float prixEntree(int nb_a, int nb_e) 
{
    /* Hyp : Prend en paramètre le nombre d'adultes, d'enfant d'au moins 5 ans. Renvoie la somme à payer */
    float total;
    int adult, enfant;
    adult = 0;
    enfant = 0;
    if ((nb_a >= 2) && (nb_e >= 3))
    {
        adult = nb_a - 2;
        enfant = nb_e - 3;
        total = TFAMILLE + adult*TADULTE + enfant*TENFANT;
    } 
    else total = nb_a * TADULTE + nb_e * TENFANT;
    return total;
}


// EXERCICES SUR LES BOUCLES
// Calculer le jour maximum pour que toute la population soit affectée 
int jours(int contact, int population, float percentage)
{
    int susceptible = 0;     // number of susceptible 
    float target = (population * percentage) / 100;
    int nb_jours;

    for (unsigned i = 1; i <= population; ++i)
    {
        susceptible += pow(contact,i);
        target -= susceptible;

        if (target <= susceptible) 
        {
            nb_jours = i;
            break;
        }
    }
    return nb_jours;
}
// Calculer le pourcentage de gens affectée après un nombre de jours indiqués
float pourcentage(int contact, int population, int jours)
{
    // Renvoie le nombre d'infected après un certain nombre de jours en paramètre
    float susceptible = 0;
    float infected = 1;
    float sum = 0;
    float res;
    for (unsigned i = 1; i <= jours; i++)
    {
        susceptible = infected * contact;
        sum = infected + susceptible; 
        infected = sum;
    }
    if (sum > population) res = 100;
    else res = (infected / population) * 100;
    return res;
}
// Afficher les nombres appartenant à l'intersection de 2 intervalle [a1,a2] et [b1,b2]
void afficheIntersection(int a1, int a2, int b1, int b2)
{
    // Affiche les entiers appartenant à leur intersection
    
    for (unsigned i = a1; i <= a2; ++i)
    {
        for (unsigned j = b1; j <= b2; ++j)
        {
            if (i == j) printf("%d ", i);
        }
    }
    if (a2 < b1) printf("Vide\n");
}
// Đoạn này thì tao đéo biết nó là cái gì hết
int valeur(void) 
{
    int n;
    scanf("%d",&n);
    return n;
}
float moyenne(float n)
{
    float s = 0;
    for (unsigned i = 1; i <= n; ++i) s += valeur();
    return s/n;
}
float moyennePos(int n)
{
    int m;
    float s = 0;
    float som = 0;
    if (n == 0) return -1;

    for (unsigned i = 0; i <= n; ++i)
    {
        m = valeur();
        if (m > 0 || m == 0)
        {
            s += m;
            som += 1;
        }
    }
    if (som != 0) return s/som;
    else return -1;
}
void afficheMultiples(int a, int b)
{
    int res = 0;
    for (unsigned i = 1; i < b; ++i)
    {
        res = i * a;
        if (res < b || res == b) printf("%d ",res);
    }
}


// EXERCICES SUR LES POINTEURS
#define NB_VALEURS 6

void pos_neg_zero(int n) 
{
    if (n > 0) printf("%d est positif\n",n);
    else if (n < 0) printf("%d est negatif\n",n);
    else printf("%d est nul\n",n);
}
void echange(int *a, int *b)
{
    int x = *a;
    *a = *b;
    *b = x;
}
void tri_croissant(int *a, int *b)
{
    int x = *a, y = *b;
    if (x >= y) 
    {
        echange(&x,&y);
        *a = x; *b = y;
    }
}
void tri_3(int *a, int *b, int *c)
{
    int x = *a, y = *b, z = *c;
    if (x >= y)
    {
        if (x >= z && z >= y) 
        {
            tri_croissant(&x,&y);
            tri_croissant(&y,&z);
        }
        else if (x >= z && y >= z) tri_croissant(&x,&z);
        else if (z >= x && z >= y) tri_croissant(&x,&y);
        *a = x, *b = y, *c = z;
    }
    else if (y >= x)
    {
        if (z >= x && y >= z) tri_croissant(&y,&z);
        else if (x >= z && y >= z) 
        {
            tri_croissant(&x,&z);
            tri_croissant(&y,&z);
        }
        *a = x, *b = y, *c = z;
    }
}


// EXERCICES SUR LES TABLEAUX
// Conversion le tableau Farenheit en degrés Celsius.
 void conversion(int tabF[],float tabC[],int *taille)
{
    int size = *taille;
    for (unsigned j = 0; j < size; ++j) tabC[j] = (tabF[j]-32.)*5.0/9.0;
}
// Calculer la température moyenne des journées où il a gelé
float moy_temp(float temp[], int nbj)
{
    float s = 0;
    for (unsigned i = 0; i < nbj; ++i) s += temp[i];

    return s/nbj;
}
float moy_temp_gel(float temp[],int nbj)
{
    float s = 0;
    float total = 0;
    for (unsigned i = 0; i < nbj; ++i)
    {
        if (temp[i] < 0)
        {
            s += temp[i];
            total += 1;
        }
    }
    return s/total;
}
// Renvoie la position à laquelle l'élément el doit être inséré dans le tableau d'entiers tab trié par ordre croissant, de manière à préserver l'ordre
int indiceInsert(int tab[], int el, int nb, int taille)
{
    /*
    La fonction renvoie la position à laquelle l'élément el doit être inséré dans le tableau d'entiers tab trié par ordre croissant, de manière à préserver l'ordre. L'insertion se fait sans doublon : si l'élément est déjà présent, il ne devra pas être ajouté.
    Si le tableau est plein ou si l'élément est déjà présent, la fonction renvoie la valeur -1.
    */
   int res;
   if (nb == taille) res = -1;
   else if (el < tab[0]) res = 0;
   else
   {
        for (unsigned i = 0; i < nb; ++i)
        {
            if (tab[i] == el)
            {
                res = -1;
                break;
            }
            else
            {
                if (tab[i] > el) res = i - 1;
                else res = i + 1;
            }
        }
   }
   return res;
}
// Réalise l'insertion de el dans tab si l'élément n'est pas déjà présent et si le tableau n'est pas plein
int insertElt(int tab[], int el, int *nbel, int taille)
{
    int indice = indiceInsert(tab,el,*nbel,taille);
    if (indice == -1) return 0;
    for(int i = *nbel; i > indice; --i) *(tab + i) = *(tab + i - 1);
    *(tab + indice) = el;
    *nbel += 1;
    return 1;
}

void affiche_tab(int tab[], int taille) 
{
	int i;
    for (i = 0; i < taille; i++) printf("%d  ", tab[i]);
    printf("\n");
}
// Renvoie le tableau trié obtenu en fusionnant les deux tableaux
int *fusion (int tab1[], int taille1, int tab2[], int taille2) 
{
/* realise la fusion triee des tableaux tries tab1 et tab2 */
    int taille = taille1 + taille2;
    int *tab_fus = malloc( taille * sizeof(int));
    int i1 = 0;
    int i2 = 0;
    for(int i = 0; i<taille; i++)
    {
        if((i1 < taille1) && ((i2 >= taille2 ) || tab1[i1] <= tab2[i2]))
        {
            tab_fus[i] = tab1[i1];
            i1++;
        }
        else
        {
            tab_fus[i] = tab2[i2];
            i2++;
        }
    }
    return tab_fus;
}


// EXERCICES SUR LES CHAINES DE CARACTÈRES
// Compter les mots d'une chaine de caractères à exclusion des espaces
int compte_mots(char chain[])
{
    int taille = strlen(chain);
    int tmp = 0;
    if (chain[taille-1] != ' ') tmp++;
    if (taille == 0) tmp = 0;


    for (unsigned i = 0; i < taille; ++i)
    {
        if (chain[i] != ' ')
        {
            for (unsigned j = i; j < taille; ++j)
            {
                if (chain[j] == ' ')
                {
                    tmp++;
                    i = j;
                    break;
                }
                else continue;
            }
        }
        else continue;
    }
    return tmp;
}


// EXERCICES SUR LES TABLEAUX MULTI-DIMENSIONEL
//Complétez la fonction init_zero qui initialise à 0 le contenu de chacune des cases du tableau. 
#define NB_JOURS 8
#define NB_AMIS 4

void init_zero(float tab[][NB_JOURS], int taille)
{
    for (unsigned i = 0; i < taille; ++i)
    {
        for (unsigned j = 0; j < NB_JOURS; ++j) tab[i][j] = 0.;
    }
}
// met à jour le tableau des dépenses
void affecte_depenses(float tab[][NB_JOURS], int jour, float montant, int id)
{
    float paid = montant / 4.;
    for (unsigned i = 0; i < NB_JOURS; ++i)
    {
        if (i == jour)
        {
            for (unsigned j = 0; j < NB_AMIS; ++j)
            {
                if (j == id) tab[j][i] = montant - paid;
                else tab[j][i] = -paid;
            }
        }
    }
}
// renvoie le solde de ses dépenses sur l'ensemble du séjour
float calcul_solde(float tab[][NB_JOURS], int id)
{ 
    float somme = 0;
    for (unsigned i = 0; i < NB_AMIS; ++i)
    {
        if (i == id)
        {
            for (unsigned j = 0; j < NB_JOURS; ++j) somme += tab[i][j]; 
        }
    }
    return somme;
}
void affiche_soldes(float tab[][NB_JOURS])
{
    for (unsigned i = 0; i < NB_AMIS; ++i) printf("Solde pour %d : %.2f\n",i,calcul_solde(tab,i));
}
// Comparer les 2 tableaux
int compare_tab(int tab1[], int tab2[]) 
{
    int i = 0;
    while((tab1[i] != -1) && (tab1[i] != -1))
    {
        if (tab1[i] != tab2[i]) return -1;
        ++i;
    }
    if ((tab1[i] != -1) || (tab2[i] != -1)) return -1;
    return 0;
}
// Compress a table
void compress_tab(int tab_brut[], int tab_compress[]) 
{
    int i = 1;
    int j = 0;
    int c = 1;
    int last = tab_brut[0];
    while (tab_brut[i] != -1)
    {
        if (tab_brut[i] == last) ++c;
        else
        {
            if (c != 1) 
            {
                tab_compress[j] = c;
                ++j;
            }
            tab_compress[j] = last;
            tab_compress[j+1] = -1;
            ++j;
            c = 1;
            last = tab_brut[i];
        }
        ++i;
    }
    if (c != 1) 
    {
        tab_compress[j] = c;
        ++j;
    }
    tab_compress[j] = last;
    tab_compress[j+1] = -1;
}
void compress_tab(int tab_brut[], int tab_compress[]) 
{
    int i = 1;
    int j = 0;
    int c = 1;
    int last = tab_brut[0];
    while (tab_brut[i] != -1)
    {
        if (tab_brut[i] == last) ++c;
        else
        {
            if (c != 1)
            {
                tab_compress[j] = c;
                ++j;
            }
            tab_compress[j] = last;
            tab_compress[j+1] = -1;
            ++j;
            c = 1;
            last = tab_brut[i];
        }
        ++i;
    }
    if (c != 1) 
    {
        tab_compress[j] = c;
        ++j;
    }
    tab_compress[j] = last;
    tab_compress[j+1] = -1;
}


// EXERCICES SUR LA RÉCURSIVITÉ SUR LES TABLEAUX ET SUR LES CHAINES DE CARACTÈRES
int recherche_iter(int tab[], int taille , int val)
{
    int i = 0;
    while (i<taille) 
    {
        if (tab[i] == val) return i;
        ++i;
    }
    return -1;
}
// The same with the previous one but recursive style
int recherche_rec(int tab[], int taille, int val)
{
    int i = taille - 1;
    if (taille == 0) return -1;
    if (tab[i] == val) return i;
    else return recherche_rec(tab,i,val);
}
// renvoie l'indice le plus petit auquel se trouve la valeur dans le tableau, -1 si elle n'est pas présente. La fonction doit être récursive.
int recherche_rec_aux(int tab[], int taille,int ind, int val)
{
    if (ind == taille) return -1;
    if (tab[ind] == val) return ind;
    else return recherche_rec_aux(tab,taille,ind+1,val);
}

// This one is actually recherche_rec in moodle
int recherche_rec_main(int tab[], int taille, int elem) 
{
    return recherche_rec_aux(tab, taille, 0, elem);
}
// renvoie 1 si la première chaîne est le début de la deuxième, 0 sinon. 
int est_deb(char chaine1[], char chaine2[])
{
    if (*chaine1 == '\0') return 1;
    if (*chaine1 != *chaine2) return 0;
    return est_deb(chaine1 + 1,chaine2 + 1);
}
// renvoie 1 si la première chaîne est incluse dans la deuxième, 0 sinon.
int est_incluse(char ch1[], char ch2[])
{
    if(*ch2 == '\0') return 0;
    if(est_deb(ch1,ch2) == 1) return 1;
    return(est_incluse(ch1, ch2 + 1));
}
