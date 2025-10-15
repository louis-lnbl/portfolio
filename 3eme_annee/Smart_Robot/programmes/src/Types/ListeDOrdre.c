#include <stdbool.h> 
#include <stddef.h>  
#include <assert.h>
#include <errno.h>
#include <stdlib.h>
#include "../../include/Types/ListeChaineeDOrdre.h"
#include "../../include/Types/ListeDOrdre.h" 

LDO_ListeDOrdre LDO_liste() {
  LDO_ListeDOrdre liste;
  liste.lesElements = LCDO_listeVide();
  liste.nbElements = 0;
  return liste;
}

bool LDO_estVide(LDO_ListeDOrdre liste) {
  return liste.nbElements == 0;
}


void LDO_inserer(LDO_ListeDOrdre *liste, Ordre element, unsigned int position) {

  if (position == 1) {
    LCDO_ajouter(&(liste->lesElements), element);
    liste->nbElements++;
  }
  else {
    LCDO_ListeChaineeDOrdre courant = liste->lesElements;
    for (unsigned int i = 1; i < position - 1; i++) {
      courant = courant->listeSuivante;
    }

    LCDO_Noeud *nouveauNoeud = (LCDO_Noeud*)malloc(sizeof(LCDO_Noeud));
    nouveauNoeud->element = element;
    nouveauNoeud->listeSuivante = courant->listeSuivante;
    courant->listeSuivante = nouveauNoeud;

    liste->nbElements++;
  }
}


void LDO_supprimer(LDO_ListeDOrdre *liste, unsigned int position) {


  if (position == 1) {
    LCDO_supprimerTete(&(liste->lesElements));
  }
  else {
    LCDO_ListeChaineeDOrdre courant = liste->lesElements;
    for (unsigned int i = 1; i < position - 1; i++) {
      courant = courant->listeSuivante;
    }

    LCDO_Noeud *aSupprimer = courant->listeSuivante;
    courant->listeSuivante = aSupprimer->listeSuivante;
    free(aSupprimer);

    liste->nbElements--;
  }
}


Ordre LDO_obtenirElement(LDO_ListeDOrdre liste, unsigned int position) {
  LCDO_ListeChaineeDOrdre courant = liste.lesElements;
  for (unsigned int i = 1; i < position; i++) {
    courant = courant->listeSuivante;
  }
  return courant->element;
}

unsigned int LDO_longueur(LDO_ListeDOrdre liste) {
  return liste.nbElements;
}
