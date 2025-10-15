/**
 * @file Labyrinthe.h
 * @brief Gestion des labyrinthes, leurs caractéristiques et leurs opérations.
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
 * @brief Représente un labyrinthe avec ses propriétés et liaisons.
 * 
 * Contient les informations suivantes :
 * - `entree` : Case et direction d'entrée du labyrinthe.
 * - `sortie` : Case et direction de sortie du labyrinthe.
 * - `largeurLabyrinthe` : Largeur du labyrinthe.
 * - `liaisonsCases` : Matrice d'adjacence représentant les liaisons entre les cases.
 */
typedef struct LAB_Labyrinthe {
    CD_CaseEtDirection entree; 
    CD_CaseEtDirection sortie;
    unsigned int largeur; 
    MDA_MatriceDAdjacence liaisonsCases; 
} LAB_Labyrinthe;


/**
 * @brief Initialise un labyrinthe avec ses caractéristiques principales.
 * @param largeurLabyrinthe [E] Largeur du labyrinthe.
 * @param entree [E] Case d'entrée.
 * @param sortie [E] Case de sortie.
 * @param directionEntree [E] Direction à l'entrée.
 * @param directionSortie [E] Direction à la sortie.
 * @return Le labyrinthe initialisé.
 * @pre 
 *   - `entree != sortie`
 *   - `entree` et `sortie` doivent être sur la bordure.
 *   - `entree` et `sortie` <= `largeur(labyrinthe)²`
 */
LAB_Labyrinthe LAB_labyrinthe(unsigned int largeurLabyrinthe, unsigned int entree, unsigned int sortie, Direction directionEntree, Direction directionSortie);

/**
 * @brief Casse un mur entre deux cases pour les relier.
 * @param laby [E/S] Pointeur vers le labyrinthe.
 * @param case1 [E] Première case.
 * @param case2 [E] Deuxième case.
 * @pre 
 *   - `case1 != case2`
 *   - `case1` et `case2` doivent être inférieures à `largeur(labyrinthe)²`.
 *   - La liaison entre `case1` et `case2` ne doit pas déjà exister.
 */
void LAB_casserMur(LAB_Labyrinthe* laby, unsigned int case1, unsigned int case2);

/**
 * @brief Retourne la largeur du labyrinthe.
 * @param laby [E] Le labyrinthe.
 * @return La largeur du labyrinthe.
 */
int LAB_largeur(LAB_Labyrinthe laby);

/**
 * @brief Retourne la case d'entrée du labyrinthe.
 * @param laby [E] Le labyrinthe.
 * @return La case d'entrée.
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
 * @param uneCase [E] La case concernée.
 * @return Un ensemble de directions possibles.
 * @pre `uneCase` doit être inférieure à `largeur(labyrinthe)²`.
 */
EDD_EnsembleDeDirection LAB_directionsPossibles(LAB_Labyrinthe laby, unsigned int uneCase);

/**
 * @brief Retourne les cases accessibles depuis une case donnée.
 * @param laby [E] Le labyrinthe.
 * @param uneCase [E] La case concernée.
 * @return Un ensemble de cases accessibles.
 * @pre `uneCase` doit être inférieure à `largeur(labyrinthe)²`.
 */
EDNNN_EnsembleDeNNN LAB_casesAccessibles(LAB_Labyrinthe laby, unsigned int uneCase);

/**
 * @brief Retourne la case atteinte depuis une case donnée et une direction spécifique.
 * @param laby [E] Le labyrinthe.
 * @param uneCase [E] La case de départ.
 * @param saDirection [E] La direction.
 * @return La case atteinte.
 * @pre La direction spécifiée doit être valide pour la case donnée.
 */
unsigned int LAB_caseDestination(LAB_Labyrinthe laby, unsigned int uneCase, Direction saDirection);

/**
 * @brief Retourne les cases adjacentes à une case donnée.
 * @param laby [E] Le labyrinthe.
 * @param uneCase [E] La case concernée.
 * @return Un ensemble de cases adjacentes.
 * @pre `uneCase` doit être inférieure à `largeur(labyrinthe)²`.
 */
EDNNN_EnsembleDeNNN LAB_casesAdjacentes(LAB_Labyrinthe laby, unsigned int uneCase);

/**
 * @brief Retourne les cases non accessibles depuis une case donnée.
 * @param laby [E] Le labyrinthe.
 * @param uneCase [E] La case concernée.
 * @return Un ensemble de cases non accessibles.
 * @pre `uneCase` doit être inférieure à `largeur(labyrinthe)²`.
 */
EDNNN_EnsembleDeNNN LAB_casesNonAccesbiles(LAB_Labyrinthe laby, unsigned int uneCase);

/**
 * @brief Retourne les directions d'entrée et de sortie du labyrinthe.
 * @param laby [E] Le labyrinthe.
 * @param directionEntree [E/S] Pointeur pour recevoir la direction d'entrée.
 * @param directionSortie [E/S] Pointeur pour recevoir la direction de sortie.
 */
void LAB_DirectionEntreeEtSortie(LAB_Labyrinthe laby, Direction* directionEntree, Direction* directionSortie);

#endif
