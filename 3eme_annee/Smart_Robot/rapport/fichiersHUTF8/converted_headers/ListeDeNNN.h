/**
 * @file ListeDeNNN.h
 * @brief Gestion des listes contenant des Ã©lÃ©ments de type `NNN` (entiers non signÃ©s).
 */

#ifndef LISTEDENNN
#define LISTEDENNN

#include <stdbool.h> 
#include <stddef.h>  
#include <assert.h>
#include "ListeChaineeDeNNN.h" 

/**
 * @struct LDNNN_ListeDeNNN
 * @brief Structure reprÃ©sentant une liste de `NNN` (entiers non signÃ©s).
 * 
 * Cette structure inclut :
 * - Une liste chaÃ®nÃ©e contenant les Ã©lÃ©ments (`lesElements`).
 * - Le nombre d'Ã©lÃ©ments prÃ©sents dans la liste (`nbElements`).
 */
typedef struct LDNNN_ListeDeNNN {
    LCDNNN_ListeChaineeDeNNN lesElements;  
    unsigned int nbElements;               
} LDNNN_ListeDeNNN;

/**
 * @brief Initialise une liste de `NNN` vide.
 * @return Une liste vide de type `LDNNN_ListeDeNNN`.
 */
LDNNN_ListeDeNNN LDNNN_liste();

/**
 * @brief VÃ©rifie si une liste de `NNN` est vide.
 * @param liste [E] La liste Ã  vÃ©rifier.
 * @return `true` si la liste est vide, `false` sinon.
 */
bool LDNNN_estVide(LDNNN_ListeDeNNN liste);

/**
 * @brief InsÃ¨re un Ã©lÃ©ment Ã  une position donnÃ©e dans la liste.
 * 
 * @param liste [E/S] Pointeur vers la liste dans laquelle insÃ©rer l'Ã©lÃ©ment.
 * @param element [E] L'Ã©lÃ©ment Ã  insÃ©rer.
 * @param position [E] La position oÃ¹ insÃ©rer l'Ã©lÃ©ment 
 * @pre `position` doit Ãªtre compris entre `1` et `nbElements + 1`. L'Ã©lÃ©ment ne doit pas Ãªtre nul (`element != 0`).
 */
void LDNNN_inserer(LDNNN_ListeDeNNN *liste, unsigned int element, unsigned int position); 

/**
 * @brief Supprime un Ã©lÃ©ment Ã  une position donnÃ©e dans la liste.
 * 
 * @param liste [E/S] Pointeur vers la liste dans laquelle supprimer un Ã©lÃ©ment.
 * @param position [E] La position de l'Ã©lÃ©ment Ã  supprimer.
 * @pre `position` doit Ãªtre compris entre `1` et `nbElements`.
 */
void LDNNN_supprimer(LDNNN_ListeDeNNN *liste, unsigned int position); 

/**
 * @brief Obtient un Ã©lÃ©ment Ã  une position donnÃ©e dans la liste.
 * 
 * @param liste [E] La liste contenant l'Ã©lÃ©ment.
 * @param position [E] La position de l'Ã©lÃ©ment Ã  obtenir.
 * @return L'Ã©lÃ©ment Ã  la position spÃ©cifiÃ©e.
 * @pre `position` doit Ãªtre compris entre `1` et `nbElements`.
 */
unsigned int LDNNN_obtenirElement(LDNNN_ListeDeNNN liste, unsigned int position); 

/**
 * @brief Retourne la longueur de la liste.
 * 
 * @param liste [E] La liste dont on veut connaÃ®tre la longueur.
 * @return Le nombre d'Ã©lÃ©ments dans la liste.
 */
unsigned int LDNNN_longueur(LDNNN_ListeDeNNN liste);

#endif

