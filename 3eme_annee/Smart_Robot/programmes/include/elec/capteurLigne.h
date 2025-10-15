/**
 * @file capteurLigne.h
 * @brief Décris les fonctions analysant les lignes sous le robot.
 */
#ifndef __CAPTEURLIGNE__
#define __CAPTEURLIGNE__

/**
 * @brief CL_detectionIntersection permet de savoir si on a détecté une intersection.
 * @return renvoie 1 si une intersection est detecté 0 sinon.
 * 
 */
int CL_detectionIntersection();
/**
 * @brief CL_sortieLabyrinthe permet de savoir si on a détecté que le robot est sortie du labyrinthe.
 * @return renvoie 1 si le robot est bien sortie 0 sinon.
 * 
 */
int CL_sortieLabyrinthe();
/**
 * @brief CL_seRedresser permet de savoir si on a détecté une situation ou le robot doit se redresser, afin de bien suivre la ligne sous celui-ci.
 * @return renvoie 1 si le robot doit se redresser 0 sinon.
 * 
 */
int CL_seRedresser();

#endif