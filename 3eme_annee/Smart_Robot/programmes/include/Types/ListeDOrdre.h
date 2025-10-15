/**
 * @file ListeDOrdre.h
 * @brief Gestion des listes contenant des éléments de type `Ordre`.
 */

#ifndef LISTEDORDRE
#define LISTEDORDRE

#include <stdbool.h> 
#include <stddef.h>  
#include <assert.h>
#include "ListeChaineeDOrdre.h" 

/**
 * @struct LDO_ListeDOrdre
 * @brief Structure représentant une liste de `Ordre`.
 * 
 * Cette structure inclut :
 * - Une liste chaînée contenant les éléments (`lesElements`).
 * - Le nombre d'éléments présents dans la liste (`nbElements`).
 */
typedef struct LDO_ListeDOrdre {
    LCDO_ListeChaineeDOrdre lesElements;  
    unsigned int nbElements;             
} LDO_ListeDOrdre;

/**
 * @brief Initialise une liste de `Ordre` vide.
 * @return Une liste vide de type `LDO_ListeDOrdre`.
 */
LDO_ListeDOrdre LDO_liste();

/**
 * @brief Vérifie si une liste de `Ordre` est vide.
 * @param liste [E] La liste à vérifier.
 * @return `true` si la liste est vide, `false` sinon.
 */
bool LDO_estVide(LDO_ListeDOrdre liste);

/**
 * @brief Insère un élément à une position donnée dans la liste.
 * 
 * @param liste [E/S] Pointeur vers la liste dans laquelle insérer l'élément.
 * @param element [E] L'élément à insérer.
 * @param position [E] La position où insérer l'élément.
 * @pre `position` doit être compris entre `1` et `nbElements + 1`. L'élément ne doit pas être nul (`element != 0`).
 */
void LDO_inserer(LDO_ListeDOrdre *liste, Ordre element, unsigned int position);

/**
 * @brief Supprime un élément à une position donnée dans la liste.
 * 
 * @param liste [E/S] Pointeur vers la liste dans laquelle supprimer un élément.
 * @param position [E] La position de l'élément à supprimer.
 * @pre `position` doit être compris entre `1` et `nbElements`.
 */
void LDO_supprimer(LDO_ListeDOrdre *liste, unsigned int position); 

/**
 * @brief Obtient un élément à une position donnée dans la liste.
 * 
 * @param liste [E] La liste contenant l'élément.
 * @param position [E] La position de l'élément à obtenir.
 * @return L'élément à la position spécifiée.
 * @pre `position` doit être compris entre `1` et `nbElements`.
 */
Ordre LDO_obtenirElement(LDO_ListeDOrdre liste, unsigned int position);

/**
 * @brief Retourne la longueur de la liste.
 * 
 * @param liste [E] La liste dont on veut connaître la longueur.
 * @return Le nombre d'éléments dans la liste.
 */
unsigned int LDO_longueur(LDO_ListeDOrdre liste);

#endif
