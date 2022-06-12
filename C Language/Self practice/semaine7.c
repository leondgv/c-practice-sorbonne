#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

// Define struct pọint
typedef struct _point { float x; float y; char couleur[10]; } point;

// Define struct mon_point
point mon_point = {
    .x = 3., 
    .y = 4., 
    .couleur = "rouge"
};
/* Tester la structure ci-dessus
int main(void)
{
    printf("%.f\n", mon_point.x);
    printf("%.f\n", mon_point.y);
    printf("%s\n", mon_point.couleur);
    return 0; 
}
*/
// Define struct rectangle
typedef struct _rectangle rectangle;
struct _rectangle { 
    point coin1; 
    point coin2; 
    
    char trait[10]; 
    char fond[10];
}; 

// Define mon_rectangle
rectangle mon_rectangle = {
    .coin1 = {.x = 100, .y = 200},
    .coin2 = {.x = 300, .y = 2},

    .trait = "rouge",
    .fond = "blanc",
};
int inf(float a, float b)
{
    // Renvoie la valeur inférieure entre a et b
    if (a < b) return a;
    else return b;
}
int sup(float a, float b)
{
    // Renvoie la valeur supérieure entre a et b
    if (a < b) return b;
    else return a;
}
int point_dans_rectangle(point point, rectangle *rectangle)
{
    if ((inf(rectangle->coin1.x, rectangle->coin2.x) <= point.x) && (point.x <= sup(rectangle->coin1.x, rectangle->coin2.x)) && (inf(rectangle->coin1.y, rectangle->coin2.y) <= point.y) && (point.y <= sup(rectangle->coin1.y, rectangle->coin2.y))) return 1;
    else return 0; 
}
/* Tester la fonction ci-dessus
int main(void)
{
    point A = {.x = 100, .y = 150};
    rectangle ABCD = {
        .coin1.x = 100, 
        .coin1.y = 100,
        .coin2.x = 200,
        .coin2.y = 500
    };
    assert(point_dans_rectangle(A, &ABCD) == 1);

    return 0; 
}
*/
rectangle intersection_rectangles(rectangle *r1, rectangle *r2)
{
    // Renvoie l'intersection de 2 rectangles
    rectangle tmp;
    point p1, p2;

    p1.x = r2->coin1.x;
    p1.y = r1->coin1.y;

    p2.x = r1->coin2.x;
    p2.y = r2->coin2.y;

    int p1_in_r1 = point_dans_rectangle(p1,r1);
    int p1_in_r2 = point_dans_rectangle(p1,r2);
    int p2_in_r1 = point_dans_rectangle(p2,r1);
    int p2_in_r2 = point_dans_rectangle(p2,r2);

    if ((r1 != NULL) && (r2 != NULL))
    {
        if ((p1_in_r1 == 1) && (p1_in_r2 == 1) && (p2_in_r1 == 1) && (p2_in_r2 == 1)) 
        {
            tmp.coin1.x = r2->coin1.x;
            tmp.coin1.y = r1->coin1.y;

            tmp.coin2.x = r1->coin2.x;
            tmp.coin2.y = r2->coin2.y;
        }
    }
    return tmp; 
}
// Tester la fonction ci-dessus
/*
int main(void)
{
    rectangle rec1 = { 
        .coin1.x = 3,
        .coin1.y = 3,

        .coin2.x = 5,
        .coin2.y = 1
    };
    rectangle rec2 = {
        .coin1.x = 4,
        .coin1.y = 4,

        .coin2.x = 6,
        .coin2.y = 2
    };
    rectangle rec = intersection_rectangles(&rec1,&rec2);
    printf("%.f\t", rec.coin1.x);
    printf("%.f\t", rec.coin1.y);
    printf("%.f\t", rec.coin2.x);
    printf("%.f\t", rec.coin2.y);

    return 0; 
}
*/
// Define le type article
typedef struct _article article;
struct _article { int reference; float prix; int quantity; };

#define TAILLE_STOCK 40

// Define a tableau stock pour contenir tout le stock
article stock[TAILLE_STOCK]; // Unused declaration

void augmentationPrix(float taux, article article)
{
    // Modifie the price of the article in stock
    float tax = (100 + taux)/100;
    article.prix *= tax;
    printf("%.2f\n",article.prix);
}
void augmentationGenerale(article st[], int taille_stock, float tax)
{
    for (unsigned i = 0; i < taille_stock; ++i) augmentationPrix(tax, st[i]);
}
/* Tester la fonction ci-dessus
int main(void)
{
    article s[] = { { 152, 10.5, 10 },{ 432, 24.3, 50 } };

    augmentationGenerale(s, 2, 10.0);
    return 0; 
}
*/
int validationReferences(article st[], int taille)
{
    int val = st[0].reference;
    for (unsigned i = 1; i < taille; ++i)
    {
        st[i].reference -= val;
        if (st[i].reference != 0) return 0;
        break;
    }
    return 1; 
}
int main(void)
{
    article s[] = { { 432, 10.5, 10 }, { 432, 24.3, 50 } };
    printf("%d\n", validationReferences(s,2));

    return 0; 
}