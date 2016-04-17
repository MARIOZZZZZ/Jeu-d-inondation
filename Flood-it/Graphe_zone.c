#include <stdio.h>
#include <stdlib.h>
#include "Liste_case.h"
#include "Bordure.h"
#include "Graphe_zone.h"
#include "Sequence_aleatoire.h"

/* Fonction pour determiner l'adjacence de deux sommets dans un 
   graphe
   1 si s1 est inclus dans s2
   2 si s2 est inclus dans s1
   3 si double inclusion
   0 si aucune inclusion
*/
int adjacent(Sommet *s1, Sommet *s2){

  int i = 0;
  Cellule_som *ptr_courant = s1->sommet_adj;

  while (ptr_courant)
    if (ptr_courant->sommet == s2) {
      i = 1;

      break; // on saute le while car on a trouve une inclusion
    }
    else ptr_courant = ptr_courant->suiv;


  ptr_courant = s2->sommet_adj;
  while (ptr_courant)
    if (ptr_courant->sommet == s1) {
      if (i == 1)
	i = 3; // double-inclusion
      else
	i = 2; // s2 inclus dans s1

      break; // on saute le while car on a trouve une inclusion
    }
    else ptr_courant = ptr_courant->suiv;

  return i;
}

Cellule_som *ajoute_liste_sommet(Sommet *psommet, Cellule_som *cell_som){

  Cellule_som *cell;

  cell = (Cellule_som *)malloc(sizeof(Cellule_som));

  cell->sommet = psommet;
  cell->suiv = cell_som;
   printf("test6\n");
  return cell;

}

void detruit_liste_sommet(Cellule_som *cell_som){

  Cellule_som *courant = cell_som;
  while(courant){
    cell_som=courant->suiv;

    free(courant);

    courant = cell_som;
  }
}

void ajoute_voisin(Sommet *s1, Sommet *s2){

  s1->sommet_adj = ajoute_liste_sommet(s2, s1->sommet_adj);
  s2->sommet_adj = ajoute_liste_sommet(s1, s2->sommet_adj);
}


void cree_graphe_zone( Graphe_zone *G, int** M, int nb){

  int i, j;
  Sommet *s = NULL, *s2 = NULL;

  // ici on considere G->som = NULL de base
      
  // allocation des sommets de G
  for (i=0; i<nb; i++){
    printf("test1\n");
    for (j=0; j<nb; j++)

     
      if (G->mat[i][j] == NULL) {
	
	s = (Sommet *) malloc(sizeof(Sommet)); // initalisation d'un sommet vide
	s->nbcase_som = 0;
	
	s->cases = malloc(sizeof(Elnt_liste));
	
	/*init_liste(&(s->cases));*/

	s->cases->i = i; /* !!!!!! */
	//	printf("test7\n");
	s->cases->j = j;
	s->sommet_adj = NULL;
	
	G->mat[i][j] = s;
	
	(G->nbsom)++;
	 
	/* ceci marche meme si G->som n'a pas de liste a la base
	 * donc le "dernier" element sera a NULL
	 */
	G->som = ajoute_liste_sommet(s, G->som);
	// printf("test2\n");

	// on remplit les sommets en appelant trouve_zone
	trouve_zone(M, i, j, s, G, nb);

      }
  }


  // recherche des sommets adjacents
  for (i=0; i < nb; i++)
    for(j=0; j < (nb - 1); j++) {
      /* Si deux cases adjacentes de la matrice pointent vers des Sommets
       * differents qui ne sont pas deja adjacents alors une relation
       * d'adjacence est ajoutée. Sinon, on passe aux cases suivantes
       */
      s = G->mat[i][j];
      s2 = G->mat[i][j+1];
      // si les sommets sont adjacents, on skip
      if (s == s2 || adjacent(s, s2) != 0)
	continue;

      // Si les sommets sont diff et qu'ils ne sont pas deja adjacents
      ajoute_voisin(s, s2);
    }
}

void trouve_zone(int **M, int i, int j, Sommet *s, Graphe_zone *G, int nb){

  Liste *p = malloc (sizeof(Liste));
  
  

  s->cl = M[i][j]; // Mise a jour de la couleur de la case
  detruit_liste_sommet(s->sommet_adj); // Suppresion des membres de la zone
  s->nbcase_som = 0;


  init_liste(p);

  ajoute_en_tete(p, i, j); // On empile la premiere case

  while (!test_liste_vide(p)) {
    enleve_en_tete(p, &i, &j);
    printf("test4\n");

    if ((j+1 < nb) &&
	(M[i][j] == s->cl) &&
	(!rechercher_Liste(i, j+1, p)) &&
	(!rechercher_Liste(i, j+1, &(s->cases)))) {
      	printf("test5\n");
      ajoute_en_tete(&(s->cases), i, j+1); // Ajout de la case a la liste des membres de la zone
      s->nbcase_som++; // Incr du compteur de zone
      ajoute_en_tete(p, i, j+1);
    }
    

    if ((j-1 >= 0) &&
	(M[i][j] == s->cl) &&
	(!rechercher_Liste(i, j+1, p)) &&
	(!rechercher_Liste(i, j-1, &(s->cases)))) {
      	printf("test9\n");
      ajoute_en_tete(&(s->cases), i, j-1); // Ajout de la case a la liste des membres de la zone
      s->nbcase_som++; // Incr du compteur de zone
      ajoute_en_tete(p, i, j-1);
    }

    if ((i+1< nb) &&
	(M[i][j] == s->cl) &&
	(!rechercher_Liste(i, j+1, p)) &&
	(!rechercher_Liste(i+1, j, &(s->cases)))) {
      	printf("test10\n");
      ajoute_en_tete(&(s->cases), i+1, j); // Ajout de la case a la liste des membres de la zone
      s->nbcase_som++; // Incr du compteur de zone
      ajoute_en_tete(p, i+1, j);
    }

    if ((i-1 < nb) &&
	(M[i][j] == s->cl) &&
	(!rechercher_Liste(i, j+1, p)) &&
	(!rechercher_Liste(i-1, j, &(s->cases)))) {
      	printf("test11\n");
      ajoute_en_tete(&(s->cases), i-1, j); // Ajout de la case a la liste des membres de la zone
      s->nbcase_som++; // Incr du compteur de zone
      ajoute_en_tete(p, i-1, j);
    }
    
  
    //On pointe la case de la matrice de G sur la zone
    G->mat[i][j] = s;
    G->som++;

   
  }
  detruit_liste(p);

}

void affichage_graphe(Graphe_zone *G, int nb){

  int i=0, j=0;
  Cellule_som *parcours; /* sert a parcourir la liste des sommets */

  for (i=0; i<nb; i++)
    for (j=0; j<nb; j++) {
      parcours = G->mat[i][j]->sommet_adj;
      printf("Dans le sommet [%d][%d], on a les noeuds ", i, j);
      while (parcours) {
	printf("%d ", parcours->sommet->num);
	parcours = parcours->suiv;
      }
      printf("\n");
    }

}

void maj_bordure_graphe(Graphe_zone *G, int **M, int nbCl)
{
  int i, j, iMax = 0;
  int *tab = NULL;

  //recuperation de la liste des zones de bordure
  Cellule_som *bordureElem = NULL;

  // deux elements Cellule_Som* pour suppression
  Cellule_som *a = G->mat[0][0]->sommet_adj;
  Cellule_som *temp = a;
  
  Sommet *Zsg = G->mat[0][0];
  Liste *casesAAjouter = NULL, *elem = NULL;

  tab = (int *) malloc(sizeof(int) * nbCl);
  if(tab == NULL) {
		fprintf(stderr, "Erreur d'allocation dans la fonction : update_bordure_graphe ");
		exit(1);
	}

  for(i = 0; i < nbCl; i++)
      tab[i] = 0;

  while(a != NULL) {
      tab[(a->sommet)->cl]++;
      a = a->suiv;
    }
  
  for(i = 1; i < nbCl; i++) {
    if(tab[i] > tab[iMax]) {
      iMax = i;
    }
    else {
      iMax = iMax;
    }
     
  }
  // iMax -> indice de la couleur la plus presente = valeur de la couleur
  changeCouleurZsg(G, M, iMax);

  // on supprime toutes les zones de la bordure de la meme couleur que iMax
  // on ajoute a la zsg les cases des zones supprimees et leurs adjacences
  // on a le nombre de zones dans tab[iMax]

  a = (G->mat[0][0])->sommet_adj;
  elem = &(Zsg->cases);
  while((*elem)->suiv != NULL)
    elem = &((*elem)->suiv);

  while(a != NULL) {
    
    if((a->sommet)->cl == iMax) {
      bordureElem = a->sommet->sommet_adj;
      
      while (bordureElem) { // ajout des adjacences
				ajoute_voisin(a->sommet, bordureElem->sommet);
				bordureElem = bordureElem->suiv;
      }
      
      // on enleve a de la liste d'adjacence de Zsg
      // recuperation des cases
      casesAAjouter = &(a->sommet->cases);
      (*elem)->suiv = *casesAAjouter;
      
      while ((*elem)->suiv) {
	i = (*elem)->i; // ajoute de Zsg dans la matrice de Sommets
	j = (*elem)->j; // pour les nouvelles cases
	G->mat[i][j] = Zsg;
	elem = &((*elem)->suiv);
      }

      // destruction du sommet
      temp->suiv = a->suiv;
      free(a); //on a supprime un sommet
      a = temp->suiv;
      G->nbsom--; // on le retire du compteur


    }
    else {
      // destruction du sommet
      temp = a;
      a = a->suiv;
    }
  }
}


void changeCouleurZsg(Graphe_zone *G, int ** M,  int cl)
{
  Liste *elem = &((G->mat[0][0])->cases);
  int i, j;
  (G->mat[0][0])->cl = cl;

  while(elem != NULL) {
    i = (*elem)->i;
    j = (*elem)->j;
      M[i][j] = cl;
      elem = &((*elem)->suiv);
    }
}
