/**
 * @file gestionFichier.h
 * @brief Interface pour la lecture du fichier contenant le labyrinthe.
 */

#ifndef GESTIONFICHIER
#define GESTIONFICHIER

#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <stdbool.h>
#include <string.h>
#include "../../include/Types/ListeDeCDC.h"
#include "../../include/Types/Direction.h"


/**
 * @brief Lit le fichier pour pouvoir représenter le labyrinte.
 * 
 * @param nomFichier [E] Le nom du fichier contenant le labyrinthe.
 * @param largeur [E/S] largeur du labyrinthe.
 * @param caseEntree [E/S] case d'entree du labyrinthe.
 * @param caseSortie [E/S] case de sortie du labyrinthe.
 * @param directionPorteEntree [E/S] direction de la porte d'entrée du labyrinthe.
 * @param directionPorteSortie [E/S] direction de la porte de sortie du labyrinthe.
 * @param listeLiaisons [E/S] liste des liaisons entre les cases du labyrinthe.
 * 
 * @pre
 * - `nomFichier` doit exister.
 */
void GF_gestionDuFichier(char* nomFichier, unsigned int *largeur, unsigned int* caseEntree, unsigned int *caseSortie, Direction *directionPorteEntree, Direction *directionPorteSortie, LDCDC_ListeDeCDC *listeLiaisons);

#endif
