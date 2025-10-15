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

#define BUZZ 40;

void SET_setupBranchement() {
  wiringPiSetupGpio();
  pinMode(BUZZ, OUTPUT);  
}

void BUZZ_buzz (){
  digitalWrite(BUZZ,1);//acitve le buzzeur
}

void BUZZ_debuzz (){
  digitalWrite(BUZZ,0);//desactive le buzzeur
}


void main(){
  SET_setupBranchement();
  while(1){
    delay(1000);
    BUZZ_buzz();
    delay(1000);
    BUZZ_debuzz();
  }
}
