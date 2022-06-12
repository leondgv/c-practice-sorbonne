#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int *somCumulee(int t[], int n)
{
    int *tCumul = malloc(sizeof(int) * n);
    tCumul[0] = t[0];
    for (unsigned i = 1; i < n; ++i) tCumul[i] = tCumul[i - 1] + t[i];
    return tCumul;
}
int tirerSelonScore(int t[], int n)
{
    int r = -1, *tCumul = somCumulee(t, n), i = 1;
    if (tCumul[n - 1] > 0)
    {
        r = rand() % tCumul[n - 1];
        i = 0;
        while (tCumul[i] <= r) ++i;
    }
    free(tCumul);
    return i;
}

#define NB_LG 4
#define NB_COL 5
void initMonde(int monde[NB_LG][NB_COL])
{
    unsigned i, j;
    for (i = 1; i < NB_LG - 1; ++i) for (j = 1; j < NB_COL - 1; ++j) monde[i][j] = 1;
    for (i = 0; i < NB_LG; ++i)
    {
        monde[i][0] = 0;
        monde[i][NB_COL - 1] = 0;
    }
    for (j = 0; j < NB_COL; ++j)
    {
        monde[0][j] = 0;
        monde[NB_LG - 1][j] = 0;
    }
}



// Gestion des fourmis, listes
typedef struct _tyFourmi {
    int i;
    int j;
    char sens;
    int energie;
    struct _tyFourmi *suiv;
} tyFourmi;

#define MAX_E 10
tyFourmi* insererEnTete(tyFourmi* listeFourmis)
{
    tyFourmi* fourmi;
    fourmi = malloc(sizeof(tyFourmi));
    fourmi->i = 1;
    fourmi->j = 1;
    fourmi->sens = 'A';
    fourmi->energie = rand() % MAX_E + 1;
    fourmi->suiv = listeFourmis;
    return fourmi;
}
void copiePheromone(int monde[NB_LG][NB_COL], tyFourmi fourmi, int tDir[])
{
    int x = fourmi.i, y = fourmi.j;
    tDir[0] = monde[x - 1][y];
    tDir[1] = monde[x][y - 1];
    if (fourmi.sens == 'A')
    {
        tDir[2] = monde[x + 1][y];
        tDir[3] = monde[x][y + 1];
    }
    else 
    {
        tDir[2] = 0;
        tDir[3] = 0;
    }
}
void bougerUneFourmi(tyFourmi *unefourmi, int monde[NB_LG][NB_COL])
{ 
    int tDir[4], dir;
    copiePheromone(monde, *unefourmi, tDir); 
    dir = tirerSelonScore(tDir, 4);
    if (dir == 0) unefourmi->i -= 1; /* haut */
    else if (dir == 1) unefourmi->j -= 1; /* gauche */ 
    else if (dir == 2) unefourmi->i += 1; /* bas */ 
    else unefourmi->j += 1; /* droite */
}

#define PHEROMONE 10
int majFourmi(tyFourmi *uneFourmi, int monde[NB_LG][NB_COL])
{ 
    int nourriture = 0;
    uneFourmi->energie--;
    if (uneFourmi->i == NB_LG-2 && uneFourmi->j == NB_COL-2)uneFourmi->sens = 'R'; 
    else if (uneFourmi->sens == 'R')
    {
        monde[uneFourmi->i][uneFourmi->j] += PHEROMONE; 
        if (uneFourmi->i == 1 && uneFourmi->j == 1 ) nourriture += 1;
    }
    else if (uneFourmi->i==1 && uneFourmi->j==1 ) 
    {
        if (uneFourmi->sens == 'R') uneFourmi->sens = 'A';
        uneFourmi->energie = MAX_E;
    }
    return nourriture; 
}
int longueurListe(tyFourmi *pListe)
{ 
    int i=0;
    while(pListe)
    { 
        i++;
        pListe=pListe->suiv;
    }
    return i; 
}
int bougerLesFourmis(tyFourmi *pListe, int monde[NB_LG][NB_COL])
{
    tyFourmi *pF = pListe;
    int quantiteNourriture = 0; 
    while(pF)
    {
        bougerUneFourmi(pF, monde);
        quantiteNourriture += majFourmi(pF, monde);
        pF = pF->suiv;
    }
    return quantiteNourriture; 
}
tyFourmi *supprimerUneFourmi(tyFourmi *pListe, tyFourmi *aSupprimer)
{
    tyFourmi *tmp;
    if (pListe == NULL) return NULL;
    else if (pListe == aSupprimer) 
    {
        tmp = pListe->suiv; 
        free(pListe); 
        return tmp;
    }
    pListe->suiv = supprimerUneFourmi(pListe->suiv, aSupprimer); 
    return pListe;
}
tyFourmi * supprimerFourmisMortes(tyFourmi *pListe)
{
    tyFourmi *pF = pListe, *pTmp;
    while(pF)
    { 
        if(pF->energie <= 0)
        {
            pTmp = pF->suiv;
            pListe = supprimerUneFourmi(pListe, pF);
            pF = pTmp;
        }
        else pF = pF->suiv;
    }
    return pListe; 
}
int main(void)
{
    int i, quantiteNourriture=0, monde[NB_LG][NB_COL]; 
    tyFourmi *pListe = NULL;
    initMonde(monde);
    for(i = 0; i < 10; i++) pListe = insererEnTete(pListe);
    /* Deplacer et supprimer les fourmis mortes : utilisation de la
        fonction longueurListe */
    while(longueurListe(pListe) > 0)
    { 
        quantiteNourriture += bougerLesFourmis(pListe, monde); 
        pListe = supprimerFourmisMortes(pListe);
    }
    /*Afficher la quantite de nourriture ramenee*/
    printf("Quantite de nourriture finale %d\n", quantiteNourriture);
    return 0; 
}
