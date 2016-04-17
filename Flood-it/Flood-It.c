#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "API_Grille.h"
#include "API_Gene_instance.h"
#include "Sequence_aleatoire.h"
#include "Bordure.h"
#include "Strategies_pilotees.h"

 
 
void afficher_menu(int* val){	
  int choix;
  
  printf("0- Exit\n");
  printf("1- Recursive\n");
  printf("2- Imperative\n");
  printf("3 -Rapide\n");
  printf("4 -MaxBordure\n");
  //printf("3- Comparer le temps de recherche par auteur\n");
  // printf("4- Modifier le taille de la table d'hachage (Par defaut: 100)\n");

  
  printf("Votre choix : ");
  scanf("%d", &choix);
  
  *val = choix;
  printf("\x1b[2J\x1b[1;1H");
}


int main(int argc,char**argv){

  int dim, nbcl, nivdif, graine;
  Grille *G;
  int i,j;
  int **M;

  clock_t
    temps_initial, /* Temps initial en micro-secondes */
    temps_final;   /* Temps final en micro-secondes */
  float
    temps_cpu;     /* Temps total en secondes */ 
 


  if(argc!=5){
    printf("usage: %s <dimension nb_de_couleurs niveau_difficulte graine>\n",argv[0]);
    return 1;
  }

  dim=atoi(argv[1]);


  nbcl=atoi(argv[2]);
  nivdif=atoi(argv[3]);
  graine=atoi(argv[4]);

  /* Generation de l'instance */

  M=(int **) malloc(sizeof(int*)*dim);
  for (i=0;i<dim;i++){
    M[i]=(int*) malloc(sizeof(int)*dim);
    if (M[i]==0) printf("Pas assez d'espace mémoire disponible\n");
  }

   

  //Grille_attente_touche();
 
  int iter, choix;

  //int coul = M[0][0] == 0? 1 : 0;
  
  printf("\x1b[2J\x1b[1;1H");
  printf("Welcome !\n\n");


  
  /* Manipulation de la menu */
  
  do{
    afficher_menu(&choix);

    switch(choix){
    case 0:
      printf("\x1b[2J\x1b[1;1H");
      printf("Adieu ... :'( \n");
      break;

    case 1:
      /* Affichage de la grille */

      Gene_instance_genere_matrice(dim, nbcl, nivdif, graine, M);
      Grille_init(dim,nbcl, 500,&G);

      Grille_ouvre_fenetre(G);

      for (i=0;i<dim;i++)
	for (j=0;j<dim;j++){
	  Grille_attribue_couleur_case(G,i,j,M[i][j]);
	}
      
      Grille_redessine_Grille();

      /*------------------------*/

      iter = sequence_aleatoire_rec(M, G, dim, nbcl, 1);
      
      printf("%d Iterations necessaires!\n", iter);

      /* Fermeture de la grille */
      Grille_attente_touche();
 
      Grille_ferme_fenetre();

      Grille_free(&G);
      break;
      
    case 2:
      Gene_instance_genere_matrice(dim, nbcl, nivdif, graine, M);
      Grille_init(dim,nbcl, 500,&G);

      Grille_ouvre_fenetre(G);

      for (i=0;i<dim;i++)
	for (j=0;j<dim;j++){
	  Grille_attribue_couleur_case(G,i,j,M[i][j]);
	}

      Grille_redessine_Grille();
      
      iter = sequence_aleatoire_imp(M, G, dim, nbcl, 1);
      
      printf("%d Iterations necessaires!\n", iter);

      Grille_attente_touche();
 
      Grille_ferme_fenetre();
  
      Grille_free(&G);
      break;

    case 3:
      Gene_instance_genere_matrice(dim, nbcl, nivdif, graine, M);
      Grille_init(dim,nbcl, 500,&G);

      Grille_ouvre_fenetre(G);

      for (i=0;i<dim;i++)
	for (j=0;j<dim;j++){
	  Grille_attribue_couleur_case(G,i,j,M[i][j]);
	}

      Grille_redessine_Grille();
      
      iter = strequence_aleatoire_rapide(M, G, dim, nbcl);
      
      printf("%d Iterations necessaires!\n", iter);

      Grille_attente_touche();
 
      Grille_ferme_fenetre();
  
      Grille_free(&G);
      break;


    case 4:
      Gene_instance_genere_matrice(dim, nbcl, nivdif, graine, M);
      Grille_init(dim,nbcl, 500,&G);

      Grille_ouvre_fenetre(G);

      for (i=0;i<dim;i++)
	for (j=0;j<dim;j++){
	  Grille_attribue_couleur_case(G,i,j,M[i][j]);
	}

      Grille_redessine_Grille();
      
      iter = maxBordure(G, M, dim);
      
      printf("%d Iterations necessaires!\n", iter);

      Grille_attente_touche();
 
      Grille_ferme_fenetre();
  
      Grille_free(&G);
      break;

      
    default:
      printf("la option n'est pas connue!!\n");
      break;
    }

  }while(choix != 0);
  
 

  return 0;
}
