/**
 * @file CaseEtDirection.h
 * @brief Définition du type CD_caseEtDirection et des fonctions associées.
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
    unsigned int laCase; /**< Représente une case dans le labyrinthe. */
    Direction laDirection; /**< Représente une direction associée à la case. */
} CD_CaseEtDirection;

/**
 * @brief Initialise une structure CD_caseEtDirection avec une case et une direction données.
 * @param c [E] La case à associer.
 * @param d [E] La direction à associer.
 * @return Une structure CD_caseEtDirection initialisée.
 * @pre Aucune.
 */
struct CD_CaseEtDirection CD_caseEtDirection(unsigned int c, Direction d);

/**
 * @brief Fixe une nouvelle case dans une structure CD_caseEtDirection existante.
 * @param cd [E/S] Pointeur vers la structure CD_caseEtDirection à modifier.
 * @param c [E] La nouvelle case à associer.
 * @return La structure CD_caseEtDirection modifiée.
 * @pre c <= largeur(labyrinthe)².
 * @note Si `c > largeur(labyrinthe)²`, une assertion échouera.
 */
void CD_fixerCase(CD_CaseEtDirection *cd, unsigned int c); /*assertion: c > largeur(labyrinthe)² */

/**
 * @brief Fixe une nouvelle direction dans une structure CD_caseEtDirection existante.
 * @param cd [E/S] Pointeur vers la structure CD_caseEtDirection à modifier.
 * @param d [E] La nouvelle direction à associer.
 * @return La structure CD_caseEtDirection modifiée.
 * @pre `d` doit être une direction valide définie dans le type `Direction`.
 * @note Si `d` n'est pas dans `Direction`, une assertion échouera.
 */
void CD_fixerDirection(CD_CaseEtDirection *cd, Direction d); /*assertion: d pas dans Direction */

/**
 * @brief Obtient la case associée à une structure CD_caseEtDirection.
 * @param cd [E] La structure CD_caseEtDirection à consulter.
 * @return La case associée (un entier non nul).
 * @pre Aucune.
 */
unsigned int CD_obtenirCase(CD_CaseEtDirection cd);

/**
 * @brief Obtient la direction associée à une structure CD_caseEtDirection.
 * @param cd [E] La structure CD_caseEtDirection à consulter.
 * @return La direction associée.
 * @pre Aucune.
 */
Direction CD_obtenirDirection(CD_CaseEtDirection cd);

#endif
