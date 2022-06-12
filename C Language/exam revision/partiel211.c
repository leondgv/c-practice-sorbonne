#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// VALIDATION D'ANNEE
#define NB_MAX_UE 6
typedef struct _etu_t {
    int Num;   
    int nb_UE_S1, nb_UE_S2;     
    int coef_S1[NB_MAX_UE];
    int coef_S2[NB_MAX_UE];
    float notes_S1[NB_MAX_UE];
    float notes_S2[NB_MAX_UE];
} Etu_t;
float Calculer_Moyenne(float tNotes[], int tECTS[], int nbUEs)
{
    int total = 0, frac = 0;
    for (unsigned i = 0; i < nbUEs; ++i)
    {
        total += tNotes[i] * tECTS[i];
        frac += tECTS[i];
    }
    return total / frac;
}
int Valide(Etu_t etu)
{
    return ((Calculer_Moyenne(etu.notes_S1, etu.coef_S1, etu.nb_UE_S1) + Calculer_Moyenne(etu.notes_S2, etu.coef_S2, etu.nb_UE_S2)) / 2 >= 50);
}
int Compter_candidats(Etu_t tEtu[], int nbEtu)
{
    int valid = 0;
    for (unsigned i = 0; i < nbEtu; ++i) if (Valide(tEtu[i])) valid += 1;
    return valid;
}



// CANDIDATURES EN L2
char* Tab_Parcours[5] = {
    "Mono",
    "Mono intensif",
    "Mono alternance",
    "MajMin",
    "DM"
};
char* Tab_Disc[5] = {
    "Mathematics",
    "Informatique",
    "Biology",
    "Meditation scientifique",
    "Professionel des ecoles"
}; 
typedef struct Voeu_t_ Voeu_t; 
typedef struct Candidat_t_ {
    int Num;
    Voeu_t* liste_Voeux;
} Candidat_t;
struct Voeu_t_ {
    int Disc1;
    int Disc2;
    int Parcours;
    struct Voeu_t_* psuiv;
};

// IDK how to do this one so read it carefully pls
Candidat_t* Extraire_candidats(Etu_t tEtu[], int nbEtu, int* nbCand)
{
    Candidat_t* tCandidats = NULL;
    *nbCand = Compter_candidats(tEtu, nbEtu);
    
    if (*nbCand == 0) return NULL;
    tCandidats = (Candidat_t*)malloc(sizeof(Candidat_t) * (*nbCand));
    for (unsigned i = 0, j = 0; i < nbEtu; ++i)
    {
        if (Valide(tEtu[i]))
        {
            tCandidats[j].Num = tEtu[i].Num;
            tCandidats[j].liste_Voeux = NULL;
            ++j;
        }
    }
    return tCandidats;
}


// Saisie des voeux
void Afficher_tab_str(char* Tab[], int Nb)
{
    for (unsigned i = 0; i < Nb; ++i) printf("\t%d : %s\n", i + 1, Tab[i]);
}   // Simply the affichage function
int Saisir_valeur(int valMin, int valMax, int valInterdite)
{
    int val, judge = 0;
    while (judge == 0)
    {
        printf("Saisie une valeur :");
        scanf("%d\n",&val);
        if (val > valMax || val < valMin || val == valInterdite) printf("Invalid value. La valeur a l'entree doit etre compris entre %d et %d et doit etre differente de %d", valMin, valMax, valInterdite);
        else judge = 1;
    }
    return val;
}

#define NB_PARCOURS 5   // Nombre total de parcours
#define NB_MAJ 3    // Nombre de majeures (ou monos)
#define NB_MIN 5
#define NUM_MAJMIN 4
#define NUM_MAJMAJ 5
Voeu_t* Saisir_un_voeu(char* Tab_Disc[], char* Tab_Parcours[])
{
    printf("Choisir un type de parcours parmi les parcours possible, 0 si vous souhaitez arreter: \n");
    Afficher_tab_str(Tab_Parcours, NB_PARCOURS);
    int p = Saisir_valeur(0, NB_PARCOURS, -1);
    if (p == 0) return NULL;

    Voeu_t* pVoeu = malloc(sizeof(Voeu_t));
    pVoeu->Parcours = p;
    pVoeu->Disc2 = 0;
    pVoeu->psuiv = NULL;
    printf("Voici la liste des premiers disciplines disponibles: \n");
    Afficher_tab_str(Tab_Disc, NB_MAJ);
    printf("Veuillez ssaisir une premiere discipline:");
    pVoeu->Disc1 = Saisir_valeur(1, NB_MAJ, -1);

    int nbDisc2 = 0;
    if (pVoeu->Parcours == NUM_MAJMIN) nbDisc2 = NB_MIN;
    else if (pVoeu->Parcours == NUM_MAJMAJ) nbDisc2 = NB_MAJ;
    if (nbDisc2 != 0)
    {
        printf("Voici la liste des secondes disciplines disponibles: \n");
        Afficher_tab_str(Tab_Disc, nbDisc2);
        printf("Veuillez saisir une seconde discipline:");
        pVoeu->Disc2 = Saisir_valeur(1, nbDisc2, pVoeu->Disc1);
    }
    return pVoeu;
}
// Fonction qui ajoute un voeu en fin de la liste des voeux
Voeu_t* Inserer_fin(Voeu_t *voeu, Voeu_t* liste_Voeux)
{
    Voeu_t* tmp = liste_Voeux;
    if (tmp == NULL) return voeu;
    while (tmp->psuiv != NULL) tmp = tmp->psuiv;
    tmp->psuiv = voeu;
    return liste_Voeux;
}
Voeu_t* Saisir_les_voeux(char* Tab_Disc[], char* Tab_Parcours[])
{
    Voeu_t* un_voeu = NULL, *des_voeux = NULL;
    un_voeu = Saisir_un_voeu(Tab_Disc, Tab_Parcours);
    while (un_voeu != NULL)
    {
        des_voeux = Inserer_fin(un_voeu, des_voeux);
        un_voeu = Saisir_un_voeu(Tab_Disc, Tab_Parcours);
    }
    return des_voeux;
}



// AFFECTATION SELON DES VOEUX
typedef struct Liste_candidats_t_ {
    int Num;    // Identifiant
    struct Liste_candidats_t_ *psuiv;
} Liste_candidats_t;
int Appartient_voeu(Voeu_t* liste_voeux, int p, int d1, int d2)
{
    while (liste_voeux != NULL)
    {
        if ((liste_voeux->Disc1 == d1) && (liste_voeux->Disc2 == d2) && (liste_voeux->Parcours == p)) return 1;
        liste_voeux = liste_voeux->psuiv;
    }
    return 0;
}
Liste_candidats_t* Extraire_Candidats_Parcours(Candidat_t tCandidats[], int nbCandidats, int Parcours, int Disc1, int Disc2)
{
    Liste_candidats_t *pL = NULL, *pNew = NULL;
    for (unsigned i = 0; i < nbCandidats; ++i)
    {
        if (Appartient_voeu(tCandidats[i].liste_Voeux, Parcours, Disc1, Disc2))
        {
            pNew = malloc(sizeof(Liste_candidats_t));
            pNew->Num = tCandidats[i].Num;
            pNew->psuiv = pL;
            pL = pNew;
        }
    }
    return pL;
}
Liste_candidats_t* Selectionner_Candidats_Parcours(Liste_candidats_t* pL)
{
    Liste_candidats_t* pTmp = pL, *pTmp2 = NULL, *pPrev = NULL;
    int res = 0;
    while (pTmp)
    {
        printf("\nAdmettez vous le candidat numero %d (0 ou 1)?\n",pTmp->Num);
        res = Saisir_valeur(0, 1, -1);
        if (res != 1)
        {
            // Supprimer le candidat
            pTmp2 = pTmp->psuiv;
            free(pTmp);
            pTmp = pTmp2;

            if (pPrev != NULL) pPrev->psuiv = pTmp;     // Chainage avec le precedent
            pL = pTmp;  // Cas particulier du 1er
        }
        pPrev = pTmp;
        pTmp = pTmp->psuiv;
    }
    return pL;
}   // Cai nay doc khong hieu me gi =))))))
int main(void)
{
    // Just for fun :))))
    printf("%d\n",Saisir_valeur(0, 1, -1));
    return 0;
}