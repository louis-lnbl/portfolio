#include <stdio.h>
#include <wiringPi.h>

int moteurEN12 = 19 ; //enable gauche
int moteur1A = 27 ;//avancer droit
int moteur2A = 9 ;//arriere droit
int moteur3A = 17 ;//avancer gauche
int moteur4A = 4 ;//reculer gauche

int moteurEN34 = 12 ; //enable droit
int valeur = 0;
int sens = 1;

void setup(int pourcentageG, int pourcentageD,int duree,int stop) {
  wiringPiSetupGpio();
  
  wiringPiSetupGpio();
  pinMode(moteurEN12,PWM_OUTPUT);
  pinMode(moteur1A,OUTPUT);
  pinMode(moteur2A,OUTPUT);
  pinMode(moteur3A,OUTPUT);
  pinMode(moteur4A,OUTPUT);
  pinMode(moteurEN34,PWM_OUTPUT);


  digitalWrite(moteur1A,0 && !stop);
  digitalWrite(moteur2A,0 && !stop);
  digitalWrite(moteur3A,0 && !stop);
  digitalWrite(moteur4A,1 && !stop);

  pwmWrite(moteurEN12,(1024*pourcentageG)/100);
  pwmWrite(moteurEN34,(1024*pourcentageD)/100);
  delay(duree);
  digitalWrite(moteurEN12,LOW);
  digitalWrite(moteurEN34,LOW);
}

void main(void){
  // tests vitesse moteur pour avancer droit :
  int pourcentageG;
  int pourcentageD;
  int duree;
  printf("pourcentage moteur gauche \n ");
  scanf("%d", &pourcentageG);
  printf("pourcentage moteur droit \n ");
  scanf("%d", &pourcentageD);
  printf("durÃ©e de l'opÃ©ration ?  \n ");
  scanf("%d", &duree);
  setup(pourcentageG,pourcentageD,duree,0 );
  setup(pourcentageG,pourcentageD,duree,1);
}