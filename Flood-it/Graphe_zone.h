#ifndef GRAPHE_ZONES
#define GRAPHE_ZONES

#include "Liste_case.h"



typedef struct sommet Sommet ;

/* Element d’une liste cha\^in\’ee de pointeurs sur Sommets */
typedef struct cellule_som {
  Sommet * sommet ;
  struct cellule_som * suiv ;

} Cellule_som ;


struct sommet {
  int num ;        /* Numero du sommet (sert uniquement a l’affichage) */
  int cl ;         /* Couleur d’origine du sommet-zone */
  Liste cases ;    /* Listes des cases du sommet-zone */
  int nbcase_som ; /* Nombre de cases de cette liste */

  Cellule_som * sommet_adj ; /* Liste des ar\eteses pointeurs sur les sommets adjacents */

  int marque; /* Cet entier servira pour le marquage des sommets
		 dans les algorithmes de parcours: 0 non marque, 1 marque */

  Sommet *pere; /* Ce pointeur servira pour retenir un chemin
		   dans les algorithmes de parcours:
		   il servira a noter le Pere dans les parcours en largeur */



};


typedef struct graphe_zone {
  int nbsom ;         /* Nombre de sommets dans le graphe */
  Cellule_som * som ; /* Liste chainee des sommets du graphe */

  Sommet *** mat ;    /* Matrice de pointeurs sur les sommets 
			indiquant a quel sommet appartient une 
			case (i,j) de la grille */

} Graphe_zone;

typedef struct s_bordure {
  int nbcl; // nombre de couleurs differentes
  int *taille_liste; // taille de la liste contenue dans la case [i][j] de tab
  Cellule_som **tab; // tableau de listes de Cellule_som figurant dans la case [i][j]
} Bordure;



int adjacent(Sommet *s1, Sommet *s2);

Cellule_som *ajoute_liste_sommet(Sommet *ptrsommet, Cellule_som *cell_som);

void detruit_liste_sommet(Cellule_som *cell_som);

void ajoute_voisin(Sommet *s1, Sommet *s2);

void cree_graphe_zone( Graphe_zone *G, int** M, int nb);

void trouve_zone(int **M, int i, int j, Sommet *s, Graphe_zone *G, int nb);

void affichage_graphe(Graphe_zone *G, int nb);

/* Mise a jour de la bordure graphe */
void maj_bordure_graphe(Graphe_zone *G, int **M, int nbcl);

/* On prend un graphe et une couleur
 *	On change la couleur du sommet de la Zsg
 *	On parcourt toutes les cases de la Zsg et on leur donne leur nouvelle couleur
 */
void changeCouleurZsg(Graphe_zone *G, int ** M,  int cl);

#endif
