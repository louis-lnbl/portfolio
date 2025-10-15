/**
 * @file ecran.c
 * @brief Spécifie les fonctions relatives à l'écran lcd
 */
#include <lcd.h>
#include <wiringPiI2C.h>
#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>
#include "../../include/elec/ecran.h"

//constante LCD

#define        AF_BASE    64
#define        AF_RS                (AF_BASE + 0)
#define        AF_RW                (AF_BASE + 1)
#define        AF_E                 (AF_BASE + 2)
#define        AF_LED               (AF_BASE + 3)

#define        AF_DB4               (AF_BASE + 4)
#define        AF_DB5               (AF_BASE + 5)
#define        AF_DB6               (AF_BASE + 6)
#define        AF_DB7               (AF_BASE + 7)


/**
 * @brief LCD_initLcd initialise l'écran lcd
 *
 * @return renvoie la variable relative a l'écran lcd
 * 
 */
int LCD_initLcd(){//Initialisation de l'ecran LCD
    int lcdHandle;

	int i;

    pcf8574Setup(AF_BASE,0x27); //pcf8574 I2C address
    
    lcdHandle = lcdInit(2, 16, 4, AF_RS, AF_E, AF_DB4,AF_DB5,AF_DB6,AF_DB7, 0,0,0,0) ;
    
    if (lcdHandle < 0)
    {
        fprintf (stderr, "lcdInit failed\n") ;
        exit (EXIT_FAILURE) ;
    }
    
    for(i=0;i<8;i++) {
        pinMode(AF_BASE+i,OUTPUT);
        digitalWrite(AF_LED, 1);
        digitalWrite(AF_RW, 0);
    }
    return lcdHandle;
}

/**
 * @brief LCD_afficherAvancer affiche avancer sur l'écran lcd
 *
 * @param lcdHandle variable relative a l'écran
 * 
 */
void LCD_afficherAvancer( int lcdHandle) {
    lcdClear(lcdHandle);
    lcdPosition(lcdHandle, 0, 1);
    lcdPuts(lcdHandle, "En avant !"); 
}

/**
 * @brief LCD_afficherVirageDroite affiche Virage à droite sur l'écran lcd
 *
 * @param lcdHandle variable relative a l'écran
 * 
 */
void LCD_afficherVirageDroite( int lcdHandle) {
    lcdClear(lcdHandle);
    lcdPosition(lcdHandle, 0, 1);
    lcdPuts(lcdHandle, "Virage a droite"); 
}

/**
 * @brief LCD_afficherVirageGauche affiche virage à gauche sur l'écran lcd
 *
 * @param lcdHandle variable relative a l'écran
 * 
 */
void LCD_afficherVirageGauche( int lcdHandle) {
    lcdClear(lcdHandle);
    lcdPosition(lcdHandle, 0, 1);
    lcdPuts(lcdHandle, "Virage a gauche"); 
}

/**
 * @brief LCD_afficherIntersection affiche Intersection détectée sur l'écran lcd
 *
 * @param lcdHandle variable relative a l'écran
 * 
 */
void LCD_afficherIntersection(int lcdHandle) {
    lcdClear(lcdHandle);
    lcdPosition(lcdHandle, 0, 1);
    lcdPuts(lcdHandle, "Intersection detectee"); 
}

/**
 * @brief LCD_afficherArretUrgence affiche Arret d'urgence sur l'écran lcd
 *
 * @param lcdHandle variable relative a l'écran
 * 
 */
void LCD_afficherArretUrgence(int lcdHandle) {
    lcdClear(lcdHandle);
    lcdPosition(lcdHandle, 0, 1);
    lcdPuts(lcdHandle, "Arret d'urgence"); 
}

/**
 * @brief LCD_afficherFin affiche Sortie trouvee! sur l'écran lcd
 *
 * @param lcdHandle variable relative a l'écran
 * 
 */
void LCD_afficherFin(int lcdHandle){
    lcdClear(lcdHandle);
    lcdPosition(lcdHandle, 0, 1);
    lcdPuts(lcdHandle, "Sortie trouvee !"); 
}
