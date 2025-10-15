/**
 * @file ListeDeCDC.h
 * @brief Gestion des listes contenant des éléments de type `CDC` (chaînes de caractères).
 */

#ifndef LISTEDECDC
#define LISTEDECDC

#include <stdbool.h> 
#include <stddef.h>  
#include <assert.h>
#include "ListeChaineeDeCDC.h" 

/**
 * @struct LDCDC_ListeDeCDC
 * @brief Structure représentant une liste de `CDC` (chaînes de caractères).
 * 
 * Cette structure inclut :
 * - Une liste chaînée contenant les éléments (`lesElements`).
 * - Le nombre d'éléments présents dans la liste (`nbElements`).
 */
typedef struct LDCDC_ListeDeCDC {
    LCDCDC_ListeChaineeDeCDC lesElements;  
    unsigned int nbElements;              
} LDCDC_ListeDeCDC;

/**
 * @brief Initialise une liste de `CDC` vide.
 * @return Une liste vide de type `LDCDC_ListeDeCDC`.
 */
LDCDC_ListeDeCDC LDCDC_liste();

/**
 * @brief Vérifie si une liste de `CDC` est vide.
 * @param liste [E] La liste à vérifier.
 * @return `true` si la liste est vide, `false` sinon.
 */
bool LDCDC_estVide(LDCDC_ListeDeCDC liste);

/**
 * @brief Insère un élément à une position donnée dans la liste.
 * 
 * @param liste [E/S] Pointeur vers la liste dans laquelle insérer l'élément.
 * @param element [E] L'élément à insérer.
 * @param position [E] La position où insérer l'élément.
 * @pre `position` doit être compris entre `1` et `nbElements + 1`. L'élément ne doit pas être nul (`element != 0`).
 */
void LDCDC_inserer(LDCDC_ListeDeCDC *liste, char* element, unsigned int position); 

/**
 * @brief Supprime un élément à une position donnée dans la liste.
 * 
 * @param liste [E/S] Pointeur vers la liste dans laquelle supprimer un élément.
 * @param position [E] La position de l'élément à supprimer.
 * @pre `position` doit être compris entre `1` et `nbElements`.
 */
void LDCDC_supprimer(LDCDC_ListeDeCDC *liste, unsigned int position); 

/**
 * @brief Obtient un élément à une position donnée dans la liste.
 * 
 * @param liste [E] La liste contenant l'élément.
 * @param position [E] La position de l'élément à obtenir.
 * @return L'élément à la position spécifiée.
 * @pre `position` doit être compris entre `1` et `nbElements`.
 */
char* LDCDC_obtenirElement(LDCDC_ListeDeCDC liste, unsigned int position); 

/**
 * @brief Retourne la longueur de la liste.
 * 
 * @param liste [E] La liste dont on veut connaître la longueur.
 * @return Le nombre d'éléments dans la liste.
 */
unsigned int LDCDC_longueur(LDCDC_ListeDeCDC liste);

#endif
