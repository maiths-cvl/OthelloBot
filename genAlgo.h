#ifndef GENALGO_H
#define GENALGO_H
#include <stdbool.h>
#include "matrice_l.h"
#include "jeu.h"
#include "tableau.h"

#define DEPTH1 4 // profondeur de calcul du premier bot
#define DEPTH2 2 // profondeur de calcul du deuxième bot
#define WIDTH 8
#define HEIGHT 8
#define INFINI 1000000000.0 // le score n'ira pas jusque là je l'espère

typedef struct {
    double score;
    coord co;
} ScoreCo;

double score(matrix* grille, int joueur);

ScoreCo calcul(matrix* grille, int joueur, int hauteur, bool final_layer);

#endif