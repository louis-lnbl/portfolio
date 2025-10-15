#include <errno.h>
#include <assert.h>

#include "../../include/Labyrinthe/traitementLabyrinthe.h"
#include "../../include/Types/labyrinthe.h"
#include "../../include/Types/PileDeNNN.h"
#include "../../include/Types/ListeDeCaseEtDirection.h"
#include "../../include/Types/ListeDOrdre.h"
#include "../../include/Labyrinthe/trouverChemin.h"
#include "../../include/Labyrinthe/casesEnOrdres.h"

LDO_ListeDOrdre TL_resolution(LAB_Labyrinthe laby){
  PDNNN_PileDeNNN p = TC_trouverPlusCourtChemin(laby);
  LDCD_ListeDeCaseEtDirection casesDirections = CEO_conversionCasesEnCasesEtDirections(laby, p);
  LDO_ListeDOrdre ordres = CEO_conversionCasesEtDirectionsEnOrdres(casesDirections, laby);
  return ordres;
}
