/**
 * @file ListeChaineeDeDirection.h
 * @brief Gestion des listes chaÃ®nÃ©es contenant des Ã©lÃ©ments de type Direction.
 */

#ifndef LISTECHAINEEDEDIRECTION
#define LISTECHAINEEDEDIRECTION

#include <stdbool.h> 
#include <stddef.h>  
#include <assert.h>
#include "Direction.h"

/**
 * @struct LCDD_Noeud
 * @brief ReprÃ©sente un nÅud d'une liste chaÃ®nÃ©e de directions.
 * 
 * Chaque nÅud contient :
 * - un Ã©lÃ©ment de type `Direction` (`element`).
 * - un pointeur vers le nÅud suivant (`listeSuivante`).
 */
typedef struct LCDD_Noeud {
    Direction element;              
    struct LCDD_Noeud *listeSuivante; 
} LCDD_Noeud;

/**
 * @typedef LCDD_ListeChaineeDeDirection
 * @brief Type reprÃ©sentant une liste chaÃ®nÃ©e de directions.
 */
typedef LCDD_Noeud* LCDD_ListeChaineeDeDirection;


#define LCDD_ERREUR_MEMOIRE 1
/**
 * @brief CrÃ©e une liste chaÃ®nÃ©e vide.
 * @return Une liste chaÃ®nÃ©e vide.
 */
LCDD_ListeChaineeDeDirection LCDD_listeVide();

/**
 * @brief VÃ©rifie si une liste chaÃ®nÃ©e est vide.
 * @param uneListe [E] La liste chaÃ®nÃ©e Ã  vÃ©rifier.
 * @return `true` si la liste est vide, `false` sinon.
 */
bool LCDD_estVide(LCDD_ListeChaineeDeDirection uneListe);

/**
 * @brief Ajoute un Ã©lÃ©ment Ã  la tÃªte de la liste chaÃ®nÃ©e.
 * @param uneListe [E/S] Pointeur vers la liste chaÃ®nÃ©e.
 * @param element [E] L'Ã©lÃ©ment de type Direction Ã  ajouter.
 */
void LCDD_ajouter(LCDD_ListeChaineeDeDirection *uneListe, Direction element);

/**
 * @brief Obtient l'Ã©lÃ©ment stockÃ© dans le premier nÅud de la liste.
 * @param uneListe [E] La liste chaÃ®nÃ©e.
 * @return L'Ã©lÃ©ment du premier nÅud (de type Direction).
 * @pre La liste ne doit pas Ãªtre vide.
 */
Direction LCDD_obtenirElement(LCDD_ListeChaineeDeDirection uneListe);

/**
 * @brief Remplace l'Ã©lÃ©ment du premier nÅud de la liste.
 * @param uneListe [E/S] Pointeur vers la liste chaÃ®nÃ©e.
 * @param element [E] Le nouvel Ã©lÃ©ment Ã  stocker (de type Direction).
 * @pre La liste ne doit pas Ãªtre vide.
 */
void LCDD_fixerElement(LCDD_ListeChaineeDeDirection *uneListe, Direction element);

/**
 * @brief Obtient la liste chaÃ®nÃ©e suivante.
 * @param uneListe [E] La liste chaÃ®nÃ©e.
 * @return La liste chaÃ®nÃ©e suivante.
 * @pre La liste ne doit pas Ãªtre vide.
 */
LCDD_ListeChaineeDeDirection LCDD_obtenirListeSuivante(LCDD_ListeChaineeDeDirection uneListe); /* assert : estVide(uneListe) */

/**
 * @brief Fixe le nÅud suivant de la liste chaÃ®nÃ©e.
 * @param uneListe [E/S] Pointeur vers la liste chaÃ®nÃ©e.
 * @param nelleSuite [E] La nouvelle liste Ã  placer en tant que suivante.
 * @pre La liste ne doit pas Ãªtre vide.
 */
void LCDD_fixerListeSuivante(LCDD_ListeChaineeDeDirection *uneListe, LCDD_ListeChaineeDeDirection nelleSuite); /* assert : estVide(uneListe) */

/**
 * @brief Supprime le premier nÅud de la liste chaÃ®nÃ©e.
 * @param uneListe [E/S] Pointeur vers la liste chaÃ®nÃ©e.
 * @pre La liste ne doit pas Ãªtre vide.
 */
void LCDD_supprimerTete(LCDD_ListeChaineeDeDirection *uneListe); /* assert : estVide(uneListe) */

/**
 * @brief Supprime tous les nÅuds de la liste chaÃ®nÃ©e.
 * @param uneListe [E/S] Pointeur vers la liste chaÃ®nÃ©e.
 */
void LCDD_supprimer(LCDD_ListeChaineeDeDirection *uneListe);

#endif
