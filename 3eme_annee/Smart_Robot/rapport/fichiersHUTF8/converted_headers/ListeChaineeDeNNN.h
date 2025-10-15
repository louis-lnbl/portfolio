/**
 * @file ListeChaineeDeNNN.h
 * @brief Gestion des listes chaÃ®nÃ©es contenant des Ã©lÃ©ments de type entier non signÃ©.
 */

#ifndef LISTECHAINEEDENNN
#define LISTECHAINEEDENNN

#include <stdbool.h> 
#include <stddef.h>  
#include <assert.h>

/**
 * @struct LCDNNN_Noeud
 * @brief ReprÃ©sente un nÅud d'une liste chaÃ®nÃ©e d'entiers non signÃ©s.
 * 
 * Chaque nÅud contient :
 * - un Ã©lÃ©ment de type `unsigned int` (`element`).
 * - un pointeur vers le nÅud suivant (`listeSuivante`).
 */
typedef struct LCDNNN_Noeud {
    unsigned int element;              
    struct LCDNNN_Noeud *listeSuivante; 
} LCDNNN_Noeud;

/**
 * @typedef LCDNNN_ListeChaineeDeNNN
 * @brief Type reprÃ©sentant une liste chaÃ®nÃ©e d'entiers non signÃ©s.
 */
typedef LCDNNN_Noeud* LCDNNN_ListeChaineeDeNNN;


#define LCDNNN_ERREUR_MEMOIRE 1
/**
 * @brief CrÃ©e une liste chaÃ®nÃ©e vide.
 * @return Une liste chaÃ®nÃ©e vide.
 */
LCDNNN_ListeChaineeDeNNN LCDNNN_listeVide();

/**
 * @brief VÃ©rifie si une liste chaÃ®nÃ©e est vide.
 * @param uneListe [E] La liste chaÃ®nÃ©e Ã  vÃ©rifier.
 * @return `true` si la liste est vide, `false` sinon.
 */
bool LCDNNN_estVide(LCDNNN_ListeChaineeDeNNN uneListe);

/**
 * @brief Ajoute un Ã©lÃ©ment Ã  la tÃªte de la liste chaÃ®nÃ©e.
 * @param uneListe [E/S] Pointeur vers la liste chaÃ®nÃ©e.
 * @param element [E] L'Ã©lÃ©ment Ã  ajouter (de type `unsigned int`).
 */
void LCDNNN_ajouter(LCDNNN_ListeChaineeDeNNN *uneListe, unsigned int element);

/**
 * @brief Obtient l'Ã©lÃ©ment stockÃ© dans le premier nÅud de la liste.
 * @param uneListe [E] La liste chaÃ®nÃ©e.
 * @return L'Ã©lÃ©ment du premier nÅud (de type `unsigned int`).
 * @pre La liste ne doit pas Ãªtre vide.
 */
unsigned int LCDNNN_obtenirElement(LCDNNN_ListeChaineeDeNNN uneListe); /* assert : estVide(uneListe) */

/**
 * @brief Remplace l'Ã©lÃ©ment du premier nÅud de la liste.
 * @param uneListe [E/S] Pointeur vers la liste chaÃ®nÃ©e.
 * @param element [E] Le nouvel Ã©lÃ©ment Ã  stocker (de type `unsigned int`).
 * @pre La liste ne doit pas Ãªtre vide.
 */
void LCDNNN_fixerElement(LCDNNN_ListeChaineeDeNNN *uneListe, unsigned int element); /* assert : estVide(uneListe) */

/**
 * @brief Obtient la liste chaÃ®nÃ©e suivante.
 * @param uneListe [E] La liste chaÃ®nÃ©e.
 * @return La liste chaÃ®nÃ©e suivante.
 * @pre La liste ne doit pas Ãªtre vide.
 */
LCDNNN_ListeChaineeDeNNN LCDNNN_obtenirListeSuivante(LCDNNN_ListeChaineeDeNNN uneListe); /* assert : estVide(uneListe) */

/**
 * @brief Fixe le nÅud suivant de la liste chaÃ®nÃ©e.
 * @param uneListe [E/S] Pointeur vers la liste chaÃ®nÃ©e.
 * @param nelleSuite [E] La nouvelle liste Ã  placer en tant que suivante.
 * @pre La liste ne doit pas Ãªtre vide.
 */

void LCDNNN_fixerListeSuivante(LCDNNN_ListeChaineeDeNNN *uneListe, LCDNNN_ListeChaineeDeNNN nelleSuite);  /* assert : estVide(uneListe) */

/**
 * @brief Supprime le premier nÅud de la liste chaÃ®nÃ©e.
 * @param uneListe [E/S] Pointeur vers la liste chaÃ®nÃ©e.
 * @pre La liste ne doit pas Ãªtre vide.
 */
void LCDNNN_supprimerTete(LCDNNN_ListeChaineeDeNNN *uneListe); /* assert : estVide(uneListe) */

/**
 * @brief Supprime tous les nÅuds de la liste chaÃ®nÃ©e.
 * @param uneListe [E/S] Pointeur vers la liste chaÃ®nÃ©e.
 */
void LCDNNN_supprimer(LCDNNN_ListeChaineeDeNNN *uneListe);

/**
 * @brief ConcatÃ¨ne deux listes chaÃ®nÃ©es de piles.
 * 
 * @param liste1 [E] Pointeur vers la premiÃ¨re liste chaÃ®nÃ©e.
 * @param liste2 [E] La deuxiÃ¨me liste chaÃ®nÃ©e Ã  concatÃ©ner.
 * @return La nouvelle liste chaÃ®nÃ©e rÃ©sultant de la concatÃ©nation. Renvoie `NULL` en cas d'erreur mÃ©moire.
 */
void LCDNNN_concatener(LCDNNN_ListeChaineeDeNNN *liste1, LCDNNN_ListeChaineeDeNNN liste2);

/**
 * @brief Inverse l'ordre des nÅuds dans une liste chaÃ®nÃ©e de piles.
 * 
 * @param uneliste [E/S] Pointeur vers la liste chaÃ®nÃ©e Ã  inverser.
 * @return La nouvelle tÃªte de la liste inversÃ©e.
 */
void LCDNNN_inverser(LCDNNN_ListeChaineeDeNNN *uneliste);

/**
 * @brief Effectue une copie profonde d'une liste chaÃ®nÃ©e.
 * 
 * @param uneliste [E] La liste chaÃ®nÃ©e Ã  copier.
 * @return La nouvelle liste chaÃ®nÃ©e contenant les mÃªmes valeurs que la liste source. 
 *         Renvoie `NULL` si une erreur mÃ©moire survient pendant l'allocation.
 */
LCDNNN_ListeChaineeDeNNN LCDNNN_copier(LCDNNN_ListeChaineeDeNNN uneliste);

#endif
