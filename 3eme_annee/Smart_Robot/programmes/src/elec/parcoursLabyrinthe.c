#include <wiringPi.h>

#include <pthread.h>
#include <stdio.h>

#include "../../include/elec/parcoursLabyrinthe.h"
#include "../../include/elec/capteurLigne.h"
#include "../../include/elec/capteurObstacle.h"
#include "../../include/elec/buzz.h"
#include "../../include/elec/codeMoteur.h"
#include "../../include/elec/ecran.h"
#include "../../include/elec/setup.h"

#include "../../include/Types/Ordre.h"
#include "../../include/Types/ListeDOrdre.h"

int obstacle = 0;//obstacle devant?
float distance = 0;//distance mesurer par les capteurs ultrason
int situation = 0;// situation actuelle (on avance, on tourne a droite ou a gauche, fin du parcours)
int lcdHandle = 0;//lcd variable
int vitesse = 0;//vitesse du robot

pthread_mutex_t mutex;

void* arretDUrgence(void* arg) {
    while (1) {
        pthread_mutex_lock(&mutex);  // Protéger l'accès à `distance` et `obstacle`
        distance = CO_distanceMesure();
        if (distance > 15) {
            BUZZ_debuzz();
            obstacle = 0; // Pas d'obstacle
        } else {
            CM_setupMoteur(0, 0, 0, 0, 1);
            BUZZ_buzz();
            obstacle = 1; // Obstacle détecté
        }
        pthread_mutex_unlock(&mutex);  // Libérer le mutex
        usleep(50000); // Pause de 50 ms pour libérer le CPU
    }
    return NULL;
}

void* gestionLCD(void* arg) {
    int lcdHandle = *(int*)arg;

    while (1) {
        pthread_mutex_lock(&mutex); // Protéger l'accès aux variables partagées
        int localSituation = situation;
        int localObstacle = obstacle;
        float localDistance = distance;
        pthread_mutex_unlock(&mutex);

        if (localObstacle == 1) {
            LCD_afficherArretUrgence(lcdHandle);
        } else {
            switch (localSituation) {
                case 4:
                    LCD_afficherFin(lcdHandle);
                    break;
                case 3:
                    LCD_afficherVirageGauche(lcdHandle);
                    break;
                case 2:
                    LCD_afficherVirageDroite(lcdHandle);
                    break;
                case 1:
                    LCD_afficherAvancer(lcdHandle);
                    break;
                case 0:
                    LCD_afficherIntersection(lcdHandle);
                    break;
            }
        }
        usleep(500000); // 500 ms
    }
    return NULL;
}

/**
 * @brief PL_parcoursLabyrinthe va parcourir le labyrinthe selon une liste d'ordres en utilisant obstacle et situation.
 * 
 * @param vitesseInput vitesse souhaité lors du parcours
 * @param lcdHandleInput variable relative à l'écran lcd afin de l'actualisé au cours du parcours
 * @param laListeDOrdres une liste d'ordres de type Ordre qui nous permettrons de parcourir le labyrinthe
 *
 */
void PL_parcoursLabyrinthe (int vitesseInput, int lcdHandleInput, LDO_ListeDOrdre laListeDOrdres){
  
  lcdHandle = lcdHandleInput;
  vitesse = vitesseInput;

  pthread_t threadUrgence;
  pthread_t threadLCD; 

  pthread_mutex_init(&mutex, NULL); // Initialisation du mutex
  if (pthread_create(&threadUrgence, NULL, arretDUrgence, NULL) != 0) {
        printf("Erreur lors de la création du thread arretUrgence \n");
        return -1;
    }
  printf("Thread arretUrgence créé avec succès\n");

  if (pthread_create(&threadLCD, NULL, gestionLCD, &lcdHandle) != 0) {
        printf("Erreur lors de la création du thread LCD\n");
        return -1;
    }
  printf("Thread LCD créé avec succès\n");
  Ordre unOrdre;
  unsigned int i = 1;
  CM_setupMoteur(0,0,1,1,1);
  while(i < LDO_longueur(laListeDOrdres)){
    unOrdre = LDO_obtenirElement(laListeDOrdres,i);
    printf("ordre : %d\n ", i);
    int avpr = 0;
    switch (unOrdre){
      case AV://on a deja avancer jusqu'a trouver un tournant 
        situation = 1;
        if(avpr==1){
          CM_setupMoteur(vitesse,vitesse,1,1,0);
          delay(500);
        }
        printf("Avancer\n");
        while((digitalRead(capteurD)==1 || digitalRead(capteurG)==1)){//on avance pour ne plus detecter l'intersection
          printf("sort inter\n");
          CM_setupMoteur(vitesse, vitesse, 1, 1, 0);
        }
        printf("sortie boucle\n");
        while(CL_detectionIntersection() != 1){
          if(obstacle == 0){
            CM_avancer(vitesse, obstacle);
          }
        }
        avpr = 1;
        printf("Intersection\n");
        situation = 0;//intersection
        break;
      case TD:
        CM_setupMoteur(vitesse-2, vitesse-27,1,1,0); //test
        delay(400); //test
        printf("Tourner Droite\n");
        while((digitalRead(capteurAv)==1) || digitalRead(capteurD)==1){//on avance pour ne plus detecter l'intersection
          CM_setupMoteur(vitesse-3, vitesse-30, 1, 1, 0);
        }

        situation = 2;//droite
        while(digitalRead(capteurAv) != 1){
          if(obstacle == 0){
            CM_tourner(DROITE, vitesse, obstacle);
          }
        }
        printf("Intersection\n");
        situation = 0;//intersection
        avpr=0;
        break;
      case TG:
        CM_setupMoteur(vitesse-27, vitesse-2,1,1,0); //test
        delay(400); //test
        printf("Tourner Gauche\n");
        while((digitalRead(capteurAv)==1) || digitalRead(capteurG)==1){//on avance pour ne plus detecter l'intersection
          CM_setupMoteur(vitesse-30, vitesse-3, 1, 1, 0);
        }
        situation = 3;//gauche
        while(digitalRead(capteurAv) != 1){
          if(obstacle == 0){
            CM_tourner(GAUCHE, vitesse, obstacle);
          }
        }
        situation = 0;//intersection
        printf("intersection\n");
        avpr = 0;
        break;
      default:
        break;   
      }
    i=i+1;
    CM_setupMoteur(0,0,1,1,1);
    //delay(5000);
  }
  int j = 0;
  while(j<50000){
    CM_avancer(vitesse,vitesse,1,1,0);
    j=j+1;
  }
  //CM_setupMoteur(vitesse,vitesse,1,1,0);
  delay(500);
  situation = 4;//fin du parcours
  //CM_emote(vitesse);
  CM_setupMoteur(0,0,1,1,1);
  
}
  
  

      
