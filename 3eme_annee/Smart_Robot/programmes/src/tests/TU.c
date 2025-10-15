/**
 * @file TU.c
 * @brief Tests Unitaires des .c partie algo uniquement, la partie electrique sera testé directement sur le robot (carte RPI)
 */

#include <stdio.h>
#include <CUnit/Basic.h>
#include <string.h>
#include <stdbool.h>


#include "../../include/Labyrinthe/casesEnOrdres.h"
#include "../../include/Labyrinthe/initialisationLabyrinthe.h"
#include "../../include/Labyrinthe/traitementLabyrinthe.h"
#include "../../include/Labyrinthe/trouverChemin.h"

#include "../../include/Types/Ordre.h"
#include "../../include/Types/Direction.h"
#include "../../include/Types/ListeDeCDC.h"
#include "../../include/Types/labyrinthe.h"

// penser a faire des fonction pour egalites de listes 

// si utilisé dans le futur (a modifier)
int float_egaux(float a, float b, float epsilon) {
    return fabs(a - b) < epsilon;
}



// partie TU ConversionCases en ordres 
void test_ConversionCaseOrdreAvancer(void){
    unsigned int case1 = 6;
    unsigned int case2 = 11;
    unsigned int case3 = 16;
    Ordre OrdreDonnee;
    OrdreDonnee = casesEnOrdres(case1 , case2 , case3);
    CU_ASSERT_TRUE(OrdreDonnee == AV);
}
void test_ConversionCaseOrdreTournerGauche(void){
    unsigned int case1 = 6;
    unsigned int case2 = 11;
    unsigned int case3 = 12;
    Ordre OrdreDonnee;
    OrdreDonnee = casesEnOrdres(case1 , case2 , case3);
    CU_ASSERT_TRUE(OrdreDonnee == TG);
}
void test_ConversionCaseOrdreTournerDroit(void){
    unsigned int case1 = 11;
    unsigned int case2 = 12;
    unsigned int case3 = 17;
    Ordre OrdreDonnee;
    OrdreDonnee = casesEnOrdres(case1 , case2 , case3);
    CU_ASSERT_TRUE(OrdreDonnee == TD);
}




// partie initialisation Labyrinthe 
void test_initLaby(void){
    unsigned int largeurLabyrinthe = 5;
    unsigned int entree = 6;
    unsigned int sortie = 20;
    Direction directionEntree = D;
    Direction directionSortie = D;
    LDCDC_ListeDeCDC liaisonsCases;
    LAB_Labyrinthe Laby;

    Laby = creerLabyrinthe(largeurLabyrinthe,entree,sortie,directionEntree,directionSortie,liaisonsCases);
    CU_ASSERT_TRUE();
}

void test_casesAccessiblesLabyTrue(void){
    unsigned int largeurLabyrinthe = 5;
    unsigned int entree = 6;
    unsigned int sortie = 20;
    Direction directionEntree = D;
    Direction directionSortie = D;
    LDCDC_ListeDeCDC liaisonsCases;
    LAB_Labyrinthe Laby;

    Laby = creerLabyrinthe(largeurLabyrinthe,entree,sortie,directionEntree,directionSortie,liaisonsCases);

    unsigned int case1 = 23;
    unsigned int case2 = 24;
    bool estAccessible = false;
    estAccessible = estCaseAccessible(Laby,case1,case2);

    CU_ASSERT_TRUE(estAccessible == true);
}

void test_casesAccessiblesLabyFalse(void){
    unsigned int largeurLabyrinthe = 5;
    unsigned int entree = 6;
    unsigned int sortie = 20;
    Direction directionEntree = D;
    Direction directionSortie = D;
    LDCDC_ListeDeCDC liaisonsCases;
    LAB_Labyrinthe Laby;

    Laby = creerLabyrinthe(largeurLabyrinthe,entree,sortie,directionEntree,directionSortie,liaisonsCases);

    unsigned int case1 = 12;
    unsigned int case2 = 7;
    bool estAccessible = true;
    estAccessible = estCaseAccessible(Laby,case1,case2);

    CU_ASSERT_TRUE(estAccessible == false);
}

void test_TestcreerPassageTrue(void){
    unsigned int largeurLabyrinthe = 5;
    unsigned int entree = 6;
    unsigned int sortie = 20;
    Direction directionEntree = D;
    Direction directionSortie = D;
    LDCDC_ListeDeCDC liaisonsCases = 12-13;
    LAB_Labyrinthe Laby;

    Laby = creerLabyrinthe(largeurLabyrinthe,entree,sortie,directionEntree,directionSortie,liaisonsCases);


    creerPassage(&Laby, liaisonsCases);

    unsigned int case1 = 12;
    unsigned int case2 = 13;
    bool estAccessible = false;
    estAccessible = estCaseAccessible(Laby,case1,case2);
    CU_ASSERT_TRUE(estAccessible == true);
}

void test_TestcreerPassageFalse(void){
    unsigned int largeurLabyrinthe = 5;
    unsigned int entree = 6;
    unsigned int sortie = 20;
    Direction directionEntree = D;
    Direction directionSortie = D;
    LDCDC_ListeDeCDC liaisonsCases = 12-13;
    LAB_Labyrinthe Laby;

    Laby = creerLabyrinthe(largeurLabyrinthe,entree,sortie,directionEntree,directionSortie,liaisonsCases);


    creerPassage(&Laby, liaisonsCases);

    unsigned int case1 = 12;
    unsigned int case2 = 11;
    bool estAccessible = true;
    estAccessible = estCaseAccessible(Laby,case1,case2);
    CU_ASSERT_TRUE(estAccessible == false);
}




// traitement du labyrinthe et solution de sortie 

void test_SolutionLaby(void){
  unsigned int largeurLabyrinthe = 5;
  unsigned int entree = 6;
  unsigned int sortie = 20;
  Direction directionEntree = D;
  Direction directionSortie = D;
  LDCDC_ListeDeCDC liaisonsCases = 1-6  2-3  3-4  4-5  4-9  5-10  6-11  7-8  8-13  9-14  10-15  11-12  11-16  12-13  12-17  14-19  16-21  17-22  18-23  19-24  20-25 22-23  23-24  24-25;
  LAB_Labyrinthe Laby;

  Laby = creerLabyrinthe(largeurLabyrinthe,entree,sortie,directionEntree,directionSortie,liaisonsCases);



  LDO_ListeDOrdre resultat; 

  resultat = LDO_ListeDOrdre resolution(LAB_Labyrinthe laby);

  LDO_ListeDOrdre resultatAttendu =  LDO_liste();
  LDO_inserer(&resultatAttendu,AV,1);
  LDO_inserer(&resultatAttendu,TD,2);
  LDO_inserer(&resultatAttendu,AV,3);
  LDO_inserer(&resultatAttendu,TG,4);
  LDO_inserer(&resultatAttendu,AV,5);
  LDO_inserer(&resultatAttendu,TD,6);
  LDO_inserer(&resultatAttendu,AV,7);
  LDO_inserer(&resultatAttendu,TG,8);
  LDO_inserer(&resultatAttendu,AV,9);
  LDO_inserer(&resultatAttendu,AV,10);
  LDO_inserer(&resultatAttendu,AV,11);
  LDO_inserer(&resultatAttendu,TG,12);
  LDO_inserer(&resultatAttendu,AV,13);
  LDO_inserer(&resultatAttendu,TD,14);
  LDO_inserer(&resultatAttendu,AV,15);
    
   
    CU_ASSERT_TRUE(resultat == resultatAttendu)
}




// trouvée chemin 

void test_trouveLesChemins(void){



}




int init_suite_success(void) { 
  // defini les var globales du sys 
  return 0; 
}

int clean_suite_success(void) { 
  return 0; 
}

int main(int argc, char* *argv){
  CU_pSuite pSuiteBoiteBlanche = NULL;
  CU_pSuite pSuiteBoiteNoire = NULL;

  // initialisation du registre de tests 
  if (CUE_SUCCESS != CU_initialize_registry())
    return CU_get_error();

  // ajout d'une suite de test, je ne sais pas si on a des tests boites blanches a voir 
  pSuiteBoiteBlanche = CU_add_suite("Tests (boite blanche)", init_suite_success, clean_suite_success);
  if (NULL == pSuiteBoiteBlanche) {
    CU_cleanup_registry();
    return CU_get_error();
  }

  pSuiteBoiteNoire = CU_add_suite("Tests (boite noire)", init_suite_success, clean_suite_success);
  if (NULL == pSuiteBoiteNoire) {
    CU_cleanup_registry();
    return CU_get_error();
  }  

  // Ajout des tests unitaires 

  if (   
    
       (NULL == CU_add_test(pSuiteBoiteNoire, "erreur conversion case en ordre avancer ",test_ConversionCaseOrdreAvancer ))
    || (NULL == CU_add_test(pSuiteBoiteNoire, "erreur conversion case en ordre tourner a gauche",test_ConversionCaseOrdreTournerGauche ))
    || (NULL == CU_add_test(pSuiteBoiteNoire, "erreur conversion case en ordre tourner a droite",test_ConversionCaseOrdreTournerDroit ))
    || (NULL == CU_add_test(pSuiteBoiteNoire, "erreur initialisation du labyrinthe",test_initLaby ))
    || (NULL == CU_add_test(pSuiteBoiteNoire, "erreur case acccessibles ",test_casesAccessiblesLabyTrue))
    || (NULL == CU_add_test(pSuiteBoiteNoire, "erreur case non accessibles ",test_casesAccessiblesLabyFalse ))
    || (NULL == CU_add_test(pSuiteBoiteNoire, "erreur creer passage ",test_TestcreerPassageTrue ))
    || (NULL == CU_add_test(pSuiteBoiteNoire, "erreur non creation du passage ",test_TestcreerPassageFalse))
    || (NULL == CU_add_test(pSuiteBoiteNoire, "erreur solution du labyrinthe ",test_SolutionLaby ))
    || (NULL == CU_add_test(pSuiteBoiteNoire, "erreur trouver les chemins de sortie du labyrinthe ",test_trouveLesChemins ))
    // penser a rajouter les derniers tests unitaires pas encore creer 
    )
    {
      CU_cleanup_registry();
      return CU_get_error();
    }

  // Lancement des tests 
  CU_basic_set_mode(CU_BRM_VERBOSE);
  CU_basic_run_tests();
  printf("\n");
  CU_basic_show_failures(CU_get_failure_list());
  printf("\n\n");

  // Nettoyage du registre 
  CU_cleanup_registry();
  return CU_get_error();
}
