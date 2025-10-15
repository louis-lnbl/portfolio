/**
 * @file ListeChaineeDeCDC.h
 * @brief Gestion des listes chaÃ®nÃ©es contenant des Ã©lÃ©ments de type char[30].
 */

#ifndef LISTECHAINEEDECDC
#define LISTECHAINEEDECDC

#include <stdbool.h> 
#include <stddef.h>  
#include <assert.h>

/**
 * @struct LCDCDC_Noeud
 * @brief ReprÃ©sente un nÅud d'une liste chaÃ®nÃ©e de chaÃ®nes de caractÃ¨res.
 * 
 * Chaque nÅud contient :
 * - un tableau de caractÃ¨res de taille 30 (`element`).
 * - un pointeur vers le nÅud suivant (`listeSuivante`).
 */
typedef struct LCDCDC_Noeud {
    char element[30];              
    struct LCDCDC_Noeud *listeSuivante; 
} LCDCDC_Noeud;

/**
 * @typedef LCDC_ListeChaineeDeCDC
 * @brief Type reprÃ©sentant une liste chaÃ®nÃ©e de chaÃ®nes de caractÃ¨res.
 */
typedef LCDCDC_Noeud* LCDCDC_ListeChaineeDeCDC;

#define LCDCDC_ERREUR_MEMOIRE 1

/**
 * @brief CrÃ©e une liste chaÃ®nÃ©e vide.
 * @return Une liste chaÃ®nÃ©e vide.
 */
LCDCDC_ListeChaineeDeCDC LCDCDC_listeVide();

/**
 * @brief VÃ©rifie si une liste chaÃ®nÃ©e est vide.
 * @param uneListe [E] La liste chaÃ®nÃ©e Ã  vÃ©rifier.
 * @return `true` si la liste est vide, `false` sinon.
 */
bool LCDCDC_estVide(LCDCDC_ListeChaineeDeCDC uneListe);

/**
 * @brief Ajoute un Ã©lÃ©ment Ã  la tÃªte de la liste chaÃ®nÃ©e.
 * @param uneListe [E/S] Pointeur vers la liste chaÃ®nÃ©e.
 * @param element [E] L'Ã©lÃ©ment Ã  ajouter.
 */
void LCDCDC_ajouter(LCDCDC_ListeChaineeDeCDC *uneListe, char *element);

/**
 * @brief Obtient l'Ã©lÃ©ment stockÃ© dans le premier nÅud de la liste.
 * @param uneListe [E] La liste chaÃ®nÃ©e.
 * @return L'Ã©lÃ©ment du premier nÅud.
 * @pre La liste ne doit pas Ãªtre vide.
 */
char *LCDCDC_obtenirElement(LCDCDC_ListeChaineeDeCDC uneListe); /* assert : estVide(uneListe) */

/**
 * @brief Remplace l'Ã©lÃ©ment du premier nÅud de la liste.
 * @param uneListe [E/S] Pointeur vers la liste chaÃ®nÃ©e.
 * @param element [E] Le nouvel Ã©lÃ©ment Ã  stocker.
 * @pre La liste ne doit pas Ãªtre vide.
 */
void LCDCDC_fixerElement(LCDCDC_ListeChaineeDeCDC *uneListe, char *element); /* assert : estVide(uneListe) */

/**
 * @brief Obtient la liste chaÃ®nÃ©e suivante.
 * @param uneListe [E] La liste chaÃ®nÃ©e.
 * @return La liste chaÃ®nÃ©e suivante.
 * @pre La liste ne doit pas Ãªtre vide.
 */
LCDCDC_ListeChaineeDeCDC LCDCDC_obtenirListeSuivante(LCDCDC_ListeChaineeDeCDC uneListe); /* assert : estVide(uneListe) */

/**
 * @brief Fixe le nÅud suivant de la liste chaÃ®nÃ©e.
 * @param uneListe [E/S] Pointeur vers la liste chaÃ®nÃ©e.
 * @param nelleSuite [E] La nouvelle liste Ã  placer en tant que suivante.
 * @pre La liste ne doit pas Ãªtre vide.
 */
void LCDCDC_fixerListeSuivante(LCDCDC_ListeChaineeDeCDC *uneListe, LCDCDC_ListeChaineeDeCDC nelleSuite); /* assert : estVide(uneListe) */

/**
 * @brief Supprime le premier nÅud de la liste chaÃ®nÃ©e.
 * @param uneListe [E/S] Pointeur vers la liste chaÃ®nÃ©e.
 * @pre La liste ne doit pas Ãªtre vide.
 */
void LCDCDC_supprimerTete(LCDCDC_ListeChaineeDeCDC *uneListe); /* assert : estVide(uneListe) */

/**
 * @brief Supprime tous les nÅuds de la liste chaÃ®nÃ©e.
 * @param uneListe [E/S] Pointeur vers la liste chaÃ®nÃ©e.
 */
void LCDCDC_supprimer(LCDCDC_ListeChaineeDeCDC *uneListe);

#endif
