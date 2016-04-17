#ifndef __SEQUENCE_ALEATOIRE__
#define __SEQUENCE_ALEATOIRE__

#include<stdlib.h>
#include "Liste_case.h"
#include "API_Grille.h"

/* 1 si case[i][j] se trouve dans L, 0 si non */
int rechercher_Liste(int i, int j, Liste *L);

/* Affecter la zone par cl et mettre a jour une zone et sa taille recursive */
void trouve_zone_rec(int **M, int dim, int i, int j, int *taille, Liste *L, int cl);

int sequence_aleatoire_rec(int **M, Grille *G, int dim, int nbcl, int aff);

/* Version imperative de la fonction trouve_zone */
void trouve_zone_imp(int **M, int dim, int i, int j, int *taille, Liste *Pile, int cl);

/* Sequence_aleatoire en version imperative */
int sequence_aleatoire_imp(int **M, Grille *G, int dim, int nbcl, int aff);

/* Sequence alea en utilisant le bordure */
int strequence_aleatoire_rapide(int **M, Grille *G, int dim, int nbcl);
#endif
