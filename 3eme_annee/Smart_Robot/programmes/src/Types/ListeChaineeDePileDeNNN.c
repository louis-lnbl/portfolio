#include <stdbool.h> 
#include <stddef.h>  
#include <assert.h>
#include <errno.h>
#include <stdlib.h>
#include "../../include/Types/PileDeNNN.h"
#include "../../include/Types/ListeChaineeDePileDeNNN.h"


LCDPDNNN_ListeChaineeDePileDeNNN LCDPDNNN_listeVide(){
	errno=0;
	return NULL;
}


bool LCDPDNNN_estVide(LCDPDNNN_ListeChaineeDePileDeNNN uneListe){
	errno=0;
	return uneListe == NULL;
}


void LCDPDNNN_ajouter(LCDPDNNN_ListeChaineeDePileDeNNN *uneListe, PDNNN_PileDeNNN element){
	LCDPDNNN_ListeChaineeDePileDeNNN pNoeud = (LCDPDNNN_ListeChaineeDePileDeNNN)malloc(sizeof(LCDPDNNN_Noeud));
	if (pNoeud!=NULL){
	errno = 0;
	pNoeud -> element = element;
	pNoeud -> listeSuivante = *uneListe;
	*uneListe = pNoeud;
	}
	else{
	errno= LCDPDNNN_ERREUR_MEMOIRE;
	}
}


PDNNN_PileDeNNN LCDPDNNN_obtenirElement(LCDPDNNN_ListeChaineeDePileDeNNN uneListe){ 
	assert(!LCDPDNNN_estVide(uneListe));
	errno=0;
	return uneListe->element;
}

void LCDPDNNN_fixerElement(LCDPDNNN_ListeChaineeDePileDeNNN *uneListe, PDNNN_PileDeNNN element){ 
	assert(!LCDPDNNN_estVide(*uneListe));
	errno=0;
	(*uneListe)->element = element;
}

LCDPDNNN_ListeChaineeDePileDeNNN LCDPDNNN_obtenirListeSuivante(LCDPDNNN_ListeChaineeDePileDeNNN uneListe){ 
	assert(!LCDPDNNN_estVide(uneListe));
	errno=0;
	return uneListe->listeSuivante;
}

void LCDPDNNN_fixerListeSuivante(LCDPDNNN_ListeChaineeDePileDeNNN *uneListe, LCDPDNNN_ListeChaineeDePileDeNNN nelleSuite){ /* assert : estVide(uneListe) */
	assert(!LCDPDNNN_estVide(*uneListe));
	errno=0;
	(*uneListe)->listeSuivante = nelleSuite;
}

void LCDPDNNN_supprimerTete(LCDPDNNN_ListeChaineeDePileDeNNN *uneListe){ /* assert : estVide(uneListe) */
	LCDPDNNN_ListeChaineeDePileDeNNN temp;
	assert(!LCDPDNNN_estVide(*uneListe));
	errno=0;
	temp=*uneListe; 
	*uneListe = LCDPDNNN_obtenirListeSuivante(*uneListe);
	free(temp);
}


void LCDPDNNN_supprimer(LCDPDNNN_ListeChaineeDePileDeNNN *uneListe){
	errno=0;
	if (!LCDPDNNN_estVide(*uneListe)){
		LCDPDNNN_supprimerTete(uneListe);
		LCDPDNNN_supprimer(uneListe);
	}
}


void LCDPDNNN_concatener(LCDPDNNN_ListeChaineeDePileDeNNN *liste1, LCDPDNNN_ListeChaineeDePileDeNNN liste2) {
  LCDPDNNN_ListeChaineeDePileDeNNN temp;

  if (LCDPDNNN_estVide(*liste1)) {
    *liste1 = liste2;
  }
  else {
    if (!LCDPDNNN_estVide(liste2)) {
      temp = LCDPDNNN_obtenirListeSuivante(*liste1);
      LCDPDNNN_concatener(&temp, liste2);
      if (LCDPDNNN_estVide(LCDPDNNN_obtenirListeSuivante(*liste1))) {
	LCDPDNNN_fixerListeSuivante(liste1, temp);
      }
    }
  }
}



void LCDPDNNN_inverser(LCDPDNNN_ListeChaineeDePileDeNNN *uneliste){
  LCDPDNNN_ListeChaineeDePileDeNNN temp;

  if (!LCDPDNNN_estVide(*uneliste)) {
    temp = LCDPDNNN_obtenirListeSuivante(*uneliste);
    LCDPDNNN_inverser(&temp);
    LCDPDNNN_fixerListeSuivante(uneliste, LCDPDNNN_listeVide());
    LCDPDNNN_concatener(&temp, *uneliste);
    *uneliste = temp;
  }
}
    



LCDPDNNN_ListeChaineeDePileDeNNN LCDPDNNN_copier(LCDPDNNN_ListeChaineeDePileDeNNN uneliste){
  LCDPDNNN_ListeChaineeDePileDeNNN copie= LCDPDNNN_listeVide();
  LCDPDNNN_ListeChaineeDePileDeNNN temp = uneliste;
  
  while (!LCDPDNNN_estVide(temp)) {
    LCDPDNNN_ajouter(&copie, LCDPDNNN_obtenirElement(temp));
    temp = LCDPDNNN_obtenirListeSuivante(temp);
  }
  LCDPDNNN_inverser(&copie);

  return copie;
}
