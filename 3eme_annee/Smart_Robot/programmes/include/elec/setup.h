/**
 * @file setup.h
 * @brief Setup tout les composants utiliser
 */

#ifndef __SETUP__
#define __SETUP__

/**
 * @def BUZZ
 * Le port physique de la raspberry associer au buzzer
*/
#define BUZZ 20
/**
 * @def Trig
 * Le port physique de la raspberry lié à la variable trig du capteur d'obstacle
 * @def Echo
 * Le port physique de la raspberry lié à la variable echo du capteur d'obstacle
*/
#define  Trig 24  
#define  Echo 23 
/**
 * @def moteurEnG
 * Le port physique de la raspberry permettant d'activer le moteur gauche
  * @def moteurEnD
 * Le port physique de la raspberry permettant d'activer le moteur droit
  * @def moteurGb1
 * Le port physique de la raspberry permettant de faire avancer le moteur gauche
  * @def moteurGb2
 * Le port physique de la raspberry permettant de faire reculer le moteur gauche
  * @def moteurDb1
 * Le port physique de la raspberry permettant de faire avancer le moteur droit
  * @def moteurDb2
 * Le port physique de la raspberry permettant de faire reculer le moteur droit
*/
#define moteurEnG 19
#define moteurEnD 12
#define moteurGb1 17 //avancer
#define moteurGb2 4
#define moteurDb1 27 //avancer
#define moteurDb2 9
/**
 * @def capteurAv
 * Le port physique de la raspberry associer au capteur de ligne avant
  * @def capteurD
 * Le port physique de la raspberry associer au capteur de ligne droit
  * @def capteurG
 * Le port physique de la raspberry associer au capteur de ligne gauche
  * @def capteurAr
 * Le port physique de la raspberry associer au capteur de ligne arriere
*/
#define capteurAv 5
#define capteurD 13
#define capteurG 26
#define capteurAr 6

/**
 * @brief SET_setupBranchement permet de setup tout les port de la raspberry qu'on va utiliser pour : les moteurs, les capteurs de lignes, le buzzer, le capteur d'obstacle.
 */
void SET_setupBranchement();

#endif
