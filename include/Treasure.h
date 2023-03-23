/* Auteur: PEREZ LEFEUVRE Vincent - QUACH Kevin
 * Date de création: 06-12-2021
 * Date de modification: 13-01-2022 */

#ifndef __TREASURE__
#define __TREASURE__

#include "Object.h"

#define NB_OBJECT_TREASURE 2 

typedef struct {
    int pos_x, pos_y;
    Object object[NB_OBJECT_TREASURE];
} Treasure;

typedef struct {
    Treasure treasure;
    int state;
}Chest;

/* Generate a Treasure on the coordinates pos_x, pos_y */
Treasure generate_treasure(int nb_floor, int pos_x, int pos_y);    

/* Initiate a chest */
Chest init_chest();

#endif