/**
 * @file EnsembleDeNNN.h
 * @brief DÃ©finition des fonctions et structures pour manipuler un ensemble de naturels non nuls.
 */

#ifndef ENSEMBLEDENNN
#define ENSEMBLEDENNN

#include <stdbool.h>
#include "ListeChaineeDeNNN.h"

/**
 * @struct EDNNN_EnsembleDeNNN
 * @brief ReprÃ©sente un ensemble de naturels non nuls.
 * 
 * Cette structure contient :
 * - `lesElements` : Une liste chaÃ®nÃ©e des naturels non nuls prÃ©sents dans l'ensemble.
 * - `nbElements` : Le nombre d'Ã©lÃ©ments dans l'ensemble.
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
 * @brief Ajoute un Ã©lÃ©ment Ã  un ensemble.
 * @param unEnsemble [E/S] Pointeur vers l'ensemble oÃ¹ ajouter l'Ã©lÃ©ment.
 * @param element [E] L'Ã©lÃ©ment naturel non nul Ã  ajouter.
 * @pre L'Ã©lÃ©ment ne doit pas dÃ©jÃ  Ãªtre prÃ©sent dans l'ensemble.
 */
void EDNNN_ajouter(EDNNN_EnsembleDeNNN *unEnsemble, unsigned int element);

/**
 * @brief Retire un Ã©lÃ©ment d'un ensemble.
 * @param unEnsemble [E/S] Pointeur vers l'ensemble dont retirer l'Ã©lÃ©ment.
 * @param element [E] L'Ã©lÃ©ment naturel non nul Ã  retirer.
 * @pre L'Ã©lÃ©ment doit Ãªtre prÃ©sent dans l'ensemble.
 */
void EDNNN_retirer(EDNNN_EnsembleDeNNN *unEnsemble, unsigned int element);

/**
 * @brief VÃ©rifie si un Ã©lÃ©ment est prÃ©sent dans un ensemble.
 * @param unEnsemble [E] L'ensemble Ã  vÃ©rifier.
 * @param element [E] L'Ã©lÃ©ment naturel non nul Ã  rechercher.
 * @return `true` si l'Ã©lÃ©ment est prÃ©sent, `false` sinon.
 * @pre Aucune.
 */
bool EDNNN_estPresent(EDNNN_EnsembleDeNNN unEnsemble, unsigned int element);

/**
 * @brief Retourne le nombre d'Ã©lÃ©ments dans un ensemble.
 * @param unEnsemble [E] L'ensemble Ã  analyser.
 * @return Le nombre d'Ã©lÃ©ments dans l'ensemble.
 * @pre Aucune.
 */
unsigned int EDNNN_cardinalite(EDNNN_EnsembleDeNNN unEnsemble);

/**
 * @brief Calcule l'union de deux ensembles.
 * @param e1 [E] Le premier ensemble.
 * @param e2 [E] Le deuxiÃ¨me ensemble.
 * @return Un nouvel ensemble contenant l'union des deux ensembles.
 * @pre Aucune.
 */
EDNNN_EnsembleDeNNN EDNNN_unionEnsemble(EDNNN_EnsembleDeNNN e1, EDNNN_EnsembleDeNNN e2);

/**
 * @brief Calcule l'intersection de deux ensembles.
 * @param e1 [E] Le premier ensemble.
 * @param e2 [E] Le deuxiÃ¨me ensemble.
 * @return Un nouvel ensemble contenant l'intersection des deux ensembles.
 * @pre Aucune.
 */
EDNNN_EnsembleDeNNN EDNNN_intersection(EDNNN_EnsembleDeNNN e1, EDNNN_EnsembleDeNNN e2);

/**
 * @brief Calcule la soustraction de deux ensembles.
 * @param e1 [E] Le premier ensemble.
 * @param e2 [E] Le deuxiÃ¨me ensemble.
 * @return Un nouvel ensemble contenant les Ã©lÃ©ments de `e1` qui ne sont pas dans `e2`.
 * @pre Aucune.
 */
EDNNN_EnsembleDeNNN EDNNN_soustraction(EDNNN_EnsembleDeNNN e1, EDNNN_EnsembleDeNNN e2);

/**
 * @brief Donne le Premier Ã©lÃ©ment qui se trouve dans l'ensemble
 * @param [e] un ensemble.
 * @return Le premier NNN qui se trouve dans l'ensemble.
 * @pre L'ensemble n'est pas vide.
 */
unsigned int EDNNN_obtenirPremierElement(EDNNN_EnsembleDeNNN unEnsemble);

#endif
