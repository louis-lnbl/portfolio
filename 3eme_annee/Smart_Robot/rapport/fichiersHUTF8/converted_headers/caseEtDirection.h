/**
 * @file CaseEtDirection.h
 * @brief DÃ©finition du type CD_caseEtDirection et des fonctions associÃ©es.
 */

#ifndef __CASEETDIRECTION__
#define __CASEETDIRECTION__

#include <errno.h>
#include <assert.h>
#include "Direction.h"

/**
 * @typedef CD_CaseEtDirection
 * @brief Structure associant une case et une direction dans un labyrinthe.
 */
typedef struct CD_CaseEtDirection {
    unsigned int laCase; /**< ReprÃ©sente une case dans le labyrinthe. */
    Direction laDirection; /**< ReprÃ©sente une direction associÃ©e Ã  la case. */
} CD_CaseEtDirection;

/**
 * @brief Initialise une structure CD_caseEtDirection avec une case et une direction donnÃ©es.
 * @param c [E] La case Ã  associer.
 * @param d [E] La direction Ã  associer.
 * @return Une structure CD_caseEtDirection initialisÃ©e.
 * @pre Aucune.
 */
struct CD_CaseEtDirection CD_caseEtDirection(unsigned int c, Direction d);

/**
 * @brief Fixe une nouvelle case dans une structure CD_caseEtDirection existante.
 * @param cd [E/S] Pointeur vers la structure CD_caseEtDirection Ã  modifier.
 * @param c [E] La nouvelle case Ã  associer.
 * @return La structure CD_caseEtDirection modifiÃ©e.
 * @pre c <= largeur(labyrinthe)Â².
 * @note Si `c > largeur(labyrinthe)Â²`, une assertion Ã©chouera.
 */
void CD_fixerCase(CD_CaseEtDirection *cd, unsigned int c); /*assertion: c > largeur(labyrinthe)Â² */

/**
 * @brief Fixe une nouvelle direction dans une structure CD_caseEtDirection existante.
 * @param cd [E/S] Pointeur vers la structure CD_caseEtDirection Ã  modifier.
 * @param d [E] La nouvelle direction Ã  associer.
 * @return La structure CD_caseEtDirection modifiÃ©e.
 * @pre `d` doit Ãªtre une direction valide dÃ©finie dans le type `Direction`.
 * @note Si `d` n'est pas dans `Direction`, une assertion Ã©chouera.
 */
void CD_fixerDirection(CD_CaseEtDirection *cd, Direction d); /*assertion: d pas dans Direction */

/**
 * @brief Obtient la case associÃ©e Ã  une structure CD_caseEtDirection.
 * @param cd [E] La structure CD_caseEtDirection Ã  consulter.
 * @return La case associÃ©e (un entier non nul).
 * @pre Aucune.
 */
unsigned int CD_obtenirCase(CD_CaseEtDirection cd);

/**
 * @brief Obtient la direction associÃ©e Ã  une structure CD_caseEtDirection.
 * @param cd [E] La structure CD_caseEtDirection Ã  consulter.
 * @return La direction associÃ©e.
 * @pre Aucune.
 */
Direction CD_obtenirDirection(CD_CaseEtDirection cd);

#endif
