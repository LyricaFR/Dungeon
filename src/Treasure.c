/* Auteur: PEREZ LEFEUVRE Vincent - QUACH Kevin
 * Date de création: 06-12-2021
 * Date de modification: 05-01-2022 */

#include "../include/Treasure.h"

Treasure generate_treasure(int nb_floor, int pos_x, int pos_y){
	int i;
	Treasure treasure;
	treasure.pos_x = pos_x;
	treasure.pos_y = pos_y;	
	for(i = 0; i < NB_OBJECT_TREASURE; i++){
		treasure.object[i] = generate_object(nb_floor);
	}
	return treasure;
}    

Chest init_chest(){
	Chest chest;
	chest.state = 0;
	return chest;
}