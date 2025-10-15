#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <wiringPiI2C.h>
#include <linux/input.h>
#include <wiringPi.h>
#include <softPwm.h>
#include <sys/time.h> 
#include <lcd.h>

#include <pthread.h>

#include "../include/elec/ecran.h"
#include "../include/elec/codeMoteur.h"
#include "../include/elec/capteurObstacle.h"
#include "../include/elec/capteurLigne.h"
#include "../include/elec/buzz.h"
#include "../include/elec/setup.h"
#include "../include/elec/parcoursLabyrinthe.h"


#include "../include/Types/ListeDOrdre.h"


LDO_ListeDOrdre recupererOrdres(){
  char lOrdre[3];  
    int i = 1;
    LDO_ListeDOrdre laListe;

    laListe = LDO_liste();  
    printf("La liste des ordres pour arriver à la sortie est : \n");
    do {
        scanf("%2s", lOrdre);  

        if (strcmp(lOrdre, "AV") == 0) {
            LDO_inserer(&laListe, AV, i);
            printf("AV\n");
            i++;
        } else if (strcmp(lOrdre, "TG") == 0) {
            LDO_inserer(&laListe, TG, i);
            printf("TG\n");
            i++;
        } else if (strcmp(lOrdre, "TD") == 0) {
            LDO_inserer(&laListe, TD, i);
            printf("TD\n");
            i++;
        } 
    }
    while (lOrdre[0] != '.');

    return laListe;
}


int main(int argc ,char **argv){

  LDO_ListeDOrdre listeOrdres1= recupererOrdres();
    if (wiringPiSetup()==-1){
		printf("Problème d'initialization\n") ;
    }//init wiringpi
    
    SET_setupBranchement();

    int lcdHandle = LCD_initLcd();//init écran lcd
  
    PL_parcoursLabyrinthe(51, lcdHandle, listeOrdres1);

    CM_setupMoteur(80,80,1,1,1);

    return 0;
}
