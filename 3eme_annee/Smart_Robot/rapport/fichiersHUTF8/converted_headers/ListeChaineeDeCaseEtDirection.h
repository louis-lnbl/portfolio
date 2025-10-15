/**
 * @file ListeChaineeDeCaseEtDirection.h
 * @brief Gestion des listes chaÃ®nÃ©es contenant des Ã©lÃ©ments de type `CD_CaseEtDirection`.
 */

#ifndef LISTECHAINEEDECASEETDIRECTION
#define LISTECHAINEEDECASEETDIRECTION

#include <stdbool.h>
#include <stddef.h>
#include <assert.h>
#include "caseEtDirection.h"

/**
 * @struct LCDCD_Noeud
 * @brief ReprÃ©sente un nÅud d'une liste chaÃ®nÃ©e de `CD_CaseEtDirection`.
 * 
 * Chaque nÅud contient :
 * - un Ã©lÃ©ment de type `CD_CaseEtDirection` (`element`).
 * - un pointeur vers le nÅud suivant (`listeSuivante`).
 */
typedef struct LCDCD_Noeud {
    CD_CaseEtDirection element;    
    struct LCDCD_Noeud *listeSuivante;  
} LCDCD_Noeud;

/**
 * @typedef LCDCD_ListeChaineeDeCaseEtDirection
 * @brief Type reprÃ©sentant une liste chaÃ®nÃ©e de `CD_CaseEtDirection`.
 */
typedef LCDCD_Noeud* LCDCD_ListeChaineeDeCaseEtDirection;


#define LCDCD_ERREUR_MEMOIRE 1

/**
 * @brief CrÃ©e une liste chaÃ®nÃ©e vide.
 * @return Une liste chaÃ®nÃ©e vide de type `LCDCD_ListeChaineeDeCaseEtDirection`.
 */
LCDCD_ListeChaineeDeCaseEtDirection LCDCD_listeVide();

/**
 * @brief VÃ©rifie si une liste chaÃ®nÃ©e est vide.
 * @param uneListe [E] La liste chaÃ®nÃ©e Ã  vÃ©rifier.
 * @return `true` si la liste est vide, `false` sinon.
 */
bool LCDCD_estVide(LCDCD_ListeChaineeDeCaseEtDirection uneListe);

/**
 * @brief Ajoute un Ã©lÃ©ment Ã  la tÃªte de la liste chaÃ®nÃ©e.
 * @param uneListe [E/S] Pointeur vers la liste chaÃ®nÃ©e.
 * @param element [E] L'Ã©lÃ©ment de type `CD_CaseEtDirection` Ã  ajouter.
 */
void LCDCD_ajouter(LCDCD_ListeChaineeDeCaseEtDirection *uneListe, CD_CaseEtDirection element);

/**
 * @brief Obtient l'Ã©lÃ©ment stockÃ© dans le premier nÅud de la liste.
 * @param uneListe [E] La liste chaÃ®nÃ©e.
 * @return L'Ã©lÃ©ment du premier nÅud (de type `CD_CaseEtDirection`).
 * @pre La liste ne doit pas Ãªtre vide.
 */
CD_CaseEtDirection LCDCD_obtenirElement(LCDCD_ListeChaineeDeCaseEtDirection uneListe); /* assert : estVide(uneListe) */

/**
 * @brief Remplace l'Ã©lÃ©ment du premier nÅud de la liste.
 * @param uneListe [E/S] Pointeur vers la liste chaÃ®nÃ©e.
 * @param element [E] Le nouvel Ã©lÃ©ment Ã  stocker (de type `CD_CaseEtDirection`).
 * @pre La liste ne doit pas Ãªtre vide.
 */
void LCDCD_fixerElement(LCDCD_ListeChaineeDeCaseEtDirection *uneListe, CD_CaseEtDirection element); /* assert : estVide(uneListe) */

/**
 * @brief Obtient la liste chaÃ®nÃ©e suivante.
 * @param uneListe [E] La liste chaÃ®nÃ©e.
 * @return La liste chaÃ®nÃ©e suivante.
 * @pre La liste ne doit pas Ãªtre vide.
 */
LCDCD_ListeChaineeDeCaseEtDirection LCDCD_obtenirListeSuivante(LCDCD_ListeChaineeDeCaseEtDirection uneListe); /* assert : estVide(uneListe) */

/**
 * @brief Fixe le nÅud suivant de la liste chaÃ®nÃ©e.
 * @param uneListe [E/S] Pointeur vers la liste chaÃ®nÃ©e.
 * @param nelleSuite [E] La nouvelle liste Ã  placer en tant que suivante.
 * @pre La liste ne doit pas Ãªtre vide.
 */
void LCDCD_fixerListeSuivante(LCDCD_ListeChaineeDeCaseEtDirection *uneListe, LCDCD_ListeChaineeDeCaseEtDirection nelleSuite); /* assert : estVide(uneListe) */

/**
 * @brief Supprime le premier nÅud de la liste chaÃ®nÃ©e.
 * @param uneListe [E/S] Pointeur vers la liste chaÃ®nÃ©e.
 * @pre La liste ne doit pas Ãªtre vide.
 */
void LCDCD_supprimerTete(LCDCD_ListeChaineeDeCaseEtDirection *uneListe); /* assert : estVide(uneListe) */

/**
 * @brief Supprime tous les nÅuds de la liste chaÃ®nÃ©e.
 * @param uneListe [E/S] Pointeur vers la liste chaÃ®nÃ©e.
 */
void LCDCD_supprimer(LCDCD_ListeChaineeDeCaseEtDirection *uneListe);

#endif

