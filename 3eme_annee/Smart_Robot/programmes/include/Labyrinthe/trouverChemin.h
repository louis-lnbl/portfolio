/**
 * @file trouverChemin.h
 * @brief Interface pour la recherche de chemins dans un labyrinthe.
 */

#ifndef TROUVERCHEMIN
#define TROUVERCHEMIN

#include <errno.h>
#include <assert.h>
#include <stdbool.h>
#include "../../include/Types/labyrinthe.h"
#include "../../include/Types/PileDeNNN.h"
#include "../../include/Types/EnsembleDePileDeNNN.h"
#include "../../include/Types/caseEtDirection.h"
#include "../../include/Types/EnsembleDeNNN.h"

/**
 * @brief Trouve tous les chemins possibles dans le labyrinthe.
 * 
 * @param laby [E] Le labyrinthe à explorer.
 * @param cheminCourant [E/S] La pile représentant le chemin en cours d'exploration.
 * @param cheminsPossibles [E/S] L'ensemble des chemins trouvés.
 * 
 * @pre
 * - `cheminCourant` doit être une pile initialisée.
 * - `cheminsPossibles` doit être un ensemble initialisé.
 */
void TC_trouverLesChemins(LAB_Labyrinthe laby, PDNNN_PileDeNNN *cheminCourant, EDPDNNN_EnsembleDePileDeNNN *cheminsPossibles);

/**
 * @brief Compare les chemins possibles pour déterminer le plus court.
 * 
 * @param cheminsPossibles [E] L'ensemble des chemins à comparer.
 * 
 * @return Une pile représentant le chemin le plus court trouvé dans l'ensemble.
 * 
 * @pre
 * - `cheminsPossibles` doit contenir au moins un chemin valide.
 */
PDNNN_PileDeNNN TC_comparaisonChemins(EDPDNNN_EnsembleDePileDeNNN cheminsPossibles);

/**
 * @brief Trouve le chemin le plus court dans le labyrinthe entre l'entrée et la sortie.
 * 
 * @param laby [E] Le labyrinthe à analyser.
 * 
 * @return Une pile représentant le chemin le plus court.
 * 
 * @pre
 * - Le labyrinthe `laby` doit être correctement initialisé.
 */
PDNNN_PileDeNNN TC_trouverPlusCourtChemin(LAB_Labyrinthe laby);

#endif
