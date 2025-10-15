/**
 * @file trouverLesOrdres.h
 * @brief Interface pour la recherche d'ordres pour sortir du labyrinthe.
 */

#ifndef TROUVERLESORDRES
#define TROUVERLESORDRES

#include <errno.h>
#include <assert.h>
#include <stdio.h>
#include <stdbool.h>
#include "../../include/Labyrinthe/gestionFichier.h"
#include "../../include/Labyrinthe/initialisationLabyrinthe.h"
#include "../../include/Labyrinthe/traitementLabyrinthe.h"
#include "../../include/Types/ListeDOrdre.h"


/**
 * @brief Trouve les ordres pour sortir du labyrinthe.
 * 
 * @param nomFichier [E] nom du fichier contenant le labyrinthe.
 * 
 * @pre
 * - `nomFichier` doit exister.
 */
LDO_ListeDOrdre TLO_trouverOrdres(char* nomFichier);

#endif
