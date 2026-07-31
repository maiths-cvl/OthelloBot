#ifndef HEURISTIQUE_H
#define HEURISTIQUE_H

#include <stdlib.h>
#include <stdio.h>
#include "matrice_l.h"

static const double POIDS_GRILLE[64] = { // matrice de poids basique
    100, -20,  10,   5,   5,  10, -20,  100,
    -20, -50,  -2,  -2,  -2,  -2, -50,  -20,
     10,  -2,  -1,  -1,  -1,  -1,  -2,   10,
      5,  -2,  -1,  -1,  -1,  -1,  -2,    5,
      5,  -2,  -1,  -1,  -1,  -1,  -2,    5,
     10,  -2,  -1,  -1,  -1,  -1,  -2,   10,
    -20, -50,  -2,  -2,  -2,  -2, -50,  -20,
    100, -20,  10,   5,   5,  10, -20,  100
};

double score(matrix* grille, int joueur, double* grille_poid);

#endif