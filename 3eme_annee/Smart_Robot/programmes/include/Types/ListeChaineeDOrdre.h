/**
 * @file ListeChaineeDOrdre.h
 * @brief Gestion des listes chaînées contenant des éléments de type `Ordre`.
 */

#ifndef LISTECHAINEEDORDRE
#define LISTECHAINEEDORDRE

#include <stdbool.h> 
#include <stddef.h>  
#include <assert.h>
#include "Ordre.h"

/**
 * @struct LCDO_Noeud
 * @brief Représente un nœud d'une liste chaînée d'éléments de type `Ordre`.
 * 
 * Chaque nœud contient :
 * - un élément de type `Ordre` (`element`).
 * - un pointeur vers le nœud suivant (`listeSuivante`).
 */
typedef struct LCDO_Noeud {
    Ordre element;              
    struct LCDO_Noeud *listeSuivante;
} LCDO_Noeud;

/**
 * @typedef LCDO_ListeChaineeDOrdre
 * @brief Type représentant une liste chaînée d'éléments de type `Ordre`.
 */
typedef LCDO_Noeud* LCDO_ListeChaineeDOrdre;

#define LCDO_ERREUR_MEMOIRE 1

/**
 * @brief Crée une liste chaînée vide.
 * @return Une liste chaînée vide.
 */
LCDO_ListeChaineeDOrdre LCDO_listeVide();

/**
 * @brief Vérifie si une liste chaînée est vide.
 * @param uneListe [E] La liste chaînée à vérifier.
 * @return `true` si la liste est vide, `false` sinon.
 */
bool LCDO_estVide(LCDO_ListeChaineeDOrdre uneListe);

/**
 * @brief Ajoute un élément de type `Ordre` à la tête de la liste chaînée.
 * @param uneListe [E/S] Pointeur vers la liste chaînée.
 * @param element [E] L'élément de type `Ordre` à ajouter.
 */
void LCDO_ajouter(LCDO_ListeChaineeDOrdre *uneListe, Ordre element);

/**
 * @brief Obtient l'élément stocké dans le premier nœud de la liste.
 * @param uneListe [E] La liste chaînée.
 * @return L'élément de type `Ordre` du premier nœud.
 * @pre La liste ne doit pas être vide.
 */
Ordre LCDO_obtenirElement(LCDO_ListeChaineeDOrdre uneListe); /* assert : estVide(uneListe) */

/**
 * @brief Remplace l'élément du premier nœud de la liste.
 * @param uneListe [E/S] Pointeur vers la liste chaînée.
 * @param element [E] Le nouvel élément de type `Ordre` à stocker.
 * @pre La liste ne doit pas être vide.
 */
void LCDO_fixerElement(LCDO_ListeChaineeDOrdre *uneListe, Ordre element); /* assert : estVide(uneListe) */

/**
 * @brief Obtient la liste chaînée suivante.
 * @param uneListe [E] La liste chaînée.
 * @return La liste chaînée suivante.
 * @pre La liste ne doit pas être vide.
 */
LCDO_ListeChaineeDOrdre LCDO_obtenirListeSuivante(LCDO_ListeChaineeDOrdre uneListe); /* assert : estVide(uneListe) */

/**
 * @brief Fixe le nœud suivant de la liste chaînée.
 * @param uneListe [E/S] Pointeur vers la liste chaînée.
 * @param nelleSuite [E] La nouvelle liste à placer en tant que suivante.
 * @pre La liste ne doit pas être vide.
 */
void LCDO_fixerListeSuivante(LCDO_ListeChaineeDOrdre *uneListe, LCDO_ListeChaineeDOrdre nelleSuite); /* assert : estVide(uneListe) */

/**
 * @brief Supprime le premier nœud de la liste chaînée.
 * @param uneListe [E/S] Pointeur vers la liste chaînée.
 * @pre La liste ne doit pas être vide.
 */
void LCDO_supprimerTete(LCDO_ListeChaineeDOrdre *uneListe); /* assert : estVide(uneListe) */

/**
 * @brief Supprime tous les nœuds de la liste chaînée.
 * @param uneListe [E/S] Pointeur vers la liste chaînée.
 */
void LCDO_supprimer(LCDO_ListeChaineeDOrdre *uneListe);

#endif

