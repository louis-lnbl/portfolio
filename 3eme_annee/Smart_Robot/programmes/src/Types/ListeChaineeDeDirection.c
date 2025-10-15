#include <stdbool.h>
#include <stdio.h>
#include <stddef.h>  
#include <assert.h>
#include <errno.h>
#include <stdlib.h>
#include "../../include/Types/ListeChaineeDeDirection.h"
#include "../../include/Types/Direction.h"


LCDD_ListeChaineeDeDirection LCDD_listeVide(){
	errno=0;
	return NULL;
}



bool LCDD_estVide(LCDD_ListeChaineeDeDirection uneListe){
	errno=0;
	return uneListe == NULL;
}


void LCDD_ajouter(LCDD_ListeChaineeDeDirection *uneListe, Direction element){
		LCDD_ListeChaineeDeDirection pNoeud = (LCDD_ListeChaineeDeDirection)malloc(sizeof(LCDD_Noeud));
	if (pNoeud!=NULL){
	errno = 0;
	pNoeud -> element = element;
	pNoeud -> listeSuivante = *uneListe;
	*uneListe = pNoeud;
	}
	else{
	errno=LCDD_ERREUR_MEMOIRE;
	}
}


Direction LCDD_obtenirElement(LCDD_ListeChaineeDeDirection uneListe){
  Direction d;
	assert(!LCDD_estVide(uneListe));
	errno=0;
	d = uneListe->element;
	return d;
}


void LCDD_fixerElement(LCDD_ListeChaineeDeDirection *uneListe, Direction element){
	assert(!LCDD_estVide(*uneListe));
	errno=0;
	(*uneListe)->element = element;
}

LCDD_ListeChaineeDeDirection LCDD_obtenirListeSuivante(LCDD_ListeChaineeDeDirection uneListe){ 
	assert(!LCDD_estVide(uneListe));
	errno=0;
	return uneListe->listeSuivante;
}

void LCDD_fixerListeSuivante(LCDD_ListeChaineeDeDirection *uneListe, LCDD_ListeChaineeDeDirection nelleSuite){ 
	assert(!LCDD_estVide(*uneListe));
	errno=0;
	(*uneListe)->listeSuivante = nelleSuite;
}

void LCDD_supprimerTete(LCDD_ListeChaineeDeDirection *uneListe){
	LCDD_ListeChaineeDeDirection temp;
	assert(!LCDD_estVide(*uneListe));
	errno=0;
	temp=*uneListe; 
	*uneListe = LCDD_obtenirListeSuivante(*uneListe);
	free(temp);
}

void LCDD_supprimer(LCDD_ListeChaineeDeDirection *uneListe){
	errno=0;
	if (!LCDD_estVide(*uneListe)){
		LCDD_supprimerTete(uneListe);
		LCDD_supprimer(uneListe);
	}
}

