#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <stdbool.h>
#include <string.h>
#include "../../include/Labyrinthe/gestionFichier.h"
#include "../../include/Types/ListeDeCDC.h"
#include "../../include/Types/Direction.h"

void GF_gestionDuFichier(char* nomFichier, unsigned int *largeur, unsigned int* caseEntree, unsigned int *caseSortie, Direction *directionPorteEntree, Direction *directionPorteSortie, LDCDC_ListeDeCDC *listeLiaisons){
  char* modeDOuverture = "r";
  FILE* fichier = fopen(nomFichier,modeDOuverture);

  unsigned int val = 0;
  unsigned int i = 0;
  int nombreDeCaractereMaxAlire = 30;
  char* point = ".";
  if (fichier != NULL){

    char chaine[30] ="";
    bool EstunPoint = false;

    fgets(chaine,nombreDeCaractereMaxAlire,fichier);
    *largeur = (unsigned int)atoi(chaine);

    fgets(chaine,nombreDeCaractereMaxAlire,fichier);
    while (!(chaine[i] == 'D' || chaine[i] == 'G' || chaine[i] == 'H' || chaine[i] == 'B' )){
      val = val*10 + (chaine[i]-'0');
      i++;
    }
    *caseEntree = val;
    switch (chaine[i]){
	case 'D':
	  *directionPorteEntree = D;
	  break;
	case 'G':
	  *directionPorteEntree = G;
	  break;
	case 'H':
	  *directionPorteEntree = H;
	  break;
	case 'B':
	  *directionPorteEntree = B;
	  break;
      }

    val = 0;
    i=0;
    
    fgets(chaine,nombreDeCaractereMaxAlire,fichier);
    while (!(chaine[i] == 'D' || chaine[i] == 'G' || chaine[i] == 'H' || chaine[i] == 'B' )){
      val = val*10 + (chaine[i]-'0');
      i++;
    }
    *caseSortie = val;
    switch (chaine[i]){
	case 'D':
	  *directionPorteSortie = D;
	  break;
	case 'G':
	  *directionPorteSortie = G;
	  break;
	case 'H':
	  *directionPorteSortie = H;
	  break;
	case 'B':
	  *directionPorteSortie = B;
	  break;
    }


    while (fgets(chaine,nombreDeCaractereMaxAlire,fichier) != NULL && !(EstunPoint)){
      if (chaine[0] == point[0]){
	EstunPoint = true;
      }
      else {
	LDCDC_inserer(listeLiaisons,chaine,LDCDC_longueur(*listeLiaisons)+1);
      }
    }
    fclose(fichier);

  }
  else{
    errno = 1;
    printf("fichier vide ou inexistant");
  }
}


