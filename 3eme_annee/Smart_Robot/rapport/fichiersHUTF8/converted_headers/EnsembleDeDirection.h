/**
 * @file EnsembleDeDirection.h
 * @brief DÃ©finition des fonctions et structures pour manipuler un ensemble de directions.
 */

#ifndef ENSEMBLEDEDIRECTION
#define ENSEMBLEDEDIRECTION

#include <stdbool.h>
#include "Direction.h"
#include "ListeChaineeDeDirection.h"

/**
 * @struct EDD_EnsembleDeDirection
 *  @brief ReprÃ©sente un ensemble de directions utilisant une liste chaÃ®nÃ©e.
 * 
 * Cette structure contient :
 * - `lesElements` : Une liste chaÃ®nÃ©e des directions prÃ©sentes dans l'ensemble.
 * - `nbElements` : Le nombre de directions dans l'ensemble.
 */
typedef struct EDD_EnsembleDeDirection {
    LCDD_ListeChaineeDeDirection lesElements;
    unsigned int nbElements;
} EDD_EnsembleDeDirection;

/**
 * @brief Initialise un ensemble de directions vide.
 * @return Un ensemble de directions vide.
 * @pre Aucune.
 */
EDD_EnsembleDeDirection EDD_ensemble();

/**
 * @brief Ajoute une direction Ã  un ensemble.
 * @param unEnsemble [E/S] Pointeur vers l'ensemble oÃ¹ ajouter la direction.
 * @param direction [E] La direction Ã  ajouter.
 * @pre La direction ne doit pas dÃ©jÃ  Ãªtre prÃ©sente dans l'ensemble.
 */
void EDD_ajouter(EDD_EnsembleDeDirection *unEnsemble, Direction direction);

/**
 * @brief Retire une direction d'un ensemble.
 * @param unEnsemble [E/S] Pointeur vers l'ensemble dont retirer la direction.
 * @param direction [E] La direction Ã  retirer.
 * @pre La direction doit Ãªtre prÃ©sente dans l'ensemble.
 */
void EDD_retirer(EDD_EnsembleDeDirection *unEnsemble, Direction direction);

/**
 * @brief VÃ©rifie si une direction est prÃ©sente dans un ensemble.
 * @param unEnsemble [E] L'ensemble Ã  vÃ©rifier.
 * @param direction [E] La direction Ã  rechercher.
 * @return `true` si la direction est prÃ©sente, `false` sinon.
 * @pre Aucune.
 */
bool EDD_estPresent(EDD_EnsembleDeDirection unEnsemble, Direction direction);

/**
 * @brief Retourne le nombre de directions dans un ensemble.
 * @param unEnsemble [E] L'ensemble Ã  analyser.
 * @return Le nombre de directions dans l'ensemble.
 * @pre Aucune.
 */
unsigned int EDD_cardinalite(EDD_EnsembleDeDirection unEnsemble);

/**
 * @brief Calcule l'union de deux ensembles de directions.
 * @param e1 [E] Le premier ensemble.
 * @param e2 [E] Le deuxiÃ¨me ensemble.
 * @return Un nouvel ensemble contenant l'union des deux ensembles.
 * @pre Aucune.
 */
EDD_EnsembleDeDirection EDD_unionEnsemble(EDD_EnsembleDeDirection e1, EDD_EnsembleDeDirection e2);

/**
 * @brief Calcule l'intersection de deux ensembles de directions.
 * @param e1 [E] Le premier ensemble.
 * @param e2 [E] Le deuxiÃ¨me ensemble.
 * @return Un nouvel ensemble contenant l'intersection des deux ensembles.
 * @pre Aucune.
 */
EDD_EnsembleDeDirection EDD_intersection(EDD_EnsembleDeDirection e1, EDD_EnsembleDeDirection e2);

/**
 * @brief Calcule la soustraction de deux ensembles de directions.
 * @param e1 [E] Le premier ensemble.
 * @param e2 [E] Le deuxiÃ¨me ensemble.
 * @return Un nouvel ensemble contenant les Ã©lÃ©ments de `e1` qui ne sont pas dans `e2`.
 * @pre Aucune.
 */
EDD_EnsembleDeDirection EDD_soustraction(EDD_EnsembleDeDirection e1, EDD_EnsembleDeDirection e2);


/**
 * @brief Donne le Premier Ã©lÃ©ment qui se trouve dans l'ensemble
 * @param [e] un ensemble.
 * @return La premiÃ¨re direction qui se trouve dans l'ensemble.
 * @pre L'ensemble n'est pas vide.
 */
Direction EDD_obtenirPremierElement(EDD_EnsembleDeDirection unEnsemble);

#endif


