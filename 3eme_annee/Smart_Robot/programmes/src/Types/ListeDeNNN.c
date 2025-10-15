#include <stdbool.h> 
#include <stddef.h>  
#include <assert.h>
#include <errno.h>
#include <stdlib.h>
#include "../../include/Types/ListeChaineeDeNNN.h"
#include "../../include/Types/ListeDeNNN.h" 

LDNNN_ListeDeNNN LDNNN_liste(){
	LDNNN_ListeDeNNN liste;
	liste.lesElements = LCDNNN_listeVide();
	liste.nbElements = 0;
	return liste;
}


bool LDNNN_estVide(LDNNN_ListeDeNNN liste){
	return liste.nbElements == 0;
}


void LDNNN_inserer(LDNNN_ListeDeNNN *liste, unsigned int element, unsigned int position){

  if (position == 1) {
    LCDNNN_ListeChaineeDeNNN nouveauNoeud = (LCDNNN_ListeChaineeDeNNN)malloc(sizeof(LCDNNN_Noeud));
    nouveauNoeud->element = element;
    nouveauNoeud->listeSuivante = liste->lesElements;
    liste->lesElements = nouveauNoeud;
    liste->nbElements++;
    return;
  }
  else{
    LCDNNN_ListeChaineeDeNNN courant = liste->lesElements;
    for (unsigned int i = 1; i < position - 1; i++) {
      courant = courant->listeSuivante;
    }

    LCDNNN_ListeChaineeDeNNN nouveauNoeud = (LCDNNN_ListeChaineeDeNNN)malloc(sizeof(LCDNNN_Noeud));
    nouveauNoeud->element = element;
    nouveauNoeud->listeSuivante = courant->listeSuivante;

    courant->listeSuivante = nouveauNoeud;
    liste->nbElements++;
  }
}


void LDNNN_supprimer(LDNNN_ListeDeNNN *liste, unsigned int position){
  if (position == 1) {
    LCDNNN_ListeChaineeDeNNN aSupprimer = liste->lesElements;
    liste->lesElements = aSupprimer->listeSuivante;         
    free(aSupprimer);                                    
  } else {
    LCDNNN_ListeChaineeDeNNN courant = liste->lesElements;
    for (unsigned int i = 1; i < position - 1; i++) {
      courant = courant->listeSuivante;
    }

    LCDNNN_ListeChaineeDeNNN aSupprimer = courant->listeSuivante;
    courant->listeSuivante = aSupprimer->listeSuivante;          
    free(aSupprimer);                                         
  }
  liste->nbElements--;
}



unsigned int LDNNN_obtenirElement(LDNNN_ListeDeNNN liste, unsigned int position){
  LCDNNN_ListeChaineeDeNNN courant = liste.lesElements;
  for (unsigned int i = 1; i < position; i++) {
    courant = courant->listeSuivante;
  }
  return courant->element;
}

unsigned int LDNNN_longueur(LDNNN_ListeDeNNN liste){
	return liste.nbElements;
}
