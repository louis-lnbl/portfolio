/**
 * @file MatriceDAdjacence.h
 * @brief Gestion d'une matrice d'adjacence pour représenter les connexions entre les cases d'un labyrinthe.
 */

#ifndef MATRICEDADJACENCE
#define MATRICEDADJACENCE

#include <errno.h>
#include "ListeChaineeDeNNN.h"
#include <stdlib.h>

/**
 * @struct MDA_MatriceDAdjacence
 * @brief Structure représentant une matrice d'adjacence.
 * 
 * Cette structure est composée de :
 * - Un tableau de pointeurs vers des tableaux de naturels non signés représentant les connexions entre les cases.
 * - Le nombre total de cases dans la matrice (`nbCases`).
 */
typedef struct MDA_MatriceDAdjacence {
    unsigned int **tableau;  
    unsigned int nbElements;              
} MDA_MatriceDAdjacence;

#define MDA_ERREUR_MEMOIRE 1

/**
 * @brief Crée une matrice d'adjacence vide.
 * 
 * @param nbCases [E] Nombre total de cases à gérer dans la matrice.
 * @return Une matrice d'adjacence initialisée avec `nbCases` cases.
 */
MDA_MatriceDAdjacence MDA_creerMatriceDAdjacence(unsigned int nbCases);

/**
 * @brief Créé un lien entre deux cases dans la matrice d'adjacence.
 * 
 * @param laMatrice [E/S] Pointeur vers la matrice où ajouter le lien.
 * @param case1 [E] La première case du lien.
 * @param case2 [E] La seconde case du lien.
 * @pre `case1` et `case2` doivent être inférieurs à `nbCases`. Le lien ne doit pas exister auparavant. `case2` doit être adjacente à `case1`
 */
void MDA_creerLien(MDA_MatriceDAdjacence *laMatrice, unsigned int case1, unsigned int case2);

/**
 * @brief Retire un lien entre deux cases dans la matrice d'adjacence.
 * 
 * @param laMatrice [E/S] Pointeur vers la matrice d'où supprimer le lien.
 * @param case1 [E] La première case du lien.
 * @param case2 [E] La seconde case du lien.
 * @pre `case1` et `case2` doivent être inférieurs à `nbCases`.
 */
void MDA_retirerLien(MDA_MatriceDAdjacence *laMatrice, unsigned int case1, unsigned int case2);

/**
 * @brief Obtient les liens associés à une case donnée dans la matrice.
 * 
 * @param laMatrice [E] La matrice d'adjacence contenant les liens.
 * @param case1 [E] La case pour laquelle obtenir les liens.
 * @return Une liste chaînée des cases connectées à `case1`.
 * @pre `case1` doit être inférieur à `nbCases`.
 */
LCDNNN_ListeChaineeDeNNN MDA_obtenirLiens(MDA_MatriceDAdjacence laMatrice, unsigned int case1);

/**
 * @brief Libère la mémoire utilisée par une matrice d'adjacence.
 * 
 * @param laMatrice [E/S] Pointeur vers la matrice à libérer.
 */
void MDA_libererMatrice(MDA_MatriceDAdjacence *laMatrice);

#endif
