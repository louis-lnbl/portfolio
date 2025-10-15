#include <stdbool.h> 
#include <stddef.h>  
#include <assert.h>
#include <errno.h>
#include <stdlib.h>
#include "../../include/Types/ListeChaineeDeNNN.h"
#include "../../include/Types/EnsembleDeNNN.h"

EDNNN_EnsembleDeNNN EDNNN_ensemble(){
	EDNNN_EnsembleDeNNN ensemble;
	ensemble.lesElements = LCDNNN_listeVide();
	ensemble.nbElements = 0;
	return ensemble;
}

void EDNNN_ajouter(EDNNN_EnsembleDeNNN *unEnsemble, unsigned int element){
	if (!EDNNN_estPresent(*unEnsemble, element)){
        	LCDNNN_ajouter(&unEnsemble->lesElements, element);
        	unEnsemble->nbElements++;
   	}
}

void EDNNN_retirer(EDNNN_EnsembleDeNNN *unEnsemble, unsigned int element){
	LCDNNN_ListeChaineeDeNNN *noeudCourant = &(unEnsemble->lesElements);
 	LCDNNN_ListeChaineeDeNNN precedent = NULL;
    	bool elementRetire = false;

    	while (!LCDNNN_estVide(*noeudCourant) && !elementRetire) {
        	if (LCDNNN_obtenirElement(*noeudCourant) == element) {
         		if (precedent == NULL) { 
                		LCDNNN_supprimerTete(noeudCourant);
            		} 
            		else {
                		LCDNNN_fixerListeSuivante(&precedent, LCDNNN_obtenirListeSuivante(*noeudCourant));
		                free(*noeudCourant);
		                *noeudCourant = NULL; 
            		}
            		unEnsemble->nbElements--;
            		elementRetire = true;
       			} 
       		else {
        		precedent = *noeudCourant;
         		noeudCourant = &(*noeudCourant)->listeSuivante;
        	}
    	}
}


bool EDNNN_estPresent(EDNNN_EnsembleDeNNN unEnsemble, unsigned int element){
	LCDNNN_ListeChaineeDeNNN noeudCourant = unEnsemble.lesElements;
   	 bool estPresent = false;

    	while (!LCDNNN_estVide(noeudCourant) && !estPresent) {
        	if (LCDNNN_obtenirElement(noeudCourant) == element) {
       	        	estPresent = true;
        }
        noeudCourant = LCDNNN_obtenirListeSuivante(noeudCourant);
   	}

    return estPresent;
}

unsigned int EDNNN_cardinalite(EDNNN_EnsembleDeNNN unEnsemble){

	return unEnsemble.nbElements;
}


EDNNN_EnsembleDeNNN EDNNN_unionEnsemble(EDNNN_EnsembleDeNNN e1, EDNNN_EnsembleDeNNN e2){
	EDNNN_EnsembleDeNNN unionEnsemble = EDNNN_ensemble();

    	LCDNNN_ListeChaineeDeNNN noeudCourant = e1.lesElements;
    	while (!LCDNNN_estVide(noeudCourant)) {
        	EDNNN_ajouter(&unionEnsemble, LCDNNN_obtenirElement(noeudCourant));
        	noeudCourant = LCDNNN_obtenirListeSuivante(noeudCourant);
    	}

    	noeudCourant = e2.lesElements;
    	while (!LCDNNN_estVide(noeudCourant)){
        	EDNNN_ajouter(&unionEnsemble, LCDNNN_obtenirElement(noeudCourant));
        	noeudCourant = LCDNNN_obtenirListeSuivante(noeudCourant);
    }

    return unionEnsemble;
}


EDNNN_EnsembleDeNNN EDNNN_intersection(EDNNN_EnsembleDeNNN e1, EDNNN_EnsembleDeNNN e2){
	EDNNN_EnsembleDeNNN intersectionEnsemble = EDNNN_ensemble();

 	LCDNNN_ListeChaineeDeNNN noeudCourant = e1.lesElements;
    	while (!LCDNNN_estVide(noeudCourant)) {
        	unsigned int element = LCDNNN_obtenirElement(noeudCourant);
        	if (EDNNN_estPresent(e2, element)) {
            		EDNNN_ajouter(&intersectionEnsemble, element);
     		}
        	noeudCourant = LCDNNN_obtenirListeSuivante(noeudCourant);
    	}

    	return intersectionEnsemble;
}


EDNNN_EnsembleDeNNN EDNNN_soustraction(EDNNN_EnsembleDeNNN e1, EDNNN_EnsembleDeNNN e2){
	EDNNN_EnsembleDeNNN soustractionEnsemble = EDNNN_ensemble();

    	LCDNNN_ListeChaineeDeNNN noeudCourant = e1.lesElements;
    	while (!LCDNNN_estVide(noeudCourant)) {
       		unsigned int element = LCDNNN_obtenirElement(noeudCourant);
        		if (!EDNNN_estPresent(e2, element)) {
            			EDNNN_ajouter(&soustractionEnsemble, element);
        		}
        		noeudCourant = LCDNNN_obtenirListeSuivante(noeudCourant);
   	}

    return soustractionEnsemble;
}


unsigned int EDNNN_obtenirPremierElement(EDNNN_EnsembleDeNNN unEnsemble){
  unsigned int uneValeur;
  uneValeur = LCDNNN_obtenirElement(unEnsemble.lesElements);
  return uneValeur;
}
