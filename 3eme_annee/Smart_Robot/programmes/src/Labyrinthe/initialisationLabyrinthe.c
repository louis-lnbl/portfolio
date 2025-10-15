#include <errno.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "../../include/Labyrinthe/initialisationLabyrinthe.h"
#include "../../include/Types/Direction.h"
#include "../../include/Types/ListeDeCDC.h"
#include "../../include/Types/labyrinthe.h"


LAB_Labyrinthe IL_creerLabyrinthe(unsigned int largeurLabyrinthe, unsigned int entree, unsigned int sortie, Direction directionPorteEntree, Direction directionPorteSortie, LDCDC_ListeDeCDC liaisonsCases){
  LAB_Labyrinthe laby = LAB_labyrinthe(largeurLabyrinthe, entree, sortie, directionPorteEntree, directionPorteSortie);
  IL_creerPassage(&laby, liaisonsCases);
  return laby;
}

void IL_creerPassage(LAB_Labyrinthe* laby, LDCDC_ListeDeCDC liaisonsCases){
  unsigned int i;

  for (i=1; i<=LDCDC_longueur(liaisonsCases); i++) {
    char* element = LDCDC_obtenirElement(liaisonsCases, i);
    unsigned int case1;
    unsigned int case2;
    IL_separationCases(element,&case1,&case2);
    LAB_casserMur(laby,case1,case2);
  }
}

void IL_separationCases(char* casesASeparer,unsigned int *case1,unsigned int *case2){

  unsigned int milieu;
  int i=0;
  while (!(casesASeparer[i] == '-')) {
    milieu = i+1;
    i++;
  }
  char case1CDC[5]="";
  char case2CDC[5]="";

  for(int j=0;j<milieu;j++){
    case1CDC[j] = casesASeparer[j];
  }
  for(int p=milieu+1;p<strlen(casesASeparer)-1;p++){
    case2CDC[p-milieu-1] = casesASeparer[p];
  }

  *case1 = atoi(case1CDC); 
  *case2 = atoi(case2CDC);
}
