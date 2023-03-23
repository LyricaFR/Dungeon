/* Auteur: PEREZ LEFEUVRE Vincent - QUACH Kevin
 * Date de création: 21-11-2021
 * Date de modification: 13-01-2022 */

#ifndef __INVENTORY__
#define __INVENTORY__

#include "Object.h"
  
#define NB_OBJECT 12

typedef struct{
    int state; /* 0 = close , 1 = open */
    int select; /* 0 - 11 */
    Object grid[NB_OBJECT];
}Inventory;

/* Initiate the inventory, all the slots are set on empty */
Inventory create_inventory();

/* Manage the item selected in the inventory depending on where the user clicks with the mouse or using the keyboard's directional arrows */
void change_select(Inventory * inventory, MLV_Keyboard_button touche, int clic_x, int clic_y);

/* Drop the selectem item, if the item is an equipment and is equipped, it won't be dropped, when an item is dropped, the slot becomes empty */
void drop_item(Inventory * inventory);    


#endif