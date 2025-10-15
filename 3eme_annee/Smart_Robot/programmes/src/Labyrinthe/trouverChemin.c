#include <stdio.h>
#include <errno.h>
#include <assert.h>
#include <stdbool.h>
#include "../../include/Types/labyrinthe.h"
#include "../../include/Types/PileDeNNN.h"
#include "../../include/Types/EnsembleDePileDeNNN.h"
#include "../../include/Types/caseEtDirection.h"
#include "../../include/Types/EnsembleDeNNN.h"


void TC_trouverLesChemins(LAB_Labyrinthe laby, PDNNN_PileDeNNN *cheminCourant, EDPDNNN_EnsembleDePileDeNNN *cheminsPossibles){
  unsigned int uneCase;
  EDNNN_EnsembleDeNNN lesCasesAccessibles;

  if (!(PDNNN_estVide(*cheminCourant))){
    if (PDNNN_obtenirElement(*cheminCourant) == CD_obtenirCase(LAB_caseDeSortie(laby))){
      EDPDNNN_ajouter(cheminsPossibles, PDNNN_copier(*cheminCourant));
    }
    else{
      lesCasesAccessibles = LAB_casesAccessibles(laby,PDNNN_obtenirElement(*cheminCourant));
      while (!(EDNNN_cardinalite(lesCasesAccessibles) == 0)){
	uneCase = EDNNN_obtenirPremierElement(lesCasesAccessibles);
	EDNNN_retirer(&lesCasesAccessibles,uneCase);
	if (!(PDNNN_estPresent(*cheminCourant,uneCase))){
	  PDNNN_empiler(cheminCourant,uneCase);
	  TC_trouverLesChemins(laby,cheminCourant,cheminsPossibles);
	}
      }
    }
    PDNNN_depiler(cheminCourant);
  }
}



PDNNN_PileDeNNN TC_comparaisonChemins(EDPDNNN_EnsembleDePileDeNNN cheminsPossibles){
  PDNNN_PileDeNNN pileCourante;
  PDNNN_PileDeNNN plusPetitePile;
  unsigned int longueurCourante;
  unsigned int plusPetiteLongueur;
  EDPDNNN_EnsembleDePileDeNNN lesCheminsPossibles = cheminsPossibles;
  plusPetitePile = EDPDNNN_obtenirPremierElement(lesCheminsPossibles);
  EDPDNNN_retirer(&lesCheminsPossibles,plusPetitePile);
  plusPetiteLongueur = PDNNN_longueur(plusPetitePile);
  while (!(EDPDNNN_cardinalite(lesCheminsPossibles) == 0)){
    pileCourante = EDPDNNN_obtenirPremierElement(lesCheminsPossibles);
    EDPDNNN_retirer(&lesCheminsPossibles,pileCourante);
    longueurCourante = PDNNN_longueur(pileCourante);
    if (longueurCourante < plusPetiteLongueur){
      plusPetitePile = pileCourante;
      plusPetiteLongueur = longueurCourante;
    }
  }
  return plusPetitePile;
}


PDNNN_PileDeNNN TC_trouverPlusCourtChemin(LAB_Labyrinthe laby){
  unsigned int premiereCase = CD_obtenirCase(LAB_caseDEntree(laby));
  EDPDNNN_EnsembleDePileDeNNN cheminsPossibles = EDPDNNN_ensemble();;
  PDNNN_PileDeNNN cheminLePlusCourt = PDNNN_pile();

  PDNNN_PileDeNNN cheminCourant = PDNNN_pile();
  PDNNN_empiler(&cheminCourant,premiereCase);
  TC_trouverLesChemins(laby,&cheminCourant,&cheminsPossibles);
  cheminLePlusCourt = TC_comparaisonChemins(cheminsPossibles);
  return cheminLePlusCourt;
}
