#ifndef GEN_H
#define GEN_H

#include "heuristique.h"

#define ITERATION 10
#define N 100 // nombre de générations par itérations
static const int GRILLE_DEPART[64] = {
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 1, -1, 0, 0, 0,
    0, 0, 0, -1, 1, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
};

// matrice de poid = stratégie
typedef struct {
    double* tab; // matrices de poid
    double score; // score obtenu avec cette matrice de poid (i.e: stratégie)
} matScore;

typedef struct {
    int score;
    int indice;
} couple;

double* muter(double* grille);

void afficherGrille(double* grille);

int comparer(const void* a, const void* b);

double** init_gen();

void boucle(matScore* resultats);

void entrainement();

#endif