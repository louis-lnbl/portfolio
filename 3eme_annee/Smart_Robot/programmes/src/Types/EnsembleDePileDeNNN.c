#include <stdbool.h> 
#include <stddef.h>  
#include <assert.h>
#include <errno.h>
#include <stdlib.h>
#include "../../include/Types/EnsembleDePileDeNNN.h"
#include "../../include/Types/ListeChaineeDePileDeNNN.h"


EDPDNNN_EnsembleDePileDeNNN EDPDNNN_ensemble(){
	EDPDNNN_EnsembleDePileDeNNN ensemble;
	ensemble.lesElements = LCDPDNNN_listeVide();
	ensemble.nbElements = 0;
	return ensemble;
}


void EDPDNNN_ajouter(EDPDNNN_EnsembleDePileDeNNN *unEnsemble, PDNNN_PileDeNNN element){
	if (!EDPDNNN_estPresent(*unEnsemble, element)) {
	  LCDPDNNN_ajouter(&(unEnsemble->lesElements), element);
        unEnsemble->nbElements++;
    }
}


void EDPDNNN_retirer(EDPDNNN_EnsembleDePileDeNNN *unEnsemble, PDNNN_PileDeNNN element){
	LCDPDNNN_ListeChaineeDePileDeNNN *noeudCourant = &(unEnsemble->lesElements);
    	LCDPDNNN_ListeChaineeDePileDeNNN precedent = NULL;
    	bool elementRetire = false;

    	while (!LCDPDNNN_estVide(*noeudCourant) && !elementRetire) {
    		if (LCDPDNNN_obtenirElement(*noeudCourant) == element){
            		if (precedent == NULL) {
                		LCDPDNNN_supprimerTete(noeudCourant);
            		} else {
                		LCDPDNNN_fixerListeSuivante(&precedent, LCDPDNNN_obtenirListeSuivante(*noeudCourant));
                		free(*noeudCourant);
                		*noeudCourant = NULL;
            		}
            		unEnsemble->nbElements--;
            		elementRetire = true;
        		} else {
        	    	precedent = *noeudCourant;
            		noeudCourant = &(*noeudCourant)->listeSuivante;
        		}
    		}
}


bool EDPDNNN_estPresent(EDPDNNN_EnsembleDePileDeNNN unEnsemble, PDNNN_PileDeNNN element){
  EDPDNNN_EnsembleDePileDeNNN copie = EDPDNNN_copier(unEnsemble);
  bool estPresent = false;
  PDNNN_PileDeNNN temp;

  while ((!estPresent) && (!(EDPDNNN_cardinalite(copie) == 0))) {
    temp = EDPDNNN_obtenirPremierElement(copie);
    EDPDNNN_retirer(&copie, temp);
    if (PDNNN_egale(temp, element)) {
      estPresent = true;
    }
  }
  return estPresent;
}


unsigned int EDPDNNN_cardinalite(EDPDNNN_EnsembleDePileDeNNN unEnsemble){
    return unEnsemble.nbElements;
}


EDPDNNN_EnsembleDePileDeNNN EDPDNNN_unionEnsemble(EDPDNNN_EnsembleDePileDeNNN e1, EDPDNNN_EnsembleDePileDeNNN e2){
	EDPDNNN_EnsembleDePileDeNNN unionEnsemble = EDPDNNN_ensemble();

   	LCDPDNNN_ListeChaineeDePileDeNNN noeudCourant = e1.lesElements;
    	while (!LCDPDNNN_estVide(noeudCourant)) {
       		EDPDNNN_ajouter(&unionEnsemble, LCDPDNNN_obtenirElement(noeudCourant));
        	noeudCourant = LCDPDNNN_obtenirListeSuivante(noeudCourant);
    	}

    	noeudCourant = e2.lesElements;
    	while (!LCDPDNNN_estVide(noeudCourant)) {
        	EDPDNNN_ajouter(&unionEnsemble, LCDPDNNN_obtenirElement(noeudCourant));
        	noeudCourant = LCDPDNNN_obtenirListeSuivante(noeudCourant);
    	}

    	return unionEnsemble;
}


EDPDNNN_EnsembleDePileDeNNN EDPDNNN_intersection(EDPDNNN_EnsembleDePileDeNNN e1, EDPDNNN_EnsembleDePileDeNNN e2){
	EDPDNNN_EnsembleDePileDeNNN intersectionEnsemble = EDPDNNN_ensemble();

    	LCDPDNNN_ListeChaineeDePileDeNNN noeudCourant = e1.lesElements;
    	while (!LCDPDNNN_estVide(noeudCourant)) {
        	PDNNN_PileDeNNN element = LCDPDNNN_obtenirElement(noeudCourant);
        	if (EDPDNNN_estPresent(e2, element)) {
            		EDPDNNN_ajouter(&intersectionEnsemble, element);
        	}
        	noeudCourant = LCDPDNNN_obtenirListeSuivante(noeudCourant);
    	}

	return intersectionEnsemble;
}


EDPDNNN_EnsembleDePileDeNNN EDPDNNN_soustraction(EDPDNNN_EnsembleDePileDeNNN e1, EDPDNNN_EnsembleDePileDeNNN e2){
	EDPDNNN_EnsembleDePileDeNNN soustractionEnsemble = EDPDNNN_ensemble();

   	LCDPDNNN_ListeChaineeDePileDeNNN noeudCourant = e1.lesElements;
    	while (!LCDPDNNN_estVide(noeudCourant)) {
        	PDNNN_PileDeNNN element = LCDPDNNN_obtenirElement(noeudCourant);
        	if (!EDPDNNN_estPresent(e2, element)) {
            		EDPDNNN_ajouter(&soustractionEnsemble, element);
       		}
        	noeudCourant = LCDPDNNN_obtenirListeSuivante(noeudCourant);
    	}

    	return soustractionEnsemble;
}


PDNNN_PileDeNNN EDPDNNN_obtenirPremierElement(EDPDNNN_EnsembleDePileDeNNN unEnsemble){
  PDNNN_PileDeNNN unePile;
  unePile = LCDPDNNN_obtenirElement(unEnsemble.lesElements);
  return unePile;
}


EDPDNNN_EnsembleDePileDeNNN EDPDNNN_copier(EDPDNNN_EnsembleDePileDeNNN unEnsemble) {
  EDPDNNN_EnsembleDePileDeNNN copie = EDPDNNN_ensemble();
  LCDPDNNN_ListeChaineeDePileDeNNN temp;
  unsigned int i = 0;

  copie.lesElements = LCDPDNNN_copier(unEnsemble.lesElements);
  temp = copie.lesElements;
  while (!LCDPDNNN_estVide(temp)) {
    i++;
    temp = LCDPDNNN_obtenirListeSuivante(temp);
  }
  copie.nbElements = i;
  return copie;
}
