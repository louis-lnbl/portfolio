/**
 * @file Direction.h
 * @brief Définition du type Direction représentant les directions possibles.
 */

#ifndef DIRECTION
#define DIRECTION

/**
 * @enum Direction
 * @brief Représente les directions possibles dans un labyrinthe ou une grille.
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
