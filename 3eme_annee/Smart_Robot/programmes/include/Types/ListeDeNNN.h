/**
 * @file ListeDeNNN.h
 * @brief Gestion des listes contenant des éléments de type `NNN` (entiers non signés).
 */

#ifndef LISTEDENNN
#define LISTEDENNN

#include <stdbool.h> 
#include <stddef.h>  
#include <assert.h>
#include "ListeChaineeDeNNN.h" 

/**
 * @struct LDNNN_ListeDeNNN
 * @brief Structure représentant une liste de `NNN` (entiers non signés).
 * 
 * Cette structure inclut :
 * - Une liste chaînée contenant les éléments (`lesElements`).
 * - Le nombre d'éléments présents dans la liste (`nbElements`).
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
 * @brief Vérifie si une liste de `NNN` est vide.
 * @param liste [E] La liste à vérifier.
 * @return `true` si la liste est vide, `false` sinon.
 */
bool LDNNN_estVide(LDNNN_ListeDeNNN liste);

/**
 * @brief Insère un élément à une position donnée dans la liste.
 * 
 * @param liste [E/S] Pointeur vers la liste dans laquelle insérer l'élément.
 * @param element [E] L'élément à insérer.
 * @param position [E] La position où insérer l'élément 
 * @pre `position` doit être compris entre `1` et `nbElements + 1`. L'élément ne doit pas être nul (`element != 0`).
 */
void LDNNN_inserer(LDNNN_ListeDeNNN *liste, unsigned int element, unsigned int position); 

/**
 * @brief Supprime un élément à une position donnée dans la liste.
 * 
 * @param liste [E/S] Pointeur vers la liste dans laquelle supprimer un élément.
 * @param position [E] La position de l'élément à supprimer.
 * @pre `position` doit être compris entre `1` et `nbElements`.
 */
void LDNNN_supprimer(LDNNN_ListeDeNNN *liste, unsigned int position); 

/**
 * @brief Obtient un élément à une position donnée dans la liste.
 * 
 * @param liste [E] La liste contenant l'élément.
 * @param position [E] La position de l'élément à obtenir.
 * @return L'élément à la position spécifiée.
 * @pre `position` doit être compris entre `1` et `nbElements`.
 */
unsigned int LDNNN_obtenirElement(LDNNN_ListeDeNNN liste, unsigned int position); 

/**
 * @brief Retourne la longueur de la liste.
 * 
 * @param liste [E] La liste dont on veut connaître la longueur.
 * @return Le nombre d'éléments dans la liste.
 */
unsigned int LDNNN_longueur(LDNNN_ListeDeNNN liste);

#endif

