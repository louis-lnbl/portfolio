/**
 * @file initialisationLabyrinthe.h
 * @brief Interface pour l'initialisation d'un labyrinthe.
 */

#ifndef INITIALISATIONLABYRINTHE
#define INITIALISATIONLABYRINTHE

#include <errno.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../../include/Types/ListeDeCDC.h"
#include "../../include/Types/labyrinthe.h"
#include "../../include/Types/Direction.h"


/**
 * @brief Créé un labyrinthe en spécifiant ses paramètres principaux.
 * 
 * @param largeurLabyrinthe [E] La largeur (ou taille) du labyrinthe en nombre de cases.
 * @param entree [E] L'indice de la case d'entrée.
 * @param sortie [E] L'indice de la case de sortie.
 * @param directionEntree [E] La direction initiale à l'entrée du labyrinthe.
 * @param directionSortie [E] La direction finale à la sortie du labyrinthe.
 * @param liaisonsCases [E] Les liaisons entre les cases du labyrinthe.
 * 
 * @return `LAB_Labyrinthe` représentant le labyrinthe créé.
 * 
 * @pre
 * - `entree` et `sortie` doivent être sur la bordure.
 * - `entree != sortie`.
 * - `entree <= largeur(labyrinthe)^2` et `sortie <= largeur(labyrinthe)^2`.
 */
LAB_Labyrinthe IL_creerLabyrinthe(unsigned int largeurLabyrinthe, unsigned int entree, unsigned int sortie, Direction directionPorteEntree, Direction directionPorteSortie, LDCDC_ListeDeCDC liaisonsCases);

/**
 * @brief Ajoute des passages entre les cases dans le labyrinthe.
 * 
 * @param laby [E/S] Un pointeur vers le labyrinthe où les passages seront ajoutés.
 * @param liaisonsCases [E] Les liaisons définissant les passages entre les cases.
 *
 */
void IL_creerPassage(LAB_Labyrinthe* laby, LDCDC_ListeDeCDC liaisonsCases);

/**
 * @brief Renvoie les cases à relier en Naturel Non Nul.
 * 
 * @param casesASeparer [E] les deux cases à relier.
 * @param case1 [S] valeur de la case 1.
 * @param case2 [S] valeur de la case 2.
 * 
 * @pre
 * - 'casesASeparer != ""
 */
void IL_separationCases(char* casesASeparer,unsigned int *case1,unsigned int *case2);

#endif
