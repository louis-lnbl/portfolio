#include <stdbool.h> 
#include <stddef.h>  
#include <assert.h>
#include <errno.h>
#include <stdlib.h>
#include "../../include/Types/caseEtDirection.h"
#include "../../include/Types/ListeChaineeDeCaseEtDirection.h"


LCDCD_ListeChaineeDeCaseEtDirection LCDCD_listeVide() {
    errno = 0;
    return NULL;
}


bool LCDCD_estVide(LCDCD_ListeChaineeDeCaseEtDirection uneListe) {
    errno = 0;
    return uneListe == NULL;
}


void LCDCD_ajouter(LCDCD_ListeChaineeDeCaseEtDirection *uneListe, CD_CaseEtDirection element) {
    LCDCD_ListeChaineeDeCaseEtDirection pNoeud = (LCDCD_ListeChaineeDeCaseEtDirection)malloc(sizeof(LCDCD_Noeud));
    if (pNoeud != NULL) {
        errno = 0;
        pNoeud->element = element;
        pNoeud->listeSuivante = *uneListe;
        *uneListe = pNoeud;
    } else {
        errno = LCDCD_ERREUR_MEMOIRE;
    }
}


CD_CaseEtDirection LCDCD_obtenirElement(LCDCD_ListeChaineeDeCaseEtDirection uneListe) { 
    assert(!LCDCD_estVide(uneListe));
    errno = 0;
    return uneListe->element;
}


void LCDCD_fixerElement(LCDCD_ListeChaineeDeCaseEtDirection *uneListe, CD_CaseEtDirection element) {
    assert(!LCDCD_estVide(*uneListe));
    errno = 0;
    (*uneListe)->element = element;
}


LCDCD_ListeChaineeDeCaseEtDirection LCDCD_obtenirListeSuivante(LCDCD_ListeChaineeDeCaseEtDirection uneListe) { 
    assert(!LCDCD_estVide(uneListe));
    errno = 0;
    return uneListe->listeSuivante;
}


void LCDCD_fixerListeSuivante(LCDCD_ListeChaineeDeCaseEtDirection *uneListe, LCDCD_ListeChaineeDeCaseEtDirection nelleSuite) { 
    assert(!LCDCD_estVide(*uneListe));
    errno = 0;
    (*uneListe)->listeSuivante = nelleSuite;
}


void LCDCD_supprimerTete(LCDCD_ListeChaineeDeCaseEtDirection *uneListe) { 
    LCDCD_ListeChaineeDeCaseEtDirection temp;
    assert(!LCDCD_estVide(*uneListe));
    errno = 0;
    temp = *uneListe; 
    *uneListe = LCDCD_obtenirListeSuivante(*uneListe);
    free(temp);
}


void LCDCD_supprimer(LCDCD_ListeChaineeDeCaseEtDirection *uneListe) {
    errno = 0;
    if (!LCDCD_estVide(*uneListe)) {
        LCDCD_supprimerTete(uneListe);
        LCDCD_supprimer(uneListe);
    }
}
