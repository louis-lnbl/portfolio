/**
 * @file codeMoteur.h
 * @brief Décris les différentes fonctions permettant de faire bouger le robot.
 */

#ifndef __CODEMOTEUR__
#define __CODEMOTEUR__

typedef enum {GAUCHE, DROITE} Sens;
/**
 * @brief CM_rotation permet au robot d'effectuer une rotation sur lui-même
 * 
 * @param sensRotation le sens de la rotation de type Sens 
 * @param vitesse la vitesse du robot
 * @param obstacle indique si il y a un obstacle sur le chemin via un thread associé
 * 
 */
void CM_rotation(Sens sensRotation, int vitesse, int obstacle);
/**
 * @brief CM_virage permet au robot d'effectuer un virage avec une roue tournant plus vite que l'autre
 * 
 * @param sensVirage le sens du virage de type Sens 
 * @param vitesse la vitesse du robot
 * @param obstacle indique si il y a un obstacle sur le chemin via un thread associé
 * 
 */
void CM_virage(Sens sensVirage, int vitesse, int obstacle);
/**
 * @brief CM_tourner permet au robot de tourner en fesant d'abbord un virage puis une rotation
 * 
 * @param sensTournant le sens du tournant de type Sens 
 * @param vitesse la vitesse du robot
 * @param obstacle indique si il y a un obstacle sur le chemin via un thread associé
 * 
 */
void CM_tourner(Sens sensTournant, int vitesse, int obstacle);
/**
 * @brief CM_avancer permet au robot d'avancer
 * 
 * @param vitesse la vitesse du robot
 * @param obstacle indique si il y a un obstacle sur le chemin via un thread associé
 * 
 */
void CM_avancer();
/**
 * @brief CM_setupMoteur permet de donner une instruction aux moteurs 
 *
 * @param vitesseMoteurG la vitesse souhaiter pour le moteur gauche 
 * @param vitesseMoteurD la vitesse souhaiter pour le moteur droit 
 * @param avanceMoteurG indique 1 si le moteur gauche doit être activé, 0 sinon
 * @param avanceMoteurD indique 1 si le moteur droit doit être activé, 0 sinon
 * @param stop indique 1 si on doit stopper les moteurs, 0 sinon
 *
 */
void CM_setupMoteur(unsigned int vitesseMoteurG, unsigned int vitesseMoteurD, int avanceMoteurG, int avanceMoteurD, int stop);

void CM_emote(unsigned int vitesse);

#endif
