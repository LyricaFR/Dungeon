/* Auteur: PEREZ LEFEUVRE Vincent - QUACH Kevin
 * Date de création: 21-11-2021
 * Date de modification: 08-01-2022 */

#include "../include/Character.h"

/* Initialise le character */
Character create_character(Job job){
    Character character;
    /* Character Stats */
    character.job = job;
    if (job == WARRIOR){
        character.Atk = 13;
        character.Int = 7;
        character.Def = 13;
    }
    else if (job == MAGE){
        character.Atk = 9;
        character.Int = 16;
        character.Def = 8;
    }
    else {
        character.Atk = 10;
        character.Int = 10;
        character.Def = 10;
    }
    character.hp = 10 * character.Def;
    character.hp_max = 10 * character.Def;  
    character.mp = 10 * character.Int - 50;
    character.mp_max = 10 * character.Int - 50;     
    character.Exp = 0;
    character.Lv = 1;
    character.point = 0;
    character.critical_hit = 5; /* % */
    character.coef_exp = 1; /* 1 ou 2 */
    character.direction = SOUTH;
    character.inventory = create_inventory();
    character.state_map = 0;
    character.state_skill = 0;
    character.stuff = init_stuff();
    character.effect = init_effect();
    /* Character Position*/
    character.pos_x = STAGE_WIDTH / 2;
    character.pos_y = STAGE_HEIGHT / 2;
    /* Camera Position */
    character.camera.pos_x = STAGE_WIDTH / 2 - NB_CELL_COL / 2;
    character.camera.pos_y = STAGE_HEIGHT / 2 - NB_CELL_LIG / 2;
    character.chest = init_chest();
    character.nb_mob = 0;
    return character;
}

Job class_select(MLV_Image* screen){
    Job job;
    int clic_x, clic_y;
    MLV_Keyboard_button touche;
    MLV_draw_image(screen, 0, 0);
    MLV_update_window();
    int class_select = 1;
    /* Select class */
    while (class_select){
        MLV_wait_keyboard_or_mouse(&touche, NULL, NULL, &clic_x, &clic_y);
        if (clic_x > 86 && clic_x < 276 && clic_y > 345 && clic_y < 377){
            job = WARRIOR;
            class_select = 0;
        }
        if (clic_x > 324 && clic_x < 514 && clic_y > 345 && clic_y < 377){
            job = TRAVELER;
            class_select = 0;
        }
        if (clic_x > 557 && clic_x < 747 && clic_y > 345 && clic_y < 377){
            job = MAGE;
            class_select = 0;
        }
    }
    return job;
}

/* Deplace le character et sa camera */
void move(Character * character, int x, int y){
        /*  On deplace le personnage */
        character->pos_x += x;
        character->pos_y += y; 
        /* On deplace la camera en fonction des bord du terrain */
        if (character->camera.pos_x > 0 && character->camera.pos_x + NB_CELL_COL < STAGE_WIDTH)
            character->camera.pos_x += x;
        else if (character->pos_x > NB_CELL_COL / 2 && character->pos_x + 1 < STAGE_WIDTH - NB_CELL_COL / 2)
            character->camera.pos_x += x;
        if (character->camera.pos_y > 0 && character->camera.pos_y + NB_CELL_LIG < STAGE_HEIGHT)
            character->camera.pos_y += y;
        else if (character->pos_y > NB_CELL_LIG / 2 && character->pos_y + 1 < STAGE_HEIGHT - NB_CELL_LIG / 2)
            character->camera.pos_y += y;
}

/* Descend d'un etage le donjon */
void go_down(Dungeon * dungeon, Character * character){
    /* Si on est au dernier etage créé on en ajoute un */
    if (dungeon->current_floor == dungeon->nb_floor) add_floor(dungeon);
    dungeon->current_floor++;  /* On descend d'un etage */
    /* On positionne le character et sa camera a l'escalier central */
    character->pos_x = STAGE_WIDTH / 2;
    character->pos_y = STAGE_HEIGHT / 2; 
    character->camera.pos_x = character->pos_x - NB_CELL_COL / 2;
    character->camera.pos_y = character->pos_y - NB_CELL_LIG / 2;      
}

/* Monte d'un etage le donjon */
void go_up(Dungeon * dungeon, Character * character){
    int i, j;
    /* On verifie qu'on est pas au premier etage du donjon */
    if(dungeon->current_floor == 1) return;
    dungeon->current_floor--;  /* On monte d'un etage */
    /* On cherche l'escalier de l'etage du dessus et on y positionne le character avec sa camera */
    for (i = 0; i < STAGE_WIDTH;i++){
        for (j = 0; j < STAGE_HEIGHT;j++){
            if (dungeon->stage[dungeon->current_floor - 1].grid[i][j].type == STAIR_DOWN){ 
                character->pos_x = i;
                character->pos_y = j; 
                character->camera.pos_x = i - NB_CELL_COL / 2;
                character->camera.pos_y = j - NB_CELL_LIG / 2;    
                if (character->pos_x < 4)
                    character->camera.pos_x = 0;
                if (character->pos_y < 4)
                    character->camera.pos_y = 0;     
                if (character->pos_x > STAGE_WIDTH - 1 - (NB_CELL_COL - 1) / 2)
                    character->camera.pos_x = STAGE_WIDTH - NB_CELL_COL;
                if (character->pos_y > STAGE_HEIGHT - 1 - (NB_CELL_LIG - 1) / 2)
                    character->camera.pos_y = STAGE_HEIGHT - NB_CELL_LIG;  
                return;     
            }    
        }
    }
}

/* Lance une attaque */
int attack(Character * character, int atk, int accuracy){
    /* 80% - 120% */
    int damage = damage = ((80 + rand() % 41) / 100.0 ) * atk;
    /* 5% */
    if (rand() % (100 / accuracy) == 1)
        damage = damage * 3;
    return damage;
}

void effect_potion(Character * character){
    character->coef_exp = 1;
    character->critical_hit = 5;    
    if(character->effect.regeneration.nb_round != 0 && ((character->effect.regeneration.nb_round) % 3) == 0)
        regeneration_potion(&character->hp, &character->mp, character->hp_max, character->mp_max);          
    else if(character->effect.accuracy.nb_round != 0)
        accuracy_potion(&character->critical_hit);    
    else if(character->effect.learning.nb_round!= 0)
        learning_potion(&character->coef_exp);     
    round_count_down(&character->effect.regeneration);
    round_count_down(&character->effect.accuracy);
    round_count_down(&character->effect.learning);                    
}

void monster_attack(Character * character, Stage stage){
    int i;
    Cell * adjacent = generate_adjacent(stage, character->pos_x, character->pos_y);
    for (i = 0; i < 4; i++){
        if (adjacent[i].type == MONSTER)
            character->hp -= (attack(character, adjacent[i].entity.monster.Atk, 5) - character->Def);
    }
}

/* Execute les interractions du personnage sur le dongeon et ses entités */
void interaction(Character *character, Dungeon * dungeon, Direction direction, MLV_Keyboard_button touche, int x, int y, int clic_x, int clic_y){
    int floor = dungeon->current_floor - 1; /* L'etage actuel */
    Cell cell = dungeon->stage[floor].grid[character->pos_x + x][character->pos_y + y]; /* Cell ou le joueur se dirige */
    character->direction = direction;    /* On change la direction du joueur */
    effect_potion(character);        
    /* Character move */
    if (cell.type == ROOM || cell.type == STAIR_UP || cell.type == STAIR_DOWN)
        move(character, x, y);

    /*  Character open treasure */
    else if (cell.type == TREASURE){
        character->chest.state = 1;
        character->chest.treasure = dungeon->stage[floor].grid[character->pos_x + x][character->pos_y + y].entity.treasure;
    }

    /* Character lance le combat et on determine les enemy adjacent */
    else if (cell.type == MONSTER){
        dungeon->stage[floor].grid[character->pos_x + x][character->pos_y + y].entity.monster.hp -= 
        attack(character, character->Atk + character->stuff.weapon.quality, character->critical_hit);    
        if (monster_is_dead(dungeon->stage[floor].grid[character->pos_x + x][character->pos_y + y].entity.monster)){
            character->nb_mob++;
            character->Exp += (dungeon->stage[floor].floor * 30) * character->coef_exp;
            dungeon->stage[floor].grid[character->pos_x + x][character->pos_y + y].type = ROOM;
        } 
        monster_attack(character, dungeon->stage[floor]);
    }
    /* Character descent dans le donjon */
    if (cell.type == STAIR_DOWN) go_down(dungeon, character);

    /* Chractere monte dans le donjon */
    else if (cell.type == STAIR_UP) go_up(dungeon, character);
}

void move_interaction(Character * character, Dungeon * dungeon, MLV_Keyboard_button touche, int clic_x, int clic_y){
    if((touche == MLV_KEYBOARD_UP || touche == MLV_KEYBOARD_z))      /* Move Up */
        interaction(character, dungeon, NORTH, touche, 0, -1, clic_x, clic_y);
    if((touche == MLV_KEYBOARD_DOWN || touche == MLV_KEYBOARD_s))    /* Move Down */
        interaction(character, dungeon, SOUTH, touche, 0, 1, clic_x, clic_y);
    if((touche == MLV_KEYBOARD_RIGHT || touche == MLV_KEYBOARD_d))  /* Move Right */
        interaction(character, dungeon, EAST, touche, 1, 0, clic_x, clic_y);    
    if((touche == MLV_KEYBOARD_LEFT || touche == MLV_KEYBOARD_q))    /* Move Left */
        interaction(character, dungeon, WEST, touche, -1, 0, clic_x, clic_y);    
}

void use_item(Character * character){
    int index;
    index = character->inventory.select;
    Object obj = character->inventory.grid[index];
    if (obj.type == POTION){
        if (obj.entity.potion.type == HEAL)
            restaure_potion(&character->hp, character->hp_max, HEAL_PERCENT);
        else if (obj.entity.potion.type == MAGIC)
            restaure_potion(&character->mp, character->mp_max, MAGIC_PERCENT);
        else if (obj.entity.potion.type == REGENERATION)
            round_potion(&(character->effect), obj.entity.potion, 30);
        else if (obj.entity.potion.type == ACCURACY)
            round_potion(&(character->effect), obj.entity.potion, 30);  
        else if (obj.entity.potion.type == LEARNING)
            round_potion(&(character->effect), obj.entity.potion, 30);            
        character->inventory.grid[index].type = EMPTY;  
    }
}

void inventory_interaction(Character * character, MLV_Keyboard_button touche, int clic_x, int clic_y){
    int pos_x = (NB_CELL_COL * 64 / 2) - 316 / 2;
    int pos_y = (NB_CELL_LIG * 64 / 2) - 244 / 2;    
    change_select(&(character->inventory), touche, clic_x, clic_y);
    if (touche == MLV_KEYBOARD_t || (clic_x >  pos_x + 332 && clic_x < pos_x + 332 + 64 && clic_y > pos_y + 244  - 80 && clic_y < pos_y + 244  - 16)) 
        drop_item(&(character->inventory));
    if ((touche == MLV_KEYBOARD_u) || (clic_x >  pos_x + 332 && clic_x < pos_x + 332 + 64 && clic_y > pos_y  + 80  - 64 && clic_y < pos_y + 80))
        use_item(character);
}

/* Monte le niveau du joueur si il a assez d'experience */
void level_up(Character * character){
    if (350 + 50 * character->Lv <= character->Exp){
        character->Exp = character->Exp - (350 + 50 * character->Lv);
        character->Lv++;
        character->hp = character->hp_max;
        character->mp = character->mp_max;
        character->point += 3;
    }
}

void skill_interaction(Character * character, MLV_Keyboard_button touche, int clic_x, int clic_y){
    int pos_x = (NB_CELL_COL * 64 / 2) - 256 / 2;
    int pos_y = (NB_CELL_LIG * 64 / 2) - 161 / 2; 
    if (character->point > 0){      
        if (clic_x > pos_x + 31 && clic_x < pos_x + 64 && clic_y > pos_y + 86 && clic_y < pos_y + 86 + 33){
            character->Def++;
            character->point--;
        }
        else if (clic_x > pos_x + 111 && clic_x < pos_x + 144 && clic_y > pos_y + 86 && clic_y < pos_y + 86 + 33){
            character->Int++;
            character->point--;
        }
        else if (clic_x > pos_x + 191 && clic_x < pos_x + 224 && clic_y > pos_y + 86 && clic_y < pos_y + 86 + 33){
            character->Atk++;    
            character->point--;
        }
    }
}

void choice_attack(Character * character, Stage * stage, MLV_Keyboard_button touche, int clic_x, int clic_y, int pos_x, int pos_y){
    /* Magic Attack */
    if (stage->grid[pos_x][pos_y].type == MONSTER){
        if(touche == MLV_KEYBOARD_e || (clic_x > 320 && clic_x < 512 && clic_y > NB_CELL_LIG * 64 - 32 && clic_y < NB_CELL_LIG * 64)) {                                            
            stage->grid[pos_x][pos_y].entity.monster.hp -= attack(character, character->Int * 2 + character->stuff.wand.quality, character->critical_hit);
            character->mp -= 20;  
        }
        /* Melee Attack */
        else stage->grid[pos_x][pos_y].entity.monster.hp -= attack(character, character->Atk + character->stuff.weapon.quality, character->critical_hit);    
        if (monster_is_dead(stage->grid[pos_x][pos_y].entity.monster)){
            character->nb_mob++;
            character->Exp += (stage->floor * 30) * character->coef_exp;
            stage->grid[pos_x][pos_y].type = ROOM;
        }
        monster_attack(character, *stage);  
    }    
}


void fight(Character * character, Stage * stage, MLV_Keyboard_button touche, int clic_x, int clic_y){
    if (character->direction == NORTH)
        choice_attack(character, stage, touche, clic_x, clic_y, character->pos_x, character->pos_y - 1);
    if (character->direction == SOUTH)
        choice_attack(character, stage, touche, clic_x, clic_y, character->pos_x, character->pos_y + 1);        
    if (character->direction == EAST)
        choice_attack(character, stage, touche, clic_x, clic_y, character->pos_x + 1, character->pos_y);        
    if (character->direction == WEST)                
        choice_attack(character, stage, touche, clic_x, clic_y, character->pos_x - 1, character->pos_y); 
}

int is_open_chest(Character character, Stage stage, Object * object){
    int i;
    for (i = 0; i < NB_OBJECT_TREASURE; i++){
        if (stage.grid[character.chest.treasure.pos_x][character.chest.treasure.pos_y].entity.treasure.object[i].type != EMPTY){
            (*object) = character.chest.treasure.object[i];
            return i + 1;
        }
    }
    return 0;
}

void remove_equipment(Character * character){
    int i;
    for (i = 0; i < NB_OBJECT; i++){
        if (character->inventory.grid[i].type == EQUIPMENT){
            if (character->inventory.grid[i].entity.equipment.equip){
                if (character->inventory.grid[i].entity.equipment.type == ARMOR){
                    if (character->inventory.grid[i].entity.equipment.quality < character->stuff.armor.quality)
                        character->inventory.grid[i].entity.equipment.equip = 0;
                }
                if (character->inventory.grid[i].entity.equipment.type == WAND){
                    if (character->inventory.grid[i].entity.equipment.quality < character->stuff.wand.quality)
                        character->inventory.grid[i].entity.equipment.equip = 0;
                }
                if (character->inventory.grid[i].entity.equipment.type == WEAPON){
                    if (character->inventory.grid[i].entity.equipment.quality < character->stuff.weapon.quality)
                        character->inventory.grid[i].entity.equipment.equip = 0;
                }                                
            }
        }
    }
}

void chest_interaction(Character * character, Stage * stage, int clic_x, int clic_y){
    int i, tmp;
    Object object;
    tmp = is_open_chest(*character, *stage, &object);
    if (!tmp){
        character->chest.state = 0;
        return;
    }
    if (clic_x > 775 && clic_x < 775 + 32 && clic_y > 242 && clic_y < 242 + 32){
        for (i = 0; i < 12; i++){
            if (character->inventory.grid[i].type == EMPTY){
                if (object.type == EQUIPMENT)
                    equip(&character->stuff, &object.entity.equipment);
                character->inventory.grid[i] = object;
                stage->grid[character->chest.treasure.pos_x][character->chest.treasure.pos_y].entity.treasure.object[tmp - 1].type = EMPTY;
                break;
            }
        }
    }

    if (clic_x > 775 && clic_x < 775 + 32 && clic_y > 304 && clic_y < 304 + 32)
        stage->grid[character->chest.treasure.pos_x][character->chest.treasure.pos_y].entity.treasure.object[tmp - 1].type = EMPTY;

    remove_equipment(character);

    if (stage->grid[character->chest.treasure.pos_x][character->chest.treasure.pos_y].entity.treasure.object[NB_OBJECT_TREASURE - 1].type == EMPTY)
      stage->grid[character->chest.treasure.pos_x][character->chest.treasure.pos_y].type = ROOM; 
}

void change_direction(Character * character, int clic_x, int clic_y){
    int x, y;
    x = character->camera.pos_x + clic_x / 64;
    y = character->camera.pos_y + clic_y / 64;
    if (x == character->pos_x && y == character->pos_y + 1)
        character->direction = SOUTH;
    else if(x == character->pos_x && y == character->pos_y - 1)
        character->direction = NORTH;
    else if(x == character->pos_x + 1 && y == character->pos_y)
        character->direction = EAST; 
    else if(x == character->pos_x - 1 && y == character->pos_y)
        character->direction = WEST;              
}

/* Permet de faire interargir le personnage dans le stage */
void character_interaction(Character * character, Dungeon * dungeon, MLV_Keyboard_button touche, int clic_x, int clic_y, int map){
    /* Si l'inventaire est ouvert */
    change_direction(character, clic_x, clic_y);
    if(character->inventory.state)
        inventory_interaction(character, touche, clic_x, clic_y);

    if (character->chest.state){
        inventory_interaction(character, touche, clic_x, clic_y);
        chest_interaction(character, &dungeon->stage[dungeon->current_floor - 1], clic_x, clic_y);
    }

    if(character->state_skill)
        skill_interaction(character, touche, clic_x, clic_y);
    /* Si on est pas en combat et que l'inventaire n'est pas ouvert */
    if (!character->inventory.state && !character->state_skill && !character->chest.state)
        move_interaction(character, dungeon, touche, clic_x, clic_y);

    /* Active et désactive l'inventaire */
    if((touche == MLV_KEYBOARD_i) || (clic_x > 512 && clic_x < 704 && clic_y > NB_CELL_LIG * 64 - 32 && clic_y < NB_CELL_LIG * 64))                                                                                    
         if (!character->state_skill) character->inventory.state = -(character->inventory.state - 1); 
    /* Active et désactive la carte */            
    if(touche == MLV_KEYBOARD_m && map)                                                                                    
        character->state_map = -(character->state_map - 1);

    if(touche == MLV_KEYBOARD_c || (clic_x > 10 && clic_x < 43 && clic_y > 64 * 6 && clic_y < 64 * 6 + 33))                                                                                  
        if (!character->inventory.state) character->state_skill = -(character->state_skill - 1);    
    /* Lance les attaques si on est en combat */
    if((touche == MLV_KEYBOARD_a)|| ((touche == MLV_KEYBOARD_e) && character->mp >= 20)
        || (clic_x > 128 && clic_x < 320 && clic_y > NB_CELL_LIG * 64 - 32 && clic_y < NB_CELL_LIG * 64)
        || ((clic_x > 320 && clic_x < 512 && clic_y > NB_CELL_LIG * 64 - 32 && clic_y < NB_CELL_LIG * 64) && character->mp >= 20)){
        effect_potion(character); 
        fight(character, &dungeon->stage[dungeon->current_floor - 1], touche, clic_x, clic_y);        
    } 
    character->hp_max = 10 * (character->Def + character->stuff.armor.quality);
    character->mp_max = 10 * (character->Int + character->stuff.wand.quality) - 50;
    level_up(character);
}

/* Verifie si le character est en vie */
int is_dead(Character character){
    if (character.hp <= 0) return 1;
    return 0;
}

