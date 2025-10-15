/**
 * @file ListeChaineeDeCDC.h
 * @brief Gestion des listes chaînées contenant des éléments de type char[30].
 */

#ifndef LISTECHAINEEDECDC
#define LISTECHAINEEDECDC

#include <stdbool.h> 
#include <stddef.h>  
#include <assert.h>

/**
 * @struct LCDCDC_Noeud
 * @brief Représente un nœud d'une liste chaînée de chaînes de caractères.
 * 
 * Chaque nœud contient :
 * - un tableau de caractères de taille 30 (`element`).
 * - un pointeur vers le nœud suivant (`listeSuivante`).
 */
typedef struct LCDCDC_Noeud {
    char element[30];              
    struct LCDCDC_Noeud *listeSuivante; 
} LCDCDC_Noeud;

/**
 * @typedef LCDC_ListeChaineeDeCDC
 * @brief Type représentant une liste chaînée de chaînes de caractères.
 */
typedef LCDCDC_Noeud* LCDCDC_ListeChaineeDeCDC;

#define LCDCDC_ERREUR_MEMOIRE 1

/**
 * @brief Crée une liste chaînée vide.
 * @return Une liste chaînée vide.
 */
LCDCDC_ListeChaineeDeCDC LCDCDC_listeVide();

/**
 * @brief Vérifie si une liste chaînée est vide.
 * @param uneListe [E] La liste chaînée à vérifier.
 * @return `true` si la liste est vide, `false` sinon.
 */
bool LCDCDC_estVide(LCDCDC_ListeChaineeDeCDC uneListe);

/**
 * @brief Ajoute un élément à la tête de la liste chaînée.
 * @param uneListe [E/S] Pointeur vers la liste chaînée.
 * @param element [E] L'élément à ajouter.
 */
void LCDCDC_ajouter(LCDCDC_ListeChaineeDeCDC *uneListe, char *element);

/**
 * @brief Obtient l'élément stocké dans le premier nœud de la liste.
 * @param uneListe [E] La liste chaînée.
 * @return L'élément du premier nœud.
 * @pre La liste ne doit pas être vide.
 */
char *LCDCDC_obtenirElement(LCDCDC_ListeChaineeDeCDC uneListe); /* assert : estVide(uneListe) */

/**
 * @brief Remplace l'élément du premier nœud de la liste.
 * @param uneListe [E/S] Pointeur vers la liste chaînée.
 * @param element [E] Le nouvel élément à stocker.
 * @pre La liste ne doit pas être vide.
 */
void LCDCDC_fixerElement(LCDCDC_ListeChaineeDeCDC *uneListe, char *element); /* assert : estVide(uneListe) */

/**
 * @brief Obtient la liste chaînée suivante.
 * @param uneListe [E] La liste chaînée.
 * @return La liste chaînée suivante.
 * @pre La liste ne doit pas être vide.
 */
LCDCDC_ListeChaineeDeCDC LCDCDC_obtenirListeSuivante(LCDCDC_ListeChaineeDeCDC uneListe); /* assert : estVide(uneListe) */

/**
 * @brief Fixe le nœud suivant de la liste chaînée.
 * @param uneListe [E/S] Pointeur vers la liste chaînée.
 * @param nelleSuite [E] La nouvelle liste à placer en tant que suivante.
 * @pre La liste ne doit pas être vide.
 */
void LCDCDC_fixerListeSuivante(LCDCDC_ListeChaineeDeCDC *uneListe, LCDCDC_ListeChaineeDeCDC nelleSuite); /* assert : estVide(uneListe) */

/**
 * @brief Supprime le premier nœud de la liste chaînée.
 * @param uneListe [E/S] Pointeur vers la liste chaînée.
 * @pre La liste ne doit pas être vide.
 */
void LCDCDC_supprimerTete(LCDCDC_ListeChaineeDeCDC *uneListe); /* assert : estVide(uneListe) */

/**
 * @brief Supprime tous les nœuds de la liste chaînée.
 * @param uneListe [E/S] Pointeur vers la liste chaînée.
 */
void LCDCDC_supprimer(LCDCDC_ListeChaineeDeCDC *uneListe);

#endif
