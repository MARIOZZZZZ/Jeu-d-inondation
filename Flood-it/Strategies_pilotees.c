#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "Strategies_pilotees.h"


int maxBordure(Grille *Gr, int **M, int dim){

  int i , j, cpt = 0;
  Graphe_zone *G = malloc(sizeof(Graphe_zone));
  G->nbsom = 0;
  G->som = NULL;
	
  G->mat = (Sommet ***) malloc(sizeof(Sommet**)*dim);
	
  for(i = 0; i < dim; i++) {
    G->mat[i] = (Sommet **) malloc(sizeof(Sommet*)*dim);
   
    for(j = 0; j < dim; j++)
      G->mat[i][j] = NULL;
  }
  
  cree_graphe_zone(G, M, dim);
  printf("test\n");
  while (G->nbsom > 0) {
    maj_bordure_graphe(G, M, Gr->nbcl);
    cpt++;
  }
  
  return cpt;
}
