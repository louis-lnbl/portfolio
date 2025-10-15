#include <errno.h>
#include <assert.h>
#include <stdio.h>
#include <stdbool.h>
#include "../../include/Labyrinthe/gestionFichier.h"
#include "../../include/Labyrinthe/initialisationLabyrinthe.h"
#include "../../include/Labyrinthe/traitementLabyrinthe.h"
#include "../../include/Types/ListeDOrdre.h"
#include "../../include/Types/Direction.h"
#include "../../include/Types/ListeDeCDC.h"
#include "../../include/Types/labyrinthe.h"
#include "../../include/Labyrinthe/trouverLesOrdres.h"

LDO_ListeDOrdre TLO_trouverOrdres(char* nomFichier){
  unsigned int largeur, caseEntree, caseSortie;
  Direction directionPorteEntree, directionPorteSortie;
  LDCDC_ListeDeCDC listeLiaisons = LDCDC_liste();
  LAB_Labyrinthe laby;
  LDO_ListeDOrdre ordres;
    
  GF_gestionDuFichier(nomFichier, &largeur, &caseEntree, &caseSortie, &directionPorteEntree, &directionPorteSortie, &listeLiaisons);
  laby = IL_creerLabyrinthe(largeur, caseEntree, caseSortie, directionPorteEntree, directionPorteSortie, listeLiaisons);
  ordres = TL_resolution(laby);
  return ordres;
}
