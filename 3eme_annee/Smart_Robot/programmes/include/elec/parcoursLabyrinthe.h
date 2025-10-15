/**
 * @file parcoursLabyrinthe.h
 * @brief Décris le parcours du labyrinthe
 */

#ifndef __PARCOURSLABYRINTHE__
#define __PARCOURSLABYRINTHE__
#include "../../include/Types/ListeDOrdre.h"
/**
 * @brief PL_parcoursLabyrinthe va parcourir le labyrinthe selon une liste d'ordres en utilisant obstacle et situation. obstacle permet grâce à un thread externe de detecter un obstacle face au robot. situation est actualisé pendant la progression du robot afin de mettre à jour l'écran lcd via un thread externe.
 * 
 * @param vitesseInput vitesse souhaité lors du parcours
 * @param lcdHandleInput variable relative à l'écran lcd afin de l'actualisé au cours du parcours
 * @param laListeDOrdres une liste d'ordres de type Ordre qui nous permettrons de parcourir le labyrinthe
 *
 */
void PL_parcoursLabyrinthe (int vitesseInput, int lcdHandleInput, LDO_ListeDOrdre laListeDOrdres);

#endif
