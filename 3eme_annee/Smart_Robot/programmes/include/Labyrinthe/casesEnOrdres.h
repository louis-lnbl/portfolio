/**
 * @file casesENOrdres.h
 * @brief convertis les cases données en ordre pour le robot
 */


#ifndef CASESENORDRES
#define CASESENORDRES

#include <errno.h>
#include <assert.h>
#include <stdbool.h>
#include "../../include/Types/Ordre.h"
#include "../../include/Types/Direction.h"
#include "../../include/Types/caseEtDirection.h"
#include "../../include/Types/labyrinthe.h"
#include "../../include/Types/PileDeNNN.h"
#include "../../include/Types/ListeDOrdre.h"
#include "../../include/Types/ListeDeCaseEtDirection.h"
#include "../../include/Types/EnsembleDeDirection.h"


/**
 * @brief Détermine l'ordre à choisir à une certaine position dans le labyrinthe.
 * 
 * @param laby [E] Le labyrinthe à explorer.
 * @param directionCasePrecedente [E] la direction de la case précédente.
 * @param directionCaseActuelle [E] la direction de la case actuelle.
 * @param caseActuelle [E] la case actuelle.
 * @param ordres [E/S] la liste des ordres à effectuer.
 */
void CEO_choixOrdre(LAB_Labyrinthe laby, Direction directionCasePrecedente, Direction directionCaseActuelle, unsigned int caseActuelle, LDO_ListeDOrdre *ordres); 

/**
 * @brief renvoie la direction en fonction de la position de la porte.
 * 
 * @param la position de la porte de la porte.
 *
 * @return la direction.
 */
 Direction CEO_positionPorteEnDirection(Direction d);

/**
 * @brief convertis les cases données en type caseEtDirection.
 * 
 * @param une pile de cases à a parcourir.
 *
 * @return une liste représentant les cases et les directions à suivre.
 */
LDCD_ListeDeCaseEtDirection CEO_conversionCasesEnCasesEtDirections(LAB_Labyrinthe laby, PDNNN_PileDeNNN p);

/**
 * @brief convertis les cases et les directions en ordres.
 * 
 * @param une liste représentant les cases et les directions à suivre.
 * @param le labyrinthe à explorer.
 *
 * @return une liste représentant les ordres à suivre.
 */
LDO_ListeDOrdre CEO_conversionCasesEtDirectionsEnOrdres(LDCD_ListeDeCaseEtDirection casesDirections, LAB_Labyrinthe laby);

#endif
