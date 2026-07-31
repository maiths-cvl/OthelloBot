#ifndef GENALGO_H
#define GENALGO_H
#include "matrice_l.h"
#include "jeu.h"
#include "tableau.h"

#define DEPTH 2 // profondeur de calcul
#define WIDTH 8
#define HEIGHT 8
#define INFINI 1000000000.0 // le score n'ira pas jusque là je l'espère

double score(matrix* grille, int joueur);

coord calcul(matrix* grille, int joueur);

#endif