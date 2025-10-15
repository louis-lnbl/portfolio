#include <errno.h>
#include <assert.h>
#include <stdio.h>
#include <stdbool.h>
#include "../../include/Labyrinthe/gestionFichier.h"
#include "../../include/Labyrinthe/initialisationLabyrinthe.h"
#include "../../include/Labyrinthe/traitementLabyrinthe.h"
#include "../../include/Types/caseEtDirection.h"
#include "../../include/Types/ListeDOrdre.h"
#include "../../include/Types/Direction.h"
#include "../../include/Types/ListeDeCDC.h"
#include "../../include/Types/labyrinthe.h"
#include "../../include/Labyrinthe/trouverLesOrdres.h"
#include "../../include/Labyrinthe/trouverChemin.h"
#include "../../include/Types/PileDeNNN.h"
#include "../../include/Labyrinthe/casesEnOrdres.h"
#include "../../include/Labyrinthe/traitementLabyrinthe.h"




void afficherListeOrdre(LDO_ListeDOrdre o){
  printf("La liste est \n");
  unsigned int i = 1;
  while (i<= LDO_longueur(o)) {
    switch (LDO_obtenirElement(o, i)) {
    case AV : printf("AV\n");
      break;
    case TG : printf("TG\n");
      break;
    case TD : printf("TD\n");
      break;
    }
    i++;
  }
  printf(".\n");
}


int main(int argc, char** argv){
  char *nomFichier = argv[1];
  unsigned int largeur, caseEntree, caseSortie;
  Direction directionPorteEntree, directionPorteSortie;
  LDCDC_ListeDeCDC listeLiaisons = LDCDC_liste();
  LAB_Labyrinthe laby;
  LDO_ListeDOrdre ordres;
  
  GF_gestionDuFichier(nomFichier, &largeur, &caseEntree, &caseSortie, &directionPorteEntree, &directionPorteSortie, &listeLiaisons);
  laby = IL_creerLabyrinthe(largeur, caseEntree, caseSortie, directionPorteEntree, directionPorteSortie, listeLiaisons);
  ordres = TL_resolution(laby);
  afficherListeOrdre(ordres);

  /* Partie Robot */
  
  return 0;
}
