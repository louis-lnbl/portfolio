/**
 * @file ListeDOrdre.h
 * @brief Gestion des listes contenant des Ã©lÃ©ments de type `Ordre`.
 */

#ifndef LISTEDORDRE
#define LISTEDORDRE

#include <stdbool.h> 
#include <stddef.h>  
#include <assert.h>
#include "ListeChaineeDOrdre.h" 

/**
 * @struct LDO_ListeDOrdre
 * @brief Structure reprÃ©sentant une liste de `Ordre`.
 * 
 * Cette structure inclut :
 * - Une liste chaÃ®nÃ©e contenant les Ã©lÃ©ments (`lesElements`).
 * - Le nombre d'Ã©lÃ©ments prÃ©sents dans la liste (`nbElements`).
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
 * @brief VÃ©rifie si une liste de `Ordre` est vide.
 * @param liste [E] La liste Ã  vÃ©rifier.
 * @return `true` si la liste est vide, `false` sinon.
 */
bool LDO_estVide(LDO_ListeDOrdre liste);

/**
 * @brief InsÃ¨re un Ã©lÃ©ment Ã  une position donnÃ©e dans la liste.
 * 
 * @param liste [E/S] Pointeur vers la liste dans laquelle insÃ©rer l'Ã©lÃ©ment.
 * @param element [E] L'Ã©lÃ©ment Ã  insÃ©rer.
 * @param position [E] La position oÃ¹ insÃ©rer l'Ã©lÃ©ment.
 * @pre `position` doit Ãªtre compris entre `1` et `nbElements + 1`. L'Ã©lÃ©ment ne doit pas Ãªtre nul (`element != 0`).
 */
void LDO_inserer(LDO_ListeDOrdre *liste, Ordre element, unsigned int position);

/**
 * @brief Supprime un Ã©lÃ©ment Ã  une position donnÃ©e dans la liste.
 * 
 * @param liste [E/S] Pointeur vers la liste dans laquelle supprimer un Ã©lÃ©ment.
 * @param position [E] La position de l'Ã©lÃ©ment Ã  supprimer.
 * @pre `position` doit Ãªtre compris entre `1` et `nbElements`.
 */
void LDO_supprimer(LDO_ListeDOrdre *liste, unsigned int position); 

/**
 * @brief Obtient un Ã©lÃ©ment Ã  une position donnÃ©e dans la liste.
 * 
 * @param liste [E] La liste contenant l'Ã©lÃ©ment.
 * @param position [E] La position de l'Ã©lÃ©ment Ã  obtenir.
 * @return L'Ã©lÃ©ment Ã  la position spÃ©cifiÃ©e.
 * @pre `position` doit Ãªtre compris entre `1` et `nbElements`.
 */
Ordre LDO_obtenirElement(LDO_ListeDOrdre liste, unsigned int position);

/**
 * @brief Retourne la longueur de la liste.
 * 
 * @param liste [E] La liste dont on veut connaÃ®tre la longueur.
 * @return Le nombre d'Ã©lÃ©ments dans la liste.
 */
unsigned int LDO_longueur(LDO_ListeDOrdre liste);

#endif
