#include <stdio.h>
#include <stdlib.h>
#include "pile.h"

int maximumScore(double* tab, int taille){ // retourne l'indice de l'élément le plus petit
    if (tab == NULL) {
        return -1.0; // -1 signifie erreur
    }
    int max = 0;
    for (int i =0; i<taille;i++){
        if (tab[max] < tab[i]) { // on va considérer que les cases de même scores se valent strictement
            max = i;
        }
    }
    return max;
}

// s'il y a plusieurs cases qui se valent, on prendra toujours la plus en haut à droite car c'est le fonctionnement de l'algo, ce qui pourrait donner des stratégies a l'algo qui faudrait prendre en compte dans l'heuristique
// on pourrait aussi faire une fonction random qui choisit de manière aléatoire quand il y a des égalitées pour équilibrer ce phénomène