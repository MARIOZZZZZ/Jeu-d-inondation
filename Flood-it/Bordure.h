#ifndef _BORDURE_
#define _BORDURE_

#include <stdio.h>
#include "Liste_case.h"


typedef struct {

  int dim ; /* dimension de la grille */
  int nbcl ; /* nombre de couleurs */

  Liste *Lzsg ; /* Liste des cases de la zone Zsg */
  Liste ** B ; /* Tableau de listes de cases de la bordure*/
  int ** App ; /* Tableau a double entree des appartenances */

} S_Zsg ;


/* initialisation de la structure */
void init_Zsg(S_Zsg *sz, int dim, int nbcl);

/* Ajoute une case dans la liste Lzsg */
void ajoute_Zsg(S_Zsg *sz, int i, int j);

/* Ajoute une case dans la bordure d’une couleur cl donnée */
void ajoute_Bordure(S_Zsg *sz, int i, int j, int cl);

/* renvoie vrai si une case est dans LZsg */
int appartient_Zsg(S_Zsg *sz, int i, int j);

/* renvoie vrai si une case est dans la bordure de couleur cl donnée */
int appartient_Bordure(S_Zsg *sz, int cl);

/* mettre a jour le Lzsg et bordure */
int agrandit_Zsg(int **M, S_Zsg *Z, int cl, int k, int l);

#endif
