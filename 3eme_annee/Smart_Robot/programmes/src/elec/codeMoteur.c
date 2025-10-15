/**
 * @file codeMoteur.c
 * @brief Spécifie les différentes fonctions permettant de faire bouger le robot.
 */
#include <lcd.h>
#include <wiringPiI2C.h>
#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>
#include "../../include/elec/setup.h"
#include "../../include/elec/codeMoteur.h"
#include "../../include/elec/capteurLigne.h"



/**
 * @brief CM_rotation permet au robot d'effectuer une rotation sur lui-même
 * 
 * @param sensRotation le sens de la rotation de type Sens 
 * @param vitesse la vitesse du robot
 * @param obstacle indique si il y a un obstacle sur le chemin via un thread associé
 * 
 */
void CM_rotation(Sens sensRotation, int vitesse, int obstacle) {//plus utiliser
	unsigned int vitesseMoteurG = vitesse-10; 
	unsigned int vitesseMoteurD = vitesse-10;
	int avanceMoteurG;
	int avanceMoteurD;
	if (sensRotation == GAUCHE) {
		avanceMoteurG = 0;
		avanceMoteurD = 1;
	}
	else {
		avanceMoteurG = 1;
		avanceMoteurD = 0;
	}
	while (!(digitalRead(capteurAv)==1) && (obstacle == 0)) {
		CM_setupMoteur(vitesseMoteurG, vitesseMoteurD, avanceMoteurG, avanceMoteurD, 0);
	}
	CM_setupMoteur(vitesseMoteurG, vitesseMoteurD, avanceMoteurG, avanceMoteurD, 1);
}

/**
 * @brief CM_virage permet au robot d'effectuer un virage avec une roue tournant plus vite que l'autre
 * 
 * @param sensVirage le sens du virage de type Sens 
 * @param vitesse la vitesse du robot
 * @param obstacle indique si il y a un obstacle sur le chemin via un thread associé
 * 
 */
void CM_virage(Sens sensVirage, int vitesse, int obstacle) {
	unsigned int vitesseMoteurG; 
	unsigned int vitesseMoteurD;
	int avanceMoteurG;
	int avanceMoteurD;
	if (sensVirage == GAUCHE) {
		vitesseMoteurG = vitesse-28; 
		vitesseMoteurD = vitesse-3;
		avanceMoteurG = 1;
		avanceMoteurD = 1;
	}
	else {
		vitesseMoteurG = vitesse-3; //roue exterieur
		vitesseMoteurD = vitesse-28;//roue interieur
		avanceMoteurG = 1;
		avanceMoteurD = 1;
	}
	while (!(digitalRead(capteurD)==0 && digitalRead(capteurG)==0 && (digitalRead(capteurAv)==1)) && (obstacle == 0) ) {
		CM_setupMoteur(vitesseMoteurG, vitesseMoteurD, avanceMoteurG, avanceMoteurD, 0);
	}
}


/**
 * @brief CM_tourner permet au robot de tourner en fesant d'abbord un virage puis une rotation
 * 
 * @param sensTournant le sens du tournant de type Sens 
 * @param vitesse la vitesse du robot
 * @param obstacle indique si il y a un obstacle sur le chemin via un thread associé
 * 
 */
void CM_tourner(Sens sensTournant, int vitesse, int obstacle) {
	CM_virage(sensTournant, vitesse, obstacle);
}

/**
 * @brief CM_avancer permet au robot d'avancer
 * 
 * @param vitesse la vitesse du robot
 * @param obstacle indique si il y a un obstacle sur le chemin via un thread associé
 * 
 */
void CM_avancer(int vitesse, int obstacle) {
  unsigned int vitesseMoteurG = vitesse; 
  unsigned int vitesseMoteurD = vitesse;
  int avanceMoteurG = 1;
  int avanceMoteurD = 1;
  int stop = 0;
  Sens sensRedressage;
  if (CL_seRedresser() == 1) {
    if (digitalRead(capteurG) == 1) {
      sensRedressage = GAUCHE;
	  printf("Redressage gauche\n");
    }
    else {
      sensRedressage = DROITE;
	  printf("redressage droite\n");
    }
    CM_rotation(sensRedressage, vitesse, obstacle);
  }
  else{
	CM_setupMoteur(vitesseMoteurG, vitesseMoteurD, avanceMoteurG, avanceMoteurD, stop);
  }
}

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
void CM_setupMoteur(unsigned int vitesseMoteurG, unsigned int vitesseMoteurD, int avanceMoteurG, int avanceMoteurD, int stop) {
	digitalWrite(moteurGb1, avanceMoteurG && !stop);
    digitalWrite(moteurGb2, !avanceMoteurG && !stop);
    digitalWrite(moteurDb1, avanceMoteurD && !stop);
    digitalWrite(moteurDb2, !avanceMoteurD && !stop);
    pwmWrite(moteurEnG,(1024*vitesseMoteurG)/100);
    pwmWrite(moteurEnD,(1024*vitesseMoteurD)/100);
}

void CM_emote(unsigned int vitesse){
	int k=0;
	while(k<5){
	CM_setupMoteur(vitesse,vitesse,1,0,0);
	delay(100);
	CM_setupMoteur(vitesse,vitesse,0,1,0);
	delay(100);
	k=k+1;
	}
	CM_setupMoteur(0,0,1,1,1);
}
