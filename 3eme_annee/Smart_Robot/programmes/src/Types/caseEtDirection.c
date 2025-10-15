#include <errno.h>
#include <assert.h>
#include "../../include/Types/Direction.h"
#include "../../include/Types/caseEtDirection.h"


CD_CaseEtDirection CD_caseEtDirection(unsigned int c, Direction d){
  CD_CaseEtDirection cd;
  cd.laCase = c;
  cd.laDirection = d;
  return cd;
}


void CD_fixerCase(CD_CaseEtDirection* cd, unsigned int c){
  (*cd).laCase = c;
}


void CD_fixerDirection(CD_CaseEtDirection* cd, Direction d){
  (*cd).laDirection = d;
}


unsigned int CD_obtenirCase(CD_CaseEtDirection cd){
  return cd.laCase;
}


Direction CD_obtenirDirection(CD_CaseEtDirection cd){
  return cd.laDirection;
}
