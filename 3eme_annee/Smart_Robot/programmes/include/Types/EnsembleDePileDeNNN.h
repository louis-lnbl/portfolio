/**
 * @file EnsembleDePileDeNNN.h
 * @brief Définition des fonctions et structures pour manipuler un ensemble de piles de naturels non nuls.
 */

#ifndef ENSEMBLEDEPILEDENNN
#define ENSEMBLEDEPILEDENNN

#include <stdbool.h>
#include "ListeChaineeDePileDeNNN.h"

/**
 * @struct EDPDNNN_EnsembleDePileDeNNN
 * @brief Représente un ensemble de piles de naturels non nuls.
 * 
 * Cette structure contient :
 * - `lesElements` : Une liste chaînée des piles de naturels non nuls.
 * - `nbElements` : Le nombre de piles dans l'ensemble.
 */
typedef struct EDPDNNN_EnsembleDePileDeNNN {
    LCDPDNNN_ListeChaineeDePileDeNNN lesElements; 
    unsigned int nbElements; 
} EDPDNNN_EnsembleDePileDeNNN;

/**
 * @brief Initialise un ensemble de piles de naturels non nuls vide.
 * @return Un ensemble vide.
 * @pre Aucune.
 */
EDPDNNN_EnsembleDePileDeNNN EDPDNNN_ensemble();

/**
 * @brief Ajoute une pile à un ensemble.
 * @param unEnsemble [E/S] Pointeur vers l'ensemble où ajouter la pile.
 * @param element [E] La pile de naturels non nuls à ajouter.
 * @pre La pile ne doit pas déjà être présente dans l'ensemble.
 */
void EDPDNNN_ajouter(EDPDNNN_EnsembleDePileDeNNN *unEnsemble, PDNNN_PileDeNNN element);

/**
 * @brief Retire une pile d'un ensemble.
 * @param unEnsemble [E/S] Pointeur vers l'ensemble dont retirer la pile.
 * @param element [E] La pile de naturels non nuls à retirer.
 * @pre La pile doit être présente dans l'ensemble.
 */
void EDPDNNN_retirer(EDPDNNN_EnsembleDePileDeNNN *unEnsemble, PDNNN_PileDeNNN element);

/**
 * @brief Vérifie si une pile est présente dans un ensemble.
 * @param unEnsemble [E] L'ensemble à vérifier.
 * @param element [E] La pile de naturels non nuls à rechercher.
 * @return `true` si la pile est présente, `false` sinon.
 * @pre Aucune.
 */
bool EDPDNNN_estPresent(EDPDNNN_EnsembleDePileDeNNN unEnsemble, PDNNN_PileDeNNN element);

/**
 * @brief Retourne le nombre de piles dans un ensemble.
 * @param unEnsemble [E] L'ensemble à analyser.
 * @return Le nombre de piles dans l'ensemble.
 * @pre Aucune.
 */
unsigned int EDPDNNN_cardinalite(EDPDNNN_EnsembleDePileDeNNN unEnsemble);

/**
 * @brief Calcule l'union de deux ensembles.
 * @param e1 [E] Le premier ensemble.
 * @param e2 [E] Le deuxième ensemble.
 * @return Un nouvel ensemble contenant l'union des deux ensembles.
 * @pre Aucune.
 */
EDPDNNN_EnsembleDePileDeNNN EDPDNNN_unionEnsemble(EDPDNNN_EnsembleDePileDeNNN e1, EDPDNNN_EnsembleDePileDeNNN e2);

/**
 * @brief Calcule l'intersection de deux ensembles.
 * @param e1 [E] Le premier ensemble.
 * @param e2 [E] Le deuxième ensemble.
 * @return Un nouvel ensemble contenant l'intersection des deux ensembles.
 * @pre Aucune.
 */
EDPDNNN_EnsembleDePileDeNNN EDPDNNN_intersection(EDPDNNN_EnsembleDePileDeNNN e1, EDPDNNN_EnsembleDePileDeNNN e2);

/**
 * @brief Calcule la soustraction de deux ensembles.
 * @param e1 [E] Le premier ensemble.
 * @param e2 [E] Le deuxième ensemble.
 * @return Un nouvel ensemble contenant les éléments de `e1` qui ne sont pas dans `e2`.
 * @pre Aucune.
 */
EDPDNNN_EnsembleDePileDeNNN EDPDNNN_soustraction(EDPDNNN_EnsembleDePileDeNNN e1, EDPDNNN_EnsembleDePileDeNNN e2);

/**
 * @brief Donne le Premier élément qui se trouve dans l'ensemble
 * @param [e] un ensemble.
 * @return La première pile de NNN qui se trouve dans l'ensemble.
 * @pre L'ensemble n'est pas vide.
 */
PDNNN_PileDeNNN EDPDNNN_obtenirPremierElement(EDPDNNN_EnsembleDePileDeNNN unEnsemble);

/**
 * @brief Crée une copie profonde d'un ensemble de piles.
 * 
 * @param unEnsemble [E] L'ensemble de piles source à copier.
 * @return Un nouvel ensemble contenant les mêmes piles que l'ensemble source. Renvoie `NULL`
 *         en cas d'erreur mémoire ou si la copie ne peut pas être effectuée.
 */
EDPDNNN_EnsembleDePileDeNNN EDPDNNN_copier(EDPDNNN_EnsembleDePileDeNNN unEnsemble);
#endif
