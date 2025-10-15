/**
 * @file buzz.c
 * @brief Spécifie les fonctions du buzzer
 */
#include <lcd.h>
#include <wiringPiI2C.h>
#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>
#include "../../include/elec/buzz.h"
#include "../../include/elec/setup.h"

/**
 * @brief BUZZ_buzz permet d'activer le buzzer  
 */
void BUZZ_buzz (){
	digitalWrite(BUZZ,1);//acitve le buzzeur
	}

/**
 * @brief BUZZ_debuzz permet de désactiver le buzzer  
 */
void BUZZ_debuzz (){
	digitalWrite(BUZZ,0);//desactive le buzzeur
	}
