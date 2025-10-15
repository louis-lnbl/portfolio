#include <stdbool.h>
#include <stddef.h>
#include <assert.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include "../../include/Types/ListeDeCDC.h"
#include "../../include/Types/ListeChaineeDeCDC.h" 


LDCDC_ListeDeCDC LDCDC_liste(){
  LDCDC_ListeDeCDC liste;
  liste.lesElements = LCDCDC_listeVide();
  liste.nbElements = 0;
  return liste;
}


bool LDCDC_estVide(LDCDC_ListeDeCDC liste){
  return liste.nbElements == 0;
}


void LDCDC_inserer(LDCDC_ListeDeCDC *liste, char *element, unsigned int position){
    
  if (position == 1) {
    LCDCDC_ajouter(&liste->lesElements, element);
  }
  else {
    LCDCDC_ListeChaineeDeCDC courant = liste->lesElements;
    for (unsigned int i = 1; i < position - 1; i++) {
      courant = courant->listeSuivante;
    }
    LCDCDC_ListeChaineeDeCDC nouveauNoeud = (LCDCDC_ListeChaineeDeCDC)malloc(sizeof(LCDCDC_Noeud)); 
    strcpy(nouveauNoeud->element, element);
    nouveauNoeud->listeSuivante = courant->listeSuivante;
    courant->listeSuivante = nouveauNoeud;
  }
  liste->nbElements++;
}


void LDCDC_supprimer(LDCDC_ListeDeCDC *liste, unsigned int position){
  if (position == 1) {
    LCDCDC_supprimerTete(&liste->lesElements);
  }
  else {
    LCDCDC_ListeChaineeDeCDC courant = liste->lesElements;
    for (unsigned int i = 1; i < position - 1; i++) {
      courant = courant->listeSuivante;
    }
    LCDCDC_ListeChaineeDeCDC aSupprimer = courant->listeSuivante;
    courant->listeSuivante = aSupprimer->listeSuivante;
    free(aSupprimer);
  }
  liste->nbElements--;
}


char* LDCDC_obtenirElement(LDCDC_ListeDeCDC liste, unsigned int position){
  LCDCDC_ListeChaineeDeCDC courant = liste.lesElements;
  for (unsigned int i = 1; i < position; i++) {
    courant = courant->listeSuivante;
  }
  return courant->element;
}


unsigned int LDCDC_longueur(LDCDC_ListeDeCDC liste){
  return liste.nbElements;
}
