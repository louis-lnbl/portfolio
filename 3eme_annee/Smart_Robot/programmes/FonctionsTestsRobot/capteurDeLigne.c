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

#define capteurAv 29
#define capteurD 33
#define capteurG 37
#define capteurAr 31

void SET_setupBranchement() {
  wiringPiSetupGpio();
  pinMode(capteurAr, INPUT);
  pinMode(capteurAv, INPUT);
  pinMode(capteurD, INPUT);
  pinMode(capteurG, INPUT);
}

void main(){
  SET_setupBranchement();
  int i=1;
  while(1){
    printf("1: avant, 2:arriere, 3:Gauche, 4:Droite\n");
    scanf(%d,i);
    switch (i){
    case (1):
      printf("%d\n",digitalRead(capteurAv)); //les digitalread ne sont pas dans le code !!
      break;
    case (2):
      printf("%d\n", digitalRead(capteurAr));
      break;
    case (3):
      printf("%d\n", digitalRead(capteurG));
      break;
    case (4):
      printf("%d\n", digitalRead(capteurD));
      break;
    default:
      break;
    }
    delay(250);
  }
}