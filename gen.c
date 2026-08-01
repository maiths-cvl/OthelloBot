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
        for (int j = 0; j<N;j++){ // on fait s'affronter tous les individus d'une génération entre-eux, k et j représentent chacun des individus (leur indice dans le tableau des matrices de poids)
            matrix* grille = createM(GRILLE_DEPART, 8, 8); // malloc vers une matrice et un tableau d'int dedans
            // N^2 malloc de la même grille

            bool run = true;
            int fin = 0;
            bool premierJoueur = false;
            bool couleur = false;

            if (k>j){
                couleur = false;
            } else if (k<j){
                couleur = true;
            } else { // égalité
                // cas spécial
            }
            // boucle du jeu
            while(run && fin <2){ // les blancs: 1,  commencent
                if (!couleur){
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
                } else {
                    if (premierJoueur && fin == 1){
                        fin = 0;
                    }

                    if(Placer(grille, 1, calcul(grille, 1, DEPTH1, true, resultats[j].tab).co) == -2){
                        fin+=1;
                        premierJoueur = true;
                    }
                    //afficher(grille); // printf qui utilise du temps d'execution

                    if (!premierJoueur && fin == 1){
                        fin = 0;
                    }

                    if (Placer(grille, -1, calcul(grille, -1, DEPTH2, true, resultats[k].tab).co) == -2){
                        fin+=1;
                        premierJoueur = false;
                    }
                }
            }
            double scoreFinal = 0.0;
            for (int i =0;i<64;i++){ // score pour le joueur 1, et sa négation pour le joueur -1
                scoreFinal += grille->tab[i];
            }
            resultats[k].score += scoreFinal/((double) N); // moyenne des résultats sur tous les combats
            resultats[j].score += -scoreFinal/((double) N);
            freeM(grille);
        }
        //printf("%d a fini tous ses combats, ", k);
    }
    printf("\n");
}

double* muter(double* grille){
    double* res = malloc(64*sizeof(double));
    // 1 malloc

    for(int i=0;i<64;i++){
        res[i] = grille[i]*(1+(((double) rand()/RAND_MAX)*0.4-0.2));
    }
    return res;
}

void afficherGrille(double* grille){
    printf("{\n");
    for (int i = 0; i<8;i++){
        printf("{");
        for (int j = 0; j<8;j++){
            if(j==7){
                if (grille[i*8+j] == -1){
                    printf(RED "%lf" RESET, grille[i*8+j]);
                } else if (grille[i*8+j] == 0){
                    printf(MAGENTA "%lf" RESET, grille[i*8+j]);
                } else {
                    printf("%lf", grille[i*8+j]);
                }
            } else {
                if (grille[i*8+j] == -1){
                    printf(RED "%lf, " RESET, grille[i*8+j]);
                } else if (grille[i*8+j] == 0){
                    printf(MAGENTA "%lf, " RESET, grille[i*8+j]);
                } else {
                    printf("%lf, ", grille[i*8+j]);
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
        resultats[k].score = 0; // on initialise les scores au minimum
    }

    int percent = (int) ((double)N)*0.2;

    for (int k = 0;k<ITERATION;k++){
        printf("Itération %d\n", k+1);
        boucle(resultats); // ne renvoi rien mais rajoute les résultats dans le tableau résultat

        couple* tabT = malloc(N*sizeof(couple));
        for(int i = 0;i<N;i++){
            tabT[i].score = resultats[i].score;
            tabT[i].indice = i;
        }

        qsort(tabT, N, sizeof(couple), comparer);

        for(int i = 0;i<percent;i++){ // on met les 20 meilleures dans le début de résultats
            resultats[i].tab = resultats[tabT[i].indice].tab; // on place les matrices
        }
        for(int i = percent;i<N;i++){ // rajoute les mutations dans le reste
            resultats[i].tab = muter(resultats[i % percent].tab); // on place les matrices
        }

        free(tabT);
    }
    for(int i=0;i<percent;i++){
        printf("Grille n°%d, score : %lf\n", i+1, resultats[i].score);
        afficherGrille(resultats[i].tab);
        printf("\n");
    }

    for(int i = 0;i<N;i++){
        free(resultats[i].tab);
    }
    free(tab);
    free(resultats);
}


// à améliorer: le système de score final qui n'est actuellement que la moyenne des scores de tous les combats, peut être tout stocker ou bien différencier des cas
