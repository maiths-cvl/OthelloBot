#include <stdlib.h>
#include <stdio.h>
#include "heuristique.h"
#include "matrice_l.h"

double score(matrix* grille, int joueur, double* grille_poid){
    double score_total = 0.0;
    
    for (int i = 0; i < 64; i++) {
        // Multiplie la valeur de la case (1, -1 ou 0) par le poids stratégique
        score_total += grille->tab[i] * grille_poid[i];
    }
    
    // Si joueur vaut 1, retourne score_total. Si -1, retourne -score_total
    return joueur * score_total;
}