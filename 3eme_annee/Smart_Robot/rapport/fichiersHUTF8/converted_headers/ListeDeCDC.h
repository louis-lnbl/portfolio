/**
 * @file ListeDeCDC.h
 * @brief Gestion des listes contenant des Ã©lÃ©ments de type `CDC` (chaÃ®nes de caractÃ¨res).
 */

#ifndef LISTEDECDC
#define LISTEDECDC

#include <stdbool.h> 
#include <stddef.h>  
#include <assert.h>
#include "ListeChaineeDeCDC.h" 

/**
 * @struct LDCDC_ListeDeCDC
 * @brief Structure reprÃ©sentant une liste de `CDC` (chaÃ®nes de caractÃ¨res).
 * 
 * Cette structure inclut :
 * - Une liste chaÃ®nÃ©e contenant les Ã©lÃ©ments (`lesElements`).
 * - Le nombre d'Ã©lÃ©ments prÃ©sents dans la liste (`nbElements`).
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
 * @brief VÃ©rifie si une liste de `CDC` est vide.
 * @param liste [E] La liste Ã  vÃ©rifier.
 * @return `true` si la liste est vide, `false` sinon.
 */
bool LDCDC_estVide(LDCDC_ListeDeCDC liste);

/**
 * @brief InsÃ¨re un Ã©lÃ©ment Ã  une position donnÃ©e dans la liste.
 * 
 * @param liste [E/S] Pointeur vers la liste dans laquelle insÃ©rer l'Ã©lÃ©ment.
 * @param element [E] L'Ã©lÃ©ment Ã  insÃ©rer.
 * @param position [E] La position oÃ¹ insÃ©rer l'Ã©lÃ©ment.
 * @pre `position` doit Ãªtre compris entre `1` et `nbElements + 1`. L'Ã©lÃ©ment ne doit pas Ãªtre nul (`element != 0`).
 */
void LDCDC_inserer(LDCDC_ListeDeCDC *liste, char* element, unsigned int position); 

/**
 * @brief Supprime un Ã©lÃ©ment Ã  une position donnÃ©e dans la liste.
 * 
 * @param liste [E/S] Pointeur vers la liste dans laquelle supprimer un Ã©lÃ©ment.
 * @param position [E] La position de l'Ã©lÃ©ment Ã  supprimer.
 * @pre `position` doit Ãªtre compris entre `1` et `nbElements`.
 */
void LDCDC_supprimer(LDCDC_ListeDeCDC *liste, unsigned int position); 

/**
 * @brief Obtient un Ã©lÃ©ment Ã  une position donnÃ©e dans la liste.
 * 
 * @param liste [E] La liste contenant l'Ã©lÃ©ment.
 * @param position [E] La position de l'Ã©lÃ©ment Ã  obtenir.
 * @return L'Ã©lÃ©ment Ã  la position spÃ©cifiÃ©e.
 * @pre `position` doit Ãªtre compris entre `1` et `nbElements`.
 */
char* LDCDC_obtenirElement(LDCDC_ListeDeCDC liste, unsigned int position); 

/**
 * @brief Retourne la longueur de la liste.
 * 
 * @param liste [E] La liste dont on veut connaÃ®tre la longueur.
 * @return Le nombre d'Ã©lÃ©ments dans la liste.
 */
unsigned int LDCDC_longueur(LDCDC_ListeDeCDC liste);

#endif
