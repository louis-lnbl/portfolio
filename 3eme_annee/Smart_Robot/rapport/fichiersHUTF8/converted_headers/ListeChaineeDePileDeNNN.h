/**
 * @file ListeChaineeDePileDeNNN.h
 * @brief Gestion des listes chaÃ®nÃ©es contenant des piles d'entiers non signÃ©s.
 */

#ifndef LISTECHAINEEDEPILEDENNN
#define LISTECHAINEEDEPILEDENNN

#include <stdbool.h> 
#include <stddef.h>  
#include <assert.h>
#include "PileDeNNN.h"

/**
 * @struct LCDPDNNN_Noeud
 * @brief ReprÃ©sente un nÅud d'une liste chaÃ®nÃ©e de piles d'entiers non signÃ©s.
 * 
 * Chaque nÅud contient :
 * - une pile de type `PDNNN_PileDeNNN` (`element`).
 * - un pointeur vers le nÅud suivant (`listeSuivante`).
 */
typedef struct LCDPDNNN_Noeud {
    PDNNN_PileDeNNN element;             
    struct LCDPDNNN_Noeud *listeSuivante;  
} LCDPDNNN_Noeud;

/**
 * @typedef LCDPDNNN_ListeChaineeDePileDeNNN
 * @brief Type reprÃ©sentant une liste chaÃ®nÃ©e de piles d'entiers non signÃ©s.
 */
typedef LCDPDNNN_Noeud* LCDPDNNN_ListeChaineeDePileDeNNN;

#define LCDPDNNN_ERREUR_MEMOIRE 1

/**
 * @brief CrÃ©e une liste chaÃ®nÃ©e vide.
 * @return Une liste chaÃ®nÃ©e vide.
 */
LCDPDNNN_ListeChaineeDePileDeNNN LCDPDNNN_listeVide();

/**
 * @brief VÃ©rifie si une liste chaÃ®nÃ©e est vide.
 * @param uneListe [E] La liste chaÃ®nÃ©e Ã  vÃ©rifier.
 * @return `true` si la liste est vide, `false` sinon.
 */
bool LCDPDNNN_estVide(LCDPDNNN_ListeChaineeDePileDeNNN uneListe);

/**
 * @brief Ajoute une pile Ã  la tÃªte de la liste chaÃ®nÃ©e.
 * @param uneListe [E/S] Pointeur vers la liste chaÃ®nÃ©e.
 * @param element [E] La pile Ã  ajouter (de type `PDNNN_PileDeNNN`).
 */
void LCDPDNNN_ajouter(LCDPDNNN_ListeChaineeDePileDeNNN *uneListe, PDNNN_PileDeNNN element);

/**
 * @brief Obtient la pile stockÃ©e dans le premier nÅud de la liste.
 * @param uneListe [E] La liste chaÃ®nÃ©e.
 * @return La pile du premier nÅud (de type `PDNNN_PileDeNNN`).
 * @pre La liste ne doit pas Ãªtre vide.
 */
PDNNN_PileDeNNN LCDPDNNN_obtenirElement(LCDPDNNN_ListeChaineeDePileDeNNN uneListe); /* assert : estVide(uneListe) */

/**
 * @brief Remplace la pile du premier nÅud de la liste.
 * @param uneListe [E/S] Pointeur vers la liste chaÃ®nÃ©e.
 * @param element [E] La nouvelle pile Ã  stocker (de type `PDNNN_PileDeNNN`).
 * @pre La liste ne doit pas Ãªtre vide.
 */
void LCDPDNNN_fixerElement(LCDPDNNN_ListeChaineeDePileDeNNN *uneListe, PDNNN_PileDeNNN element); /* assert : estVide(uneListe) */

/**
 * @brief Obtient la liste chaÃ®nÃ©e suivante.
 * @param uneListe [E] La liste chaÃ®nÃ©e.
 * @return La liste chaÃ®nÃ©e suivante.
 * @pre La liste ne doit pas Ãªtre vide.
 */
LCDPDNNN_ListeChaineeDePileDeNNN LCDPDNNN_obtenirListeSuivante(LCDPDNNN_ListeChaineeDePileDeNNN uneListe); /* assert : estVide(uneListe) */

/**
 * @brief Fixe le nÅud suivant de la liste chaÃ®nÃ©e.
 * @param uneListe [E/S] Pointeur vers la liste chaÃ®nÃ©e.
 * @param nelleSuite [E] La nouvelle liste Ã  placer en tant que suivante.
 * @pre La liste ne doit pas Ãªtre vide.
 */
void LCDPDNNN_fixerListeSuivante(LCDPDNNN_ListeChaineeDePileDeNNN *uneListe, LCDPDNNN_ListeChaineeDePileDeNNN nelleSuite); /* assert : estVide(uneListe) */

/**
 * @brief Supprime le premier nÅud de la liste chaÃ®nÃ©e.
 * @param uneListe [E/S] Pointeur vers la liste chaÃ®nÃ©e.
 * @pre La liste ne doit pas Ãªtre vide.
 */
void LCDPDNNN_supprimerTete(LCDPDNNN_ListeChaineeDePileDeNNN *uneListe); /* assert : estVide(uneListe) */

/**
 * @brief Supprime tous les nÅuds de la liste chaÃ®nÃ©e.
 * @param uneListe [E/S] Pointeur vers la liste chaÃ®nÃ©e.
 */
void LCDPDNNN_supprimer(LCDPDNNN_ListeChaineeDePileDeNNN *uneListe);

/**
 * @brief ConcatÃ¨ne deux listes chaÃ®nÃ©es de piles.
 * 
 * @param liste1 [E] Pointeur vers la premiÃ¨re liste chaÃ®nÃ©e.
 * @param liste2 [E] La deuxiÃ¨me liste chaÃ®nÃ©e Ã  concatÃ©ner.
 * @return La nouvelle liste chaÃ®nÃ©e rÃ©sultant de la concatÃ©nation. Renvoie `NULL` en cas d'erreur mÃ©moire.
 */
void LCDPDNNN_concatener(LCDPDNNN_ListeChaineeDePileDeNNN *liste1, LCDPDNNN_ListeChaineeDePileDeNNN liste2);

/**
 * @brief Inverse l'ordre des nÅuds dans une liste chaÃ®nÃ©e de piles.
 * 
 * @param uneliste [E/S] Pointeur vers la liste chaÃ®nÃ©e Ã  inverser.
 * @return La nouvelle tÃªte de la liste inversÃ©e.
 */
void LCDPDNNN_inverser(LCDPDNNN_ListeChaineeDePileDeNNN *uneliste);

/**
 * @brief Effectue une copie profonde d'une liste chaÃ®nÃ©e.
 * 
 * @param uneliste [E] La liste chaÃ®nÃ©e Ã  copier.
 * @return La nouvelle liste chaÃ®nÃ©e contenant les mÃªmes valeurs que la liste source. 
 *         Renvoie `NULL` si une erreur mÃ©moire survient pendant l'allocation.
 */
LCDPDNNN_ListeChaineeDePileDeNNN LCDPDNNN_copier(LCDPDNNN_ListeChaineeDePileDeNNN uneliste);

#endif
