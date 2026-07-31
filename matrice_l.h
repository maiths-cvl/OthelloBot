#ifndef MATRICE_L_H
#define MATRICE_L_H

#include <stdbool.h>

typedef struct { // matrices de double pour du deep learning
    int i; // représente le nb de lignes
    int j; // nb de colones
    int* tab; // utiliser float si optimisation
} matrix; // on pointe vers les matrices

void freeM(matrix* m);
void afficher(const matrix* a);

matrix* createM(int tab[], int i, int j);
matrix* prod(matrix* m1, matrix* m2);

#endif