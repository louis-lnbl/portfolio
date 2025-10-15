/**
 * @file PileDeNNN.h
 * @brief Gestion des piles d'entiers non négatifs (NNN).
 */

#ifndef PILEDENNN
#define PILEDENNN

#include <stdbool.h>                  
#include "ListeChaineeDeNNN.h"        

/**
 * @typedef PDNNN_PileDeNNN
 * @brief Alias pour une liste chaînée utilisée comme pile.
 */
typedef LCDNNN_ListeChaineeDeNNN PDNNN_PileDeNNN;

/**
 * @brief Créé une pile vide.
 * 
 * @return Une pile vide de type `PDNNN_PileDeNNN`.
 */
PDNNN_PileDeNNN PDNNN_pile();
	

/**
 * @brief Vérifie si une pile est vide.
 * 
 * @param pile [E] La pile à vérifier.
 * @return `true` si la pile est vide, `false` sinon.
 */
bool PDNNN_estVide(PDNNN_PileDeNNN pile);

/**
 * @brief Ajoute un élément au sommet de la pile.
 * 
 * @param pile [E] Un pointeur vers la pile.
 * @param element [E] L'élément à empiler.
 */
void PDNNN_empiler(PDNNN_PileDeNNN *pile, unsigned int element);

/**
 * @brief Retire l'élément au sommet de la pile.
 * 
 * @param pile [E] Un pointeur vers la pile.
 * @pre la pile doit être non vide.
 */
void PDNNN_depiler(PDNNN_PileDeNNN *pile);

/**
 * @brief Récupère l'élément au sommet de la pile sans le retirer.
 * 
 * @param pile [E] La pile à interroger.
 * @return L'élément au sommet de la pile.
 * @pre la pile doit être non vide.
 */
unsigned int PDNNN_obtenirElement(PDNNN_PileDeNNN pile);

/**
 * @brief Calcule le nombre d'éléments dans la pile.
 * 
 * @param pile [E] La pile à interroger.
 * @return Le nombre d'éléments dans la pile.
 */
unsigned int PDNNN_longueur(PDNNN_PileDeNNN pile);

/**
 * @brief Vérifie que l'element est dans pile
 * 
 * @param pile [E] La pile à interroger.
 * @return L'élément à chercher.
 */
bool PDNNN_estPresent(PDNNN_PileDeNNN pile, unsigned int e);

/**
 * @brief Crée une copie indépendante d'une pile donnée.
 * 
 * @param p [E] La pile source à copier.
 * @return Une nouvelle pile identique à la pile source. Renvoie `NULL` en cas d'erreur mémoire.
 */
PDNNN_PileDeNNN PDNNN_copier(PDNNN_PileDeNNN p);

/**
 * @brief Compare deux piles pour déterminer si elles sont égales.
 * 
 * @param p1 [E] La première pile à comparer.
 * @param p2 [E] La deuxième pile à comparer.
 * @return `true` si les deux piles sont égales, `false` sinon.
 */
bool PDNNN_egale(PDNNN_PileDeNNN p1, PDNNN_PileDeNNN p2);
#endif

