#include <stdbool.h> 
#include <stddef.h>  
#include <assert.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include "../../include/Types/ListeChaineeDeCDC.h"

LCDCDC_ListeChaineeDeCDC LCDCDC_listeVide(){
	errno=0;
	return NULL;
}

bool LCDCDC_estVide(LCDCDC_ListeChaineeDeCDC uneListe){
	errno=0;
	return uneListe == NULL;
}

void LCDCDC_ajouter(LCDCDC_ListeChaineeDeCDC *uneListe, char *element){
	LCDCDC_ListeChaineeDeCDC pNoeud = (LCDCDC_ListeChaineeDeCDC)malloc(sizeof(LCDCDC_Noeud));
	if (pNoeud!=NULL){
		errno = 0;
		strcpy(pNoeud->element, element);
		pNoeud -> listeSuivante = *uneListe;
		*uneListe = pNoeud;
	}
	else{
		errno=LCDCDC_ERREUR_MEMOIRE;
	}
}


char *LCDCDC_obtenirElement(LCDCDC_ListeChaineeDeCDC uneListe){ /* assert : estVide(uneListe) */
	assert(!LCDCDC_estVide(uneListe));
	errno=0;
	return uneListe->element;
}

void LCDCDC_fixerElement(LCDCDC_ListeChaineeDeCDC *uneListe, char *element){ /* assert : estVide(uneListe) */
	assert(!LCDCDC_estVide(*uneListe));
	errno=0;
	strcpy((*uneListe)->element, element);
}


LCDCDC_ListeChaineeDeCDC LCDCDC_obtenirListeSuivante(LCDCDC_ListeChaineeDeCDC uneListe){ 
	assert(!LCDCDC_estVide(uneListe));
	errno=0;
	return uneListe->listeSuivante;
}


void LCDCDC_fixerListeSuivante(LCDCDC_ListeChaineeDeCDC *uneListe, LCDCDC_ListeChaineeDeCDC nelleSuite){
	assert(!LCDCDC_estVide(*uneListe));
	errno=0;
	(*uneListe)->listeSuivante = nelleSuite;
}

void LCDCDC_supprimerTete(LCDCDC_ListeChaineeDeCDC *uneListe){ /* assert : estVide(uneListe) */
	LCDCDC_ListeChaineeDeCDC temp;
	assert(!LCDCDC_estVide(*uneListe));
	errno=0;
	temp=*uneListe; 
	*uneListe = LCDCDC_obtenirListeSuivante(*uneListe);
	free(temp);
}

void LCDCDC_supprimer(LCDCDC_ListeChaineeDeCDC *uneListe){
	errno=0;
	if (!LCDCDC_estVide(*uneListe)){
		LCDCDC_supprimerTete(uneListe);
		LCDCDC_supprimer(uneListe);
	}
}
