#include "Bordure.h"
#include "Sequence_aleatoire.h"
#include <stdio.h>
#include <stdlib.h>



void init_Zsg(S_Zsg *sz, int dim, int nbcl){

  int i,j;

  if(!sz){
    fprintf(stderr, "erreur d'allocation\n");
    exit(1);
  }
  
  sz->dim = dim;
  sz->nbcl = nbcl;
  sz->Lzsg = NULL;
  sz->B = NULL;
  sz->App = malloc(sizeof(int *)* sz->dim);

  if(sz->App == NULL){
    exit(0);
  }

  for (i=0; i<sz->dim; i++){
    sz->App[i] = malloc(sizeof(int) * sz->dim);
    for(j=0; j < sz->dim; j++)
      sz->App[i][j] = -2; /* Initialiser tout les case a -2 */
  }


  
  sz->B = (Liste **)malloc(sizeof(Liste*) * sz->nbcl);
  if(sz->B == NULL){
    exit(0);
  }
 
  for(i=0; i < sz->nbcl; i++){
    sz->B[i] = malloc(sizeof(Liste * ));
    init_liste(sz->B[i]);
  }

  sz->Lzsg = malloc(sizeof(Liste *));
  init_liste(sz->Lzsg);

  /*if ((sz->Lzsg == NULL) || (sz->B == NULL))
    exit(0);*/


}

void ajoute_Zsg(S_Zsg *sz, int i, int j){
  if (i > sz->dim || j > sz->dim)
    exit(EXIT_FAILURE);

  if (sz->App[i][j] != -1) {

    /* Remplace la liste par une nouvelle liste contenant la case supplemantaire */
    ajoute_en_tete(sz->Lzsg, i, j); 

    /* Remplace la reference a la liste dans le tableau App */
    sz->App[i][j] = -1;
  }
}

void ajoute_Bordure(S_Zsg *sz, int i, int j, int cl){
  if (i > sz->dim || j > sz->dim)
      exit(EXIT_FAILURE);

  /* Remplace la liste par une nouvelle liste contenant la case supplemantaire */
  ajoute_en_tete(sz->B[cl], i, j); 

  /* Remplace la reference a la liste dans le tableau App */
  if (cl<100)
    sz->App[i][j] = cl;

}

int appartient_Zsg(S_Zsg *sz, int i, int j){
  
  return (sz->App[i][j] == -1);

}

int appartient_Bordure(S_Zsg *sz, int cl){

  return (*(sz->B[cl]) != NULL);
  
}
 
int agrandit_Zsg(int **M, S_Zsg *Z, int cl, int k, int l){

  Liste *Pile = malloc(sizeof(Liste *));
  int i, j, x, y, cpt = 0; /* cpt pout compter le nombre de case ajoutes dans ZSG */
  Liste *c = Z->B[cl];
  int **rm;


  if(!rechercher_Liste(k, l, Z->B[cl])){
      printf("le case (k, l) n'est pas dans la bordure\n");
      exit(EXIT_FAILURE);
  } 

  init_liste(Pile);

  rm=(int **) malloc(sizeof(int*)*(Z->dim));
  for (x=0;x<(Z->dim);x++){
    rm[x]=(int*) malloc(sizeof(int)*(Z->dim));
    for (y=0;y<(Z->dim);y++)
      rm[x][y]=0;
  }
  
  /* placer tous les case de B[cl] dans la pile */
  while((*c) != NULL){
    ajoute_en_tete(Pile, (*c)->i,( *c)->j);
    rm[(*c)->i][(*c)->j] = 1;
    c = &((*c)->suiv);
  }

  detruit_liste(Z->B[cl]); /* detruir la bordure */

   
  while(!test_liste_vide(Pile)){
    enleve_en_tete(Pile, &i, &j);

    if (M[i][j] == cl) {
      /* Si le case est de la bonne couleur,  on l'ajoute a la ZSG */
      ajoute_Zsg(Z, i, j);
      cpt++;
	
      /* a gauche */
      if ((i > 0) &&
	  !((rm[i][j] == 1) || (appartient_Zsg(Z, i - 1, j)))) {
	/* Si la case n'est pas dans la pile ni dans la ZSG */
	ajoute_en_tete(Pile, i - 1, j); 
	rm[i-1][j] = 1;
      }

      /* a droite */
      if ((i < Z->dim-1) &&
	  !(rm[i + 1][j] || (appartient_Zsg(Z, i + 1, j)))) {
	/* Si la case n'est pas dans la pile ni dans la ZSG */
	ajoute_en_tete(Pile, i + 1, j);
	rm[i+1][j] = 1;
      }

      /* en bas */
       if ((j < Z->dim-1) &&
	  !(rm[i][j + 1] || (appartient_Zsg(Z, i, j+1)))) {
	/* Si la case n'est pas dans la pile ni dans la ZSG */
	ajoute_en_tete(Pile, i, j+1);
	rm[i][j+1] = 1;
      }

      /* en haut */
      if ((j > 0) &&
	  !(rm[i][j-0] || (appartient_Zsg(Z, i, j-0)))) {
	/* Si la case n'est pas dans la pile ni dans la ZSG */
	ajoute_en_tete(Pile, i, j-0);
	rm[i][j-1] = 1;
      }
    }
    else /* Sinon on l'ajoute a la bordure */
	ajoute_Bordure(Z, i, j, M[i][j]);

  }

  
  for(i=0; i<Z->dim; i++)
    free(rm[i]);

  free(rm);

  return cpt;

}
