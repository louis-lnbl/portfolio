/**
 * @file ListeDeCaseEtDirection.h
 * @brief Gestion des listes contenant des Ã©lÃ©ments de type `CaseEtDirection`.
 */

#ifndef LISTEDECASEETDIRECTION
#define LISTEDECASEETDIRECTION

#include <stdbool.h>
#include <stddef.h>
#include <assert.h>
#include "caseEtDirection.h"
#include "ListeChaineeDeCaseEtDirection.h"

/**
 * @struct LDCD_ListeDeCaseEtDirection
 * @brief Structure reprÃ©sentant une liste de `CaseEtDirection`.
 * 
 * Cette structure inclut :
 * - Une liste chaÃ®nÃ©e contenant les Ã©lÃ©ments (`lesElements`).
 * - Le nombre d'Ã©lÃ©ments prÃ©sents dans la liste (`nbElements`).
 */
typedef struct LDCD_ListeDeCaseEtDirection {
    LCDCD_ListeChaineeDeCaseEtDirection lesElements;  
    unsigned int nbElements;                    
} LDCD_ListeDeCaseEtDirection;

/**
 * @brief Initialise une liste vide de `CaseEtDirection`.
 * @return Une liste vide de type `LDCD_ListeDeCaseEtDirection`.
 */
LDCD_ListeDeCaseEtDirection LDCD_liste();

/**
 * @brief VÃ©rifie si une liste de `CaseEtDirection` est vide.
 * @param liste [E] La liste Ã  vÃ©rifier.
 * @return `true` si la liste est vide, `false` sinon.
 */
bool LDCD_estVide(LDCD_ListeDeCaseEtDirection liste);

/**
 * @brief InsÃ¨re un Ã©lÃ©ment Ã  une position donnÃ©e dans la liste.
 * 
 * @param liste [E/S] Pointeur vers la liste dans laquelle insÃ©rer l'Ã©lÃ©ment.
 * @param element [E] L'Ã©lÃ©ment Ã  insÃ©rer (de type `CaseEtDirection`).
 * @param position [E] La position oÃ¹ insÃ©rer l'Ã©lÃ©ment.
 * @pre `position` doit Ãªtre compris entre `1` et `nbElements + 1`. L'Ã©lÃ©ment ne doit pas Ãªtre nul (`element != 0`).
 */
void LDCD_inserer(LDCD_ListeDeCaseEtDirection *liste, CD_CaseEtDirection element, unsigned int position);

/**
 * @brief Supprime un Ã©lÃ©ment Ã  une position donnÃ©e dans la liste.
 * 
 * @param liste [E/S] Pointeur vers la liste dans laquelle supprimer un Ã©lÃ©ment.
 * @param position [E] La position de l'Ã©lÃ©ment Ã  supprimer.
 * @pre `position` doit Ãªtre compris entre `1` et `nbElements`.
 */
void LDCD_supprimer(LDCD_ListeDeCaseEtDirection *liste, unsigned int position);

/**
 * @brief Obtient un Ã©lÃ©ment Ã  une position donnÃ©e dans la liste.
 * 
 * @param liste [E] La liste contenant l'Ã©lÃ©ment.
 * @param position [E] La position de l'Ã©lÃ©ment Ã  obtenir.
 * @return L'Ã©lÃ©ment Ã  la position spÃ©cifiÃ©e.
 * @pre `position` doit Ãªtre compris entre `1` et `nbElements`.
 */
CD_CaseEtDirection LDCD_obtenirElement(LDCD_ListeDeCaseEtDirection liste, unsigned int position);

/**
 * @brief Retourne la longueur de la liste.
 * 
 * @param liste [E] La liste dont on veut connaÃ®tre la longueur.
 * @return Le nombre d'Ã©lÃ©ments dans la liste.
 */
unsigned int LDCD_longueur(LDCD_ListeDeCaseEtDirection liste);

#endif // LISTEDECASEETDIRECTION_H

