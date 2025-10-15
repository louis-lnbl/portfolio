/**
 * @file ListeChaineeDOrdre.h
 * @brief Gestion des listes chaÃ®nÃ©es contenant des Ã©lÃ©ments de type `Ordre`.
 */

#ifndef LISTECHAINEEDORDRE
#define LISTECHAINEEDORDRE

#include <stdbool.h> 
#include <stddef.h>  
#include <assert.h>
#include "Ordre.h"

/**
 * @struct LCDO_Noeud
 * @brief ReprÃ©sente un nÅud d'une liste chaÃ®nÃ©e d'Ã©lÃ©ments de type `Ordre`.
 * 
 * Chaque nÅud contient :
 * - un Ã©lÃ©ment de type `Ordre` (`element`).
 * - un pointeur vers le nÅud suivant (`listeSuivante`).
 */
typedef struct LCDO_Noeud {
    Ordre element;              
    struct LCDO_Noeud *listeSuivante;
} LCDO_Noeud;

/**
 * @typedef LCDO_ListeChaineeDOrdre
 * @brief Type reprÃ©sentant une liste chaÃ®nÃ©e d'Ã©lÃ©ments de type `Ordre`.
 */
typedef LCDO_Noeud* LCDO_ListeChaineeDOrdre;

#define LCDO_ERREUR_MEMOIRE 1

/**
 * @brief CrÃ©e une liste chaÃ®nÃ©e vide.
 * @return Une liste chaÃ®nÃ©e vide.
 */
LCDO_ListeChaineeDOrdre LCDO_listeVide();

/**
 * @brief VÃ©rifie si une liste chaÃ®nÃ©e est vide.
 * @param uneListe [E] La liste chaÃ®nÃ©e Ã  vÃ©rifier.
 * @return `true` si la liste est vide, `false` sinon.
 */
bool LCDO_estVide(LCDO_ListeChaineeDOrdre uneListe);

/**
 * @brief Ajoute un Ã©lÃ©ment de type `Ordre` Ã  la tÃªte de la liste chaÃ®nÃ©e.
 * @param uneListe [E/S] Pointeur vers la liste chaÃ®nÃ©e.
 * @param element [E] L'Ã©lÃ©ment de type `Ordre` Ã  ajouter.
 */
void LCDO_ajouter(LCDO_ListeChaineeDOrdre *uneListe, Ordre element);

/**
 * @brief Obtient l'Ã©lÃ©ment stockÃ© dans le premier nÅud de la liste.
 * @param uneListe [E] La liste chaÃ®nÃ©e.
 * @return L'Ã©lÃ©ment de type `Ordre` du premier nÅud.
 * @pre La liste ne doit pas Ãªtre vide.
 */
Ordre LCDO_obtenirElement(LCDO_ListeChaineeDOrdre uneListe); /* assert : estVide(uneListe) */

/**
 * @brief Remplace l'Ã©lÃ©ment du premier nÅud de la liste.
 * @param uneListe [E/S] Pointeur vers la liste chaÃ®nÃ©e.
 * @param element [E] Le nouvel Ã©lÃ©ment de type `Ordre` Ã  stocker.
 * @pre La liste ne doit pas Ãªtre vide.
 */
void LCDO_fixerElement(LCDO_ListeChaineeDOrdre *uneListe, Ordre element); /* assert : estVide(uneListe) */

/**
 * @brief Obtient la liste chaÃ®nÃ©e suivante.
 * @param uneListe [E] La liste chaÃ®nÃ©e.
 * @return La liste chaÃ®nÃ©e suivante.
 * @pre La liste ne doit pas Ãªtre vide.
 */
LCDO_ListeChaineeDOrdre LCDO_obtenirListeSuivante(LCDO_ListeChaineeDOrdre uneListe); /* assert : estVide(uneListe) */

/**
 * @brief Fixe le nÅud suivant de la liste chaÃ®nÃ©e.
 * @param uneListe [E/S] Pointeur vers la liste chaÃ®nÃ©e.
 * @param nelleSuite [E] La nouvelle liste Ã  placer en tant que suivante.
 * @pre La liste ne doit pas Ãªtre vide.
 */
void LCDO_fixerListeSuivante(LCDO_ListeChaineeDOrdre *uneListe, LCDO_ListeChaineeDOrdre nelleSuite); /* assert : estVide(uneListe) */

/**
 * @brief Supprime le premier nÅud de la liste chaÃ®nÃ©e.
 * @param uneListe [E/S] Pointeur vers la liste chaÃ®nÃ©e.
 * @pre La liste ne doit pas Ãªtre vide.
 */
void LCDO_supprimerTete(LCDO_ListeChaineeDOrdre *uneListe); /* assert : estVide(uneListe) */

/**
 * @brief Supprime tous les nÅuds de la liste chaÃ®nÃ©e.
 * @param uneListe [E/S] Pointeur vers la liste chaÃ®nÃ©e.
 */
void LCDO_supprimer(LCDO_ListeChaineeDOrdre *uneListe);

#endif

