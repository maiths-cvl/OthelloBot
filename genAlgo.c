#include <stdio.h>
#include <stdlib.h>
#include "genAlgo.h"
#include "matrice_l.h"
#include "jeu.h"
#include "tableau.h"

// Autre heuristique

// Tableau des poids statique
static const double POIDS_GRILLE[64] = {
    100, -20,  10,   5,   5,  10, -20,  100,
    -20, -50,  -2,  -2,  -2,  -2, -50,  -20,
     10,  -2,  -1,  -1,  -1,  -1,  -2,   10,
      5,  -2,  -1,  -1,  -1,  -1,  -2,    5,
      5,  -2,  -1,  -1,  -1,  -1,  -2,    5,
     10,  -2,  -1,  -1,  -1,  -1,  -2,   10,
    -20, -50,  -2,  -2,  -2,  -2, -50,  -20,
    100, -20,  10,   5,   5,  10, -20,  100
};

double score(matrix* grille, int joueur) {
    double score_total = 0.0;
    
    for (int i = 0; i < 64; i++) {
        // Multiplie la valeur de la case (1, -1 ou 0) par le poids stratégique
        score_total += grille->tab[i] * POIDS_GRILLE[i];
    }
    
    // Si joueur vaut 1, retourne score_total. Si -1, retourne -score_total
    return joueur * score_total;
}

// une mauvais heuristique
/* double score (matrix* grille, int joueur){ // heuristique à implémenter
    double score = 0.0;
    for(int i =0;i<64;i++){
        score += (double) grille->tab[i];
    }
    return joueur*score;
}
 */
coord calcul(matrix* grille, int joueur){ // cette fonction va calculer le meilleur coup pour une profondeur donnée
    
    double tab[WIDTH*HEIGHT];
    for (int i = 0;i<WIDTH*HEIGHT;i++){
        tab[i] = -INFINI;
    }
    /* for(int i =0;i<64;i++){
        printf("%lf\n ", tab[i]);
    } */


    for(int i=0;i<WIDTH*HEIGHT;i++){
        coord co = (coord){i%8, i/8}; // récupération de l'indice en coordoné (x,y)
        matrix* copie = malloc(sizeof(matrix)); // copie de la matrice de jeu pour faire des analyses
        copie->i=8;
        copie->j=8;
        copie->tab = malloc(64*sizeof(int));
        for(int j=0;j<DEPTH;j++) {
            for(int k =0; k<64;k++){
                copie->tab[k] = grille->tab[k];
            }

            if (Placer(copie, joueur, co) == 0) { // on place un pion en une case
                tab[i] = score(copie, joueur);
            }
            freeM(copie);
        }
    }
    int min = maximumScore(tab, WIDTH*HEIGHT);
    /* for(int i =0;i<64;i++){
        printf("%lf\n ", tab[i]);
    }
    printf("\nmin : %d\n%lf\n", min, tab[min]); */
    if (tab[min] == -INFINI){
        return (coord){-1, -1}; // c'est le code d'erreur, cad il n'y a aucun coup jouable.
    }
    return (coord){min%8, min/8}; // on converti l'indice du tableau en coordoné
}