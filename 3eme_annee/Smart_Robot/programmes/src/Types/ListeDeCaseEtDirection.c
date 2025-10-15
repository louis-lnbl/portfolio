#include <stdbool.h> 
#include <stddef.h>  
#include <assert.h>
#include <errno.h>
#include <stdlib.h>
#include "../../include/Types/caseEtDirection.h"
#include "../../include/Types/ListeChaineeDeCaseEtDirection.h"
#include "../../include/Types/ListeDeCaseEtDirection.h" 


LDCD_ListeDeCaseEtDirection LDCD_liste() {
    LDCD_ListeDeCaseEtDirection liste;
    liste.lesElements = LCDCD_listeVide();
    liste.nbElements = 0;
    return liste;
}


bool LDCD_estVide(LDCD_ListeDeCaseEtDirection liste) {
    return liste.nbElements == 0;
}


void LDCD_inserer(LDCD_ListeDeCaseEtDirection *liste, CD_CaseEtDirection element, unsigned int position) {
    if (position == 1) {
        LCDCD_ListeChaineeDeCaseEtDirection nouveauNoeud = (LCDCD_ListeChaineeDeCaseEtDirection)malloc(sizeof(LCDCD_Noeud));
        nouveauNoeud->element = element;
        nouveauNoeud->listeSuivante = liste->lesElements;
        liste->lesElements = nouveauNoeud;
        liste->nbElements++;
        return;
    }
    else {
        LCDCD_ListeChaineeDeCaseEtDirection courant = liste->lesElements;
        for (unsigned int i = 1; i < position - 1; i++) {
            courant = courant->listeSuivante;
        }

        LCDCD_ListeChaineeDeCaseEtDirection nouveauNoeud = (LCDCD_ListeChaineeDeCaseEtDirection)malloc(sizeof(LCDCD_Noeud));
        nouveauNoeud->element = element;
        nouveauNoeud->listeSuivante = courant->listeSuivante;

        courant->listeSuivante = nouveauNoeud;
        liste->nbElements++;
    }
}


void LDCD_supprimer(LDCD_ListeDeCaseEtDirection *liste, unsigned int position) {
    if (position == 1) {
        LCDCD_ListeChaineeDeCaseEtDirection aSupprimer = liste->lesElements;
        liste->lesElements = aSupprimer->listeSuivante;
        free(aSupprimer);
    }
    else {
        LCDCD_ListeChaineeDeCaseEtDirection courant = liste->lesElements;
        for (unsigned int i = 1; i < position - 1; i++) {
            courant = courant->listeSuivante;
        }

        LCDCD_ListeChaineeDeCaseEtDirection aSupprimer = courant->listeSuivante;
        courant->listeSuivante = aSupprimer->listeSuivante;
        free(aSupprimer);
    }
    liste->nbElements--;
}


CD_CaseEtDirection LDCD_obtenirElement(LDCD_ListeDeCaseEtDirection liste, unsigned int position) {
    LCDCD_ListeChaineeDeCaseEtDirection courant = liste.lesElements;
    for (unsigned int i = 1; i < position; i++) {
        courant = courant->listeSuivante;
    }
    return courant->element;
}

unsigned int LDCD_longueur(LDCD_ListeDeCaseEtDirection liste) {
    return liste.nbElements;
}

