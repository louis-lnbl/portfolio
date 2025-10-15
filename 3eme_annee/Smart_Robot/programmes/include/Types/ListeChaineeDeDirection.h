/**
 * @file ListeChaineeDeDirection.h
 * @brief Gestion des listes chaînées contenant des éléments de type Direction.
 */

#ifndef LISTECHAINEEDEDIRECTION
#define LISTECHAINEEDEDIRECTION

#include <stdbool.h> 
#include <stddef.h>  
#include <assert.h>
#include "Direction.h"

/**
 * @struct LCDD_Noeud
 * @brief Représente un nœud d'une liste chaînée de directions.
 * 
 * Chaque nœud contient :
 * - un élément de type `Direction` (`element`).
 * - un pointeur vers le nœud suivant (`listeSuivante`).
 */
typedef struct LCDD_Noeud {
    Direction element;              
    struct LCDD_Noeud *listeSuivante; 
} LCDD_Noeud;

/**
 * @typedef LCDD_ListeChaineeDeDirection
 * @brief Type représentant une liste chaînée de directions.
 */
typedef LCDD_Noeud* LCDD_ListeChaineeDeDirection;


#define LCDD_ERREUR_MEMOIRE 1
/**
 * @brief Crée une liste chaînée vide.
 * @return Une liste chaînée vide.
 */
LCDD_ListeChaineeDeDirection LCDD_listeVide();

/**
 * @brief Vérifie si une liste chaînée est vide.
 * @param uneListe [E] La liste chaînée à vérifier.
 * @return `true` si la liste est vide, `false` sinon.
 */
bool LCDD_estVide(LCDD_ListeChaineeDeDirection uneListe);

/**
 * @brief Ajoute un élément à la tête de la liste chaînée.
 * @param uneListe [E/S] Pointeur vers la liste chaînée.
 * @param element [E] L'élément de type Direction à ajouter.
 */
void LCDD_ajouter(LCDD_ListeChaineeDeDirection *uneListe, Direction element);

/**
 * @brief Obtient l'élément stocké dans le premier nœud de la liste.
 * @param uneListe [E] La liste chaînée.
 * @return L'élément du premier nœud (de type Direction).
 * @pre La liste ne doit pas être vide.
 */
Direction LCDD_obtenirElement(LCDD_ListeChaineeDeDirection uneListe);

/**
 * @brief Remplace l'élément du premier nœud de la liste.
 * @param uneListe [E/S] Pointeur vers la liste chaînée.
 * @param element [E] Le nouvel élément à stocker (de type Direction).
 * @pre La liste ne doit pas être vide.
 */
void LCDD_fixerElement(LCDD_ListeChaineeDeDirection *uneListe, Direction element);

/**
 * @brief Obtient la liste chaînée suivante.
 * @param uneListe [E] La liste chaînée.
 * @return La liste chaînée suivante.
 * @pre La liste ne doit pas être vide.
 */
LCDD_ListeChaineeDeDirection LCDD_obtenirListeSuivante(LCDD_ListeChaineeDeDirection uneListe); /* assert : estVide(uneListe) */

/**
 * @brief Fixe le nœud suivant de la liste chaînée.
 * @param uneListe [E/S] Pointeur vers la liste chaînée.
 * @param nelleSuite [E] La nouvelle liste à placer en tant que suivante.
 * @pre La liste ne doit pas être vide.
 */
void LCDD_fixerListeSuivante(LCDD_ListeChaineeDeDirection *uneListe, LCDD_ListeChaineeDeDirection nelleSuite); /* assert : estVide(uneListe) */

/**
 * @brief Supprime le premier nœud de la liste chaînée.
 * @param uneListe [E/S] Pointeur vers la liste chaînée.
 * @pre La liste ne doit pas être vide.
 */
void LCDD_supprimerTete(LCDD_ListeChaineeDeDirection *uneListe); /* assert : estVide(uneListe) */

/**
 * @brief Supprime tous les nœuds de la liste chaînée.
 * @param uneListe [E/S] Pointeur vers la liste chaînée.
 */
void LCDD_supprimer(LCDD_ListeChaineeDeDirection *uneListe);

#endif
