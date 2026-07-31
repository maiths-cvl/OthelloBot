#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "matrice_l.h"
#include "pile.h"
#include "genAlgo.h"
#include "jeu.h"

int main(){

    /* double tab[] = {4, 2, 3, 1.0/3.0, 1, 2, 10000000};
    printf("min tab : %d, %lf\n", minimumScore(tab, 7), tab[minimumScore(tab, 7)]);
 */
    int grille_de_depart[8*8];
    for (int i=0;i<64;i++){
        if (i == 8*3+3 || i ==8*4+4){
            grille_de_depart[i] = 1;
        } else if (i == 8*3+4 || i ==8*4+3){
            grille_de_depart[i] = -1;
        } else {
        grille_de_depart[i] = 0;
        }
    }
    matrix* grille = createM(grille_de_depart, 8, 8);

    bool run = true;
    int fin = 0;
    bool premierJoueur = false;

    // boucle du jeu
    while(run && fin <2){ // les blancs: 1,  commencent
        if (premierJoueur && fin == 1){
            fin = 0;
        }
        
        if(Placer(grille, 1, calcul(grille, 1, DEPTH1, true).co) == -2){
            fin+=1;
            premierJoueur = true;
        }
        afficher(grille);

         if (!premierJoueur && fin == 1){
            fin = 0;
        }

        if (Placer(grille, -1, calcul(grille, -1, DEPTH2, true).co) == -2){
            fin+=1;
            premierJoueur = false;
        }
        afficher(grille);
    }
    double scoreFinal = 0.0;
    for (int i =0;i<64;i++){ // score pour le joueur 1, et sa négation pour le joueur -1
        scoreFinal += grille->tab[i];
    }
    printf("La partie s'est terminée car plus aucun des deux joueurs n'avait de coup possible\n");
    printf("Le score du le joueur %d est de : %lf\nLe score du joueur %d est de : %lf\n", 1, scoreFinal, -1, -scoreFinal);
    freeM(grille);

    return 0;
}