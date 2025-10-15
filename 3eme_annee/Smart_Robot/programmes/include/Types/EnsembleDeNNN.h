/**
 * @file EnsembleDeNNN.h
 * @brief Définition des fonctions et structures pour manipuler un ensemble de naturels non nuls.
 */

#ifndef ENSEMBLEDENNN
#define ENSEMBLEDENNN

#include <stdbool.h>
#include "ListeChaineeDeNNN.h"

/**
 * @struct EDNNN_EnsembleDeNNN
 * @brief Représente un ensemble de naturels non nuls.
 * 
 * Cette structure contient :
 * - `lesElements` : Une liste chaînée des naturels non nuls présents dans l'ensemble.
 * - `nbElements` : Le nombre d'éléments dans l'ensemble.
 */
typedef struct EDNNN_EnsembleDeNNN {
    LCDNNN_ListeChaineeDeNNN lesElements; 
    unsigned int nbElements;
} EDNNN_EnsembleDeNNN;

/**
 * @brief Initialise un ensemble de naturels non nuls vide.
 * @return Un ensemble vide.
 * @pre Aucune.
 */
EDNNN_EnsembleDeNNN EDNNN_ensemble();

/**
 * @brief Ajoute un élément à un ensemble.
 * @param unEnsemble [E/S] Pointeur vers l'ensemble où ajouter l'élément.
 * @param element [E] L'élément naturel non nul à ajouter.
 * @pre L'élément ne doit pas déjà être présent dans l'ensemble.
 */
void EDNNN_ajouter(EDNNN_EnsembleDeNNN *unEnsemble, unsigned int element);

/**
 * @brief Retire un élément d'un ensemble.
 * @param unEnsemble [E/S] Pointeur vers l'ensemble dont retirer l'élément.
 * @param element [E] L'élément naturel non nul à retirer.
 * @pre L'élément doit être présent dans l'ensemble.
 */
void EDNNN_retirer(EDNNN_EnsembleDeNNN *unEnsemble, unsigned int element);

/**
 * @brief Vérifie si un élément est présent dans un ensemble.
 * @param unEnsemble [E] L'ensemble à vérifier.
 * @param element [E] L'élément naturel non nul à rechercher.
 * @return `true` si l'élément est présent, `false` sinon.
 * @pre Aucune.
 */
bool EDNNN_estPresent(EDNNN_EnsembleDeNNN unEnsemble, unsigned int element);

/**
 * @brief Retourne le nombre d'éléments dans un ensemble.
 * @param unEnsemble [E] L'ensemble à analyser.
 * @return Le nombre d'éléments dans l'ensemble.
 * @pre Aucune.
 */
unsigned int EDNNN_cardinalite(EDNNN_EnsembleDeNNN unEnsemble);

/**
 * @brief Calcule l'union de deux ensembles.
 * @param e1 [E] Le premier ensemble.
 * @param e2 [E] Le deuxième ensemble.
 * @return Un nouvel ensemble contenant l'union des deux ensembles.
 * @pre Aucune.
 */
EDNNN_EnsembleDeNNN EDNNN_unionEnsemble(EDNNN_EnsembleDeNNN e1, EDNNN_EnsembleDeNNN e2);

/**
 * @brief Calcule l'intersection de deux ensembles.
 * @param e1 [E] Le premier ensemble.
 * @param e2 [E] Le deuxième ensemble.
 * @return Un nouvel ensemble contenant l'intersection des deux ensembles.
 * @pre Aucune.
 */
EDNNN_EnsembleDeNNN EDNNN_intersection(EDNNN_EnsembleDeNNN e1, EDNNN_EnsembleDeNNN e2);

/**
 * @brief Calcule la soustraction de deux ensembles.
 * @param e1 [E] Le premier ensemble.
 * @param e2 [E] Le deuxième ensemble.
 * @return Un nouvel ensemble contenant les éléments de `e1` qui ne sont pas dans `e2`.
 * @pre Aucune.
 */
EDNNN_EnsembleDeNNN EDNNN_soustraction(EDNNN_EnsembleDeNNN e1, EDNNN_EnsembleDeNNN e2);

/**
 * @brief Donne le Premier élément qui se trouve dans l'ensemble
 * @param [e] un ensemble.
 * @return Le premier NNN qui se trouve dans l'ensemble.
 * @pre L'ensemble n'est pas vide.
 */
unsigned int EDNNN_obtenirPremierElement(EDNNN_EnsembleDeNNN unEnsemble);

#endif
