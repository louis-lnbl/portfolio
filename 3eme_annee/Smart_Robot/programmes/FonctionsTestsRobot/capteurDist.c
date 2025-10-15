
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <linux/input.h>
#include <wiringPi.h>
#include <softPwm.h>
#include <sys/time.h> 


#define  Trig    18  
#define  Echo    16


void SET_setupBranchement() {
  wiringPiSetupGpio();
  pinMode(Echo, INPUT);//captObstacle
  pinMode(Trig, OUTPUT);  
}


float CO_distanceMesure()  
{  
  struct timeval tv1;  
  struct timeval tv2;  
  long start, stop;  
  float dis;  

  digitalWrite(Trig, LOW);  
  delayMicroseconds(2);  BUZZ // Pourquoi un Buzz ??

			   digitalWrite(Trig, HIGH);  //produce a pulse
  delayMicroseconds(10); 
  digitalWrite(Trig, LOW);  
  while(!(digitalRead(Echo) == 1));  
  gettimeofday(&tv1, NULL);           //current time 
  while(!(digitalRead(Echo) == 0));  
  gettimeofday(&tv2, NULL);           //current time  
  start = tv1.tv_sec * 1000000 + tv1.tv_usec; 
  stop  = tv2.tv_sec * 1000000 + tv2.tv_usec;  

  dis = (float)(stop - start) / 1000000 * 34000 / 2;  //count the distance 
  //printf("distance = %f",dis);

  return dis;  //Calcule la difference entre le moment d'émission de l'impulsion
  // du son avec le moment d'interception afin de calculer la distance entre le capteur et l'objet
}



void main(){
  float dist;
  SET_setupBranchement()
    while(1){
      dist = CO_distanceMesure();
      printf("la distance est de : %f",dist);
      delay(250);
    }
}
