#include <stdio.h>
#include <stdlib.h>
#include "pile.h"
#include "matrice_l.h"

void empiler(pile* p, coord val){
    if (p == NULL){
        printf("La pile passé en argument est un pointeur NULL");
        return;
    }
    noeud* n = malloc(sizeof(noeud));
    n->val = val;
    n->suiv = p->debut;
    p->debut = n;
    if (p->fin == NULL) {
        p->fin = n;
    }
}

coord depiler(pile* p){
    if (p == NULL){
        printf("La pile passé en argument est un pointeur NULL");
        return (coord){-2, -2};
    } else if (p->debut != NULL){
        coord retour = p->debut->val;
        noeud* n = p->debut;
        p->debut = p->debut->suiv;
        if (p->debut == NULL){
            p->fin = NULL;
        }
        free(n);
        return retour;
    }
    // ici on a essayé de dépiler une pile vide donc on retourne l'erreur qui est (-2, -2) en terme de coordoné donc non accessible
    return (coord){-2, -2};
}

void fusionP(pile* p1, pile* p2){ // fusionner une pile avec une autre; on rajoute p2 en tête de p1 avec des pointeurs pour le faire en O(1)
    if (p2->debut != NULL) {
        if (p1->debut == NULL){
            p1->fin = p2->fin;
        }
        p2->fin->suiv = p1->debut;
        p1->debut = p2->debut;
    }
}

void freeN(noeud* n){
    if (n == NULL) {
        return;
    }
    freeN(n->suiv);
    free(n);
}

void freeP(pile* p){
    if (p == NULL){
        return;
    }
    freeN(p->debut);
    free(p);
}