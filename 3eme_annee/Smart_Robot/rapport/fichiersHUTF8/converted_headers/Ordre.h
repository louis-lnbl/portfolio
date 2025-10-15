/**
 * @file Ordre.h
 * @brief DÃ©finition des ordres utilisÃ©s dans la manipulation du robot.
 */

#ifndef ORDRE
#define ORDRE

/**
 * @enum Ordre
 * @brief ReprÃ©sente les diffÃ©rentes actions possibles du robot.
 * 
 * - `TD` : Tourner Ã  droite.
 * - `TG` : Tourner Ã  gauche.
 * - `AV` : Avancer.
 */
typedef enum {
    TD, 
    TG, 
    AV  
} Ordre;

#endif
