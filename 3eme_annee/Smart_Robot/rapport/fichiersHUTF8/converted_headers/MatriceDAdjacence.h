/**
 * @file MatriceDAdjacence.h
 * @brief Gestion d'une matrice d'adjacence pour reprÃ©senter les connexions entre les cases d'un labyrinthe.
 */

#ifndef MATRICEDADJACENCE
#define MATRICEDADJACENCE

#include <errno.h>
#include "ListeChaineeDeNNN.h"
#include <stdlib.h>

/**
 * @struct MDA_MatriceDAdjacence
 * @brief Structure reprÃ©sentant une matrice d'adjacence.
 * 
 * Cette structure est composÃ©e de :
 * - Un tableau de pointeurs vers des tableaux de naturels non signÃ©s reprÃ©sentant les connexions entre les cases.
 * - Le nombre total de cases dans la matrice (`nbCases`).
 */
typedef struct MDA_MatriceDAdjacence {
    unsigned int **tableau;  
    unsigned int nbElements;              
} MDA_MatriceDAdjacence;

#define MDA_ERREUR_MEMOIRE 1

/**
 * @brief CrÃ©e une matrice d'adjacence vide.
 * 
 * @param nbCases [E] Nombre total de cases Ã  gÃ©rer dans la matrice.
 * @return Une matrice d'adjacence initialisÃ©e avec `nbCases` cases.
 */
MDA_MatriceDAdjacence MDA_creerMatriceDAdjacence(unsigned int nbCases);

/**
 * @brief CrÃ©Ã© un lien entre deux cases dans la matrice d'adjacence.
 * 
 * @param laMatrice [E/S] Pointeur vers la matrice oÃ¹ ajouter le lien.
 * @param case1 [E] La premiÃ¨re case du lien.
 * @param case2 [E] La seconde case du lien.
 * @pre `case1` et `case2` doivent Ãªtre infÃ©rieurs Ã  `nbCases`. Le lien ne doit pas exister auparavant. `case2` doit Ãªtre adjacente Ã  `case1`
 */
void MDA_creerLien(MDA_MatriceDAdjacence *laMatrice, unsigned int case1, unsigned int case2);

/**
 * @brief Retire un lien entre deux cases dans la matrice d'adjacence.
 * 
 * @param laMatrice [E/S] Pointeur vers la matrice d'oÃ¹ supprimer le lien.
 * @param case1 [E] La premiÃ¨re case du lien.
 * @param case2 [E] La seconde case du lien.
 * @pre `case1` et `case2` doivent Ãªtre infÃ©rieurs Ã  `nbCases`.
 */
void MDA_retirerLien(MDA_MatriceDAdjacence *laMatrice, unsigned int case1, unsigned int case2);

/**
 * @brief Obtient les liens associÃ©s Ã  une case donnÃ©e dans la matrice.
 * 
 * @param laMatrice [E] La matrice d'adjacence contenant les liens.
 * @param case1 [E] La case pour laquelle obtenir les liens.
 * @return Une liste chaÃ®nÃ©e des cases connectÃ©es Ã  `case1`.
 * @pre `case1` doit Ãªtre infÃ©rieur Ã  `nbCases`.
 */
LCDNNN_ListeChaineeDeNNN MDA_obtenirLiens(MDA_MatriceDAdjacence laMatrice, unsigned int case1);

/**
 * @brief LibÃ¨re la mÃ©moire utilisÃ©e par une matrice d'adjacence.
 * 
 * @param laMatrice [E/S] Pointeur vers la matrice Ã  libÃ©rer.
 */
void MDA_libererMatrice(MDA_MatriceDAdjacence *laMatrice);

#endif
