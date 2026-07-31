#ifndef PILE_H
#define PILE_H

typedef struct { // type de coordonés
    int x;
    int y;
} coord;

typedef struct noeud {
    coord val;
    struct noeud* suiv;
} noeud;

typedef struct {
    noeud* debut; // pointeur vers le premier noeud de la pile
    noeud* fin; // pointeur vers le dernier noeud de la pile
} pile;

void empiler(pile* p, coord val);

coord depiler(pile* p);

void fusionP(pile* p1, pile* p2);

void freeN(noeud* n);

void freeP(pile* p);


#endif