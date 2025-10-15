/**
 * @file ListeChaineeDePileDeNNN.h
 * @brief Gestion des listes chaînées contenant des piles d'entiers non signés.
 */

#ifndef LISTECHAINEEDEPILEDENNN
#define LISTECHAINEEDEPILEDENNN

#include <stdbool.h> 
#include <stddef.h>  
#include <assert.h>
#include "PileDeNNN.h"

/**
 * @struct LCDPDNNN_Noeud
 * @brief Représente un nœud d'une liste chaînée de piles d'entiers non signés.
 * 
 * Chaque nœud contient :
 * - une pile de type `PDNNN_PileDeNNN` (`element`).
 * - un pointeur vers le nœud suivant (`listeSuivante`).
 */
typedef struct LCDPDNNN_Noeud {
    PDNNN_PileDeNNN element;             
    struct LCDPDNNN_Noeud *listeSuivante;  
} LCDPDNNN_Noeud;

/**
 * @typedef LCDPDNNN_ListeChaineeDePileDeNNN
 * @brief Type représentant une liste chaînée de piles d'entiers non signés.
 */
typedef LCDPDNNN_Noeud* LCDPDNNN_ListeChaineeDePileDeNNN;

#define LCDPDNNN_ERREUR_MEMOIRE 1

/**
 * @brief Crée une liste chaînée vide.
 * @return Une liste chaînée vide.
 */
LCDPDNNN_ListeChaineeDePileDeNNN LCDPDNNN_listeVide();

/**
 * @brief Vérifie si une liste chaînée est vide.
 * @param uneListe [E] La liste chaînée à vérifier.
 * @return `true` si la liste est vide, `false` sinon.
 */
bool LCDPDNNN_estVide(LCDPDNNN_ListeChaineeDePileDeNNN uneListe);

/**
 * @brief Ajoute une pile à la tête de la liste chaînée.
 * @param uneListe [E/S] Pointeur vers la liste chaînée.
 * @param element [E] La pile à ajouter (de type `PDNNN_PileDeNNN`).
 */
void LCDPDNNN_ajouter(LCDPDNNN_ListeChaineeDePileDeNNN *uneListe, PDNNN_PileDeNNN element);

/**
 * @brief Obtient la pile stockée dans le premier nœud de la liste.
 * @param uneListe [E] La liste chaînée.
 * @return La pile du premier nœud (de type `PDNNN_PileDeNNN`).
 * @pre La liste ne doit pas être vide.
 */
PDNNN_PileDeNNN LCDPDNNN_obtenirElement(LCDPDNNN_ListeChaineeDePileDeNNN uneListe); /* assert : estVide(uneListe) */

/**
 * @brief Remplace la pile du premier nœud de la liste.
 * @param uneListe [E/S] Pointeur vers la liste chaînée.
 * @param element [E] La nouvelle pile à stocker (de type `PDNNN_PileDeNNN`).
 * @pre La liste ne doit pas être vide.
 */
void LCDPDNNN_fixerElement(LCDPDNNN_ListeChaineeDePileDeNNN *uneListe, PDNNN_PileDeNNN element); /* assert : estVide(uneListe) */

/**
 * @brief Obtient la liste chaînée suivante.
 * @param uneListe [E] La liste chaînée.
 * @return La liste chaînée suivante.
 * @pre La liste ne doit pas être vide.
 */
LCDPDNNN_ListeChaineeDePileDeNNN LCDPDNNN_obtenirListeSuivante(LCDPDNNN_ListeChaineeDePileDeNNN uneListe); /* assert : estVide(uneListe) */

/**
 * @brief Fixe le nœud suivant de la liste chaînée.
 * @param uneListe [E/S] Pointeur vers la liste chaînée.
 * @param nelleSuite [E] La nouvelle liste à placer en tant que suivante.
 * @pre La liste ne doit pas être vide.
 */
void LCDPDNNN_fixerListeSuivante(LCDPDNNN_ListeChaineeDePileDeNNN *uneListe, LCDPDNNN_ListeChaineeDePileDeNNN nelleSuite); /* assert : estVide(uneListe) */

/**
 * @brief Supprime le premier nœud de la liste chaînée.
 * @param uneListe [E/S] Pointeur vers la liste chaînée.
 * @pre La liste ne doit pas être vide.
 */
void LCDPDNNN_supprimerTete(LCDPDNNN_ListeChaineeDePileDeNNN *uneListe); /* assert : estVide(uneListe) */

/**
 * @brief Supprime tous les nœuds de la liste chaînée.
 * @param uneListe [E/S] Pointeur vers la liste chaînée.
 */
void LCDPDNNN_supprimer(LCDPDNNN_ListeChaineeDePileDeNNN *uneListe);

/**
 * @brief Concatène deux listes chaînées de piles.
 * 
 * @param liste1 [E] Pointeur vers la première liste chaînée.
 * @param liste2 [E] La deuxième liste chaînée à concaténer.
 * @return La nouvelle liste chaînée résultant de la concaténation. Renvoie `NULL` en cas d'erreur mémoire.
 */
void LCDPDNNN_concatener(LCDPDNNN_ListeChaineeDePileDeNNN *liste1, LCDPDNNN_ListeChaineeDePileDeNNN liste2);

/**
 * @brief Inverse l'ordre des nœuds dans une liste chaînée de piles.
 * 
 * @param uneliste [E/S] Pointeur vers la liste chaînée à inverser.
 * @return La nouvelle tête de la liste inversée.
 */
void LCDPDNNN_inverser(LCDPDNNN_ListeChaineeDePileDeNNN *uneliste);

/**
 * @brief Effectue une copie profonde d'une liste chaînée.
 * 
 * @param uneliste [E] La liste chaînée à copier.
 * @return La nouvelle liste chaînée contenant les mêmes valeurs que la liste source. 
 *         Renvoie `NULL` si une erreur mémoire survient pendant l'allocation.
 */
LCDPDNNN_ListeChaineeDePileDeNNN LCDPDNNN_copier(LCDPDNNN_ListeChaineeDePileDeNNN uneliste);

#endif
