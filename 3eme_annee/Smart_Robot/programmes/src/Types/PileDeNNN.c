#include <stdbool.h> 
#include <stddef.h>  
#include <assert.h>
#include <errno.h>
#include <stdlib.h>
#include "../../include/Types/PileDeNNN.h"
#include "../../include/Types/ListeChaineeDeNNN.h"        

PDNNN_PileDeNNN PDNNN_pile(){
  return LCDNNN_listeVide();
}

bool PDNNN_estVide(PDNNN_PileDeNNN pile){
  return LCDNNN_estVide(pile);
}


void PDNNN_empiler(PDNNN_PileDeNNN *pile, unsigned int element){
  LCDNNN_ajouter(pile,element);
}


void PDNNN_depiler(PDNNN_PileDeNNN *pile){
  assert(!PDNNN_estVide(*pile));
  LCDNNN_supprimerTete(pile);
}


unsigned int PDNNN_obtenirElement(PDNNN_PileDeNNN pile){
  assert(!PDNNN_estVide(pile));
  return LCDNNN_obtenirElement(pile);
}

unsigned int PDNNN_longueur(PDNNN_PileDeNNN pile){
  PDNNN_PileDeNNN temp = pile;
  unsigned int longueur = 0;
  while (!LCDNNN_estVide(temp)){
    longueur++;
    temp = LCDNNN_obtenirListeSuivante(temp);
  }
  return longueur;
}

bool PDNNN_estPresent(PDNNN_PileDeNNN pile, unsigned int e){
  bool presence = false;
  while ((!LCDNNN_estVide(pile)) && (!(presence == true))){
    if (LCDNNN_obtenirElement(pile) == e){
      presence = true;
    }
    pile = LCDNNN_obtenirListeSuivante(pile);
  }
  return presence;
}


PDNNN_PileDeNNN PDNNN_copier(PDNNN_PileDeNNN p) {
  return LCDNNN_copier(p);
}


bool PDNNN_egale(PDNNN_PileDeNNN p1, PDNNN_PileDeNNN p2) {
  PDNNN_PileDeNNN copie1 = PDNNN_copier(p1);
  PDNNN_PileDeNNN copie2 = PDNNN_copier(p2);
  bool sontEgales = true;

  while (sontEgales && (!PDNNN_estVide(copie1) && (!PDNNN_estVide(copie2)))) {
    if (PDNNN_obtenirElement(copie1) != PDNNN_obtenirElement(copie2)) {
      sontEgales = false;
    }
    PDNNN_depiler(&copie1);
    PDNNN_depiler(&copie2);
    if ((!PDNNN_estVide(copie1) && (PDNNN_estVide(copie2))) || (PDNNN_estVide(copie1) && (!PDNNN_estVide(copie2)))) {
      sontEgales = false;
    }
  }
  return sontEgales;
}
