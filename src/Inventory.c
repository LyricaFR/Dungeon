/* Auteur: PEREZ LEFEUVRE Vincent - QUACH Kevin
 * Date de création: 21-11-2021
 * Date de modification: 04-01-2022 */

#include "../include/Inventory.h"

Inventory create_inventory(){
    int i;
    Inventory inventory;
    for(i = 0; i < NB_OBJECT; i++){
        inventory.grid[i].type = EMPTY; 
    }
    inventory.state = 0; /* close */
    inventory.select = 0; /* de 0 à 11 */
    return inventory;
}

void change_select(Inventory * inventory, MLV_Keyboard_button touche, int clic_x, int clic_y){
    if (clic_x > 272 && clic_x < 558 && clic_y > 182 && clic_y < 397)
        inventory->select = (clic_x - 272)/72 + 4 * (( clic_y - 182) /72);
    if (touche == MLV_KEYBOARD_UP && inventory->select >= 4)
        inventory->select -= 4;
    if (touche == MLV_KEYBOARD_DOWN && inventory->select <= 7)
        inventory->select += 4;
    if (touche == MLV_KEYBOARD_LEFT && (inventory->select + 4) % 4 != 0)
        inventory->select--;
    if (touche == MLV_KEYBOARD_RIGHT && (inventory->select + 1) % 4 != 0)
        inventory->select++;

}

void drop_item(Inventory * inventory){
    if (inventory->grid[inventory->select].type == EQUIPMENT){
        if (inventory->grid[inventory->select].entity.equipment.equip)
            return;
    }
    inventory->grid[inventory->select].type = EMPTY;
}