/**
 * @file Ordre.h
 * @brief Définition des ordres utilisés dans la manipulation du robot.
 */

#ifndef ORDRE
#define ORDRE

/**
 * @enum Ordre
 * @brief Représente les différentes actions possibles du robot.
 * 
 * - `TD` : Tourner à droite.
 * - `TG` : Tourner à gauche.
 * - `AV` : Avancer.
 */
typedef enum {
    TD, 
    TG, 
    AV,
} Ordre;

#endif
