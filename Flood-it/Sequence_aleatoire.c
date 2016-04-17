#include<stdlib.h>
#include<time.h>
#include "Sequence_aleatoire.h"
#include "Bordure.h"



int rechercher_Liste(int i, int j, Liste *L){

  if(test_liste_vide(L))
    return 0;

  if(((*L)->i)==i&&((*L)->j)==j)
    return 1;

  return rechercher_Liste(i, j, &((*L)->suiv));
}



void trouve_zone_rec(int **M, int dim, int i, int j, int *taille, Liste *L, int cl){

  int coulAct = M[i][j]; /* memoriser la couleur actuelle */

  if(coulAct == cl)
    return;

  M[i][j] = cl;
  
  if ((i > 0) && (coulAct == M[i-1][j])) { /* verifier la case a gauche */
    printf("a gauche\n");
    trouve_zone_rec(M, dim, (i-1), j, taille, L, cl);
  }

  if ((j > 0) && (coulAct == M[i][j-1])) { /* verifier la case au dessus */
    printf("au dessus\n");
    trouve_zone_rec(M, dim, i, (j-1), taille, L, cl);
  }
  
  if ((i < (dim - 1)) && (M[i+1][j] == coulAct)) { /* verifier la case a droite */
    printf("a droite\n");
    trouve_zone_rec(M, dim, (i+1), j, taille, L, cl);
  }

  if( (j < (dim - 1)) && (M[i][j+1] == coulAct)) { /* verifier la case au dessous */
    printf("au dessous\n");
  trouve_zone_rec(M, dim, i, (j+1), taille, L, cl);
  }

  /*mettre a jour la liste et le taille*/
if(!(rechercher_Liste(i, j, L))){
    (*taille)++;
    ajoute_en_tete(L, i, j);
  }
}


int sequence_aleatoire_rec(int **M, Grille *G, int dim, int nbcl, int aff){

  int i, j, cl, taille = 0, cpt = 0;
  Liste *Zsg = malloc(sizeof (Liste *));
  
  init_liste(Zsg);
  
  srand(time(NULL)); /* Generer la graine */

  while(taille < (dim*dim-1)){
    cl = rand() % nbcl; /* Initialisation de la couleur aleatoire */
    
    trouve_zone_rec(M, dim, 0, 0, &taille, Zsg, cl);
    printf("taille = %d\n", taille);
    
    if(aff==1){

      /* Reaffichage de la grille */
      for (i=0;i<dim; i++ )
	for (j=0;j<dim;j++)
	  Grille_attribue_couleur_case(G,i,j,M[i][j]);

      Grille_redessine_Grille();

      Grille_attente_touche();
      
    }
    
    cpt++;
  }


  return cpt;
}


void trouve_zone_imp(int **M, int dim, int i, int j, int *taille, Liste *Pile, int cl){

  if(test_liste_vide(Pile)) /* Asuerer le pile est bien vide */
    init_liste(Pile);

  int coulAct = M[i][j]; /* memoriser la couleur actuelle */
  int **rm;              /* Matrice pour marquer les case deja comptes */
  int x, y;
  
  if(coulAct == cl)
    return;

  rm=(int **) malloc(sizeof(int*)*dim);
  for (x=0;x<dim;x++){
    rm[x]=(int*) malloc(sizeof(int)*dim);
    for (y=0;y<dim;y++)
      rm[x][y]=0;
  }
  
  (*taille) = 0;

  ajoute_en_tete(Pile, i, j); /* empile le premier case */
  (*taille)++;
  rm[i][j] = 1;

  while(!test_liste_vide(Pile)){
    
    enleve_en_tete(Pile, &i, &j);
    M[i][j] = cl;

    if ((i > 0) && (coulAct == M[i-1][j])) { /* verifier la case a gauche */
      if(rm[i-1][j] != 1){
	ajoute_en_tete(Pile, i-1, j);
	(*taille)++;
	rm[i-1][j] = 1;
      }
    }

    if ((j > 0) && (coulAct == M[i][j-1])) { /* verifier la case au dessus */
      if(rm[i][j-1] != 1){
	ajoute_en_tete(Pile, i, j-1);
	(*taille)++;
	rm[i][j-1] = 1;
      }
    }
  
    if ((i < (dim - 1)) && (M[i+1][j] == coulAct)) { /* verifier la case a droite */
      if(rm[i+1][j] != 1){
	ajoute_en_tete(Pile, i+1, j);
	(*taille)++;
	rm[i+1][j] = 1;
      }
    }

    if( (j < (dim - 1)) && (M[i][j+1] == coulAct)) { /* verifier la case au dessous */
      if(rm[i][j+1] != 1){
	ajoute_en_tete(Pile, i, j+1);
	(*taille)++;
	rm[i][j+1] = 1;
      }
    }
    
  }
}


int sequence_aleatoire_imp(int **M, Grille *G, int dim, int nbcl, int aff){

  int i, j, cl, taille = 0, cpt = 0;
  Liste *P = malloc(sizeof (Liste *)); /* Allouer la mermoire pour le pile */
  
  init_liste(P);
  
  srand(time(NULL)); /* Generer la graine */

  while(taille < (dim*dim-1)){
    cl = rand() % nbcl; /* Initialisation de la couleur aleatoire */
   
    trouve_zone_imp(M, dim, 0, 0, &taille, P, cl);
    printf("taille = %d\n", taille);
    if(aff == 1){

      /* Reaffichage de la grille */
      for (i=0;i<dim; i++ )
	for (j=0;j<dim;j++)
	  Grille_attribue_couleur_case(G,i,j,M[i][j]);

      Grille_redessine_Grille();

      Grille_attente_touche();
      
    }
    
    cpt++;
  }

  detruit_liste(P); /* liberation de la memoire de Pile */
  return cpt;

}


int strequence_aleatoire_rapide(int **M, Grille *G, int dim, int nbcl){

  S_Zsg *z = malloc(sizeof(S_Zsg));
  int r, i,j, cpt = 0;
  int taille = 0;
  Liste *c;

  
  init_Zsg(z, dim, nbcl);
  
  srand(time(NULL)); /* Genereration de la graine */

  /* initalisation de la valeur de la demarrage */
  ajoute_Bordure(z, 0, 0, M[0][0]);

  taille = agrandit_Zsg(M, z, M[0][0], 0, 0);
    
  printf("taille=%d\n",taille);
  while(taille < ((dim*dim))){

    r = rand()%nbcl;

    if( *(z->B[r]) == NULL)
      continue;

    taille += agrandit_Zsg(M, z, r,( *(z->B[r]))->i,(*( z->B[r]))->j);

    /* colorier le Lszg */
    c = z->Lzsg;
    while((*c)){
      M[(*c)->i][(*c)->j] = r;
      c = &((*c)->suiv);
    }
    
    /* Reaffichage de la grille */
    for (i=0;i<dim; i++ )
      for (j=0;j<dim;j++)
	Grille_attribue_couleur_case(G,i,j,M[i][j]);

    Grille_redessine_Grille();

    Grille_attente_touche();
      
    
    printf("taille=%d\n",taille);
    cpt++;
  }

  return cpt;
}
