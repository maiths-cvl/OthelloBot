#ifndef JEU_H
#define JEU_H
#include <stdbool.h>
#include "matrice_l.h"
#include "pile.h"

#define  DIRECTIONS ((int[8][2]){{-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1}})

int Placer(matrix* grille, int joueur, const coord co);

#endif