/* Auteur: PEREZ LEFEUVRE Vincent - QUACH Kevin
 * Date de création: 01-01-2022
 * Date de modification: 08-01-2022 */

#include "../include/Save.h"

void save_character(Character character, int mod, FILE * file){
    fwrite(&character.hp, sizeof(int), mod, file);
    fwrite(&character.mp, sizeof(int), mod, file);
    fwrite(&character.hp_max, sizeof(int), mod, file);
    fwrite(&character.mp_max, sizeof(int), mod, file);
    fwrite(&character.Atk, sizeof(int), mod, file);
    fwrite(&character.Def, sizeof(int), mod, file); 
    fwrite(&character.Int, sizeof(int), mod, file);    
    fwrite(&character.Lv, sizeof(int), mod, file);
    fwrite(&character.Exp, sizeof(int), mod, file);
    fwrite(&character.direction, sizeof(int), mod, file);
    fwrite(&character.critical_hit, sizeof(int), mod, file);
    fwrite(&character.point, sizeof(int), mod, file);
    fwrite(&character.coef_exp, sizeof(float), mod, file);    
    fwrite(&character.pos_x, sizeof(int), mod, file);
    fwrite(&character.pos_y, sizeof(int), mod, file);       
    fwrite(&character.state_skill, sizeof(int), mod, file);     
    fwrite(&character.camera, sizeof(Camera), mod, file);
    fwrite(&character.inventory, sizeof(Inventory), mod, file); 
    fwrite(&character.stuff, sizeof(Stuff), mod, file);
    fwrite(&character.effect, sizeof(Effect), mod, file);	
    fwrite(&character.chest, sizeof(Chest), mod, file);   
    fwrite(&character.job, sizeof(int), mod, file); 
    fwrite(&character.nb_mob, sizeof(int), mod, file); 
}

void save_dungeon(Dungeon dungeon, int mod, FILE * file){
	int i, j, index;
    fwrite(&dungeon.nb_floor, sizeof(int), mod, file);
    fwrite(&dungeon.current_floor, sizeof(int), mod, file);     
    for (index = 0; index < dungeon.nb_floor; index++){
	    fwrite(&dungeon.stage[index].floor, sizeof(int), mod, file);   
	    for (i = 0; i < STAGE_WIDTH; i ++){
	        for (j = 0; j < STAGE_HEIGHT; j++){
	        	fwrite(&dungeon.stage[index].grid[i][j], sizeof(Cell), mod, file);
	        }
	    }
	}	
}

int save(Dungeon dungeon, Character character){
    FILE * file;
    file = fopen("bin/save.bin","wb");
    if (file == NULL)
        return 0;
    save_character(character, 1, file);
    save_dungeon(dungeon, 1, file);
    fclose(file);
    return 1;
}

int load_character(Character * character, int mod, FILE * file){
	fread(&character->hp, sizeof(int), mod, file);
	fread(&character->mp, sizeof(int), mod, file);
    fread(&character->hp_max, sizeof(int), mod, file);
    fread(&character->mp_max, sizeof(int), mod, file);
    fread(&character->Atk, sizeof(int), mod, file);    
    fread(&character->Def, sizeof(int), mod, file);  
    fread(&character->Int, sizeof(int), mod, file);            
    fread(&character->Lv, sizeof(int), mod, file);
    fread(&character->Exp, sizeof(int), mod, file);
    fread(&character->direction, sizeof(int), mod, file);
    fread(&character->critical_hit, sizeof(int), mod, file);
    fread(&character->point, sizeof(int), mod, file);
    fread(&character->coef_exp, sizeof(float), mod, file);
    fread(&character->pos_x, sizeof(int), mod, file);
    fread(&character->pos_y, sizeof(int), mod, file);
    fread(&character->state_skill, sizeof(int), mod, file);   
    fread(&character->camera, sizeof(Camera), mod, file);
    fread(&character->inventory, sizeof(Inventory), mod, file);
    fread(&character->stuff, sizeof(Stuff), mod, file);
    fread(&character->effect, sizeof(Effect), mod, file);
    fread(&character->chest, sizeof(Chest), mod, file);
    fread(&character->job, sizeof(int), mod, file);
    fread(&character->nb_mob, sizeof(int), mod, file);  
    character->state_map = 0;  
    return 1;
}

int load_dungeon(Dungeon * dungeon, int mod, FILE * file){
	int i, j, index;
    fread(&dungeon->nb_floor, sizeof(int), mod, file);
    fread(&dungeon->current_floor, sizeof(int), mod, file);
	(dungeon->stage) = (Stage*)malloc(sizeof(Stage) * dungeon->nb_floor);
	if (dungeon->stage == NULL)
		return 0;
    for (index = 0; index < dungeon->nb_floor; index++){
	    fread(&dungeon->stage[index].floor, sizeof(int), mod, file);   
	    for (i = 0; i < STAGE_WIDTH; i ++){
	        for (j = 0; j < STAGE_HEIGHT; j++){
	        	fread(&dungeon->stage[index].grid[i][j], sizeof(Cell), mod, file);
	        }
	    }
	}
	return 1;
}

int load(Dungeon * dungeon, Character * character){
	FILE * file = fopen("bin/save.bin", "rb");
	if (file == NULL)
		return 0;
    if (load_character(character, 1, file) == 0){
    	fprintf(stderr, "Character loading error !\n");
    	return 0;
    }
    if (load_dungeon(dungeon, 1, file) == 0){
        fprintf(stderr, "Dungeon loading error !\n");
    	return 0;
    }
    fclose(file);
	return 1;
}
