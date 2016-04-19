#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "Strategies_pilotees.h"
#include "Sequence_aleatoire.h"


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
  printf("nbsom=%d\n",G->nbsom);
  while (G->nbsom > 0) {
    maj_bordure_graphe(G, M, Gr->nbcl);

    for (i=0;i<dim; i++ )
      for (j=0;j<dim;j++)
	Grille_attribue_couleur_case(Gr,i,j,M[i][j]);
    
    Grille_redessine_Grille();
    
    Grille_attente_touche();
      
    
    // printf("test\n");
    cpt++;
   
  }
  
  return cpt;
}
