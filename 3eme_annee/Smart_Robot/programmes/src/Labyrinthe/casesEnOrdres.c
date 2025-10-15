#include <errno.h>
#include <stdio.h>
#include <assert.h>
#include <stdbool.h>
#include "../../include/Types/Ordre.h"
#include "../../include/Types/Direction.h"
#include "../../include/Types/caseEtDirection.h"
#include "../../include/Types/labyrinthe.h"
#include "../../include/Types/PileDeNNN.h"
#include "../../include/Types/ListeDOrdre.h"
#include "../../include/Types/ListeDeCaseEtDirection.h"
#include "../../include/Types/EnsembleDeDirection.h"


void CEO_choixOrdre(LAB_Labyrinthe laby, Direction directionCasePrecedente, Direction directionCaseActuelle, unsigned int caseActuelle, LDO_ListeDOrdre *ordres) {
  Ordre o;
  EDD_EnsembleDeDirection directionsPossibles;
  Direction d;
  bool estIntersection = false;

  if (directionCasePrecedente == directionCaseActuelle) {
    directionsPossibles = LAB_directionsPossibles(laby, caseActuelle);
    while (!(EDD_cardinalite(directionsPossibles) == 0)) {
      d = EDD_obtenirPremierElement(directionsPossibles);
      EDD_retirer(&directionsPossibles, d);
      switch (directionCaseActuelle) {
      case H :
	if (!((d == H) || (d == B))) {
	  estIntersection = true;
	}
	break;
      case B :
	if (!((d == H) || (d == B))) {
	  estIntersection = true;
	}
	break;
      case G :
	if (!((d == G) || (d == D))) {
	  estIntersection = true;
	}
	break;
      case D :
	if (!((d == G) || (d == D))) {
	  estIntersection = true;
	}
	break;
      }
    }
    if (estIntersection) {
      LDO_inserer(ordres, AV, LDO_longueur(*ordres) + 1);
    }
  }
  else {
    switch (directionCasePrecedente) {
    case H :
      if  (directionCaseActuelle == G) {
	o = TG;
      }
      else {
	o = TD;
      }
      break;
    case B :
      if  (directionCaseActuelle == D) {
	o = TG;
      }
      else {
	o = TD;
      }
      break;
    case G :
      if  (directionCaseActuelle == B) {
	o = TG;
      }
      else {
	o = TD;
      }
      break;
    case D :
      if  (directionCaseActuelle == H) {
	o = TG;
      }
      else {
	o = TD;
      }
      break;
    }
    LDO_inserer(ordres, o, LDO_longueur(*ordres) + 1);
    LDO_inserer(ordres, AV, LDO_longueur(*ordres) + 1);
  }
}


Direction CEO_positionPorteEnDirection(Direction d) {
  Direction res;

  switch (d) {
  case H :
    res = B;
    break;
  case B :
    res = H;
    break;
  case G :
    res = D;
    break;
  case D:
    res = G;
    break;
  }
  return res;
}


LDCD_ListeDeCaseEtDirection CEO_conversionCasesEnCasesEtDirections(LAB_Labyrinthe laby, PDNNN_PileDeNNN p) {
  LDCD_ListeDeCaseEtDirection casesDirections = LDCD_liste();
  unsigned int caseActuelle, casePrecedente;
  Direction porteEntree, porteSortie;
  PDNNN_PileDeNNN copiePile = PDNNN_copier(p);

  caseActuelle = PDNNN_obtenirElement(copiePile);
  PDNNN_depiler(&copiePile);
  LAB_DirectionEntreeEtSortie(laby, &porteEntree, &porteSortie);
  LDCD_inserer(&casesDirections, CD_caseEtDirection(caseActuelle, porteSortie), 1);
  while (PDNNN_longueur(copiePile) >= 1) {
    casePrecedente = PDNNN_obtenirElement(copiePile);
    if (casePrecedente < caseActuelle) {
      if (casePrecedente + 1 == caseActuelle) {
	LDCD_inserer(&casesDirections, CD_caseEtDirection(casePrecedente, D), 1);
      }
      else {
	LDCD_inserer(&casesDirections, CD_caseEtDirection(casePrecedente, B), 1);
      }
    }
    else {
      if (casePrecedente - 1 == caseActuelle) {
	LDCD_inserer(&casesDirections, CD_caseEtDirection(casePrecedente, G), 1);
      }
      else {
	LDCD_inserer(&casesDirections, CD_caseEtDirection(casePrecedente, H), 1);
      }
    }
    PDNNN_depiler(&copiePile);
    
    caseActuelle = casePrecedente;
  }
  return casesDirections;
}


LDO_ListeDOrdre CEO_conversionCasesEtDirectionsEnOrdres(LDCD_ListeDeCaseEtDirection casesDirections, LAB_Labyrinthe laby) {
  LDO_ListeDOrdre ordres = LDO_liste();
  Direction directionCaseActuelle, directionCasePrecedente, porteEntree, porteSortie;
  unsigned int caseActuelle, iLecture;
  

  iLecture = 1;
  LDO_inserer(&ordres, AV, LDO_longueur(ordres)+1);
  LAB_DirectionEntreeEtSortie(laby, &porteEntree, &porteSortie);
  directionCasePrecedente = CEO_positionPorteEnDirection(porteEntree);
  while (iLecture <= LDCD_longueur(casesDirections)) {
    directionCaseActuelle = CD_obtenirDirection(LDCD_obtenirElement(casesDirections, iLecture));
    caseActuelle = CD_obtenirCase(LDCD_obtenirElement(casesDirections, iLecture));
    iLecture = iLecture + 1;
    CEO_choixOrdre(laby, directionCasePrecedente, directionCaseActuelle, caseActuelle, &ordres);
    directionCasePrecedente = directionCaseActuelle;
  }
  // LDO_inserer(&ordres, ., LDO_longueur(ordres)+1);
  return ordres;
}
