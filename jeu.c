#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "jeu.h"
#include "matrice_l.h"
#include "pile.h"


// Compléxité : O(1)
int Placer(matrix* grille, int joueur, const coord co) {
    coord mut = co; // copie des coordonés originaux
    pile* pileFinale = malloc(sizeof(pile));
    pileFinale->debut = NULL;
    pileFinale->fin = NULL;
    bool placerr = false;

    if (co.x == -1 && co.y == -1){
        printf("Plus de coup légaux disponible pour le joueur %d, il passe son tour", joueur);
        return -2; // le tour doit être passé car il n'y a pas de coup légal
    } else if (grille->tab[co.y*8+co.x] == 0) {
        for(int i=0;i<8;i++){ // 8 directions dans lesquelles se déplacer
            bool run = true;
            bool ligne = false;
            pile* p = malloc(sizeof(pile));
            p->debut = NULL;
            p->fin = NULL;
            while (mut.x + DIRECTIONS[i][0] > -1 && mut.x + DIRECTIONS[i][0] < 8 && mut.y + DIRECTIONS[i][1] > -1 && mut.y + DIRECTIONS[i][1] < 8 && run == true){ // tant qu'on est pas au bord, cad dans la grille
                mut.x += DIRECTIONS[i][0];
                mut.y += DIRECTIONS[i][1];

                if (grille->tab[mut.y*8+mut.x] == 0){ // si la case est vide alors on arrête la propagation
                    run = false;
                } else if (grille->tab[mut.y*8+mut.x] == -joueur) { // s'il y a un pion adverse sur la case
                    empiler(p, mut); // empilement des coordonés des cases à modifier
                } else if (grille->tab[mut.y*8+mut.x] == joueur){ // il y a un pion allié sur la case, si on est arrivé ici c'est qu'il n'y avait pas de case vide sur le chemin
                    if (p->debut != NULL) { // on vérifie s'il y a eu des pions enemis avant le pion allié
                        placerr = true; // on dit au programme qu'il faudra placer le jeton à la fin des boucles grâce au booléen qui sera évalué plus tard
                        ligne = true;
                        run = false; // il faut arrêter de rajouter des pions apres le premier pion allié touvé
                        fusionP(pileFinale, p); // fusionner p dans pileFinale
                    } else {
                    run = false; // il faut arrêter la propagation car il y a un pion allié juste à coté de l'emplacement 
                    }
                }
            }
            if (ligne) {
                free(p);
            } else {
                freeP(p);
            }
            mut=co; // on revient à la position initiale
        }
    }

    if (placerr) {
        grille->tab[co.y*8+co.x] = joueur; // on place le pion du joueur sur la case
        while(pileFinale->debut != NULL){
            coord c = depiler(pileFinale);
            grille->tab[c.y*8+c.x] = joueur; // changer tous les pions de la pile    
        }
        freeP(pileFinale);
        return 0; // on renvoi 0 s'il n'y a pas de problème pour placer le pion
    } else {
        freeP(pileFinale);
        return -1; // on renvoi -1 si la pion n'a pas pu être placé
    }
}
