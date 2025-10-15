/**
 * @file Labyrinthe.h
 * @brief Gestion des labyrinthes, leurs caractÃ©ristiques et leurs opÃ©rations.
 */

#ifndef LABYRINTHE
#define LABYRINTHE

#include <errno.h>
#include <assert.h>
#include "Direction.h"
#include "EnsembleDeNNN.h"
#include "EnsembleDeDirection.h"
#include "MatriceDAdjacence.h"
#include "caseEtDirection.h"
#include "ListeChaineeDeNNN.h"

/**
 * @struct LAB_Labyrinthe
 * @brief ReprÃ©sente un labyrinthe avec ses propriÃ©tÃ©s et liaisons.
 * 
 * Contient les informations suivantes :
 * - `entree` : Case et direction d'entrÃ©e du labyrinthe.
 * - `sortie` : Case et direction de sortie du labyrinthe.
 * - `largeurLabyrinthe` : Largeur du labyrinthe.
 * - `liaisonsCases` : Matrice d'adjacence reprÃ©sentant les liaisons entre les cases.
 */
typedef struct LAB_Labyrinthe {
    CD_CaseEtDirection entree; 
    CD_CaseEtDirection sortie;
    unsigned int largeur; 
    MDA_MatriceDAdjacence liaisonsCases; 
} LAB_Labyrinthe;


/**
 * @brief Initialise un labyrinthe avec ses caractÃ©ristiques principales.
 * @param largeurLabyrinthe [E] Largeur du labyrinthe.
 * @param entree [E] Case d'entrÃ©e.
 * @param sortie [E] Case de sortie.
 * @param directionEntree [E] Direction Ã  l'entrÃ©e.
 * @param directionSortie [E] Direction Ã  la sortie.
 * @return Le labyrinthe initialisÃ©.
 * @pre 
 *   - `entree != sortie`
 *   - `entree` et `sortie` doivent Ãªtre sur la bordure.
 *   - `entree` et `sortie` <= `largeur(labyrinthe)Â²`
 */
LAB_Labyrinthe LAB_labyrinthe(unsigned int largeurLabyrinthe, unsigned int entree, unsigned int sortie, Direction directionEntree, Direction directionSortie);

/**
 * @brief Casse un mur entre deux cases pour les relier.
 * @param laby [E/S] Pointeur vers le labyrinthe.
 * @param case1 [E] PremiÃ¨re case.
 * @param case2 [E] DeuxiÃ¨me case.
 * @pre 
 *   - `case1 != case2`
 *   - `case1` et `case2` doivent Ãªtre infÃ©rieures Ã  `largeur(labyrinthe)Â²`.
 *   - La liaison entre `case1` et `case2` ne doit pas dÃ©jÃ  exister.
 */
void LAB_casserMur(LAB_Labyrinthe* laby, unsigned int case1, unsigned int case2);

/**
 * @brief Retourne la largeur du labyrinthe.
 * @param laby [E] Le labyrinthe.
 * @return La largeur du labyrinthe.
 */
int LAB_largeur(LAB_Labyrinthe laby);

/**
 * @brief Retourne la case d'entrÃ©e du labyrinthe.
 * @param laby [E] Le labyrinthe.
 * @return La case d'entrÃ©e.
 */
CD_CaseEtDirection LAB_caseDEntree(LAB_Labyrinthe laby);

/**
 * @brief Retourne la case de sortie du labyrinthe.
 * @param laby [E] Le labyrinthe.
 * @return La case de sortie.
 */
CD_CaseEtDirection LAB_caseDeSortie(LAB_Labyrinthe laby);

/**
 * @brief Retourne les directions possibles depuis une case.
 * @param laby [E] Le labyrinthe.
 * @param uneCase [E] La case concernÃ©e.
 * @return Un ensemble de directions possibles.
 * @pre `uneCase` doit Ãªtre infÃ©rieure Ã  `largeur(labyrinthe)Â²`.
 */
EDD_EnsembleDeDirection LAB_directionsPossibles(LAB_Labyrinthe laby, unsigned int uneCase);

/**
 * @brief Retourne les cases accessibles depuis une case donnÃ©e.
 * @param laby [E] Le labyrinthe.
 * @param uneCase [E] La case concernÃ©e.
 * @return Un ensemble de cases accessibles.
 * @pre `uneCase` doit Ãªtre infÃ©rieure Ã  `largeur(labyrinthe)Â²`.
 */
EDNNN_EnsembleDeNNN LAB_casesAccessibles(LAB_Labyrinthe laby, unsigned int uneCase);

/**
 * @brief Retourne la case atteinte depuis une case donnÃ©e et une direction spÃ©cifique.
 * @param laby [E] Le labyrinthe.
 * @param uneCase [E] La case de dÃ©part.
 * @param saDirection [E] La direction.
 * @return La case atteinte.
 * @pre La direction spÃ©cifiÃ©e doit Ãªtre valide pour la case donnÃ©e.
 */
unsigned int LAB_caseDestination(LAB_Labyrinthe laby, unsigned int uneCase, Direction saDirection);

/**
 * @brief Retourne les cases adjacentes Ã  une case donnÃ©e.
 * @param laby [E] Le labyrinthe.
 * @param uneCase [E] La case concernÃ©e.
 * @return Un ensemble de cases adjacentes.
 * @pre `uneCase` doit Ãªtre infÃ©rieure Ã  `largeur(labyrinthe)Â²`.
 */
EDNNN_EnsembleDeNNN LAB_casesAdjacentes(LAB_Labyrinthe laby, unsigned int uneCase);

/**
 * @brief Retourne les cases non accessibles depuis une case donnÃ©e.
 * @param laby [E] Le labyrinthe.
 * @param uneCase [E] La case concernÃ©e.
 * @return Un ensemble de cases non accessibles.
 * @pre `uneCase` doit Ãªtre infÃ©rieure Ã  `largeur(labyrinthe)Â²`.
 */
EDNNN_EnsembleDeNNN LAB_casesNonAccesbiles(LAB_Labyrinthe laby, unsigned int uneCase);

/**
 * @brief Retourne les directions d'entrÃ©e et de sortie du labyrinthe.
 * @param laby [E] Le labyrinthe.
 * @param directionEntree [E/S] Pointeur pour recevoir la direction d'entrÃ©e.
 * @param directionSortie [E/S] Pointeur pour recevoir la direction de sortie.
 */
void LAB_DirectionEntreeEtSortie(LAB_Labyrinthe laby, Direction* directionEntree, Direction* directionSortie);

#endif
