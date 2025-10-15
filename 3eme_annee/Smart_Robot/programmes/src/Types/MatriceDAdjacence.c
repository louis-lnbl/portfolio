
#include <stdbool.h> 
#include <stddef.h>  
#include <assert.h>
#include <errno.h>
#include <stdlib.h>
#include "../../include/Types/ListeChaineeDeNNN.h"
#include "../../include/Types/MatriceDAdjacence.h"


MDA_MatriceDAdjacence MDA_creerMatriceDAdjacence(unsigned int nbCases){
  MDA_MatriceDAdjacence uneMatrice;
  uneMatrice.nbElements = nbCases;
  uneMatrice.tableau = NULL;
  unsigned int i;
  unsigned int j;
  
  uneMatrice.tableau = (unsigned int**) malloc (uneMatrice.nbElements * sizeof(unsigned int*));
  if (!uneMatrice.tableau){
    errno = MDA_ERREUR_MEMOIRE;
  }

  for(i=1;i<=uneMatrice.nbElements;i++){
    uneMatrice.tableau[i-1] = (unsigned int*) malloc (uneMatrice.nbElements * sizeof(unsigned int));
    if (!uneMatrice.tableau[i-1]){
      errno = MDA_ERREUR_MEMOIRE;
    }

    for (j=1; j<=uneMatrice.nbElements;j++){
      uneMatrice.tableau[i-1][j-1] = 0;
    }
  }

  return uneMatrice;
}


void MDA_creerLien(MDA_MatriceDAdjacence *laMatrice, unsigned int case1, unsigned int case2){
  laMatrice->tableau[case1-1][case2-1] = 1;
  laMatrice->tableau[case2-1][case1-1] = 1;
}

void MDA_retirerLien(MDA_MatriceDAdjacence *laMatrice, unsigned int case1, unsigned int case2){
  laMatrice->tableau[case1-1][case2-1] = 0;
  laMatrice->tableau[case2-1][case1-1] = 0;
}  

LCDNNN_ListeChaineeDeNNN MDA_obtenirLiens(MDA_MatriceDAdjacence laMatrice, unsigned int case1){
  LCDNNN_ListeChaineeDeNNN listeDesLiens = LCDNNN_listeVide();
  unsigned int i;

  for (i = 0; i < laMatrice.nbElements; i++) {
    if (laMatrice.tableau[case1-1][i] != 0) {
      LCDNNN_ajouter(&listeDesLiens, i+1);
    }
  }
  return listeDesLiens;
}

void MDA_libererMatrice(MDA_MatriceDAdjacence *laMatrice){
  unsigned int i;
  
  for (i = 0; i < laMatrice->nbElements; i++) {
    free(laMatrice->tableau[i]); 
  }
  free(laMatrice->tableau);
  laMatrice->tableau = NULL;
  laMatrice->nbElements = 0;
}
