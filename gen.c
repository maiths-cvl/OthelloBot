#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "gen.h"
#include "matrice_l.h"
#include "heuristique.h"
#include "couleurs.h"
#include "genAlgo.h"

double** init_gen(){ // renvoi un tableau de N matrices de poid mutées (seule la première n'est pas mutée)
    srand(time(NULL));

    double** tab = malloc(N*sizeof(double*));

    for (int i = 0; i<N;i++){
        tab[i] = malloc(64*sizeof(double));
    }

    for(int i = 0;i<64;i++){
        tab[0][i] = POIDS_GRILLE[i];
    }

    for (int i = 1; i<N;i++){
        for(int j =0; j<64;j++){
            tab[i][j] = tab[0][j] * (1+(((double) rand()/RAND_MAX)*0.4-0.2));
        }
    }
    return tab;
}

void boucle(matScore* resultats){
    for (int k=0;k<N;k++){
        for (int j = 0; j<k;j++){ // on fait s'affronter tous les individus d'une génération entre-eux, k et j représentent chacun des individus (leur indice dans le tableau des matrices de poids)
            matrix* grille = createM(GRILLE_DEPART, 8, 8);

            bool run = true;
            int fin = 0;
            bool premierJoueur = false;

            // boucle du jeu
            while(run && fin <2){ // les blancs: 1,  commencent
                if (premierJoueur && fin == 1){
                    fin = 0;
                }
                
                if(Placer(grille, 1, calcul(grille, 1, DEPTH1, true, resultats[k].tab).co) == -2){
                    fin+=1;
                    premierJoueur = true;
                }
                //afficher(grille); // printf qui utilise du temps d'execution

                if (!premierJoueur && fin == 1){
                    fin = 0;
                }

                if (Placer(grille, -1, calcul(grille, -1, DEPTH2, true, resultats[j].tab).co) == -2){
                    fin+=1;
                    premierJoueur = false;
                }
                //afficher(grille); // printf qui utilise du temps d'execution
            }
            double scoreFinal = 0.0;
            for (int i =0;i<64;i++){ // score pour le joueur 1, et sa négation pour le joueur -1
                scoreFinal += grille->tab[i];
            }
            resultats[k].score += scoreFinal/((double) N); // moyenne des résultats sur tous les combats
            resultats[j].score += -scoreFinal/((double) N);
            freeM(grille);
        }
    }
}

double* muter(double* grille){
    for(int i=0;i<64;i++){
        grille[i] *= 1+(((double) rand()/RAND_MAX)*0.4-0.2);
    }
    return grille;
}

void afficherGrille(double* grille){
    printf("{\n");
    for (int i = 0; i<8;i++){
        printf("{");
        for (int j = 0; j<8;j++){
            if(j==7){
                if (grille[i*8+j] == -1){
                    printf(RED "%d" RESET, grille[i*8+j]);
                } else if (grille[i*8+j] == 0){
                    printf(MAGENTA "%d" RESET, grille[i*8+j]);
                } else {
                    printf("%d", grille[i*8+j]);
                }
            } else {
                if (grille[i*8+j] == -1){
                    printf(RED "%d, " RESET, grille[i*8+j]);
                } else if (grille[i*8+j] == 0){
                    printf(MAGENTA "%d, " RESET, grille[i*8+j]);
                } else {
                    printf("%d, ", grille[i*8+j]);
                }
            }
        } printf("}\n");
    }
    printf("}\n");
}

int comparer(const void* a, const void* b) { 
    const couple* coupleA = (const couple*)a;
    const couple* coupleB = (const couple*)b;

    if (coupleB->score > coupleA->score) return 1;
    if (coupleB->score < coupleA->score) return -1;

    return 0;
}

void entrainement(){

    // on initialise l'entrainement
    matScore* resultats = malloc(N*sizeof(matScore));

    double** tab = init_gen();

    for(int k = 0;k<N;k++){
        resultats[k].tab = tab[k]; // on copie les matrices de tableaux à leur emplacement
        resultats[k].score = -INFINI; // on initialise les scores au minimum
    }

    for (int k = 0;k<ITERATION;k++){
        
        boucle(resultats); // ne renvoi rien mais rajoute les résultats dans le tableau résultat

        couple* tabT = malloc(N*sizeof(couple));
        for(int i = 0;i<N;i++){
            tabT[i].score = resultats[i].score;
            tabT[i].indice = i;
        }

        qsort(tabT, N, sizeof(couple), comparer);

        for(int i = 0;i<20;i++){ // on met les 20 meilleures dans le début de résultats
            resultats[i].tab = resultats[tabT->indice].tab; // on place les matrices
            resultats[i].score = -INFINI; // on reset les scores
        }
        for(int i = 20;i<N;i++){ // rajoute les mutations dans le reste
            resultats[i].tab = muter(resultats[i % 20].tab); // on place les matrices
            resultats[i].score = -INFINI; // on reset les scores
        }

        free(tabT);
    }

    for(int i=0;i<20;i++){
        printf("Grille n°%d, score : %d\n", i, resultats[i].score);
        afficherGrille(resultats[i].tab);
        printf("%d");
    }

    for(int i = 0;i<N;i++){
        free(resultats[i].tab);
        free(tab[i]);
    }
    free(tab);
    free(resultats);
}


// à améliorer: le système de score final qui n'est actuellement que la moyenne des scores de tous les combats, peut être tout stocker ou bien différencier des cas
