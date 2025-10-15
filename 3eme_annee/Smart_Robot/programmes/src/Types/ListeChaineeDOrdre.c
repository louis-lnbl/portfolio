#include <stdbool.h> 
#include <stddef.h>  
#include <assert.h>
#include <errno.h>
#include <stdlib.h>
#include "../../include/Types/Ordre.h"
#include "../../include/Types/ListeChaineeDOrdre.h"


LCDO_ListeChaineeDOrdre LCDO_listeVide(){
	errno=0;
	return NULL;
}


bool LCDO_estVide(LCDO_ListeChaineeDOrdre uneListe){
	errno=0;
	return uneListe == NULL;
}

void LCDO_ajouter(LCDO_ListeChaineeDOrdre *uneListe, Ordre element){
	LCDO_ListeChaineeDOrdre pNoeud = (LCDO_ListeChaineeDOrdre )malloc(sizeof(LCDO_Noeud));
	if (pNoeud!=NULL){
	errno = 0;
	pNoeud -> element = element;
	pNoeud -> listeSuivante = *uneListe;
	*uneListe = pNoeud;
	}
	else{
	errno= LCDO_ERREUR_MEMOIRE;
	}
}


unsigned int LCDO_obtenirElement(LCDO_ListeChaineeDOrdre uneListe){
	assert(!LCDO_estVide(uneListe));
	errno=0;
	return uneListe->element;
}

void LCDO_fixerElement(LCDO_ListeChaineeDOrdre *uneListe, Ordre element){ 
	assert(!LCDO_estVide(*uneListe));
	errno=0;
	(*uneListe)->element = element;
}

LCDO_ListeChaineeDOrdre LCDO_obtenirListeSuivante(LCDO_ListeChaineeDOrdre uneListe){ 
	assert(!LCDO_estVide(uneListe));
	errno=0;
	return uneListe->listeSuivante;
}

void LCDO_fixerListeSuivante(LCDO_ListeChaineeDOrdre *uneListe, LCDO_ListeChaineeDOrdre nelleSuite){ 
	assert(!LCDO_estVide(*uneListe));
	errno=0;
	(*uneListe)->listeSuivante = nelleSuite;
}


void LCDO_supprimerTete(LCDO_ListeChaineeDOrdre *uneListe){ 
	LCDO_ListeChaineeDOrdre temp;
	assert(!LCDO_estVide(*uneListe));
	errno=0;
	temp=*uneListe; 
	*uneListe = LCDO_obtenirListeSuivante(*uneListe);
	free(temp);
}

void LCDO_supprimer(LCDO_ListeChaineeDOrdre *uneListe){
	errno=0;
	if (!LCDO_estVide(*uneListe)){
		LCDO_supprimerTete(uneListe);
		LCDO_supprimer(uneListe);
	}
}
