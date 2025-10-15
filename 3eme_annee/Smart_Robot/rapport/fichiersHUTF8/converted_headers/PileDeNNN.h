/**
 * @file PileDeNNN.h
 * @brief Gestion des piles d'entiers non nÃ©gatifs (NNN).
 */

#ifndef PILEDENNN
#define PILEDENNN

#include <stdbool.h>                  
#include "ListeChaineeDeNNN.h"        

/**
 * @typedef PDNNN_PileDeNNN
 * @brief Alias pour une liste chaÃ®nÃ©e utilisÃ©e comme pile.
 */
typedef LCDNNN_ListeChaineeDeNNN PDNNN_PileDeNNN;

/**
 * @brief CrÃ©Ã© une pile vide.
 * 
 * @return Une pile vide de type `PDNNN_PileDeNNN`.
 */
PDNNN_PileDeNNN PDNNN_pile();
	

/**
 * @brief VÃ©rifie si une pile est vide.
 * 
 * @param pile [E] La pile Ã  vÃ©rifier.
 * @return `true` si la pile est vide, `false` sinon.
 */
bool PDNNN_estVide(PDNNN_PileDeNNN pile);

/**
 * @brief Ajoute un Ã©lÃ©ment au sommet de la pile.
 * 
 * @param pile [E] Un pointeur vers la pile.
 * @param element [E] L'Ã©lÃ©ment Ã  empiler.
 */
void PDNNN_empiler(PDNNN_PileDeNNN *pile, unsigned int element);

/**
 * @brief Retire l'Ã©lÃ©ment au sommet de la pile.
 * 
 * @param pile [E] Un pointeur vers la pile.
 * @pre la pile doit Ãªtre non vide.
 */
void PDNNN_depiler(PDNNN_PileDeNNN *pile);

/**
 * @brief RÃ©cupÃ¨re l'Ã©lÃ©ment au sommet de la pile sans le retirer.
 * 
 * @param pile [E] La pile Ã  interroger.
 * @return L'Ã©lÃ©ment au sommet de la pile.
 * @pre la pile doit Ãªtre non vide.
 */
unsigned int PDNNN_obtenirElement(PDNNN_PileDeNNN pile);

/**
 * @brief Calcule le nombre d'Ã©lÃ©ments dans la pile.
 * 
 * @param pile [E] La pile Ã  interroger.
 * @return Le nombre d'Ã©lÃ©ments dans la pile.
 */
unsigned int PDNNN_longueur(PDNNN_PileDeNNN pile);

/**
 * @brief VÃ©rifie que l'element est dans pile
 * 
 * @param pile [E] La pile Ã  interroger.
 * @return L'Ã©lÃ©ment Ã  chercher.
 */
bool PDNNN_estPresent(PDNNN_PileDeNNN pile, unsigned int e);

/**
 * @brief CrÃ©e une copie indÃ©pendante d'une pile donnÃ©e.
 * 
 * @param p [E] La pile source Ã  copier.
 * @return Une nouvelle pile identique Ã  la pile source. Renvoie `NULL` en cas d'erreur mÃ©moire.
 */
PDNNN_PileDeNNN PDNNN_copier(PDNNN_PileDeNNN p);

/**
 * @brief Compare deux piles pour dÃ©terminer si elles sont Ã©gales.
 * 
 * @param p1 [E] La premiÃ¨re pile Ã  comparer.
 * @param p2 [E] La deuxiÃ¨me pile Ã  comparer.
 * @return `true` si les deux piles sont Ã©gales, `false` sinon.
 */
bool PDNNN_egale(PDNNN_PileDeNNN p1, PDNNN_PileDeNNN p2);
#endif

