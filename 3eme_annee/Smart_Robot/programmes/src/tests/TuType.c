/**
 * @file TUType.c
 * @brief Tests Unitaires des .c partie algo des types de données uniquement. 
 */

#include <CUnit/CUnit.h>
#include <CUnit/TestDB.h>
#include <CUnit/TestRun.h>
#include <stdio.h>
#include <CUnit/Basic.h>
#include <string.h>
#include <stdbool.h>

#include "../../include/Types/caseEtDirection.h"
#include "../../include/Types/EnsembleDeDirection.h"
#include "../../include/Types/EnsembleDeNNN.h"
#include "../../include/Types/EnsembleDePileDeNNN.h"
#include "../../include/Types/PileDeNNN.h"
#include "../../include/Types/ListeChaineeDeCDC.h"
#include "../../include/Types/ListeChaineeDeDirection.h"
#include "../../include/Types/ListeChaineeDeNNN.h"
#include "../../include/Types/ListeChaineeDOrdre.h"
#include "../../include/Types/ListeChaineeDePileDeNNN.h"
#include "../../include/Types/ListeDeCDC.h"
#include "../../include/Types/ListeDeNNN.h"
#include "../../include/Types/ListeDOrdre.h"

// si utilisé dans le futur (a modifier)
int float_egaux(float a, float b, float epsilon) {
    return fabs(a - b) < epsilon;
}



// cases et directions 

void test_CD_obtenirCase1(void){

    unsigned int case1 = 3 ;
    Direction direction1 = D;
    CD_CaseEtDirection cd = CD_caseEtDirection(case1,direction1);

    unsigned int resultat;
    unsigned int resultatAttendu = 3;
    resultat =  CD_obtenirCase(cd);
    CU_ASSERT_TRUE(resultat == resultatAttendu);
}

void test_CD_obtenirCase2(void){

    unsigned int case1 = 5 ;
    Direction direction1 = G;
    CD_CaseEtDirection cd = CD_caseEtDirection(case1,direction1);

    unsigned int resultat;
    unsigned int resultatAttendu = 5;
    resultat =  CD_obtenirCase(cd);
    CU_ASSERT_TRUE(resultat == resultatAttendu);
}

void test_CD_obtenirCase3(void){

    unsigned int case1 = 6 ;
    Direction direction1 = H;
    CD_CaseEtDirection cd = CD_caseEtDirection(case1,direction1);

    unsigned int resultat;
    unsigned int resultatAttendu = 6;
    resultat =  CD_obtenirCase(cd);
    CU_ASSERT_TRUE(resultat == resultatAttendu);
}

void test_CD_obtenirDirection1(void){

    unsigned int case1 = 6 ;
    Direction direction1 = D;
    CD_CaseEtDirection cd = CD_caseEtDirection(case1,direction1);

    Direction resultat;
    Direction resultatAttendu = D;
    resultat =  CD_obtenirDirection(cd);
    CU_ASSERT_TRUE(resultat == resultatAttendu);
}


void test_CD_obtenirDirection2(void){

    unsigned int case1 = 5 ;
    Direction direction1 = H;
    CD_CaseEtDirection cd = CD_caseEtDirection(case1,direction1);

    Direction resultat;
    Direction resultatAttendu = H;
    resultat =  CD_obtenirDirection(cd);
    CU_ASSERT_TRUE(resultat == resultatAttendu);
}

void test_CD_obtenirDirection3(void){

    unsigned int case1 = 9 ;
    Direction direction1 = H;
    CD_CaseEtDirection cd = CD_caseEtDirection(case1,direction1);

    Direction resultat;
    Direction resultatAttendu = H;
    resultat =  CD_obtenirDirection(cd);
    CU_ASSERT_TRUE(resultat == resultatAttendu);
}

void test_CD_FixerDirectionTest1(void){

    unsigned int case1 = 6 ;
    Direction direction1 = H;
    CD_CaseEtDirection cd = CD_caseEtDirection(case1,direction1);

    Direction nouvelleDirection = B;

    CD_fixerDirection(&cd, nouvelleDirection);
    Direction resultat;
    Direction resultatAttendu = B;
    resultat =  CD_obtenirDirection(cd);
    CU_ASSERT_TRUE(resultat == resultatAttendu);
}

void test_CD_FixerDirectionTest2(void){

    unsigned int case1 = 5 ;
    Direction direction1 = H;
    CD_CaseEtDirection cd = CD_caseEtDirection(case1,direction1);

    Direction nouvelleDirection = G;

    CD_fixerDirection(&cd, nouvelleDirection);
    Direction resultat;
    Direction resultatAttendu = G;
    resultat =  CD_obtenirDirection(cd);
    CU_ASSERT_TRUE(resultat == resultatAttendu);
}

void test_CD_FixerDirectionTest3(void){

    unsigned int case1 = 2 ;
    Direction direction1 = H;
    CD_CaseEtDirection cd = CD_caseEtDirection(case1,direction1);

    Direction nouvelleDirection = D;

    CD_fixerDirection(&cd, nouvelleDirection);
    Direction resultat;
    Direction resultatAttendu = D;
    resultat =  CD_obtenirDirection(cd);
    CU_ASSERT_TRUE(resultat == resultatAttendu);
}

void test_CD_FixerDirectionTest4(void){

    unsigned int case1 = 2 ;
    Direction direction1 = H;
    CD_CaseEtDirection cd = CD_caseEtDirection(case1,direction1);

    Direction nouvelleDirection = H;

    CD_fixerDirection(&cd, nouvelleDirection);
    Direction resultat;
    Direction resultatAttendu = H;
    resultat =  CD_obtenirDirection(cd);
    CU_ASSERT_TRUE(resultat == resultatAttendu);
}


void test_CD_FixerCaseTest1(void){

    unsigned int case1 = 2 ;
    Direction direction1 = H;
    CD_CaseEtDirection cd = CD_caseEtDirection(case1,direction1);

    unsigned int nouvelleCase = 1;

    CD_fixerCase(&cd, nouvelleCase);
    unsigned int resultat;
    unsigned int resultatAttendu = 1;
    resultat =  CD_obtenirCase(cd);
    CU_ASSERT_TRUE(resultat == resultatAttendu);
}

void test_CD_FixerCaseTest2(void){

    unsigned int case1 = 2 ;
    Direction direction1 = H;
    CD_CaseEtDirection cd = CD_caseEtDirection(case1,direction1);

    unsigned int nouvelleCase = 2;

    CD_fixerCase(&cd, nouvelleCase);
    unsigned int resultat;
    unsigned int resultatAttendu = 2;
    resultat =  CD_obtenirCase(cd);
    CU_ASSERT_TRUE(resultat == resultatAttendu);
}


// ensemble de direction 
void test_EDD_AjoutEtSuppression(void){

    EDD_EnsembleDeDirection EnsembleDeDirection;
    EnsembleDeDirection = EDD_ensemble();

    Direction directionVoulue = H;

    EDD_ajouter(&EnsembleDeDirection,directionVoulue);
    EDD_retirer(&EnsembleDeDirection,directionVoulue);

    unsigned int resultat = EDD_cardinalite(EnsembleDeDirection);
    unsigned int resultatAttendu =0;

    CU_ASSERT_TRUE(resultat == resultatAttendu);
}

void test_EDD_EstPresent1(void){

    EDD_EnsembleDeDirection EnsembleDeDirection;
    EnsembleDeDirection = EDD_ensemble();

    Direction directionVoulue = B;

    bool resultatAttendu = true;
    bool resultat;
    EDD_ajouter(&EnsembleDeDirection,directionVoulue);
    resultat = EDD_estPresent(EnsembleDeDirection,directionVoulue);

    CU_ASSERT_TRUE( resultatAttendu == resultat);
}

void test_EDD_EstPresent2(void){

    EDD_EnsembleDeDirection EnsembleDeDirection;
    EnsembleDeDirection = EDD_ensemble();

    Direction directionVoulue = H;
    Direction directionDemandee = B;

    bool resultatAttendu = false;
    bool resultat;
    EDD_ajouter(&EnsembleDeDirection,directionVoulue);
    resultat = EDD_estPresent(EnsembleDeDirection,directionDemandee);

    CU_ASSERT_TRUE( resultatAttendu == resultat);
}


void test_EDD_CardinaliteVide(void){
    EDD_EnsembleDeDirection EnsembleDeDirection;
    EnsembleDeDirection = EDD_ensemble();

    unsigned int resultat;
    unsigned int resultatAttendu = 0;
    resultat = EDD_cardinalite(EnsembleDeDirection);

    CU_ASSERT_TRUE(resultat == resultatAttendu);
}

void test_EDD_CardinaliteN(void){
    EDD_EnsembleDeDirection EnsembleDeDirection= EDD_ensemble();

    unsigned int resultat;
    unsigned int resultatAttendu = 2;
    EDD_ajouter(&EnsembleDeDirection,H);
    EDD_ajouter(&EnsembleDeDirection,B);


    resultat = EDD_cardinalite(EnsembleDeDirection);

    CU_ASSERT_TRUE(resultat == resultatAttendu);
}

void test_EDD_UnionAjout1(void){

    EDD_EnsembleDeDirection EnsembleDeDirection1;
    EnsembleDeDirection1 = EDD_ensemble();
    EDD_ajouter(&EnsembleDeDirection1,H);
    EDD_ajouter(&EnsembleDeDirection1,B);
    EDD_EnsembleDeDirection EnsembleDeDirection2;
    EnsembleDeDirection2 = EDD_ensemble();
    EDD_ajouter(&EnsembleDeDirection2,D);

    EDD_EnsembleDeDirection total;
    total = EDD_unionEnsemble(EnsembleDeDirection1,EnsembleDeDirection2);

    unsigned int cardinalite1 = EDD_cardinalite(EnsembleDeDirection1);
    unsigned int cardinalite2 = EDD_cardinalite(EnsembleDeDirection2);
    unsigned int cardinaliteTotal = EDD_cardinalite(total);

    CU_ASSERT_TRUE(cardinaliteTotal == cardinalite1 + cardinalite2);
    CU_ASSERT_TRUE(EDD_estPresent(total,H));
    CU_ASSERT_TRUE(EDD_estPresent(total,B));
    CU_ASSERT_TRUE(EDD_estPresent(total,D));
}

void test_EDD_UnionAjout2(void){

    EDD_EnsembleDeDirection EnsembleDeDirection1;
    EnsembleDeDirection1 = EDD_ensemble();
    EDD_ajouter(&EnsembleDeDirection1,G);
    EDD_ajouter(&EnsembleDeDirection1,D);
    EDD_EnsembleDeDirection EnsembleDeDirection2;
    EnsembleDeDirection2 = EDD_ensemble();
    EDD_ajouter(&EnsembleDeDirection2,H);

    EDD_EnsembleDeDirection total;
    total = EDD_unionEnsemble(EnsembleDeDirection2,EnsembleDeDirection1);

    unsigned int cardinalite1 = EDD_cardinalite(EnsembleDeDirection1);
    unsigned int cardinalite2 = EDD_cardinalite(EnsembleDeDirection2);
    unsigned int cardinaliteTotal = EDD_cardinalite(total);

    CU_ASSERT_TRUE(cardinaliteTotal == cardinalite1 + cardinalite2);
    CU_ASSERT_TRUE(EDD_estPresent(total,G));
    CU_ASSERT_TRUE(EDD_estPresent(total,D));
    CU_ASSERT_TRUE(EDD_estPresent(total,H));
    CU_ASSERT_FALSE(EDD_estPresent(total,B))
}

void test_EDD_UnionPasAjout1(void){

    EDD_EnsembleDeDirection EnsembleDeDirection1;
    EnsembleDeDirection1 = EDD_ensemble();
    EDD_ajouter(&EnsembleDeDirection1,H);
    EDD_ajouter(&EnsembleDeDirection1,G);
    EDD_EnsembleDeDirection EnsembleDeDirection2;
    EnsembleDeDirection2 = EDD_ensemble();
    EDD_ajouter(&EnsembleDeDirection2,G);

    EDD_EnsembleDeDirection total;
    total = EDD_unionEnsemble(EnsembleDeDirection1,EnsembleDeDirection2);

    unsigned int cardinalite1 = EDD_cardinalite(EnsembleDeDirection1);
    unsigned int cardinaliteTotal = EDD_cardinalite(total);

    CU_ASSERT_TRUE(cardinaliteTotal == cardinalite1)
    CU_ASSERT_TRUE(EDD_estPresent(total,H));
    CU_ASSERT_TRUE(EDD_estPresent(total,G));
}

void test_EDD_UnionPasAjout2(void){

    EDD_EnsembleDeDirection EnsembleDeDirection1;
    EnsembleDeDirection1 = EDD_ensemble();
    EDD_ajouter(&EnsembleDeDirection1,G);
    EDD_ajouter(&EnsembleDeDirection1,B);
    EDD_EnsembleDeDirection EnsembleDeDirection2;
    EnsembleDeDirection2 = EDD_ensemble();
    EDD_ajouter(&EnsembleDeDirection2,B);

    EDD_EnsembleDeDirection total;
    total = EDD_unionEnsemble(EnsembleDeDirection2,EnsembleDeDirection1);

    unsigned int cardinalite1 = EDD_cardinalite(EnsembleDeDirection1);
    unsigned int cardinaliteTotal = EDD_cardinalite(total);

    CU_ASSERT_TRUE(cardinaliteTotal == cardinalite1)
    CU_ASSERT_TRUE(EDD_estPresent(total,G));
    CU_ASSERT_TRUE(EDD_estPresent(total,B));
}

void test_EDD_UnionVide1(void){

    EDD_EnsembleDeDirection EnsembleDeDirection1;
    EnsembleDeDirection1 = EDD_ensemble();
    EDD_ajouter(&EnsembleDeDirection1,B);
    EDD_ajouter(&EnsembleDeDirection1,G);
    EDD_EnsembleDeDirection EnsembleDeDirection2;
    EnsembleDeDirection2 = EDD_ensemble();

    EDD_EnsembleDeDirection total;
    total = EDD_unionEnsemble(EnsembleDeDirection1,EnsembleDeDirection2);

    unsigned int cardinalite1 = EDD_cardinalite(EnsembleDeDirection1);
    unsigned int cardinaliteTotal = EDD_cardinalite(total);

    CU_ASSERT_TRUE(cardinaliteTotal == cardinalite1);
    CU_ASSERT_TRUE(EDD_estPresent(total,B));
    CU_ASSERT_TRUE(EDD_estPresent(total,G));
}

void test_EDD_UnionVide2(void){

    EDD_EnsembleDeDirection EnsembleDeDirection1;
    EnsembleDeDirection1 = EDD_ensemble();
    EDD_ajouter(&EnsembleDeDirection1,G);
    EDD_ajouter(&EnsembleDeDirection1,D);
    EDD_EnsembleDeDirection EnsembleDeDirection2;
    EnsembleDeDirection2 = EDD_ensemble();

    EDD_EnsembleDeDirection total;
    total = EDD_unionEnsemble(EnsembleDeDirection2,EnsembleDeDirection1);

    unsigned int cardinalite1 = EDD_cardinalite(EnsembleDeDirection1);
    unsigned int cardinaliteTotal = EDD_cardinalite(total);

    CU_ASSERT_TRUE(cardinaliteTotal == cardinalite1);
    CU_ASSERT_TRUE(EDD_estPresent(total,G));
    CU_ASSERT_TRUE(EDD_estPresent(total,D));
}


void test_EDD_Intersection1(void){

    EDD_EnsembleDeDirection EnsembleDeDirection1;
    EnsembleDeDirection1 = EDD_ensemble();
    EDD_ajouter(&EnsembleDeDirection1,H);
    EDD_ajouter(&EnsembleDeDirection1,B);

    EDD_EnsembleDeDirection EnsembleDeDirection2;
    EnsembleDeDirection2 = EDD_ensemble();
    EDD_ajouter(&EnsembleDeDirection2,B);

    EDD_EnsembleDeDirection total;
    total = EDD_intersection(EnsembleDeDirection1,EnsembleDeDirection2);

    unsigned int cardinaliteTotal = EDD_cardinalite(total);

    CU_ASSERT_TRUE(cardinaliteTotal == 1);
    CU_ASSERT_TRUE(EDD_estPresent(total,B));
    CU_ASSERT_FALSE(EDD_estPresent(total,H));
}


void test_EDD_Intersection2(void){

    EDD_EnsembleDeDirection EnsembleDeDirection1;
    EnsembleDeDirection1 = EDD_ensemble();
    EDD_ajouter(&EnsembleDeDirection1,B);
    EDD_ajouter(&EnsembleDeDirection1,H);

    EDD_EnsembleDeDirection EnsembleDeDirection2;
    EnsembleDeDirection2 = EDD_ensemble();

    EDD_EnsembleDeDirection total;
    total = EDD_intersection(EnsembleDeDirection1,EnsembleDeDirection2);

    unsigned int cardinalite2 = EDD_cardinalite(EnsembleDeDirection2);
    unsigned int cardinaliteTotal = EDD_cardinalite(total);

    CU_ASSERT_TRUE(cardinaliteTotal == cardinalite2);
    CU_ASSERT_FALSE(EDD_estPresent(total,H));
    CU_ASSERT_FALSE(EDD_estPresent(total,B));
    CU_ASSERT_FALSE(EDD_estPresent(total,D));
}

void test_EDD_Intersection3(void){

    EDD_EnsembleDeDirection EnsembleDeDirection1;
    EnsembleDeDirection1 = EDD_ensemble();
    EDD_ajouter(&EnsembleDeDirection1,H);
    EDD_ajouter(&EnsembleDeDirection1,G);

    EDD_EnsembleDeDirection EnsembleDeDirection2;
    EnsembleDeDirection2 = EDD_ensemble();
    EDD_ajouter(&EnsembleDeDirection2,B);
    EDD_ajouter(&EnsembleDeDirection2,D);

    EDD_EnsembleDeDirection EnsembleDeDirection3;
    EnsembleDeDirection3 = EDD_ensemble();

    EDD_EnsembleDeDirection total;
    total = EDD_intersection(EnsembleDeDirection1,EnsembleDeDirection2);

    unsigned int cardinalite3 = EDD_cardinalite(EnsembleDeDirection3);
    unsigned int cardinaliteTotal = EDD_cardinalite(total);

    CU_ASSERT_TRUE(cardinaliteTotal == cardinalite3);
    CU_ASSERT_FALSE(EDD_estPresent(total,G));
    CU_ASSERT_FALSE(EDD_estPresent(total,H));
    CU_ASSERT_FALSE(EDD_estPresent(total,D));
}


void test_EDD_Soustraction1(void){

    EDD_EnsembleDeDirection EnsembleDeDirection1;
    EnsembleDeDirection1 = EDD_ensemble();
    EDD_ajouter(&EnsembleDeDirection1,H);
    EDD_ajouter(&EnsembleDeDirection1,G);

    EDD_EnsembleDeDirection EnsembleDeDirection2;
    EnsembleDeDirection2 = EDD_ensemble();
    EDD_ajouter(&EnsembleDeDirection2,H);
    EDD_ajouter(&EnsembleDeDirection2,D);

    EDD_EnsembleDeDirection EnsembleDeDirection3;
    EnsembleDeDirection3 = EDD_ensemble();
    EDD_ajouter(&EnsembleDeDirection3,G);

    EDD_EnsembleDeDirection total;
    total = EDD_soustraction(EnsembleDeDirection1,EnsembleDeDirection2);

    unsigned int cardinalite3 = EDD_cardinalite(EnsembleDeDirection3);
    unsigned int cardinaliteTotal = EDD_cardinalite(total);

    CU_ASSERT_TRUE(cardinaliteTotal == cardinalite3);
    CU_ASSERT_TRUE(EDD_estPresent(total,G));
    CU_ASSERT_FALSE(EDD_estPresent(total,H));
    CU_ASSERT_FALSE(EDD_estPresent(total,D));
}


void test_EDD_Soustraction2(void){

    EDD_EnsembleDeDirection EnsembleDeDirection1;
    EnsembleDeDirection1 = EDD_ensemble();
    EDD_ajouter(&EnsembleDeDirection1,H);
    EDD_ajouter(&EnsembleDeDirection1,G);

    EDD_EnsembleDeDirection EnsembleDeDirection2;
    EnsembleDeDirection2 = EDD_ensemble();

    EDD_EnsembleDeDirection total;
    total = EDD_soustraction(EnsembleDeDirection1,EnsembleDeDirection2);

    unsigned int cardinalite1 = EDD_cardinalite(EnsembleDeDirection1);
    unsigned int cardinaliteTotal = EDD_cardinalite(total);

    CU_ASSERT_TRUE(cardinaliteTotal == cardinalite1);
    CU_ASSERT_TRUE(EDD_estPresent(total,G));
    CU_ASSERT_TRUE(EDD_estPresent(total,H));
    CU_ASSERT_FALSE(EDD_estPresent(total,D));
}

void test_EDD_Soustraction3(void){

    EDD_EnsembleDeDirection EnsembleDeDirection1;
    EnsembleDeDirection1 = EDD_ensemble();
    EDD_ajouter(&EnsembleDeDirection1,H);
    EDD_ajouter(&EnsembleDeDirection1,G);

    EDD_EnsembleDeDirection EnsembleDeDirection2;
    EnsembleDeDirection2 = EDD_ensemble();

    EDD_EnsembleDeDirection total;
    total = EDD_soustraction(EnsembleDeDirection2,EnsembleDeDirection1);

    unsigned int cardinalite2 = EDD_cardinalite(EnsembleDeDirection2);
    unsigned int cardinaliteTotal = EDD_cardinalite(total);

    CU_ASSERT_TRUE(cardinaliteTotal == cardinalite2);
    CU_ASSERT_FALSE(EDD_estPresent(total,G));
    CU_ASSERT_FALSE(EDD_estPresent(total,H));
    CU_ASSERT_FALSE(EDD_estPresent(total,D));
}

// Ensemble de NNN 

void test_EDNNN_AjoutSuppression1(void){

    EDNNN_EnsembleDeNNN EnsembleDeNNN1 = EDNNN_ensemble();
    unsigned int element = 10;
    EDNNN_ajouter(&EnsembleDeNNN1,element);
    EDNNN_retirer(&EnsembleDeNNN1,element);

    unsigned int resultat = EDNNN_cardinalite(EnsembleDeNNN1);
    unsigned int resultatAttendu = 0;

    CU_ASSERT_TRUE(resultatAttendu == resultat)
}

void test_EDNNN_AjoutSuppression2(void){

    EDNNN_EnsembleDeNNN EnsembleDeNNN1 = EDNNN_ensemble();
    unsigned int element = 10;
    EDNNN_ajouter(&EnsembleDeNNN1,element);

    bool resultat = false;
    resultat = EDNNN_estPresent(EnsembleDeNNN1,element);

    CU_ASSERT_TRUE(resultat)
}

void test_EDNNN_AjoutSuppression3(void){

    EDNNN_EnsembleDeNNN EnsembleDeNNN1 = EDNNN_ensemble();
    unsigned int element = 10;
    EDNNN_ajouter(&EnsembleDeNNN1,element);

    bool resultat = true;
    resultat = EDNNN_estPresent(EnsembleDeNNN1,0);

    CU_ASSERT_FALSE(resultat);
}

void test_EDNNN_Cardinalite1(void){

    EDNNN_EnsembleDeNNN EnsembleDeNNN1 = EDNNN_ensemble();
    for(int i=1;i<10;i++){
        EDNNN_ajouter(&EnsembleDeNNN1,i);
    }
    unsigned int resultat;
    unsigned int resultatAttendu = 9;
    resultat = EDNNN_cardinalite(EnsembleDeNNN1);

    CU_ASSERT_TRUE(resultat == resultatAttendu);
}

void test_EDNNN_Cardinalite2(void){

    EDNNN_EnsembleDeNNN EnsembleDeNNN1 = EDNNN_ensemble();
    unsigned int resultatAttendu = 0;
    unsigned int resultat = EDNNN_cardinalite(EnsembleDeNNN1);

    CU_ASSERT_TRUE(resultat == resultatAttendu);
}

void test_EDNNN_Union1(void){

    EDNNN_EnsembleDeNNN EnsembleDeNNN1 = EDNNN_ensemble();
    for(int i=1;i<5;i++){
        EDNNN_ajouter(&EnsembleDeNNN1,i);
    }
    EDNNN_EnsembleDeNNN EnsembleDeNNN2 = EDNNN_ensemble();
    for(int i=5;i<10;i++){
        EDNNN_ajouter(&EnsembleDeNNN2,i);
    }

    EDNNN_EnsembleDeNNN unionResultat = EDNNN_unionEnsemble(EnsembleDeNNN1, EnsembleDeNNN2);

    unsigned int cardinaliteUnion = EDNNN_cardinalite(unionResultat);
    unsigned int cardinaliteAttendu = 10;

    CU_ASSERT_TRUE(cardinaliteAttendu == cardinaliteUnion);
    for(int i=1;i<10;i++){
      CU_ASSERT_TRUE(EDNNN_estPresent(unionResultat, i));
    }
}

void test_EDNNN_Union2(void){

    EDNNN_EnsembleDeNNN EnsembleDeNNN1 = EDNNN_ensemble();
    for(int i=1;i<7;i++){
        EDNNN_ajouter(&EnsembleDeNNN1,i);
    }
    EDNNN_EnsembleDeNNN EnsembleDeNNN2 = EDNNN_ensemble();
    for(int i=5;i<10;i++){
        EDNNN_ajouter(&EnsembleDeNNN2,i);
    }

    EDNNN_EnsembleDeNNN unionResultat = EDNNN_unionEnsemble(EnsembleDeNNN1, EnsembleDeNNN2);
    
    unsigned int cardinaliteUnion = EDNNN_cardinalite(unionResultat);
    unsigned int cardinaliteAttendu = 10;

    CU_ASSERT_TRUE(cardinaliteAttendu == cardinaliteUnion);
    for(int i=1;i<10;i++){
      CU_ASSERT_TRUE(EDNNN_estPresent(unionResultat, i));
    }
}
 
void test_EDNNN_Union3(void){

    EDNNN_EnsembleDeNNN EnsembleDeNNN1 = EDNNN_ensemble();
    for(int i=1;i<10;i++){
        EDNNN_ajouter(&EnsembleDeNNN1,i);
    }
    EDNNN_EnsembleDeNNN EnsembleDeNNN2 = EDNNN_ensemble();
    for(int i=1;i<15;i++){
        EDNNN_ajouter(&EnsembleDeNNN2,i);
    }

    EDNNN_EnsembleDeNNN unionResultat = EDNNN_unionEnsemble(EnsembleDeNNN1, EnsembleDeNNN2);

    unsigned int cardinaliteUnion = EDNNN_cardinalite(unionResultat);
    unsigned int cardinaliteAttendu = 15;

    CU_ASSERT_TRUE(cardinaliteAttendu == cardinaliteUnion);
    for(int i=1;i<15;i++){
      CU_ASSERT_TRUE(EDNNN_estPresent(unionResultat, i));
    }
}

void test_EDNNN_Union4(void){

    EDNNN_EnsembleDeNNN EnsembleDeNNN1 = EDNNN_ensemble();
    
    EDNNN_EnsembleDeNNN EnsembleDeNNN2 = EDNNN_ensemble();
    for(int i=5;i<15;i++){
        EDNNN_ajouter(&EnsembleDeNNN2,i);
        EDNNN_ajouter(&EnsembleDeNNN1,i);
    }

    EDNNN_EnsembleDeNNN unionResultat = EDNNN_unionEnsemble(EnsembleDeNNN1, EnsembleDeNNN2);

    unsigned int cardinaliteUnion = EDNNN_cardinalite(unionResultat);
    unsigned int cardinaliteAttendu = 15;

    CU_ASSERT_TRUE(cardinaliteAttendu == cardinaliteUnion);
    for(int i=1;i<15;i++){
      CU_ASSERT_TRUE(EDNNN_estPresent(unionResultat, i));
    }
}

void test_EDNNN_Union5(void){

    EDNNN_EnsembleDeNNN EnsembleDeNNN1 = EDNNN_ensemble();
    
    EDNNN_EnsembleDeNNN EnsembleDeNNN2 = EDNNN_ensemble();
    for(int i=5;i<15;i++){
        EDNNN_ajouter(&EnsembleDeNNN2,i);
    }

    EDNNN_EnsembleDeNNN unionResultat = EDNNN_unionEnsemble(EnsembleDeNNN1, EnsembleDeNNN2);

    unsigned int cardinaliteUnion = EDNNN_cardinalite(unionResultat);
    unsigned int cardinaliteAttendu = 15;

    CU_ASSERT_TRUE(cardinaliteAttendu == cardinaliteUnion);
    for(int i=1;i<15;i++){
      CU_ASSERT_TRUE(EDNNN_estPresent(unionResultat, i));
    }
}

void test_EDNNN_Intersection1(void){

    EDNNN_EnsembleDeNNN EnsembleDeNNN1 = EDNNN_ensemble();
    for(int i=1;i<10;i++){
        EDNNN_ajouter(&EnsembleDeNNN1,i);
    }
    
    EDNNN_EnsembleDeNNN EnsembleDeNNN2 = EDNNN_ensemble();
    for(int i=5;i<15;i++){
        EDNNN_ajouter(&EnsembleDeNNN2,i);
    }

    EDNNN_EnsembleDeNNN unionResultat = EDNNN_intersection(EnsembleDeNNN1, EnsembleDeNNN2);

    unsigned int cardinaliteUnion = EDNNN_cardinalite(unionResultat);
    unsigned int cardinaliteAttendu = 5;

    CU_ASSERT_TRUE(cardinaliteAttendu == cardinaliteUnion);
    for(int i=5;i<10;i++){
      CU_ASSERT_TRUE(EDNNN_estPresent(unionResultat, i));
    }
}

void test_EDNNN_Intersection2(void){

    EDNNN_EnsembleDeNNN EnsembleDeNNN1 = EDNNN_ensemble();
    for(int i=4;i<7;i++){
        EDNNN_ajouter(&EnsembleDeNNN1,i);
    }
    
    EDNNN_EnsembleDeNNN EnsembleDeNNN2 = EDNNN_ensemble();
    for(int i=1;i<10;i++){
        EDNNN_ajouter(&EnsembleDeNNN2,i);
    }

    EDNNN_EnsembleDeNNN unionResultat = EDNNN_intersection(EnsembleDeNNN1, EnsembleDeNNN2);

    unsigned int cardinaliteUnion = EDNNN_cardinalite(unionResultat);
    unsigned int cardinaliteAttendu = 3;

    CU_ASSERT_TRUE(cardinaliteAttendu == cardinaliteUnion);
    for(int i=4;i<7;i++){
      CU_ASSERT_TRUE(EDNNN_estPresent(unionResultat, i));
    }
}

void test_EDNNN_Intersection3(void){

    EDNNN_EnsembleDeNNN EnsembleDeNNN1 = EDNNN_ensemble();
    for(int i=1;i<5;i++){
        EDNNN_ajouter(&EnsembleDeNNN1,i);
    }
    
    EDNNN_EnsembleDeNNN EnsembleDeNNN2 = EDNNN_ensemble();
    for(int i=10;i<15;i++){
        EDNNN_ajouter(&EnsembleDeNNN2,i);
    }

    EDNNN_EnsembleDeNNN unionResultat = EDNNN_intersection(EnsembleDeNNN1, EnsembleDeNNN2);
    
    unsigned int cardinaliteUnion = EDNNN_cardinalite(unionResultat);
    unsigned int cardinaliteAttendu = 0;

    CU_ASSERT_TRUE(cardinaliteAttendu == cardinaliteUnion);
    for(int i=1;i<5;i++){
        CU_ASSERT_FALSE(EDNNN_estPresent(unionResultat, i));
    }
    for(int i=10;i<15;i++){
        CU_ASSERT_FALSE(EDNNN_estPresent(unionResultat, i));
    }
}

void test_EDNNN_Soustraction1(void){

    EDNNN_EnsembleDeNNN EnsembleDeNNN1 = EDNNN_ensemble();
    for(int i=1;i<5;i++){
        EDNNN_ajouter(&EnsembleDeNNN1,i);
    }
    
    EDNNN_EnsembleDeNNN EnsembleDeNNN2 = EDNNN_ensemble();
    for(int i=4;i<15;i++){
        EDNNN_ajouter(&EnsembleDeNNN2,i);
    }

    EDNNN_EnsembleDeNNN unionResultat = EDNNN_soustraction(EnsembleDeNNN1, EnsembleDeNNN2);

    unsigned int cardinaliteUnion = EDNNN_cardinalite(unionResultat);
    unsigned int cardinaliteAttendu = 4;

    CU_ASSERT_TRUE(cardinaliteAttendu == cardinaliteUnion);
    for(int i=1;i<4;i++){
      CU_ASSERT_TRUE(EDNNN_estPresent(unionResultat, i));
    }
    for(int i=4;i<15;i++){
      CU_ASSERT_FALSE(EDNNN_estPresent(unionResultat, i));
    }
}

void test_EDNNN_Soustraction2(void){

    EDNNN_EnsembleDeNNN EnsembleDeNNN1 = EDNNN_ensemble();
    for(int i=1;i<5;i++){
        EDNNN_ajouter(&EnsembleDeNNN1,i);
    }
    
    EDNNN_EnsembleDeNNN EnsembleDeNNN2 = EDNNN_ensemble();

    EDNNN_EnsembleDeNNN unionResultat = EDNNN_soustraction(EnsembleDeNNN1, EnsembleDeNNN2);
    
    unsigned int cardinaliteUnion = EDNNN_cardinalite(unionResultat);
    unsigned int cardinaliteAttendu = 4;

    CU_ASSERT_TRUE(cardinaliteAttendu == cardinaliteUnion);
    for(int i=1;i<5;i++){
      CU_ASSERT_TRUE(EDNNN_estPresent(unionResultat, i));
    }
}

void test_EDNNN_Soustraction3(void){

    EDNNN_EnsembleDeNNN EnsembleDeNNN1 = EDNNN_ensemble();
    for(int i=1;i<5;i++){
        EDNNN_ajouter(&EnsembleDeNNN1,i);
    }
    
    EDNNN_EnsembleDeNNN EnsembleDeNNN2 = EDNNN_ensemble();
    for(int i=10;i<15;i++){
        EDNNN_ajouter(&EnsembleDeNNN2,i);
    }

    EDNNN_EnsembleDeNNN unionResultat = EDNNN_soustraction(EnsembleDeNNN1, EnsembleDeNNN2);
    
    unsigned int cardinaliteUnion = EDNNN_cardinalite(unionResultat);
    unsigned int cardinaliteAttendu = 4;

    CU_ASSERT_TRUE(cardinaliteAttendu == cardinaliteUnion);
    for(int i=1;i<5;i++){
      CU_ASSERT_TRUE(EDNNN_estPresent(unionResultat, i));
    }
    for(int i=10;i<15;i++){
      CU_ASSERT_FALSE(EDNNN_estPresent(unionResultat, i));
    }
}


// Ensemble de pile de NNN 

void test_EDPDNNN_AjoutSuppression1(void) {
    EDPDNNN_EnsembleDePileDeNNN EnsembleDePileDeNNN1 = EDPDNNN_ensemble();
    PDNNN_PileDeNNN pile1 = PDNNN_pile();
    PDNNN_empiler(&pile1, 10);
    EDPDNNN_ajouter(&EnsembleDePileDeNNN1, pile1);
    EDPDNNN_retirer(&EnsembleDePileDeNNN1, pile1);
    unsigned int resultat = EDPDNNN_cardinalite(EnsembleDePileDeNNN1);
    unsigned int resultatAttendu = 0;
    CU_ASSERT_TRUE(resultatAttendu == resultat);
}

void test_EDPDNNN_AjoutSuppression2(void) {
    EDPDNNN_EnsembleDePileDeNNN EnsembleDePileDeNNN1 = EDPDNNN_ensemble();
    PDNNN_PileDeNNN pile1 = PDNNN_pile();
    PDNNN_empiler(&pile1, 10);
    EDPDNNN_ajouter(&EnsembleDePileDeNNN1, pile1);
    bool resultat = EDPDNNN_estPresent(EnsembleDePileDeNNN1, pile1);
    CU_ASSERT_TRUE(resultat);
}

void test_EDPDNNN_AjoutSuppression3(void) {
    EDPDNNN_EnsembleDePileDeNNN EnsembleDePileDeNNN1 = EDPDNNN_ensemble();
    PDNNN_PileDeNNN pile1 = PDNNN_pile();
    PDNNN_empiler(&pile1, 10);
    EDPDNNN_ajouter(&EnsembleDePileDeNNN1, pile1);
    PDNNN_PileDeNNN pile2 = PDNNN_pile();
    PDNNN_empiler(&pile2, 20);
    bool resultat = EDPDNNN_estPresent(EnsembleDePileDeNNN1, pile2);
    CU_ASSERT_FALSE(resultat);
}

void test_EDPDNNN_estPresent1(void) {
    EDPDNNN_EnsembleDePileDeNNN EnsembleDePileDeNNN1 = EDPDNNN_ensemble();
    PDNNN_PileDeNNN pile1 = PDNNN_pile();
    PDNNN_empiler(&pile1, 10);
    EDPDNNN_ajouter(&EnsembleDePileDeNNN1, pile1);
    CU_ASSERT_TRUE(EDPDNNN_estPresent(EnsembleDePileDeNNN1, pile1));
}

void test_EDPDNNN_estPresent2(void) {
    EDPDNNN_EnsembleDePileDeNNN EnsembleDePileDeNNN1 = EDPDNNN_ensemble();
    PDNNN_PileDeNNN pile1 = PDNNN_pile();
    PDNNN_empiler(&pile1, 10);
    PDNNN_PileDeNNN pile2 = PDNNN_pile();
    PDNNN_empiler(&pile2, 1);
    EDPDNNN_ajouter(&EnsembleDePileDeNNN1, pile1);
    CU_ASSERT_FALSE(EDPDNNN_estPresent(EnsembleDePileDeNNN1, pile2));
}

void test_EDPDNNN_Cardinalite1(void) {
    EDPDNNN_EnsembleDePileDeNNN EnsembleDePileDeNNN1 = EDPDNNN_ensemble();
    PDNNN_PileDeNNN pile1 = PDNNN_pile();
    PDNNN_empiler(&pile1, 1);
    EDPDNNN_ajouter(&EnsembleDePileDeNNN1, pile1);
    PDNNN_PileDeNNN pile2 = PDNNN_pile();
    PDNNN_empiler(&pile2, 2);
    EDPDNNN_ajouter(&EnsembleDePileDeNNN1, pile2);
    unsigned int resultat = EDPDNNN_cardinalite(EnsembleDePileDeNNN1);
    unsigned int cardinaliteAttendue = 2;
    CU_ASSERT_TRUE(resultat == cardinaliteAttendue);
}

void test_EDPDNNN_Cardinalite2(void) {
    EDPDNNN_EnsembleDePileDeNNN EnsembleDePileDeNNN1 = EDPDNNN_ensemble();
    unsigned int resultat = EDPDNNN_cardinalite(EnsembleDePileDeNNN1);
    unsigned int cardinaliteAttendue = 0;
    CU_ASSERT_TRUE(resultat == cardinaliteAttendue);
}

void test_EDPDNNN_Union1(void) {
    EDPDNNN_EnsembleDePileDeNNN EnsembleDePileDeNNN1 = EDPDNNN_ensemble();
    EDPDNNN_EnsembleDePileDeNNN EnsembleDePileDeNNN2 = EDPDNNN_ensemble();
    PDNNN_PileDeNNN pile1 = PDNNN_pile();
    PDNNN_empiler(&pile1, 1);
    EDPDNNN_ajouter(&EnsembleDePileDeNNN1, pile1);
    PDNNN_PileDeNNN pile2 = PDNNN_pile();
    PDNNN_empiler(&pile2, 2);
    EDPDNNN_ajouter(&EnsembleDePileDeNNN2, pile2);
    PDNNN_PileDeNNN pile3 = PDNNN_pile();
    PDNNN_empiler(&pile3, 3);
    EDPDNNN_ajouter(&EnsembleDePileDeNNN2, pile3);
    EDPDNNN_EnsembleDePileDeNNN unionResultat = EDPDNNN_unionEnsemble(EnsembleDePileDeNNN1, EnsembleDePileDeNNN2);
    CU_ASSERT_TRUE(EDPDNNN_estPresent(unionResultat, pile1));
    CU_ASSERT_TRUE(EDPDNNN_estPresent(unionResultat, pile2));
    CU_ASSERT_TRUE(EDPDNNN_estPresent(unionResultat, pile3));
    unsigned int cardinaliteUnion = EDPDNNN_cardinalite(unionResultat);
    unsigned int cardinaliteAttendue = 3;
    CU_ASSERT_TRUE(cardinaliteUnion == cardinaliteAttendue);
}

void test_EDPDNNN_Union2(void) {
    EDPDNNN_EnsembleDePileDeNNN EnsembleDePileDeNNN1 = EDPDNNN_ensemble();
    EDPDNNN_EnsembleDePileDeNNN EnsembleDePileDeNNN2 = EDPDNNN_ensemble();
    PDNNN_PileDeNNN pile1 = PDNNN_pile();
    PDNNN_empiler(&pile1, 1);
    EDPDNNN_ajouter(&EnsembleDePileDeNNN1, pile1);
    PDNNN_PileDeNNN pile2 = PDNNN_pile();
    PDNNN_empiler(&pile2, 2);
    EDPDNNN_ajouter(&EnsembleDePileDeNNN1, pile2);
    EDPDNNN_ajouter(&EnsembleDePileDeNNN2, pile2);
    PDNNN_PileDeNNN pile3 = PDNNN_pile();
    PDNNN_empiler(&pile3, 3);
    EDPDNNN_ajouter(&EnsembleDePileDeNNN2, pile3);
    EDPDNNN_EnsembleDePileDeNNN unionResultat = EDPDNNN_unionEnsemble(EnsembleDePileDeNNN1, EnsembleDePileDeNNN2);
    CU_ASSERT_TRUE(EDPDNNN_estPresent(unionResultat, pile1));
    CU_ASSERT_TRUE(EDPDNNN_estPresent(unionResultat, pile2));
    CU_ASSERT_TRUE(EDPDNNN_estPresent(unionResultat, pile3));
    unsigned int cardinaliteUnion = EDPDNNN_cardinalite(unionResultat);
    unsigned int cardinaliteAttendue = 3;
    CU_ASSERT_TRUE(cardinaliteUnion == cardinaliteAttendue);
}

void test_EDPDNNN_Union3(void) {
    EDPDNNN_EnsembleDePileDeNNN EnsembleDePileDeNNN1 = EDPDNNN_ensemble();
    EDPDNNN_EnsembleDePileDeNNN EnsembleDePileDeNNN2 = EDPDNNN_ensemble();
    PDNNN_PileDeNNN pile1 = PDNNN_pile();
    PDNNN_empiler(&pile1, 1);
    EDPDNNN_ajouter(&EnsembleDePileDeNNN1, pile1);
    EDPDNNN_EnsembleDePileDeNNN unionResultat = EDPDNNN_unionEnsemble(EnsembleDePileDeNNN1, EnsembleDePileDeNNN2);
    CU_ASSERT_TRUE(EDPDNNN_estPresent(unionResultat, pile1));
    unsigned int cardinaliteUnion = EDPDNNN_cardinalite(unionResultat);
    unsigned int cardinaliteAttendue = 1;
    CU_ASSERT_TRUE(cardinaliteUnion == cardinaliteAttendue);
}

void test_EDPDNNN_Intersection1(void) {
    EDPDNNN_EnsembleDePileDeNNN EnsembleDePileDeNNN1 = EDPDNNN_ensemble();
    EDPDNNN_EnsembleDePileDeNNN EnsembleDePileDeNNN2 = EDPDNNN_ensemble();
    PDNNN_PileDeNNN pile1 = PDNNN_pile();
    PDNNN_empiler(&pile1, 1);
    EDPDNNN_ajouter(&EnsembleDePileDeNNN1, pile1);
    PDNNN_PileDeNNN pile2 = PDNNN_pile();
    PDNNN_empiler(&pile2, 2);
    EDPDNNN_ajouter(&EnsembleDePileDeNNN1, pile2);
    EDPDNNN_ajouter(&EnsembleDePileDeNNN2, pile2);
    PDNNN_PileDeNNN pile3 = PDNNN_pile();
    PDNNN_empiler(&pile3, 3);
    EDPDNNN_ajouter(&EnsembleDePileDeNNN2, pile3);
    EDPDNNN_EnsembleDePileDeNNN intersectionResultat = EDPDNNN_intersection(EnsembleDePileDeNNN1, EnsembleDePileDeNNN2);
    CU_ASSERT_TRUE(EDPDNNN_estPresent(intersectionResultat, pile2));
    CU_ASSERT_FALSE(EDPDNNN_estPresent(intersectionResultat, pile1));
    CU_ASSERT_FALSE(EDPDNNN_estPresent(intersectionResultat, pile3));
    unsigned int cardinaliteUnion = EDPDNNN_cardinalite(intersectionResultat);
    unsigned int cardinaliteAttendue = 1;
    CU_ASSERT_TRUE(cardinaliteUnion == cardinaliteAttendue);
}

void test_EDPDNNN_Intersection2(void) {
    EDPDNNN_EnsembleDePileDeNNN EnsembleDePileDeNNN1 = EDPDNNN_ensemble();
    EDPDNNN_EnsembleDePileDeNNN EnsembleDePileDeNNN2 = EDPDNNN_ensemble();
    PDNNN_PileDeNNN pile1 = PDNNN_pile();
    PDNNN_empiler(&pile1, 1);
    EDPDNNN_ajouter(&EnsembleDePileDeNNN1, pile1);
    EDPDNNN_ajouter(&EnsembleDePileDeNNN2, pile1);
    PDNNN_PileDeNNN pile2 = PDNNN_pile();
    PDNNN_empiler(&pile2, 2);
    EDPDNNN_ajouter(&EnsembleDePileDeNNN2, pile2);
    PDNNN_PileDeNNN pile3 = PDNNN_pile();
    PDNNN_empiler(&pile3, 3);
    EDPDNNN_ajouter(&EnsembleDePileDeNNN2, pile3);
    EDPDNNN_EnsembleDePileDeNNN intersectionResultat = EDPDNNN_intersection(EnsembleDePileDeNNN1, EnsembleDePileDeNNN2);
    CU_ASSERT_TRUE(EDPDNNN_estPresent(intersectionResultat, pile1));
    CU_ASSERT_FALSE(EDPDNNN_estPresent(intersectionResultat, pile2));
    CU_ASSERT_FALSE(EDPDNNN_estPresent(intersectionResultat, pile3));
    unsigned int cardinaliteUnion = EDPDNNN_cardinalite(intersectionResultat);
    unsigned int cardinaliteAttendue = 1;
    CU_ASSERT_TRUE(cardinaliteUnion == cardinaliteAttendue);
}

void test_EDPDNNN_Intersection3(void) {
    EDPDNNN_EnsembleDePileDeNNN EnsembleDePileDeNNN1 = EDPDNNN_ensemble();
    EDPDNNN_EnsembleDePileDeNNN EnsembleDePileDeNNN2 = EDPDNNN_ensemble();
    PDNNN_PileDeNNN pile1 = PDNNN_pile();
    PDNNN_empiler(&pile1, 1);
    EDPDNNN_ajouter(&EnsembleDePileDeNNN1, pile1);
    PDNNN_PileDeNNN pile2 = PDNNN_pile();
    PDNNN_empiler(&pile2, 2);
    EDPDNNN_ajouter(&EnsembleDePileDeNNN2, pile2);
    PDNNN_PileDeNNN pile3 = PDNNN_pile();
    PDNNN_empiler(&pile3, 3);
    EDPDNNN_ajouter(&EnsembleDePileDeNNN2, pile3);
    EDPDNNN_EnsembleDePileDeNNN intersectionResultat = EDPDNNN_intersection(EnsembleDePileDeNNN1, EnsembleDePileDeNNN2);
    CU_ASSERT_FALSE(EDPDNNN_estPresent(intersectionResultat, pile1));
    CU_ASSERT_FALSE(EDPDNNN_estPresent(intersectionResultat, pile2));
    CU_ASSERT_FALSE(EDPDNNN_estPresent(intersectionResultat, pile3));
    unsigned int cardinaliteUnion = EDPDNNN_cardinalite(intersectionResultat);
    unsigned int cardinaliteAttendue = 0;
    CU_ASSERT_TRUE(cardinaliteUnion == cardinaliteAttendue);
}

void test_EDPDNNN_Soustraction1(void) {
    EDPDNNN_EnsembleDePileDeNNN EnsembleDePileDeNNN1 = EDPDNNN_ensemble();
    EDPDNNN_EnsembleDePileDeNNN EnsembleDePileDeNNN2 = EDPDNNN_ensemble();
    PDNNN_PileDeNNN pile1 = PDNNN_pile();
    PDNNN_empiler(&pile1, 1);
    EDPDNNN_ajouter(&EnsembleDePileDeNNN1, pile1);
    PDNNN_PileDeNNN pile2 = PDNNN_pile();
    PDNNN_empiler(&pile2, 2);
    EDPDNNN_ajouter(&EnsembleDePileDeNNN1, pile2);
    EDPDNNN_ajouter(&EnsembleDePileDeNNN2, pile2);
    PDNNN_PileDeNNN pile3 = PDNNN_pile();
    PDNNN_empiler(&pile3, 3);
    EDPDNNN_ajouter(&EnsembleDePileDeNNN2, pile3);
    EDPDNNN_EnsembleDePileDeNNN soustractionResultat = EDPDNNN_soustraction(EnsembleDePileDeNNN1, EnsembleDePileDeNNN2);
    CU_ASSERT_TRUE(EDPDNNN_estPresent(soustractionResultat, pile1));
    CU_ASSERT_FALSE(EDPDNNN_estPresent(soustractionResultat, pile2));
    CU_ASSERT_FALSE(EDPDNNN_estPresent(soustractionResultat, pile3));
    unsigned int cardinaliteUnion = EDPDNNN_cardinalite(soustractionResultat);
    unsigned int cardinaliteAttendue = 1;
    CU_ASSERT_TRUE(cardinaliteUnion == cardinaliteAttendue);
}

void test_EDPDNNN_Soustraction2(void) {
    EDPDNNN_EnsembleDePileDeNNN EnsembleDePileDeNNN1 = EDPDNNN_ensemble();
    EDPDNNN_EnsembleDePileDeNNN EnsembleDePileDeNNN2 = EDPDNNN_ensemble();
    PDNNN_PileDeNNN pile1 = PDNNN_pile();
    PDNNN_empiler(&pile1, 1);
    EDPDNNN_ajouter(&EnsembleDePileDeNNN1, pile1);
    PDNNN_PileDeNNN pile2 = PDNNN_pile();
    PDNNN_empiler(&pile2, 2);
    EDPDNNN_ajouter(&EnsembleDePileDeNNN1, pile2);
    PDNNN_PileDeNNN pile3 = PDNNN_pile();
    PDNNN_empiler(&pile3, 3);
    EDPDNNN_ajouter(&EnsembleDePileDeNNN2, pile3);
    EDPDNNN_EnsembleDePileDeNNN soustractionResultat = EDPDNNN_soustraction(EnsembleDePileDeNNN1, EnsembleDePileDeNNN2);
    CU_ASSERT_TRUE(EDPDNNN_estPresent(soustractionResultat, pile1));
    CU_ASSERT_TRUE(EDPDNNN_estPresent(soustractionResultat, pile2));
    CU_ASSERT_FALSE(EDPDNNN_estPresent(soustractionResultat, pile3));
    unsigned int cardinaliteUnion = EDPDNNN_cardinalite(soustractionResultat);
    unsigned int cardinaliteAttendue = 2;
    CU_ASSERT_TRUE(cardinaliteUnion == cardinaliteAttendue);
}

void test_EDPDNNN_Soustraction3(void) {
    EDPDNNN_EnsembleDePileDeNNN EnsembleDePileDeNNN1 = EDPDNNN_ensemble();
    EDPDNNN_EnsembleDePileDeNNN EnsembleDePileDeNNN2 = EDPDNNN_ensemble();
    PDNNN_PileDeNNN pile1 = PDNNN_pile();
    PDNNN_empiler(&pile1, 1);
    EDPDNNN_ajouter(&EnsembleDePileDeNNN1, pile1);
    PDNNN_PileDeNNN pile2 = PDNNN_pile();
    PDNNN_empiler(&pile2, 2);
    EDPDNNN_ajouter(&EnsembleDePileDeNNN1, pile2);
    EDPDNNN_EnsembleDePileDeNNN soustractionResultat = EDPDNNN_soustraction(EnsembleDePileDeNNN1, EnsembleDePileDeNNN2);
    CU_ASSERT_TRUE(EDPDNNN_estPresent(soustractionResultat, pile1));
    CU_ASSERT_TRUE(EDPDNNN_estPresent(soustractionResultat, pile2));
    unsigned int cardinaliteUnion = EDPDNNN_cardinalite(soustractionResultat);
    unsigned int cardinaliteAttendue = 2;
    CU_ASSERT_TRUE(cardinaliteUnion == cardinaliteAttendue);
}

// Pile de NNN

void test_PileDeNNN_Vide1(void) {
    PDNNN_PileDeNNN pile = PDNNN_pile();
    CU_ASSERT_TRUE(PDNNN_estVide(pile));
}

void test_PileDeNNN_Vide2(void) {
    PDNNN_PileDeNNN pile = PDNNN_pile();
    PDNNN_empiler(&pile, 10);
    CU_ASSERT_FALSE(PDNNN_estVide(pile));
}

void test_PileDeNNN_Empile(void) {
    PDNNN_PileDeNNN pile = PDNNN_pile();
    PDNNN_empiler(&pile, 10);
    CU_ASSERT_FALSE(PDNNN_estVide(pile));
    CU_ASSERT_TRUE(PDNNN_obtenirElement(pile) == 10);
}

void test_PileDeNNN_Depile(void) {
    PDNNN_PileDeNNN pile = PDNNN_pile();
    PDNNN_empiler(&pile, 10);
    PDNNN_empiler(&pile, 11);
    PDNNN_depiler(&pile);
    CU_ASSERT_TRUE(PDNNN_obtenirElement(pile) == 10);
    PDNNN_depiler(&pile);
    CU_ASSERT_TRUE(PDNNN_estVide(pile));
}

void test_PileDeNNN_Longueur(void) {
    PDNNN_PileDeNNN pile = PDNNN_pile();
    CU_ASSERT_TRUE(PDNNN_longueur(pile) == 0);
    PDNNN_empiler(&pile, 10);
    CU_ASSERT_TRUE(PDNNN_longueur(pile) == 1);
    PDNNN_empiler(&pile, 20);
    CU_ASSERT_TRUE(PDNNN_longueur(pile) == 2);
}

// liste chainée de CDC 

void test_LCDCDC_estVide1(void) {
    LCDCDC_ListeChaineeDeCDC liste = LCDCDC_listeVide();
    bool estVide = LCDCDC_estVide(liste);
    CU_ASSERT_TRUE(estVide);  
}

void test_LCDCDC_estVide2(void) {
    LCDCDC_ListeChaineeDeCDC liste = LCDCDC_listeVide();
    char* element = "ok";
    LCDCDC_ajouter(&liste, element);
    bool estVide = LCDCDC_estVide(liste);
    CU_ASSERT_FALSE(estVide); 
}

void test_LCDCDC_obtenirElement(void) {
    LCDCDC_ListeChaineeDeCDC liste = LCDCDC_listeVide();
    char* element = "ok";
    LCDCDC_ajouter(&liste, element);

    char* premierElement = LCDCDC_obtenirElement(liste);
    CU_ASSERT_TRUE(premierElement == element);  
}

void test_LCDCDC_fixerElement(void) {
    LCDCDC_ListeChaineeDeCDC liste = LCDCDC_listeVide();
    char* ancienElement = "ok";
    char* nouvelElement = "bonjour";
    LCDCDC_ajouter(&liste, ancienElement);

    LCDCDC_fixerElement(&liste, nouvelElement);
    char* premierElement = LCDCDC_obtenirElement(liste);

    CU_ASSERT_TRUE(premierElement == nouvelElement); 
}

void test_LCDCDC_obtenirListeSuivante(void) {
    LCDCDC_ListeChaineeDeCDC liste = LCDCDC_listeVide();
    char* premierElement = "ok";
    char* secondElement = "bonjour";
    LCDCDC_ajouter(&liste, premierElement);
    LCDCDC_ajouter(&liste, secondElement);

    LCDCDC_ListeChaineeDeCDC listeSuivante = LCDCDC_obtenirListeSuivante(liste);
    char* elementSuivant = LCDCDC_obtenirElement(listeSuivante);

    CU_ASSERT_TRUE(elementSuivant == secondElement);
}

void test_LCDCDC_fixerListeSuivante(void) {
    LCDCDC_ListeChaineeDeCDC liste = LCDCDC_listeVide();
    char* premierElement = "ok";
    char* secondElement = "bonjour";
    LCDCDC_ajouter(&liste, premierElement);
    LCDCDC_ajouter(&liste, secondElement);

    LCDCDC_ListeChaineeDeCDC nouvelleListeSuivante = LCDCDC_listeVide();
    char* troisiemeElement = "bye";
    LCDCDC_ajouter(&nouvelleListeSuivante, troisiemeElement);

    LCDCDC_fixerListeSuivante(&liste, nouvelleListeSuivante);

    LCDCDC_ListeChaineeDeCDC listeSuivante = LCDCDC_obtenirListeSuivante(liste);
    char* elementSuivant = LCDCDC_obtenirElement(listeSuivante);

    CU_ASSERT_TRUE(elementSuivant == troisiemeElement);
}

void test_LCDCDC_supprimerTete(void) {
    LCDCDC_ListeChaineeDeCDC liste = LCDCDC_listeVide();
    char* element = "ok";
    LCDCDC_ajouter(&liste, element);
    LCDCDC_supprimerTete(&liste);

    CU_ASSERT_TRUE(LCDCDC_estVide(liste));  
}

void test_LCDCDC_supprimer1(void) {
    LCDCDC_ListeChaineeDeCDC liste = LCDCDC_listeVide();
    char* element1 = "ok";
    char* element2 = "bonjour";
    char* element3 = "bye";

    LCDCDC_ajouter(&liste, element1);
    LCDCDC_ajouter(&liste, element2);
    LCDCDC_ajouter(&liste, element3);

    LCDCDC_supprimer(&liste);
    CU_ASSERT_TRUE(LCDCDC_estVide(liste)); 
}

void test_LCDCDC_supprimer2(void) {
    LCDCDC_ListeChaineeDeCDC liste = LCDCDC_listeVide();
    LCDCDC_supprimer(&liste);
    CU_ASSERT_TRUE(LCDCDC_estVide(liste)); 
}


// liste chainee de Direction 

void test_LCDD_estVide1(void) {
    LCDD_ListeChaineeDeDirection liste = LCDD_listeVide();
    bool estVide = LCDD_estVide(liste);
    CU_ASSERT_TRUE(estVide);
}

void test_LCDD_estVide2(void) {
    LCDD_ListeChaineeDeDirection liste = LCDD_listeVide();
    Direction element = G;
    LCDD_ajouter(&liste, element);
    bool estVide = LCDD_estVide(liste);
    CU_ASSERT_FALSE(estVide);
}

void test_LCDD_obtenirElement(void) {
    LCDD_ListeChaineeDeDirection liste = LCDD_listeVide();
    Direction element = G;
    LCDD_ajouter(&liste, element);

    Direction premierElement = LCDD_obtenirElement(liste);
    CU_ASSERT_TRUE(premierElement == element);
}

void test_LCDD_fixerElement(void) {
    LCDD_ListeChaineeDeDirection liste = LCDD_listeVide();
    Direction ancienElement = G;
    Direction nouvelElement = D;
    LCDD_ajouter(&liste, ancienElement);

    LCDD_fixerElement(&liste, nouvelElement);
    Direction premierElement = LCDD_obtenirElement(liste);

    CU_ASSERT_TRUE(premierElement == nouvelElement);
}

void test_LCDD_obtenirListeSuivante(void) {
    LCDD_ListeChaineeDeDirection liste = LCDD_listeVide();
    Direction premierElement = G;
    Direction secondElement = D;
    LCDD_ajouter(&liste, premierElement);
    LCDD_ajouter(&liste, secondElement);

    LCDD_ListeChaineeDeDirection listeSuivante = LCDD_obtenirListeSuivante(liste);
    Direction elementSuivant = LCDD_obtenirElement(listeSuivante);

    CU_ASSERT_TRUE(elementSuivant == secondElement);
}

void test_LCDD_fixerListeSuivante(void) {
    LCDD_ListeChaineeDeDirection liste = LCDD_listeVide();
    Direction premierElement = G;
    Direction secondElement = H;
    LCDD_ajouter(&liste, premierElement);
    LCDD_ajouter(&liste, secondElement);

    LCDD_ListeChaineeDeDirection nouvelleListeSuivante = LCDD_listeVide();
    Direction troisiemeElement = D;
    LCDD_ajouter(&nouvelleListeSuivante, troisiemeElement);

    LCDD_fixerListeSuivante(&liste, nouvelleListeSuivante);

    LCDD_ListeChaineeDeDirection listeSuivante = LCDD_obtenirListeSuivante(liste);
    Direction elementSuivant = LCDD_obtenirElement(listeSuivante);

    CU_ASSERT_TRUE(elementSuivant == troisiemeElement);
}

void test_LCDD_supprimerTete1(void) {
    LCDD_ListeChaineeDeDirection liste = LCDD_listeVide();
    Direction element = G;
    LCDD_ajouter(&liste, element);
    LCDD_supprimerTete(&liste);

    CU_ASSERT_TRUE(LCDD_estVide(liste));
}

void test_LCDD_supprimerTete2(void) {
    LCDD_ListeChaineeDeDirection liste = LCDD_listeVide();
    Direction element = G;
    LCDD_ajouter(&liste, element);
    LCDD_supprimerTete(&liste);

    CU_ASSERT_FALSE(LCDD_estVide(liste));
    CU_ASSERT_FALSE(LCDD_obtenirElement(liste)==B);
}

void test_LCDD_supprimer1(void) {
    LCDD_ListeChaineeDeDirection liste = LCDD_listeVide();
    Direction element1 = G;
    Direction element2 = D;
    Direction element3 = H;

    LCDD_ajouter(&liste, element1);
    LCDD_ajouter(&liste, element2);
    LCDD_ajouter(&liste, element3);

    LCDD_supprimer(&liste);
    CU_ASSERT_TRUE(LCDD_estVide(liste));
}

void test_LCDD_supprimer2(void) {
    LCDD_ListeChaineeDeDirection liste = LCDD_listeVide();

    LCDD_supprimer(&liste);
    CU_ASSERT_TRUE(LCDD_estVide(liste));
}


// Liste chainee de pile de NNN 

void test_LCDPDNNN_estVide1(void) {
    LCDPDNNN_ListeChaineeDePileDeNNN liste = LCDPDNNN_listeVide();
    bool estVide = LCDPDNNN_estVide(liste);
    CU_ASSERT_TRUE(estVide);
}

void test_LCDPDNNN_estVide2(void) {
    LCDPDNNN_ListeChaineeDePileDeNNN liste = LCDPDNNN_listeVide();
    PDNNN_PileDeNNN pile = PDNNN_pile();
    PDNNN_empiler(&pile, 10);
    LCDPDNNN_ajouter(&liste, pile);
    bool estVide = LCDPDNNN_estVide(liste);
    CU_ASSERT_FALSE(estVide);
}

void test_LCDPDNNN_obtenirElement(void) {
    LCDPDNNN_ListeChaineeDePileDeNNN liste = LCDPDNNN_listeVide();
    PDNNN_PileDeNNN pile1 = PDNNN_pile();
    PDNNN_empiler(&pile1, 10);
    LCDPDNNN_ajouter(&liste, pile1);

    PDNNN_PileDeNNN premierElement = LCDPDNNN_obtenirElement(liste);
    CU_ASSERT_TRUE(premierElement == pile1);
}

void test_LCDPDNNN_fixerElement(void) {
    LCDPDNNN_ListeChaineeDePileDeNNN liste = LCDPDNNN_listeVide();
    PDNNN_PileDeNNN pile1 = PDNNN_pile();
    PDNNN_empiler(&pile1, 10);
    PDNNN_PileDeNNN pile2 = PDNNN_pile();
    PDNNN_empiler(&pile1, 20);
    LCDPDNNN_ajouter(&liste, pile1);

    LCDPDNNN_fixerElement(&liste, pile2);
    PDNNN_PileDeNNN premierElement = LCDPDNNN_obtenirElement(liste);

    CU_ASSERT_TRUE(premierElement == pile2);
}

void test_LCDPDNNN_obtenirListeSuivante(void) {
    LCDPDNNN_ListeChaineeDePileDeNNN liste = LCDPDNNN_listeVide();
    PDNNN_PileDeNNN pile1 = PDNNN_pile();
    PDNNN_empiler(&pile1, 10);
    PDNNN_PileDeNNN pile2 = PDNNN_pile();
    PDNNN_empiler(&pile2, 20);
    LCDPDNNN_ajouter(&liste, pile1);
    LCDPDNNN_ajouter(&liste, pile2);

    LCDPDNNN_ListeChaineeDePileDeNNN listeSuivante = LCDPDNNN_obtenirListeSuivante(liste);
    PDNNN_PileDeNNN elementSuivant = LCDPDNNN_obtenirElement(listeSuivante);

    CU_ASSERT_TRUE(elementSuivant == pile2);
}

void test_LCDPDNNN_fixerListeSuivante(void) {
    LCDPDNNN_ListeChaineeDePileDeNNN liste = LCDPDNNN_listeVide();
    PDNNN_PileDeNNN pile1 = PDNNN_pile();
    PDNNN_empiler(&pile1, 10);
    PDNNN_PileDeNNN pile2 = PDNNN_pile();
    PDNNN_empiler(&pile2, 20);
    LCDPDNNN_ajouter(&liste, pile1);
    LCDPDNNN_ajouter(&liste, pile2);

    LCDPDNNN_ListeChaineeDePileDeNNN nouvelleListeSuivante = LCDPDNNN_listeVide();
    PDNNN_PileDeNNN pile3 = PDNNN_pile();
    PDNNN_empiler(&pile3, 30);
    LCDPDNNN_ajouter(&nouvelleListeSuivante, pile3);

    LCDPDNNN_fixerListeSuivante(&liste, nouvelleListeSuivante);

    LCDPDNNN_ListeChaineeDePileDeNNN listeSuivante = LCDPDNNN_obtenirListeSuivante(liste);
    PDNNN_PileDeNNN elementSuivant = LCDPDNNN_obtenirElement(listeSuivante);

    CU_ASSERT_TRUE(elementSuivant == pile3);
}

void test_LCDPDNNN_supprimerTete(void) {
    LCDPDNNN_ListeChaineeDePileDeNNN liste = LCDPDNNN_listeVide();
    PDNNN_PileDeNNN pile = PDNNN_pile();
    PDNNN_empiler(&pile, 10);
    LCDPDNNN_ajouter(&liste, pile);
    LCDPDNNN_supprimerTete(&liste);

    CU_ASSERT_TRUE(LCDPDNNN_estVide(liste));
}

void test_LCDPDNNN_supprimer(void) {
    LCDPDNNN_ListeChaineeDePileDeNNN liste = LCDPDNNN_listeVide();
    PDNNN_PileDeNNN pile1 = PDNNN_pile();
    PDNNN_empiler(&pile1, 10);
    PDNNN_PileDeNNN pile2 = PDNNN_pile();
    PDNNN_empiler(&pile2, 20);
    PDNNN_PileDeNNN pile3 = PDNNN_pile();
    PDNNN_empiler(&pile3, 30);

    LCDPDNNN_ajouter(&liste, pile1);
    LCDPDNNN_ajouter(&liste, pile2);
    LCDPDNNN_ajouter(&liste, pile3);

    LCDPDNNN_supprimer(&liste);
    CU_ASSERT_TRUE(LCDPDNNN_estVide(liste));
}


// Liste chainée de NNN 

void test_LCDNNN_estVide1(void) {
    LCDNNN_ListeChaineeDeNNN liste = LCDNNN_listeVide();
    bool estVide = LCDNNN_estVide(liste);
    CU_ASSERT_TRUE(estVide);
}

void test_LCDNNN_estVide2(void) {
    LCDNNN_ListeChaineeDeNNN liste = LCDNNN_listeVide();
    unsigned int element = 10;
    LCDNNN_ajouter(&liste, element);
    bool estVide = LCDNNN_estVide(liste);
    CU_ASSERT_FALSE(estVide);
}

void test_LCDNNN_obtenirElement(void) {
    LCDNNN_ListeChaineeDeNNN liste = LCDNNN_listeVide();
    unsigned int element = 10;
    LCDNNN_ajouter(&liste, element);

    unsigned int premierElement = LCDNNN_obtenirElement(liste);
    CU_ASSERT_TRUE(premierElement == element);
}

void test_LCDNNN_fixerElement(void) {
    LCDNNN_ListeChaineeDeNNN liste = LCDNNN_listeVide();
    unsigned int ancienElement = 10;
    unsigned int nouvelElement = 20;
    LCDNNN_ajouter(&liste, ancienElement);

    LCDNNN_fixerElement(&liste, nouvelElement);
    unsigned int premierElement = LCDNNN_obtenirElement(liste);

    CU_ASSERT_TRUE(premierElement == nouvelElement);
}

void test_LCDNNN_obtenirListeSuivante(void) {
    LCDNNN_ListeChaineeDeNNN liste = LCDNNN_listeVide();
    unsigned int premierElement = 10;
    unsigned int secondElement = 20;
    LCDNNN_ajouter(&liste, premierElement);
    LCDNNN_ajouter(&liste, secondElement);

    LCDNNN_ListeChaineeDeNNN listeSuivante = LCDNNN_obtenirListeSuivante(liste);
    unsigned int elementSuivant = LCDNNN_obtenirElement(listeSuivante);

    CU_ASSERT_TRUE(elementSuivant == secondElement);
}

void test_LCDNNN_fixerListeSuivante(void) {
    LCDNNN_ListeChaineeDeNNN liste = LCDNNN_listeVide();
    unsigned int premierElement = 10;
    unsigned int secondElement = 20;
    LCDNNN_ajouter(&liste, premierElement);
    LCDNNN_ajouter(&liste, secondElement);

    LCDNNN_ListeChaineeDeNNN nouvelleListeSuivante = LCDNNN_listeVide();
    unsigned int troisiemeElement = 30;
    LCDNNN_ajouter(&nouvelleListeSuivante, troisiemeElement);

    LCDNNN_fixerListeSuivante(&liste, nouvelleListeSuivante);

    LCDNNN_ListeChaineeDeNNN listeSuivante = LCDNNN_obtenirListeSuivante(liste);
    unsigned int elementSuivant = LCDNNN_obtenirElement(listeSuivante);

    CU_ASSERT_TRUE(elementSuivant == troisiemeElement);
}

void test_LCDNNN_supprimerTete(void) {
    LCDNNN_ListeChaineeDeNNN liste = LCDNNN_listeVide();
    unsigned int element = 10;
    LCDNNN_ajouter(&liste, element);
    LCDNNN_supprimerTete(&liste);

    CU_ASSERT_TRUE(LCDNNN_estVide(liste));
}

void test_LCDNNN_supprimer(void) {
    LCDNNN_ListeChaineeDeNNN liste = LCDNNN_listeVide();
    unsigned int element1 = 10;
    unsigned int element2 = 20;
    unsigned int element3 = 30;

    LCDNNN_ajouter(&liste, element1);
    LCDNNN_ajouter(&liste, element2);
    LCDNNN_ajouter(&liste, element3);

    LCDNNN_supprimer(&liste);
    CU_ASSERT_TRUE(LCDNNN_estVide(liste));
}


// liste chainee d'ordres 

void test_LCDO_estVide1(void) {
    LCDO_ListeChaineeDOrdre liste = LCDO_listeVide();
    bool estVide = LCDO_estVide(liste);
    CU_ASSERT_TRUE(estVide);
}

void test_LCDO_estVide2(void) {
    LCDO_ListeChaineeDOrdre liste = LCDO_listeVide();
    Ordre element = TG;
    LCDO_ajouter(&liste, element);
    bool estVide = LCDO_estVide(liste);
    CU_ASSERT_FALSE(estVide);
}

void test_LCDO_obtenirElement(void) {
    LCDO_ListeChaineeDOrdre liste = LCDO_listeVide();
    Ordre element = TG;  
    LCDO_ajouter(&liste, element);

     Ordre premierElement = LCDO_obtenirElement(liste);
    CU_ASSERT_TRUE(premierElement == element);
}

void test_LCDO_fixerElement(void) {
    LCDO_ListeChaineeDOrdre liste = LCDO_listeVide();
    Ordre ancienElement = TG; 
    Ordre nouvelElement = TD;  
    LCDO_ajouter(&liste, ancienElement);

    LCDO_fixerElement(&liste, nouvelElement);
    Ordre premierElement = LCDO_obtenirElement(liste);

    CU_ASSERT_TRUE(premierElement == nouvelElement);
}

void test_LCDO_obtenirListeSuivante(void) {
    LCDO_ListeChaineeDOrdre liste = LCDO_listeVide();
    Ordre premierElement = TG;  
    Ordre secondElement = TD; 
    LCDO_ajouter(&liste, premierElement);
    LCDO_ajouter(&liste, secondElement);

    LCDO_ListeChaineeDOrdre listeSuivante = LCDO_obtenirListeSuivante(liste);
    Ordre elementSuivant = LCDO_obtenirElement(listeSuivante);

    CU_ASSERT_TRUE(elementSuivant == secondElement);
}

void test_LCDO_fixerListeSuivante(void) {
    LCDO_ListeChaineeDOrdre liste = LCDO_listeVide();
    Ordre premierElement = TG; 
    Ordre secondElement = TD; 
    LCDO_ajouter(&liste, premierElement);
    LCDO_ajouter(&liste, secondElement);

    LCDO_ListeChaineeDOrdre nouvelleListeSuivante = LCDO_listeVide();
    Ordre troisiemeElement = AV;  
    LCDO_ajouter(&nouvelleListeSuivante, troisiemeElement);

    LCDO_fixerListeSuivante(&liste, nouvelleListeSuivante);

    LCDO_ListeChaineeDOrdre listeSuivante = LCDO_obtenirListeSuivante(liste);
    Ordre elementSuivant = LCDO_obtenirElement(listeSuivante);

    CU_ASSERT_TRUE(elementSuivant == troisiemeElement);
}

void test_LCDO_supprimerTete(void) {
    LCDO_ListeChaineeDOrdre liste = LCDO_listeVide();
    Ordre element = TG;  
    LCDO_ajouter(&liste, element);
    LCDO_supprimerTete(&liste);

    CU_ASSERT_TRUE(LCDO_estVide(liste));
}

void test_LCDO_supprimer(void) {
    LCDO_ListeChaineeDOrdre liste = LCDO_listeVide();
    Ordre element1 = TG;  
    Ordre element2 = TD;  
    Ordre element3 = AV;  

    LCDO_ajouter(&liste, element1);
    LCDO_ajouter(&liste, element2);
    LCDO_ajouter(&liste, element3);

    LCDO_supprimer(&liste);
    CU_ASSERT_TRUE(LCDO_estVide(liste));
}

// Liste de CDC

void test_LDCDC_estVide1(void) {
    LDCDC_ListeDeCDC liste = LDCDC_liste();
    bool estVide = LDCDC_estVide(liste);
    CU_ASSERT_TRUE(estVide);  
}

void test_LDCDC_estVide2(void) {
    LDCDC_ListeDeCDC liste = LDCDC_liste();
    char* element = "unElement";
    unsigned int position = 1;
    LDCDC_inserer(&liste, element, position);
    bool estVide = LDCDC_estVide(liste);
    CU_ASSERT_FALSE(estVide); 
}

void test_LDCDC_obtenirElement(void) {
    LDCDC_ListeDeCDC liste = LDCDC_liste();
    char* element = "unElement";
    unsigned int position = 1;
    LDCDC_inserer(&liste, element, position);

    char* ElementPosition = LDCDC_obtenirElement(liste, position);
    CU_ASSERT_TRUE(ElementPosition == element);  
}

void test_LDCDC_supprimer1(void) {
    LDCDC_ListeDeCDC liste = LDCDC_liste();
    LCDCDC_ListeChaineeDeCDC listeCCDC = LCDCDC_listeVide();
    char* element = "unElement";
    LCDCDC_ajouter(&listeCCDC,element);
    for (int i=1;i==3;i++){
	LDCDC_inserer(&liste, element, i);
    }
    for (int i=1;i==3;i++){
	LDCDC_supprimer(&liste, i);
    }
    
    CU_ASSERT_TRUE(LDCDC_estVide(liste)); 
}

void test_LDCDC_supprimer2(void) {
    LDCDC_ListeDeCDC liste = LDCDC_liste();
    unsigned int position = 1;
    LDCDC_supprimer(&liste, position);
    CU_ASSERT_TRUE(LDCDC_estVide(liste)); 
}

void test_LDCDC_longueur(void) {
    LDCDC_ListeDeCDC liste = LDCDC_liste();
    LCDCDC_ListeChaineeDeCDC listeCCDC = LCDCDC_listeVide();
    char* element = "unElement";
    LCDCDC_ajouter(&listeCCDC,element);
    
    for (int i=1;i==3;i++){
	    LDCDC_inserer(&liste, element, i);
    } 
           	                         
    CU_ASSERT_TRUE(LDCDC_longueur(liste) == 3);
}

// Liste de NNN

void test_LDNNN_estVide1(void) {
    LDNNN_ListeDeNNN liste = LDNNN_liste();
    bool estVide = LDNNN_estVide(liste);
    CU_ASSERT_TRUE(estVide);
}

void test_LDNNN_estVide2(void) {
    LDNNN_ListeDeNNN liste = LDNNN_liste();
    unsigned int element = 10;
    unsigned int position = 1;
    LDNNN_inserer(&liste, element,position);
    bool estVide = LDNNN_estVide(liste);
    CU_ASSERT_FALSE(estVide);
}

void test_LDNNN_obtenirElement(void) {
    LDNNN_ListeDeNNN liste = LDNNN_liste();
    unsigned int element = 10;
    unsigned int position = 1;
    LDNNN_inserer(&liste, element, position);

    unsigned int elementPosition = LDNNN_obtenirElement(liste, position);
    CU_ASSERT_TRUE(elementPosition == element);
}

void test_LDNNN_supprimer(void) {
    LDNNN_ListeDeNNN liste = LDNNN_liste();
    unsigned int element = 10;
    unsigned int i = 1;

    for (i=1;i==3;i++){
	    LDNNN_inserer(&liste, element, i);
    }
    for (i=1;i==3;i++){
	    LDNNN_supprimer(&liste, i);
    }
    
    CU_ASSERT_TRUE(LDNNN_estVide(liste));
}

void test_LDNNN_longueur(void) {
    LDNNN_ListeDeNNN liste = LDNNN_liste();
    unsigned int element = 10;
    unsigned int i = 1;

    for (i=1;i==3;i++){
	    LDNNN_inserer(&liste, element, i);
    }
    
    CU_ASSERT_TRUE(LDNNN_longueur(liste) == 3); 
}

// Liste d'ordres 

void test_LDO_estVide1(void) {
    LDO_ListeDOrdre liste = LDO_liste();
    bool estVide = LDO_estVide(liste);
    CU_ASSERT_TRUE(estVide);
}

void test_LDO_estVide2(void) {
    LDO_ListeDOrdre liste = LDO_liste();
    Ordre element = TG;
    unsigned int position = 1;
    LDO_inserer(&liste, element, position);
    bool estVide = LDO_estVide(liste);
    CU_ASSERT_FALSE(estVide);
}

void test_LDO_obtenirElement(void) {
    LDO_ListeDOrdre liste = LDO_liste();
    Ordre element = TG;  
    unsigned int position = 1;
    LDO_inserer(&liste, element, position);

    Ordre elementPosition = LDO_obtenirElement(liste, position);
    CU_ASSERT_TRUE(elementPosition == element);
}

void test_LDO_supprimer(void) {
    LDO_ListeDOrdre liste = LDO_liste();
    Ordre element = TG;  
    unsigned int i = 1;

    for (i=1;i==3;i++){
	    LDO_inserer(&liste, element, i);
    }
    for (i=1;i==3;i++){
	    LDO_supprimer(&liste, i);
    }
    bool estVide = LDO_estVide(liste);
    CU_ASSERT_TRUE(estVide);
}

void test_LDO_longueur(void) {
    LDO_ListeDOrdre liste = LDO_liste();
    Ordre element = TG;  
    unsigned int i = 1;
    for (i=1;i==3;i++){
	    LDO_inserer(&liste, element, i);
    }
    
    CU_ASSERT_TRUE(liste.nbElements == 3);
}

//implementation des tests unitaires des types 

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
    (NULL == CU_add_test(pSuiteBoiteNoire, "erreur obtenir case ", test_CD_obtenirCase1)) 
    || (NULL == CU_add_test(pSuiteBoiteNoire, "erreur obtenir case en changant de direction 1 ", test_CD_obtenirCase2)) 
    || (NULL == CU_add_test(pSuiteBoiteNoire, "erreur obtenir case en changant de direction 2 ", test_CD_obtenirCase3)) 
    || (NULL == CU_add_test(pSuiteBoiteNoire, "erreur obtenir direction ", test_CD_obtenirDirection1)) 
    || (NULL == CU_add_test(pSuiteBoiteNoire, "erreur obtenir direction en changeant de diretion 1 ", test_CD_obtenirDirection2)) 
    || (NULL == CU_add_test(pSuiteBoiteNoire, "erreur obtenir direction en changeant de diretion 2 ", test_CD_obtenirDirection3)) 
    || (NULL == CU_add_test(pSuiteBoiteNoire, "erreur fixer direction 1", test_CD_FixerDirectionTest1)) 
    || (NULL == CU_add_test(pSuiteBoiteNoire, "erreur fixer direction 2", test_CD_FixerDirectionTest2)) 
    || (NULL == CU_add_test(pSuiteBoiteNoire, "erreur fixer direction 3", test_CD_FixerDirectionTest3)) 
    || (NULL == CU_add_test(pSuiteBoiteNoire, "erreur fixer direction avec la meme direction", test_CD_FixerDirectionTest4)) 
    || (NULL == CU_add_test(pSuiteBoiteNoire, "erreur fixer case", test_CD_FixerCaseTest1)) 
    || (NULL == CU_add_test(pSuiteBoiteNoire, "erreur fixer même case", test_CD_FixerCaseTest2)) 
    || (NULL == CU_add_test(pSuiteBoiteNoire, "erreur ensemble de direction ajout et/ou suppression d'un élément", test_EDD_AjoutEtSuppression)) 
    || (NULL == CU_add_test(pSuiteBoiteNoire, "erreur ensemble de direction presence vraie", test_EDD_EstPresent1)) 
    || (NULL == CU_add_test(pSuiteBoiteNoire, "erreur ensemble de direction presence fausse ", test_EDD_EstPresent2)) 
    || (NULL == CU_add_test(pSuiteBoiteNoire, "erreur ensemble de direction cardinalite different de 0 pour un ensemble vide", test_EDD_CardinaliteVide)) 
    || (NULL == CU_add_test(pSuiteBoiteNoire, "erreur ensemble de direction cardinalite N different ", test_EDD_CardinaliteN)) 
    || (NULL == CU_add_test(pSuiteBoiteNoire, "erreur ensemble de direction union de 3 éléments distincts ", test_EDD_UnionAjout1)) 
    || (NULL == CU_add_test(pSuiteBoiteNoire, "erreur ensemble de direction union 3 éléments distincts V2", test_EDD_UnionAjout2)) 
    || (NULL == CU_add_test(pSuiteBoiteNoire, "erreur ensemble de direction union de 3 éléments non distincts pas respecté pour un ensemble ", test_EDD_UnionPasAjout1)) 
    || (NULL == CU_add_test(pSuiteBoiteNoire, "erreur ensemble de direction union de 3 élémnts distincs diff de avant", test_EDD_UnionPasAjout2)) 
    || (NULL == CU_add_test(pSuiteBoiteNoire, "erreur ensemble de direction union vide droit ", test_EDD_UnionVide1)) 
    || (NULL == CU_add_test(pSuiteBoiteNoire, "erreur ensemble de direction union vide gauche", test_EDD_UnionVide2)) 
    || (NULL == CU_add_test(pSuiteBoiteNoire, "erreur ensemble de direction intersection classique avec un seul element", test_EDD_Intersection1)) 
    || (NULL == CU_add_test(pSuiteBoiteNoire, "erreur ensemble de direction intersection avec un ensemble vide", test_EDD_Intersection2)) 
    || (NULL == CU_add_test(pSuiteBoiteNoire, "erreur ensemble de direction intersection qui donne un ensemble vide ", test_EDD_Intersection3)) 
    || (NULL == CU_add_test(pSuiteBoiteNoire, "erreur ensemble de direction soustraction de 2 ensembles", test_EDD_Soustraction1)) 
    || (NULL == CU_add_test(pSuiteBoiteNoire, "erreur ensemble de direction soustraction V2", test_EDD_Soustraction2)) 
    || (NULL == CU_add_test(pSuiteBoiteNoire, "erreur ensemble de direction soustraction qui donne un ensemble vide ", test_EDD_Soustraction3)) 
    || (NULL == CU_add_test(pSuiteBoiteNoire, "erreur ensemble de NNN ajout et/ou suppression d'un élément dans l'ensemble ", test_EDNNN_AjoutSuppression1)) 
    || (NULL == CU_add_test(pSuiteBoiteNoire, "erreur ensemble de NNN ajout valeur et test de sa presence ", test_EDNNN_AjoutSuppression2)) 
    || (NULL == CU_add_test(pSuiteBoiteNoire, "erreur ensemble de NNN ajout valeur et test de la presence d'une autre valeur (pb initialisation) ", test_EDNNN_AjoutSuppression3)) 
    || (NULL == CU_add_test(pSuiteBoiteNoire, "erreur ensemble de NNN ajout de 9 valeur et cardinalite different de 9", test_EDNNN_Cardinalite1)) 
    || (NULL == CU_add_test(pSuiteBoiteNoire, "erreur ensemble de NNN cardinalité non nul pour un ensemble vide ", test_EDNNN_Cardinalite2)) 
    || (NULL == CU_add_test(pSuiteBoiteNoire, "erreur ensemble de NNN union classique", test_EDNNN_Union1)) 
    || (NULL == CU_add_test(pSuiteBoiteNoire, "erreur ensemble de NNN union classique V2 ", test_EDNNN_Union2)) 
    || (NULL == CU_add_test(pSuiteBoiteNoire, "erreur ensemble de NNN union avec test de presence des elements", test_EDNNN_Union3)) 
    || (NULL == CU_add_test(pSuiteBoiteNoire, "erreur ensemble de NNN union avec 2 meme ensemble ", test_EDNNN_Union4)) 
    || (NULL == CU_add_test(pSuiteBoiteNoire, "erreur ensemble de NNN union avec un ensemble vide ", test_EDNNN_Union5)) 
    || (NULL == CU_add_test(pSuiteBoiteNoire, "erreur ensemble de NNN intersection classique avec double intersection ", test_EDNNN_Intersection1)) 
    || (NULL == CU_add_test(pSuiteBoiteNoire, "erreur ensemble de NNN intersection classique une seule borne ", test_EDNNN_Intersection2)) 
    || (NULL == CU_add_test(pSuiteBoiteNoire, "erreur ensemble de NNN intersection ensemble vide ", test_EDNNN_Intersection3)) 
    || (NULL == CU_add_test(pSuiteBoiteNoire, "erreur ensemble de NNN soustraction classique", test_EDNNN_Soustraction1)) 
    || (NULL == CU_add_test(pSuiteBoiteNoire, "erreur ensemble de NNN soustraction resultat vide avec 2 meme ensemble ", test_EDNNN_Soustraction2)) 
    || (NULL == CU_add_test(pSuiteBoiteNoire, "erreur ensemble de NNN soustraction avec 2 ensemble disjoint", test_EDNNN_Soustraction3)) 
    || (NULL == CU_add_test(pSuiteBoiteNoire, "erreur ensemble de pile de NNN ajout et/ou suppression d'éléments ", test_EDPDNNN_AjoutSuppression1)) 
    || (NULL == CU_add_test(pSuiteBoiteNoire, "erreur ensemble de pile de NNN ajout et test de l'ajout par la présence ", test_EDPDNNN_AjoutSuppression2)) 
    || (NULL == CU_add_test(pSuiteBoiteNoire, "erreur ensemble de pile de NNN test ajout pile et test de presence autre pile ", test_EDPDNNN_AjoutSuppression3)) 
    || (NULL == CU_add_test(pSuiteBoiteNoire, "erreur ensemble de pile de NNN test de presence de l'élément apres ajout ", test_EDPDNNN_estPresent1)) 
    || (NULL == CU_add_test(pSuiteBoiteNoire, "erreur ensemble de pile de NNN test de non presence echoué (pb initialisation)", test_EDPDNNN_estPresent2)) 
    || (NULL == CU_add_test(pSuiteBoiteNoire, "erreur ensemble de pile de NNN cardinalité N ", test_EDPDNNN_Cardinalite1)) 
    || (NULL == CU_add_test(pSuiteBoiteNoire, "erreur ensemble de pile de NNN cardinalite d'un ensemble vide différent de 0 ", test_EDPDNNN_Cardinalite2)) 
    || (NULL == CU_add_test(pSuiteBoiteNoire, "erreur ensemble de pile de NNN union classique ", test_EDPDNNN_Union1)) 
    || (NULL == CU_add_test(pSuiteBoiteNoire, "erreur ensemble de pile de NNN pile non reinitialisée ", test_EDPDNNN_Union2)) 
    || (NULL == CU_add_test(pSuiteBoiteNoire, "erreur ensemble de pile de NNN pile vide ", test_EDPDNNN_Union3)) 
    || (NULL == CU_add_test(pSuiteBoiteNoire, "erreur ensemble de pile de NNN intersection classique", test_EDPDNNN_Intersection1)) 
    || (NULL == CU_add_test(pSuiteBoiteNoire, "erreur ensemble de pile de NNN intersection en inversant 1 et 2 ", test_EDPDNNN_Intersection2)) 
    || (NULL == CU_add_test(pSuiteBoiteNoire, "erreur ensemble de pile de NNN intersection vide ", test_EDPDNNN_Intersection3)) 
    || (NULL == CU_add_test(pSuiteBoiteNoire, "erreur ensemble de pile de NNN soustraction classique ", test_EDPDNNN_Soustraction1)) 
    || (NULL == CU_add_test(pSuiteBoiteNoire, "erreur ensemble de pile de NNN soustraction avec restes elements", test_EDPDNNN_Soustraction2)) 
    || (NULL == CU_add_test(pSuiteBoiteNoire, "erreur ensemble de pile de NNN soustraction pile vide en - ", test_EDPDNNN_Soustraction3)) 
    || (NULL == CU_add_test(pSuiteBoiteNoire, "erreur pile de NNN lors de la creation vide ", test_PileDeNNN_Vide1)) 
    || (NULL == CU_add_test(pSuiteBoiteNoire, "erreur pile de NNN ajout element ", test_PileDeNNN_Vide2)) 
    || (NULL == CU_add_test(pSuiteBoiteNoire, "erreur pile de NNN ajout et obtention élément ", test_PileDeNNN_Empile)) 
    || (NULL == CU_add_test(pSuiteBoiteNoire, "erreur pile de NNN retrait des éléments", test_PileDeNNN_Depile)) 
    || (NULL == CU_add_test(pSuiteBoiteNoire, "erreur pile de NNN longueur de la pile N et 0 ", test_PileDeNNN_Longueur)) 
    || (NULL == CU_add_test(pSuiteBoiteNoire, "erreur liste chainée de CDC creation vide", test_LCDCDC_estVide1)) 
    || (NULL == CU_add_test(pSuiteBoiteNoire, "erreur liste chainée de CDC ajout éléments ", test_LCDCDC_estVide2)) 
    || (NULL == CU_add_test(pSuiteBoiteNoire, "erreur liste chainée de CDC obtenir element ", test_LCDCDC_obtenirElement)) 
    || (NULL == CU_add_test(pSuiteBoiteNoire, "erreur liste chainée de CDC fixer élément", test_LCDCDC_fixerElement)) 
    || (NULL == CU_add_test(pSuiteBoiteNoire, "erreur liste chainée de CDC obtenir liste suivante ", test_LCDCDC_obtenirListeSuivante)) 
    || (NULL == CU_add_test(pSuiteBoiteNoire, "erreur liste chainée de CDC fixer liste suivante", test_LCDCDC_fixerListeSuivante)) 
    || (NULL == CU_add_test(pSuiteBoiteNoire, "erreur liste chainée de CDC supprimer Tete", test_LCDCDC_supprimerTete)) 
    || (NULL == CU_add_test(pSuiteBoiteNoire, "erreur liste chainée de CDC supprimer liste remplie", test_LCDCDC_supprimer1)) 
    || (NULL == CU_add_test(pSuiteBoiteNoire, "erreur liste chainée de CDC supprimer liste vide", test_LCDCDC_supprimer2)) 
    || (NULL == CU_add_test(pSuiteBoiteNoire, "erreur liste chainee de Direction creation et est vide", test_LCDD_estVide1)) 
    || (NULL == CU_add_test(pSuiteBoiteNoire, "erreur liste chainee de Direction ajout/estVide", test_LCDD_estVide2)) 
    || (NULL == CU_add_test(pSuiteBoiteNoire, "erreur liste chainee de Direction obtention élément", test_LCDD_obtenirElement)) 
    || (NULL == CU_add_test(pSuiteBoiteNoire, "erreur liste chainee de Direction fixer élément", test_LCDD_fixerElement)) 
    || (NULL == CU_add_test(pSuiteBoiteNoire, "erreur liste chainee de Direction obtenir liste suivante", test_LCDD_obtenirListeSuivante)) 
    || (NULL == CU_add_test(pSuiteBoiteNoire, "erreur liste chainee de Direction fixer liste suivante", test_LCDD_fixerListeSuivante)) 
    || (NULL == CU_add_test(pSuiteBoiteNoire, "erreur liste chainee de Direction supprimer Tete de liste puis vide", test_LCDD_supprimerTete1)) 
    || (NULL == CU_add_test(pSuiteBoiteNoire, "erreur liste chainee de Direction supprimer Tete de liste puis pleine", test_LCDD_supprimerTete2)) 
    || (NULL == CU_add_test(pSuiteBoiteNoire, "erreur liste chainee de Direction supprimer liste pleine", test_LCDD_supprimer1)) 
    || (NULL == CU_add_test(pSuiteBoiteNoire, "erreur liste chainee de Direction supprimer liste vide", test_LCDD_supprimer2)) 
    || (NULL == CU_add_test(pSuiteBoiteNoire, "erreur Liste chainee de pile de NNN est vide", test_LCDPDNNN_estVide1)) 
    || (NULL == CU_add_test(pSuiteBoiteNoire, "erreur Liste chainee de pile de NNN n'est pas vide", test_LCDPDNNN_estVide2)) 
    || (NULL == CU_add_test(pSuiteBoiteNoire, "erreur Liste chainee de pile de NNN obtenir element ", test_LCDPDNNN_obtenirElement)) 
    || (NULL == CU_add_test(pSuiteBoiteNoire, "erreur Liste chainee de pile de NNN fixer element ", test_LCDPDNNN_fixerElement)) 
    || (NULL == CU_add_test(pSuiteBoiteNoire, "erreur Liste chainee de pile de NNN obtenir liste suivante ", test_LCDPDNNN_obtenirListeSuivante)) 
    || (NULL == CU_add_test(pSuiteBoiteNoire, "erreur Liste chainee de pile de NNN fixer liste suivante ", test_LCDPDNNN_fixerListeSuivante)) 
    || (NULL == CU_add_test(pSuiteBoiteNoire, "erreur Liste chainee de pile de NNN suppression tete ", test_LCDPDNNN_supprimerTete)) 
    || (NULL == CU_add_test(pSuiteBoiteNoire, "erreur Liste chainee de pile de NNN supprimer liste ", test_LCDPDNNN_supprimer)) 
    || (NULL == CU_add_test(pSuiteBoiteNoire, "erreur Liste chainée de NNN est vide ", test_LCDNNN_estVide1)) 
    || (NULL == CU_add_test(pSuiteBoiteNoire, "erreur Liste chainée de NNN est non vide", test_LCDNNN_estVide2)) 
    || (NULL == CU_add_test(pSuiteBoiteNoire, "erreur Liste chainée de NNN obtenir element ", test_LCDNNN_obtenirElement)) 
    || (NULL == CU_add_test(pSuiteBoiteNoire, "erreur Liste chainée de NNN fixer element ", test_LCDNNN_fixerElement)) 
    || (NULL == CU_add_test(pSuiteBoiteNoire, "erreur Liste chainée de NNN obtenir liste suivante", test_LCDNNN_obtenirListeSuivante)) 
    || (NULL == CU_add_test(pSuiteBoiteNoire, "erreur Liste chainée de NNN fixer liste suivante ", test_LCDNNN_fixerListeSuivante)) 
    || (NULL == CU_add_test(pSuiteBoiteNoire, "erreur Liste chainée de NNN supprimer tete de liste ", test_LCDNNN_supprimerTete)) 
    || (NULL == CU_add_test(pSuiteBoiteNoire, "erreur Liste chainée de NNN supprimer la liste ", test_LCDNNN_supprimer)) 
    || (NULL == CU_add_test(pSuiteBoiteNoire, "erreur liste chainee d'ordres est Vide ", test_LCDO_estVide1)) 
    || (NULL == CU_add_test(pSuiteBoiteNoire, "erreur liste chainee d'ordres n'est pas vide", test_LCDO_estVide2)) 
    || (NULL == CU_add_test(pSuiteBoiteNoire, "erreur liste chainee d'ordres obtenir element ", test_LCDO_obtenirElement)) 
    || (NULL == CU_add_test(pSuiteBoiteNoire, "erreur liste chainee d'ordres fixer element ", test_LCDO_fixerElement)) 
    || (NULL == CU_add_test(pSuiteBoiteNoire, "erreur liste chainee d'ordres obtenir liste suivante ", test_LCDO_obtenirListeSuivante)) 
    || (NULL == CU_add_test(pSuiteBoiteNoire, "erreur liste chainee d'ordres fixer liste suivante ", test_LCDO_fixerListeSuivante)) 
    || (NULL == CU_add_test(pSuiteBoiteNoire, "erreur liste chainee d'ordres supprimer tete de liste ", test_LCDO_supprimerTete)) 
    || (NULL == CU_add_test(pSuiteBoiteNoire, "erreur liste chainee d'ordres supprimer toute la liste ", test_LCDO_supprimer))
    || (NULL == CU_add_test(pSuiteBoiteNoire, "erreur Liste de NNN est vide ", test_LDNNN_estVide1))     // liste de NNN implémentéééé avant Liste de CDC
    || (NULL == CU_add_test(pSuiteBoiteNoire, "erreur Liste de NNN n'est pas vide ", test_LDNNN_estVide2))
    || (NULL == CU_add_test(pSuiteBoiteNoire, "erreur Liste de NNN obtenir element ", test_LDNNN_obtenirElement))
    || (NULL == CU_add_test(pSuiteBoiteNoire, "erreur Liste de NNN supprimer element ", test_LDNNN_supprimer))
    || (NULL == CU_add_test(pSuiteBoiteNoire, "erreur Liste de NNN longeur de la liste ", test_LDNNN_longueur))
    || (NULL == CU_add_test(pSuiteBoiteNoire, "erreur Liste de CDC est vide ", test_LDCDC_estVide1))
    || (NULL == CU_add_test(pSuiteBoiteNoire, "erreur Liste de CDC non vide ", test_LDCDC_estVide2))
    || (NULL == CU_add_test(pSuiteBoiteNoire, "erreur Liste de CDC obtenir element ", test_LDCDC_obtenirElement))
    || (NULL == CU_add_test(pSuiteBoiteNoire, "erreur Liste de CDC supprimer element ", test_LDCDC_supprimer1))
    || (NULL == CU_add_test(pSuiteBoiteNoire, "erreur Liste de CDC supprimer element ", test_LDCDC_supprimer2))
    || (NULL == CU_add_test(pSuiteBoiteNoire, "erreur Liste de CDC longeur de la liste ", test_LDCDC_longueur))
    || (NULL == CU_add_test(pSuiteBoiteNoire, "erreur Liste d'ordres est vide ", test_LDO_estVide1))
    || (NULL == CU_add_test(pSuiteBoiteNoire, "erreur Liste d'ordres n'est pas vide ", test_LDO_estVide2))
    || (NULL == CU_add_test(pSuiteBoiteNoire, "erreur Liste d'ordres obtenir un élément ", test_LDO_obtenirElement))
    || (NULL == CU_add_test(pSuiteBoiteNoire, "erreur Liste d'ordres supprimer un element ", test_LDO_supprimer))
    || (NULL == CU_add_test(pSuiteBoiteNoire, "erreur Liste d'ordres longeur de la liste ", test_LDO_longueur))
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


