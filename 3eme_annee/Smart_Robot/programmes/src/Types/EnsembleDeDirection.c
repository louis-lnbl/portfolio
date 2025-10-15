#include <stdbool.h>
#include <stdio.h>
#include <stddef.h>  
#include <assert.h>
#include <errno.h>
#include <stdlib.h>
#include "../../include/Types/EnsembleDeDirection.h"
#include "../../include/Types/Direction.h"
#include "../../include/Types/ListeChaineeDeDirection.h"

EDD_EnsembleDeDirection EDD_ensemble(void){
  EDD_EnsembleDeDirection ensemble;
  ensemble.lesElements = LCDD_listeVide();
  ensemble.nbElements = 0;
  return ensemble;
}


void EDD_ajouter(EDD_EnsembleDeDirection *unEnsemble, Direction direction){
  if (!EDD_estPresent(*unEnsemble,direction)){
    LCDD_ajouter(&unEnsemble->lesElements,direction);
    unEnsemble->nbElements = unEnsemble->nbElements +1;
  }
}


void EDD_retirer(EDD_EnsembleDeDirection *unEnsemble, Direction direction){
  LCDD_ListeChaineeDeDirection *noeudCourant = &(unEnsemble->lesElements);
  LCDD_ListeChaineeDeDirection precedent = NULL;
  bool directionRetiree = false;

  while (!LCDD_estVide(*noeudCourant) && !directionRetiree) {
    if (LCDD_obtenirElement(*noeudCourant) == direction) {
      if (precedent == NULL) { 
	LCDD_supprimerTete(noeudCourant);
      } else {
	LCDD_fixerListeSuivante(&precedent, LCDD_obtenirListeSuivante(*noeudCourant));
	free(*noeudCourant);
	*noeudCourant = NULL;
      }
      unEnsemble->nbElements = unEnsemble->nbElements - 1;
      directionRetiree = true;
    } else {
      precedent = *noeudCourant;
      noeudCourant = &(*noeudCourant)->listeSuivante;
    }
  }
}

bool EDD_estPresent(EDD_EnsembleDeDirection unEnsemble, Direction direction){
  LCDD_ListeChaineeDeDirection noeudCourant = unEnsemble.lesElements;
  bool estPresent = false;

  while (!LCDD_estVide(noeudCourant) && !estPresent) {
    if (LCDD_obtenirElement(noeudCourant) == direction) {
      estPresent = true;
    }
    noeudCourant = LCDD_obtenirListeSuivante(noeudCourant);
  }
  return estPresent;
}


unsigned int EDD_cardinalite(EDD_EnsembleDeDirection unEnsemble){
  return unEnsemble.nbElements;
}


EDD_EnsembleDeDirection EDD_unionEnsemble(EDD_EnsembleDeDirection e1, EDD_EnsembleDeDirection e2){
  EDD_EnsembleDeDirection unionEnsemble = EDD_ensemble();

  LCDD_ListeChaineeDeDirection noeudCourant = e1.lesElements;
  while (!LCDD_estVide(noeudCourant)) {
    EDD_ajouter(&unionEnsemble, LCDD_obtenirElement(noeudCourant));
    noeudCourant = LCDD_obtenirListeSuivante(noeudCourant);
  }

  noeudCourant = e2.lesElements;
  while (!LCDD_estVide(noeudCourant)) {
    EDD_ajouter(&unionEnsemble, LCDD_obtenirElement(noeudCourant));
    noeudCourant = LCDD_obtenirListeSuivante(noeudCourant);
  }

  return unionEnsemble;
}


EDD_EnsembleDeDirection EDD_intersection(EDD_EnsembleDeDirection e1, EDD_EnsembleDeDirection e2){
  EDD_EnsembleDeDirection intersectionEnsemble = EDD_ensemble();

  LCDD_ListeChaineeDeDirection noeudCourant = e1.lesElements;
  while (!LCDD_estVide(noeudCourant)) {
    Direction direction = LCDD_obtenirElement(noeudCourant);
    if (EDD_estPresent(e2, direction)) {
      EDD_ajouter(&intersectionEnsemble, direction);
    }
    noeudCourant = LCDD_obtenirListeSuivante(noeudCourant);
  }

  return intersectionEnsemble;
}


EDD_EnsembleDeDirection EDD_soustraction(EDD_EnsembleDeDirection e1, EDD_EnsembleDeDirection e2){
  EDD_EnsembleDeDirection soustractionEnsemble = EDD_ensemble();

  LCDD_ListeChaineeDeDirection noeudCourant = e1.lesElements;
  while (!LCDD_estVide(noeudCourant)) {
    Direction direction = LCDD_obtenirElement(noeudCourant);
    if (!EDD_estPresent(e2, direction)) {
      EDD_ajouter(&soustractionEnsemble, direction);
    }
    noeudCourant = LCDD_obtenirListeSuivante(noeudCourant);
  }

  return soustractionEnsemble;
}


Direction EDD_obtenirPremierElement(EDD_EnsembleDeDirection unEnsemble){
  Direction uneDirection;
  uneDirection = LCDD_obtenirElement(unEnsemble.lesElements);
  return uneDirection;
}

