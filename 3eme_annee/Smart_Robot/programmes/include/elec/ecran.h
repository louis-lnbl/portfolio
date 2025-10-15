/**
 * @file ecran.h
 * @brief Décris les fonctions relatives à l'écran lcd
 */

#ifndef __LCD__
#define __LCD__

/**
 * @brief LCD_initLcd initialise l'écran lcd
 *
 * @return renvoie la variable relative a l'écran lcd
 * 
 */
int LCD_initLcd();
/**
 * @brief LCD_afficherAvancer affiche avancer sur l'écran lcd
 *
 * @param lcdHandle variable relative a l'écran
 * 
 */
void LCD_afficherAvancer( int lcdHandle);
/**
 * @brief LCD_afficherVirageDroite affiche Virage à droite sur l'écran lcd
 *
 * @param lcdHandle variable relative a l'écran
 * 
 */
void LCD_afficherVirageDroite( int lcdHandle);
/**
 * @brief LCD_afficherVirageGauche affiche virage à gauche sur l'écran lcd
 *
 * @param lcdHandle variable relative a l'écran
 * 
 */
void LCD_afficherVirageGauche( int lcdHandle);
/**
 * @brief LCD_afficherIntersection affiche Intersection détectée sur l'écran lcd
 *
 * @param lcdHandle variable relative a l'écran
 * 
 */
void LCD_afficherIntersection(int lcdHandle);
/**
 * @brief LCD_afficherArretUrgence affiche Arret d'urgence sur l'écran lcd
 *
 * @param lcdHandle variable relative a l'écran
 * 
 */
void LCD_afficherArretUrgence(int lcdHandle);
/**
 * @brief LCD_afficherFin affiche Sortie trouvee! sur l'écran lcd
 *
 * @param lcdHandle variable relative a l'écran
 * 
 */
void LCD_afficherFin(int lcdHandle);

#endif
