/**
 * @file capteurLigne.c
 * @brief Spécifie les fonctions analysant les lignes sous le robot.
 */
#include <lcd.h>
#include <wiringPiI2C.h>
#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>
#include "../../include/elec/capteurLigne.h"
#include "../../include/elec/setup.h"

/**
 * @brief CL_detectionIntersection permet de savoir si on a détecté une intersection.
 * @return renvoie 1 si une intersection est detecté 0 sinon.
 * 
 */
int CL_detectionIntersection() {
	if ((digitalRead(capteurAv) == 1) && ((digitalRead(capteurG) == 1) || (digitalRead(capteurD) == 1))) {
		return 1;
	}
	else {
		return 0;
	}
}

/**
 * @brief CL_sortieLabyrinthe permet de savoir si on a détecté que le robot est sortie du labyrinthe.
 * @return renvoie 1 si le robot est bien sortie 0 sinon.
 * 
 */
int CL_sortieLabyrinthe() {
	if ((digitalRead(capteurAr) == 0) && (digitalRead(capteurAv) == 0) && (digitalRead(capteurG) == 0) && (digitalRead(capteurD) == 0)) {
		return 1;
	}
	else {
		return 0;
	}
}

/**
 * @brief CL_seRedresser permet de savoir si on a détecté une situation ou le robot doit se redresser, afin de bien suivre la ligne sous celui-ci.
 * @return renvoie 1 si le robot doit se redresser 0 sinon.
 * 
 */
int CL_seRedresser() {//a ou exclusif b
	if ((digitalRead(capteurAv)==0) && (((digitalRead(capteurG)==1) && !(digitalRead(capteurD)==1)) || (!(digitalRead(capteurG)==1) && (digitalRead(capteurD)==1)))) {
		return 1;
	}
	else {
		return 0;
	}
}



