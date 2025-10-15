#include <errno.h>
#include <assert.h>
#include <stdio.h>
#include "../../include/Types/Direction.h"
#include "../../include/Types/EnsembleDeNNN.h"
#include "../../include/Types/EnsembleDeDirection.h"
#include "../../include/Types/MatriceDAdjacence.h"
#include "../../include/Types/caseEtDirection.h"
#include "../../include/Types/labyrinthe.h"
#include "../../include/Types/ListeChaineeDeNNN.h"


LAB_Labyrinthe LAB_labyrinthe(unsigned int largeurLabyrinthe, unsigned int entree, unsigned int sortie, Direction directionEntree, Direction directionSortie){
  LAB_Labyrinthe laby;
  CD_CaseEtDirection  lEntree;
  CD_CaseEtDirection  laSortie;
  MDA_MatriceDAdjacence lesLiaisons;
  
  laby.largeur = largeurLabyrinthe;

  lEntree = CD_caseEtDirection(entree,directionEntree);
  laby.entree = lEntree;

  laSortie = CD_caseEtDirection(sortie,directionSortie);
  laby.sortie = laSortie;
  
  lesLiaisons = MDA_creerMatriceDAdjacence((laby.largeur)*(laby.largeur));
  laby.liaisonsCases = lesLiaisons;

  return laby;
}

void LAB_casserMur(LAB_Labyrinthe* laby, unsigned int case1, unsigned int case2){
  MDA_creerLien(&laby->liaisonsCases,case1,case2);
}

int LAB_largeur(LAB_Labyrinthe laby){
  return laby.largeur;
}

CD_CaseEtDirection LAB_caseDEntree(LAB_Labyrinthe laby){
  return laby.entree;
}

CD_CaseEtDirection LAB_caseDeSortie(LAB_Labyrinthe laby){
  return laby.sortie;
}


EDD_EnsembleDeDirection LAB_directionsPossibles(LAB_Labyrinthe laby, unsigned int uneCase){
  LCDNNN_ListeChaineeDeNNN laListeDesLiaisons;
  EDD_EnsembleDeDirection directionsPossibles = EDD_ensemble();
  laListeDesLiaisons = MDA_obtenirLiens(laby.liaisonsCases,uneCase);
  while (!(laListeDesLiaisons==NULL)){
    if (LCDNNN_obtenirElement(laListeDesLiaisons)==(uneCase+1)){
      EDD_ajouter(&directionsPossibles,D);
    }
    if (LCDNNN_obtenirElement(laListeDesLiaisons)==(uneCase-1)){
      EDD_ajouter(&directionsPossibles,G);
    }
    if (LCDNNN_obtenirElement(laListeDesLiaisons)==((uneCase)-(laby.largeur))){
      EDD_ajouter(&directionsPossibles,H);
    }
    if (LCDNNN_obtenirElement(laListeDesLiaisons)==((uneCase)+(laby.largeur))){
      EDD_ajouter(&directionsPossibles,B);
    }
    laListeDesLiaisons = LCDNNN_obtenirListeSuivante(laListeDesLiaisons);
  }
  return directionsPossibles;
}
EDNNN_EnsembleDeNNN LAB_casesAccessibles(LAB_Labyrinthe laby, unsigned int uneCase){
  LCDNNN_ListeChaineeDeNNN laListeDesLiaisons;
  EDNNN_EnsembleDeNNN casesAccessibles = EDNNN_ensemble();
  laListeDesLiaisons = MDA_obtenirLiens(laby.liaisonsCases,uneCase);
  while (!(LCDNNN_estVide(laListeDesLiaisons))){
    if (LCDNNN_obtenirElement(laListeDesLiaisons)!=(uneCase)){
      EDNNN_ajouter(&casesAccessibles,LCDNNN_obtenirElement(laListeDesLiaisons));
    }
    laListeDesLiaisons = LCDNNN_obtenirListeSuivante(laListeDesLiaisons);
  }
  return casesAccessibles;
}

unsigned int LAB_caseDestination(LAB_Labyrinthe laby, unsigned int uneCase, Direction saDirection){
  unsigned int caseDestination;
  if (saDirection == H){
    caseDestination=(uneCase-(laby.largeur));
  }
  if (saDirection == B){
    caseDestination=(uneCase+(laby.largeur));
  }
  if (saDirection == G){
    caseDestination=(uneCase-1);
  }
  if (saDirection == H){
    caseDestination=(uneCase+1);
  }
  return caseDestination;
}


EDNNN_EnsembleDeNNN LAB_casesAdjacentes(LAB_Labyrinthe laby, unsigned int uneCase){
  unsigned int maxl;
  unsigned int minl;
  unsigned int maxh;
  unsigned int minh;
  unsigned int i;
  unsigned int j;
  EDNNN_EnsembleDeNNN casesAdjacentes;
  unsigned int caseCourante;

  if ((uneCase)% (laby.largeur)==1){
    minl=1;
  }
  else{
    minl=uneCase-1;
  }
  if ((uneCase)%(laby.largeur)==0){
    maxl=laby.largeur;
  }
  else{
    maxl=uneCase+1;
  }
  if ((uneCase>=1)&&(uneCase<=laby.largeur)){
    minh=1;
  }
  else{
    minh=uneCase-1;
  }
  if ((uneCase>=((laby.largeur*laby.largeur)-laby.largeur+1))&&(uneCase<=(laby.largeur*laby.largeur))){
    maxh=laby.largeur;
  }
  else{
    maxh=uneCase+1;
  }

  for (i=minl;i<=maxl;i++){
    for (j=minh-1;j<=maxh-1;j++){
      caseCourante = i+(j*laby.largeur);
      EDNNN_ajouter(&casesAdjacentes,caseCourante);
    }
  }
  return casesAdjacentes;
}

EDNNN_EnsembleDeNNN LAB_casesNonAccesbiles(LAB_Labyrinthe laby, unsigned int uneCase){
  return EDNNN_soustraction(LAB_casesAdjacentes(laby,uneCase),LAB_casesAccessibles(laby,uneCase));
}

void LAB_DirectionEntreeEtSortie(LAB_Labyrinthe laby, Direction* directionEntree, Direction* directionSortie){
  *directionEntree = CD_obtenirDirection(laby.entree);
  *directionSortie = CD_obtenirDirection(laby.sortie);
}
