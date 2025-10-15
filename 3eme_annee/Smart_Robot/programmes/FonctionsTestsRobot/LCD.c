#include <wiringPi.h>  
#include <stdio.h>  
#include <sys/time.h> 

#include <pcf8574.h>
#include <stdlib.h> 
#include <wiringPiI2C.h>
#include <stdbool.h>

#include <unistd.h>
#include <softPwm.h>
#include <math.h>
#include <time.h>
#include <string.h>
#include <stdint.h>

#define        AF_BASE    64
#define        AF_RS                (AF_BASE + 0)
#define        AF_RW                (AF_BASE + 1)
#define        AF_E                 (AF_BASE + 2)
#define        AF_LED               (AF_BASE + 3)

#define        AF_DB4               (AF_BASE + 4)
#define        AF_DB5               (AF_BASE + 5)
#define        AF_DB6               (AF_BASE + 6)
#define        AF_DB7               (AF_BASE + 7)




int LCD_initLcd(){

  int lcdHandle;

  int i;

  pcf8574Setup(AF_BASE,0x27);
    
  lcdHandle = lcdInit (2, 16, 4, AF_RS, AF_E, AF_DB4,AF_DB5,AF_DB6,AF_DB7, 0,0,0,0) ;
    
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


void LCD_afficherAvancer( int lcdHandle) {
  lcdClear(lcdHandle);
  lcdPosition(lcdHandle, 0, 1);
  lcdPuts(lcdHandle, "En avant !"); 
}

void LCD_afficherVirageDroite( int lcdHandle) {
  lcdClear(lcdHandle);
  lcdPosition(lcdHandle, 0, 1);
  lcdPuts(lcdHandle, "Virage a droite"); 
}

void LCD_afficherVirageGauche( int lcdHandle) {
  lcdClear(lcdHandle);
  lcdPosition(lcdHandle, 0, 1);
  lcdPuts(lcdHandle, "Virage a gauche"); 
}


void LCD_afficherIntersection(int lcdHandle) {
  lcdClear(lcdHandle);
  lcdPosition(lcdHandle, 0, 1);
  lcdPuts(lcdHandle, "Intersection detectee"); 
}

void LCD_afficherArretUrgence(int lcdHandle) {
  lcdClear(lcdHandle);
  lcdPosition(lcdHandle, 0, 1);
  lcdPuts(lcdHandle, "Arret d'urgence"); 
}

void LCD_afficherFin(int lcdHandle){
  lcdClear(lcdHandle);
  lcdPosition(lcdHandle, 0, 1);
  lcdPuts(lcdHandle, "Sortie trouvee !"); 
}



void main (){
  if (wiringPiSetup()==-1){
		printf("Problème d'initialization\n") ;
    }//init wiringpi
  int lcdHandle = initLcd();//init écran lcd
  //Faire les tests
  delay(1000);
  LCD_afficherAvancer(lcdHandle);
  delay(1000);
  LCD_afficherVirageDroite(lcdHandle);
  delay(1000);
  LCD_afficherVirageGauche(lcdHandle);
  delay(1000);
  LCD_afficherIntersection(lcdHandle);
  delay(1000);
  LCD_afficherArretUrgence(lcdHandle);
  delay(1000);
  LCD_afficherFin(lcdHandle);

}
