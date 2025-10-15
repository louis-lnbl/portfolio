/**
 * @file ListeChaineeDeNNN.h
 * @brief Gestion des listes chaînées contenant des éléments de type entier non signé.
 */

#ifndef LISTECHAINEEDENNN
#define LISTECHAINEEDENNN

#include <stdbool.h> 
#include <stddef.h>  
#include <assert.h>

/**
 * @struct LCDNNN_Noeud
 * @brief Représente un nœud d'une liste chaînée d'entiers non signés.
 * 
 * Chaque nœud contient :
 * - un élément de type `unsigned int` (`element`).
 * - un pointeur vers le nœud suivant (`listeSuivante`).
 */
typedef struct LCDNNN_Noeud {
    unsigned int element;              
    struct LCDNNN_Noeud *listeSuivante; 
} LCDNNN_Noeud;

/**
 * @typedef LCDNNN_ListeChaineeDeNNN
 * @brief Type représentant une liste chaînée d'entiers non signés.
 */
typedef LCDNNN_Noeud* LCDNNN_ListeChaineeDeNNN;


#define LCDNNN_ERREUR_MEMOIRE 1
/**
 * @brief Crée une liste chaînée vide.
 * @return Une liste chaînée vide.
 */
LCDNNN_ListeChaineeDeNNN LCDNNN_listeVide();

/**
 * @brief Vérifie si une liste chaînée est vide.
 * @param uneListe [E] La liste chaînée à vérifier.
 * @return `true` si la liste est vide, `false` sinon.
 */
bool LCDNNN_estVide(LCDNNN_ListeChaineeDeNNN uneListe);

/**
 * @brief Ajoute un élément à la tête de la liste chaînée.
 * @param uneListe [E/S] Pointeur vers la liste chaînée.
 * @param element [E] L'élément à ajouter (de type `unsigned int`).
 */
void LCDNNN_ajouter(LCDNNN_ListeChaineeDeNNN *uneListe, unsigned int element);

/**
 * @brief Obtient l'élément stocké dans le premier nœud de la liste.
 * @param uneListe [E] La liste chaînée.
 * @return L'élément du premier nœud (de type `unsigned int`).
 * @pre La liste ne doit pas être vide.
 */
unsigned int LCDNNN_obtenirElement(LCDNNN_ListeChaineeDeNNN uneListe); /* assert : estVide(uneListe) */

/**
 * @brief Remplace l'élément du premier nœud de la liste.
 * @param uneListe [E/S] Pointeur vers la liste chaînée.
 * @param element [E] Le nouvel élément à stocker (de type `unsigned int`).
 * @pre La liste ne doit pas être vide.
 */
void LCDNNN_fixerElement(LCDNNN_ListeChaineeDeNNN *uneListe, unsigned int element); /* assert : estVide(uneListe) */

/**
 * @brief Obtient la liste chaînée suivante.
 * @param uneListe [E] La liste chaînée.
 * @return La liste chaînée suivante.
 * @pre La liste ne doit pas être vide.
 */
LCDNNN_ListeChaineeDeNNN LCDNNN_obtenirListeSuivante(LCDNNN_ListeChaineeDeNNN uneListe); /* assert : estVide(uneListe) */

/**
 * @brief Fixe le nœud suivant de la liste chaînée.
 * @param uneListe [E/S] Pointeur vers la liste chaînée.
 * @param nelleSuite [E] La nouvelle liste à placer en tant que suivante.
 * @pre La liste ne doit pas être vide.
 */

void LCDNNN_fixerListeSuivante(LCDNNN_ListeChaineeDeNNN *uneListe, LCDNNN_ListeChaineeDeNNN nelleSuite);  /* assert : estVide(uneListe) */

/**
 * @brief Supprime le premier nœud de la liste chaînée.
 * @param uneListe [E/S] Pointeur vers la liste chaînée.
 * @pre La liste ne doit pas être vide.
 */
void LCDNNN_supprimerTete(LCDNNN_ListeChaineeDeNNN *uneListe); /* assert : estVide(uneListe) */

/**
 * @brief Supprime tous les nœuds de la liste chaînée.
 * @param uneListe [E/S] Pointeur vers la liste chaînée.
 */
void LCDNNN_supprimer(LCDNNN_ListeChaineeDeNNN *uneListe);

/**
 * @brief Concatène deux listes chaînées de piles.
 * 
 * @param liste1 [E] Pointeur vers la première liste chaînée.
 * @param liste2 [E] La deuxième liste chaînée à concaténer.
 * @return La nouvelle liste chaînée résultant de la concaténation. Renvoie `NULL` en cas d'erreur mémoire.
 */
void LCDNNN_concatener(LCDNNN_ListeChaineeDeNNN *liste1, LCDNNN_ListeChaineeDeNNN liste2);

/**
 * @brief Inverse l'ordre des nœuds dans une liste chaînée de piles.
 * 
 * @param uneliste [E/S] Pointeur vers la liste chaînée à inverser.
 * @return La nouvelle tête de la liste inversée.
 */
void LCDNNN_inverser(LCDNNN_ListeChaineeDeNNN *uneliste);

/**
 * @brief Effectue une copie profonde d'une liste chaînée.
 * 
 * @param uneliste [E] La liste chaînée à copier.
 * @return La nouvelle liste chaînée contenant les mêmes valeurs que la liste source. 
 *         Renvoie `NULL` si une erreur mémoire survient pendant l'allocation.
 */
LCDNNN_ListeChaineeDeNNN LCDNNN_copier(LCDNNN_ListeChaineeDeNNN uneliste);

#endif
