/**
 * @file ListeChaineeDeCaseEtDirection.h
 * @brief Gestion des listes chaînées contenant des éléments de type `CD_CaseEtDirection`.
 */

#ifndef LISTECHAINEEDECASEETDIRECTION
#define LISTECHAINEEDECASEETDIRECTION

#include <stdbool.h>
#include <stddef.h>
#include <assert.h>
#include "caseEtDirection.h"

/**
 * @struct LCDCD_Noeud
 * @brief Représente un nœud d'une liste chaînée de `CD_CaseEtDirection`.
 * 
 * Chaque nœud contient :
 * - un élément de type `CD_CaseEtDirection` (`element`).
 * - un pointeur vers le nœud suivant (`listeSuivante`).
 */
typedef struct LCDCD_Noeud {
    CD_CaseEtDirection element;    
    struct LCDCD_Noeud *listeSuivante;  
} LCDCD_Noeud;

/**
 * @typedef LCDCD_ListeChaineeDeCaseEtDirection
 * @brief Type représentant une liste chaînée de `CD_CaseEtDirection`.
 */
typedef LCDCD_Noeud* LCDCD_ListeChaineeDeCaseEtDirection;


#define LCDCD_ERREUR_MEMOIRE 1

/**
 * @brief Crée une liste chaînée vide.
 * @return Une liste chaînée vide de type `LCDCD_ListeChaineeDeCaseEtDirection`.
 */
LCDCD_ListeChaineeDeCaseEtDirection LCDCD_listeVide();

/**
 * @brief Vérifie si une liste chaînée est vide.
 * @param uneListe [E] La liste chaînée à vérifier.
 * @return `true` si la liste est vide, `false` sinon.
 */
bool LCDCD_estVide(LCDCD_ListeChaineeDeCaseEtDirection uneListe);

/**
 * @brief Ajoute un élément à la tête de la liste chaînée.
 * @param uneListe [E/S] Pointeur vers la liste chaînée.
 * @param element [E] L'élément de type `CD_CaseEtDirection` à ajouter.
 */
void LCDCD_ajouter(LCDCD_ListeChaineeDeCaseEtDirection *uneListe, CD_CaseEtDirection element);

/**
 * @brief Obtient l'élément stocké dans le premier nœud de la liste.
 * @param uneListe [E] La liste chaînée.
 * @return L'élément du premier nœud (de type `CD_CaseEtDirection`).
 * @pre La liste ne doit pas être vide.
 */
CD_CaseEtDirection LCDCD_obtenirElement(LCDCD_ListeChaineeDeCaseEtDirection uneListe); /* assert : estVide(uneListe) */

/**
 * @brief Remplace l'élément du premier nœud de la liste.
 * @param uneListe [E/S] Pointeur vers la liste chaînée.
 * @param element [E] Le nouvel élément à stocker (de type `CD_CaseEtDirection`).
 * @pre La liste ne doit pas être vide.
 */
void LCDCD_fixerElement(LCDCD_ListeChaineeDeCaseEtDirection *uneListe, CD_CaseEtDirection element); /* assert : estVide(uneListe) */

/**
 * @brief Obtient la liste chaînée suivante.
 * @param uneListe [E] La liste chaînée.
 * @return La liste chaînée suivante.
 * @pre La liste ne doit pas être vide.
 */
LCDCD_ListeChaineeDeCaseEtDirection LCDCD_obtenirListeSuivante(LCDCD_ListeChaineeDeCaseEtDirection uneListe); /* assert : estVide(uneListe) */

/**
 * @brief Fixe le nœud suivant de la liste chaînée.
 * @param uneListe [E/S] Pointeur vers la liste chaînée.
 * @param nelleSuite [E] La nouvelle liste à placer en tant que suivante.
 * @pre La liste ne doit pas être vide.
 */
void LCDCD_fixerListeSuivante(LCDCD_ListeChaineeDeCaseEtDirection *uneListe, LCDCD_ListeChaineeDeCaseEtDirection nelleSuite); /* assert : estVide(uneListe) */

/**
 * @brief Supprime le premier nœud de la liste chaînée.
 * @param uneListe [E/S] Pointeur vers la liste chaînée.
 * @pre La liste ne doit pas être vide.
 */
void LCDCD_supprimerTete(LCDCD_ListeChaineeDeCaseEtDirection *uneListe); /* assert : estVide(uneListe) */

/**
 * @brief Supprime tous les nœuds de la liste chaînée.
 * @param uneListe [E/S] Pointeur vers la liste chaînée.
 */
void LCDCD_supprimer(LCDCD_ListeChaineeDeCaseEtDirection *uneListe);

#endif

