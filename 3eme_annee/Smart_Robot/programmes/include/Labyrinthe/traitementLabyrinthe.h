/**
 * @file traitementLabyrinthe.h
 * @brief Interface pour la résolution des labyrinthes.
 */

#ifndef TRAITEMENTLABYRINTHE
#define TRAITEMENTLABYRINTHE

#include <errno.h>
#include <assert.h>

#include "../../include/Types/labyrinthe.h"
#include "../../include/Types/ListeDOrdre.h"
#include "../../include/Labyrinthe/trouverChemin.h"
#include "../../include/Labyrinthe/casesEnOrdres.h"

/**
 * @brief Résout le labyrinthe donné et retourne la liste des ordres nécessaires pour le parcourir.
 * 
 * @param laby [E] Le labyrinthe à résoudre.
 * 
 * @return Une liste d'ordres représentant les étapes pour traverser le labyrinthe.
 * 
 * @pre
 * - Le labyrinthe `laby` doit être correctement initialisé.
 * - Les cases d'entrée et de sortie du labyrinthe doivent être valides.
 */
LDO_ListeDOrdre TL_resolution(LAB_Labyrinthe laby);

#endif
