/**
 * @file setup.c
 * @brief Setup tout les composants utiliser
 */
#include <wiringPi.h>
#include "../../include/elec/setup.h"
/**
 * @brief SET_setupBranchement permet de setup tout les port de la raspberry qu'on va utiliser pour : les moteurs, les capteurs de lignes, le buzzer, le capteur d'obstacle.
 */
void SET_setupBranchement() {
	wiringPiSetupGpio();
    wiringPiSetup();
	pinMode(moteurEnG,PWM_OUTPUT);//moteurs
	pinMode(moteurEnD,PWM_OUTPUT);
	pinMode(moteurGb1,OUTPUT);
	pinMode(moteurGb2,OUTPUT);
	pinMode(moteurDb1,OUTPUT);
	pinMode(moteurDb2,OUTPUT);
	pinMode(capteurAr, INPUT);//captligne
	pinMode(capteurAv, INPUT);
	pinMode(capteurD, INPUT);
	pinMode(capteurG, INPUT);
	pinMode(BUZZ, OUTPUT);//buzzer
	pinMode(Echo, INPUT);//captObstacle
	pinMode(Trig, OUTPUT);  
}