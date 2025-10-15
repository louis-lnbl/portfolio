#include <stdbool.h> 
#include <stddef.h>  
#include <assert.h>
#include <errno.h>
#include <stdlib.h>
#include "../../include/Types/ListeChaineeDeNNN.h"

 
LCDNNN_ListeChaineeDeNNN LCDNNN_listeVide(){
	errno=0;
	return NULL;
}


bool LCDNNN_estVide(LCDNNN_ListeChaineeDeNNN uneListe){
	errno=0;
	return uneListe == NULL;
}

void LCDNNN_ajouter(LCDNNN_ListeChaineeDeNNN *uneListe, unsigned int element){
	LCDNNN_ListeChaineeDeNNN pNoeud = (LCDNNN_ListeChaineeDeNNN)malloc(sizeof(LCDNNN_Noeud));
	if (pNoeud!=NULL){
	errno = 0;
	pNoeud -> element = element;
	pNoeud -> listeSuivante = *uneListe;
	*uneListe = pNoeud;
	}
	else{
	errno=LCDNNN_ERREUR_MEMOIRE;
	}
}


unsigned int LCDNNN_obtenirElement(LCDNNN_ListeChaineeDeNNN uneListe){ 
	assert(!LCDNNN_estVide(uneListe));
	errno=0;
	return uneListe->element;
}

void LCDNNN_fixerElement(LCDNNN_ListeChaineeDeNNN *uneListe, unsigned int element){
	assert(!LCDNNN_estVide(*uneListe));
	errno=0;
	(*uneListe)->element = element;
}

LCDNNN_ListeChaineeDeNNN LCDNNN_obtenirListeSuivante(LCDNNN_ListeChaineeDeNNN uneListe){ 
	assert(!LCDNNN_estVide(uneListe));
	errno=0;
	return uneListe->listeSuivante;
}

void LCDNNN_fixerListeSuivante(LCDNNN_ListeChaineeDeNNN *uneListe, LCDNNN_ListeChaineeDeNNN nelleSuite){ 
	assert(!LCDNNN_estVide(*uneListe));
	errno=0;
	(*uneListe)->listeSuivante = nelleSuite;
}

void LCDNNN_supprimerTete(LCDNNN_ListeChaineeDeNNN *uneListe){ 
	LCDNNN_ListeChaineeDeNNN temp;
	assert(!LCDNNN_estVide(*uneListe));
	errno=0;
	temp=*uneListe; 
	*uneListe = LCDNNN_obtenirListeSuivante(*uneListe);
	free(temp);
}

void LCDNNN_supprimer(LCDNNN_ListeChaineeDeNNN *uneListe){
	errno=0;
	if (!LCDNNN_estVide(*uneListe)){
		LCDNNN_supprimerTete(uneListe);
		LCDNNN_supprimer(uneListe);
	}
}

void LCDNNN_concatener(LCDNNN_ListeChaineeDeNNN *liste1, LCDNNN_ListeChaineeDeNNN liste2) {
  LCDNNN_ListeChaineeDeNNN temp;

  if (LCDNNN_estVide(*liste1)) {
    *liste1 = liste2;
  }
  else {
    if (!LCDNNN_estVide(liste2)) {
      temp = LCDNNN_obtenirListeSuivante(*liste1);
      LCDNNN_concatener(&temp, liste2);
      if (LCDNNN_estVide(LCDNNN_obtenirListeSuivante(*liste1))) {
	LCDNNN_fixerListeSuivante(liste1, temp);
      }
    }
  }
}



void LCDNNN_inverser(LCDNNN_ListeChaineeDeNNN *uneliste){
  LCDNNN_ListeChaineeDeNNN temp;

  if (!LCDNNN_estVide(*uneliste)) {
    temp = LCDNNN_obtenirListeSuivante(*uneliste);
    LCDNNN_inverser(&temp);
    LCDNNN_fixerListeSuivante(uneliste, LCDNNN_listeVide());
    LCDNNN_concatener(&temp, *uneliste);
    *uneliste = temp;
  }
}
    



LCDNNN_ListeChaineeDeNNN LCDNNN_copier(LCDNNN_ListeChaineeDeNNN uneliste){
  LCDNNN_ListeChaineeDeNNN copie= LCDNNN_listeVide();
  LCDNNN_ListeChaineeDeNNN temp = uneliste;
  
  while (!LCDNNN_estVide(temp)) {
    LCDNNN_ajouter(&copie, LCDNNN_obtenirElement(temp));
    temp = LCDNNN_obtenirListeSuivante(temp);
  }
  LCDNNN_inverser(&copie);

  return copie;
}
