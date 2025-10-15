/**
 * @file ListeDeCaseEtDirection.h
 * @brief Gestion des listes contenant des éléments de type `CaseEtDirection`.
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
 * @brief Structure représentant une liste de `CaseEtDirection`.
 * 
 * Cette structure inclut :
 * - Une liste chaînée contenant les éléments (`lesElements`).
 * - Le nombre d'éléments présents dans la liste (`nbElements`).
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
 * @brief Vérifie si une liste de `CaseEtDirection` est vide.
 * @param liste [E] La liste à vérifier.
 * @return `true` si la liste est vide, `false` sinon.
 */
bool LDCD_estVide(LDCD_ListeDeCaseEtDirection liste);

/**
 * @brief Insère un élément à une position donnée dans la liste.
 * 
 * @param liste [E/S] Pointeur vers la liste dans laquelle insérer l'élément.
 * @param element [E] L'élément à insérer (de type `CaseEtDirection`).
 * @param position [E] La position où insérer l'élément.
 * @pre `position` doit être compris entre `1` et `nbElements + 1`. L'élément ne doit pas être nul (`element != 0`).
 */
void LDCD_inserer(LDCD_ListeDeCaseEtDirection *liste, CD_CaseEtDirection element, unsigned int position);

/**
 * @brief Supprime un élément à une position donnée dans la liste.
 * 
 * @param liste [E/S] Pointeur vers la liste dans laquelle supprimer un élément.
 * @param position [E] La position de l'élément à supprimer.
 * @pre `position` doit être compris entre `1` et `nbElements`.
 */
void LDCD_supprimer(LDCD_ListeDeCaseEtDirection *liste, unsigned int position);

/**
 * @brief Obtient un élément à une position donnée dans la liste.
 * 
 * @param liste [E] La liste contenant l'élément.
 * @param position [E] La position de l'élément à obtenir.
 * @return L'élément à la position spécifiée.
 * @pre `position` doit être compris entre `1` et `nbElements`.
 */
CD_CaseEtDirection LDCD_obtenirElement(LDCD_ListeDeCaseEtDirection liste, unsigned int position);

/**
 * @brief Retourne la longueur de la liste.
 * 
 * @param liste [E] La liste dont on veut connaître la longueur.
 * @return Le nombre d'éléments dans la liste.
 */
unsigned int LDCD_longueur(LDCD_ListeDeCaseEtDirection liste);

#endif // LISTEDECASEETDIRECTION_H

