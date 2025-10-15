/**
 * @file Direction.h
 * @brief DÃ©finition du type Direction reprÃ©sentant les directions possibles.
 */

#ifndef DIRECTION
#define DIRECTION

/**
 * @enum Direction
 * @brief ReprÃ©sente les directions possibles dans un labyrinthe ou une grille.
 * 
 * Les directions disponibles sont les suivantes :
 * - `D` : Droite.
 * - `G` : Gauche.
 * - `H` : Haut.
 * - `B` : Bas.
 */
typedef enum {
    D, 
    G, 
    H, 
    B 
} Direction;

#endif
