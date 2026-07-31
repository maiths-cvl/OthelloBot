#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "matrice_l.h"
#include "couleurs.h"

/* typedef struct matrix { // matrices de nombres pour du deep learning
    int i; // représente le nb de lignes
    int j; // nb de colones
    int** tab;
} matrix; */


// précodition: il faut qu'il y ait le même nombres déléments dans le tableau que de capacité dans la matrice pour tout avoir, s'il y en a moins ça crashe
matrix* createM(int tab[], int i, int j){ // complexité en O(i*j) sans compter le malloc
    matrix* m = malloc(sizeof(matrix));
    m->i=i;
    m->j=j;
    m->tab = (int *) malloc(i*j*sizeof(int));

    for (int k=0;k<i*j;k++){
        m->tab[k] = tab[k];
    }

    return m;
}

void freeM(matrix* m){ // Complexité en O(1)
    free(m->tab);
    free(m);
}

/* // précoditions: Il faut que le nombres de lignes et colones soient compatibles pour la multiplication de matrice sinon crash/ou pas
void prod(matrix a, matrix b) { // a et b sont des matrices
    assert(a.j == a.i); // les matrices ne sont pas multipliables

} */

void afficher(const matrix* a) { // Complexité en O(i*j)
    printf("{\n");
    for (int i = 0; i<a->i;i++){
        printf("{");
        for (int j = 0; j<a->j;j++){
            if(j==a->j-1){
                if (a->tab[i*a->j+j] == -1){
                    printf(RED "%d" RESET, a->tab[i*a->j+j]);
                } else if (a->tab[i*a->j+j] == 0){
                    printf(MAGENTA "%d" RESET, a->tab[i*a->j+j]);
                } else {
                    printf("%d", a->tab[i*a->j+j]);
                }
            } else {
                if (a->tab[i*a->j+j] == -1){
                    printf(RED "%d, " RESET, a->tab[i*a->j+j]);
                } else if (a->tab[i*a->j+j] == 0){
                    printf(MAGENTA "%d, " RESET, a->tab[i*a->j+j]);
                } else {
                    printf("%d, ", a->tab[i*a->j+j]);
                }
            }
            //j==a->j-1 ? printf("%d", a->tab[i*a->j+j]) : printf("%d, ", a->tab[i*a->j+j]);  
        } printf("}\n");
    }
    printf("}\n");
}

// précondition m1.j == m2.i
matrix* prod(matrix* m1, matrix* m2) {
    assert(m1->j == m2->i);
    int* tab = malloc(m1->i*m2->j*sizeof(int));
    
    for (int i =0;i<m1->i*m2->j;i++){ // complexité en O(i*j)
        tab[i] = 0;
    }
    
    matrix* res = createM(tab, m1->i, m2->j); // Complexité en O(i*j)

    int nb_col = m1->j; // == m2->i aussi

    for (int lig=0;lig<m1->i;lig++) {
        for (int col=0;col<m2->j;col++){ // le j de m1 et le i de m2
            for (int k=0;k<m1->j;k++) {
                res->tab[lig*nb_col+col] += m1->tab[lig*nb_col+k] * m2->tab[k*nb_col+col];
            }
        }
    }

    free(tab);
    return res;
}
