/* Auteur: PEREZ LEFEUVRE Vincent - QUACH Kevin
 * Date de création: 21-11-2021
 * Date de modification: 08-01-2022 */

#include "../include/Graphic.h"

MLV_Image **load_all_images(){
    int i;
    MLV_Image **images;
    images = (MLV_Image**)malloc(sizeof(MLV_Image*) * NB_IMAGES);
    if (images == NULL)
        return NULL;
    images[0] = MLV_load_image("Assets/Wall.png");
    MLV_resize_image  ( images[0], MLV_get_image_width(images[0]) * 2, MLV_get_image_height(images[0]) * 2); 
    images[1] = MLV_load_image("Assets/Wall_Ice.png");
    MLV_resize_image  ( images[1], MLV_get_image_width(images[1]) * 2, MLV_get_image_height(images[1]) * 2);    
    images[2] = MLV_load_image("Assets/Wall_Fire.png");
    MLV_resize_image  ( images[2], MLV_get_image_width(images[2]) * 2, MLV_get_image_height(images[2]) * 2);
    images[3] = MLV_load_image("Assets/Wall_Spirit.png");
    MLV_resize_image  ( images[3], MLV_get_image_width(images[3]) * 2, MLV_get_image_height(images[3]) * 2);      
    images[4] = MLV_load_image("Assets/Gameoverscreen.png");  
    images[5] = MLV_load_image("Assets/Character.png");    
    images[6] = MLV_load_image("Assets/Menuscreen.png");    
    images[7] = MLV_load_image("Assets/Interface.png");   
    images[8] = MLV_load_image("Assets/Monster.png");  
    images[9] = MLV_load_image("Assets/ClassSelect.png");
    MLV_resize_image  ( images[8], MLV_get_image_width(images[8]) * 3, MLV_get_image_height(images[8]) * 3);        
    for (i = 0; i < NB_IMAGES; i++){
        if (images[i] == NULL)
        return NULL;
    }
    return images;
}

void free_all_images(MLV_Image **images){
    int i;
    for (i = 0; i < NB_IMAGES; i++){
      MLV_free_image(images[i]);
    }
    free(images);
}

void draw_character(Character character, MLV_Image **images){   
    if (character.direction == NORTH)
        MLV_draw_partial_image(images[5], 128, 64, 64, 64, (character.pos_x - character.camera.pos_x) * NB_PIXEL, (character.pos_y - character.camera.pos_y) * NB_PIXEL - 16);   
    else if (character.direction == SOUTH)
        MLV_draw_partial_image(images[5], 128, 0, 64, 64, (character.pos_x - character.camera.pos_x) * NB_PIXEL, (character.pos_y - character.camera.pos_y) * NB_PIXEL - 16);   
    else if (character.direction == WEST)
        MLV_draw_partial_image(images[5], 128, 128, 64, 64,(character.pos_x - character.camera.pos_x) * NB_PIXEL, (character.pos_y - character.camera.pos_y) * NB_PIXEL - 16);    
    else if (character.direction == EAST){
        MLV_vertical_image_mirror(images[5]);
        MLV_draw_partial_image(images[5], 128, 128, 64, 64, (character.pos_x - character.camera.pos_x) * NB_PIXEL, (character.pos_y - character.camera.pos_y) * NB_PIXEL - 16); 
        MLV_vertical_image_mirror(images[5]);
    }
}


void draw_monster(Monster monster, int pos_x, int pos_y, MLV_Image **images){
    int size;
    size = monster.hp * (58.0 / monster.hp_max);
    MLV_draw_partial_image(images[8], 7, 7, 22 * 3, 19 * 3, pos_x * NB_PIXEL, pos_y * NB_PIXEL);        
    MLV_draw_partial_image(images[7], 484, 70, 64, 10, pos_x * NB_PIXEL , pos_y * NB_PIXEL - 20);
    MLV_draw_partial_image(images[7], 484, 60, 5 + size , 10, pos_x * NB_PIXEL, pos_y * NB_PIXEL - 20);  
}

void draw_room(int pos_x, int pos_y, MLV_Image *image){
    MLV_draw_partial_image(image, 256, 64, NB_PIXEL, NB_PIXEL, pos_x * NB_PIXEL, pos_y * NB_PIXEL);      
}

void draw_treasure(Treasure treasure, int pos_x, int pos_y, MLV_Image *image){
    MLV_draw_partial_image(image, 256, 140, 34, 32, pos_x * NB_PIXEL + 16, pos_y * NB_PIXEL + 16);  
}

void draw_stair_up(int pos_x, int pos_y, MLV_Image *image){
    MLV_draw_partial_image(image, 149 * 2, 96 * 2, 40, 64, pos_x * NB_PIXEL + 12, pos_y * NB_PIXEL - 32);
}

void draw_stair_down(int pos_x, int pos_y, MLV_Image *image){
    MLV_draw_partial_image(image, 121 * 2, 96 * 2, 56, 64, pos_x * NB_PIXEL + 4, pos_y * NB_PIXEL);
}

void draw_wall_standard(Stage stage, int pos_x, int pos_y, int i, int j, MLV_Image *image){
    if (stage.grid[pos_x + i - 1][pos_y + j].type != WALL && stage.grid[pos_x + i][pos_y + j + 1].type == WALL
        && stage.grid[pos_x + i][pos_y + j - 1].type == WALL && stage.grid[pos_x + i + 1][pos_y + j].type == WALL)
        MLV_draw_partial_image(image, 187 * 2, 257 * 2, NB_PIXEL, NB_PIXEL, i * NB_PIXEL, j * NB_PIXEL);
    if (stage.grid[pos_x + i + 1][pos_y + j].type != WALL && stage.grid[pos_x + i][pos_y + j + 1].type == WALL
        && stage.grid[pos_x + i][pos_y + j - 1].type == WALL && stage.grid[pos_x + i - 1][pos_y + j].type == WALL)
        MLV_draw_partial_image(image, 232 * 2, 257 * 2, NB_PIXEL, NB_PIXEL, i * NB_PIXEL, j * NB_PIXEL);            
    if (stage.grid[pos_x + i + 1][pos_y + j].type != WALL && stage.grid[pos_x + i][pos_y + j + 1].type == WALL
        && stage.grid[pos_x + i][pos_y + j - 1].type == WALL && stage.grid[pos_x + i - 1][pos_y + j].type != WALL)
        MLV_draw_partial_image(image, 279 * 2, 257 * 2, NB_PIXEL, NB_PIXEL, i * NB_PIXEL, j * NB_PIXEL);            
    if (stage.grid[pos_x + i][pos_y + j + 1].type != WALL && stage.grid[pos_x + i + 1][pos_y + j].type == WALL
        && stage.grid[pos_x + i - 1][pos_y + j].type == WALL && stage.grid[pos_x + i][pos_y + j - 1].type == WALL)
        MLV_draw_partial_image(image, 96 * 2, 192 * 2, NB_PIXEL ,NB_PIXEL , i * NB_PIXEL, j * NB_PIXEL);
    if (stage.grid[pos_x + i][pos_y + j - 1].type != WALL && stage.grid[pos_x + i + 1][pos_y + j].type == WALL
        && stage.grid[pos_x + i - 1][pos_y + j].type == WALL && stage.grid[pos_x + i][pos_y + j + 1].type == WALL)
        MLV_draw_partial_image(image, 96 * 2, 160 * 2, NB_PIXEL ,NB_PIXEL , i * NB_PIXEL, j * NB_PIXEL);
    if (stage.grid[pos_x + i][pos_y + j - 1].type != WALL && stage.grid[pos_x + i + 1][pos_y + j].type == WALL
        && stage.grid[pos_x + i - 1][pos_y + j].type == WALL && stage.grid[pos_x + i][pos_y + j + 1].type != WALL)
        MLV_draw_partial_image(image, 185 * 2, 341 * 2, NB_PIXEL ,NB_PIXEL , i * NB_PIXEL, j * NB_PIXEL);
    if (stage.grid[pos_x + i - 1][pos_y + j].type == WALL && stage.grid[pos_x + i][pos_y + j - 1].type == WALL
        && stage.grid[pos_x + i + 1][pos_y + j].type == WALL && stage.grid[pos_x + i][pos_y + j + 1].type == WALL) 
        MLV_draw_partial_image(image, 60 * 2, 60 * 2, NB_PIXEL, NB_PIXEL, i * NB_PIXEL, j * NB_PIXEL);  
    if (stage.grid[pos_x + i - 1][pos_y + j].type != WALL && stage.grid[pos_x + i][pos_y + j - 1].type != WALL
        && stage.grid[pos_x + i + 1][pos_y + j].type != WALL && stage.grid[pos_x + i][pos_y + j + 1].type != WALL) 
        MLV_draw_partial_image(image, 336 * 2, 0, NB_PIXEL, NB_PIXEL, i * NB_PIXEL, j * NB_PIXEL);          
}

void draw_wall_corner(Stage stage, int pos_x, int pos_y, int i, int j, MLV_Image *image){
    if (stage.grid[pos_x + i + 1][pos_y + j].type != WALL && stage.grid[pos_x + i][pos_y + j + 1].type != WALL
        && stage.grid[pos_x + i - 1][pos_y + j].type == WALL && stage.grid[pos_x + i][pos_y + j - 1].type == WALL)          
        MLV_draw_partial_image(image, 104 * 2, 192 * 2, NB_PIXEL, NB_PIXEL, i * NB_PIXEL, j * NB_PIXEL);          
    if (stage.grid[pos_x + i - 1][pos_y + j].type != WALL && stage.grid[pos_x + i][pos_y + j + 1].type != WALL
        && stage.grid[pos_x + i + 1][pos_y + j].type == WALL && stage.grid[pos_x + i][pos_y + j - 1].type == WALL)             
        MLV_draw_partial_image(image, 88 * 2, 192 * 2, NB_PIXEL, NB_PIXEL, i * NB_PIXEL, j * NB_PIXEL);
    if (stage.grid[pos_x + i + 1][pos_y + j].type != WALL && stage.grid[pos_x + i][pos_y + j - 1].type != WALL
        && stage.grid[pos_x + i - 1][pos_y + j].type == WALL && stage.grid[pos_x + i][pos_y + j + 1].type == WALL)    
        MLV_draw_partial_image(image, 104 * 2, 160 * 2, NB_PIXEL, NB_PIXEL, i * NB_PIXEL, j * NB_PIXEL);          
    if (stage.grid[pos_x + i - 1][pos_y + j].type != WALL && stage.grid[pos_x + i][pos_y + j - 1].type != WALL
        && stage.grid[pos_x + i + 1][pos_y + j].type == WALL && stage.grid[pos_x + i][pos_y + j + 1].type == WALL) 
        MLV_draw_partial_image(image, 88 * 2, 160 * 2, NB_PIXEL, NB_PIXEL, i * NB_PIXEL, j * NB_PIXEL);
    if (stage.grid[pos_x + i - 1][pos_y + j].type == WALL && stage.grid[pos_x + i][pos_y + j - 1].type != WALL
        && stage.grid[pos_x + i + 1][pos_y + j].type != WALL && stage.grid[pos_x + i][pos_y + j + 1].type != WALL) 
        MLV_draw_partial_image(image, 233 * 2, 341 * 2, NB_PIXEL, NB_PIXEL, i * NB_PIXEL, j * NB_PIXEL);
    if (stage.grid[pos_x + i - 1][pos_y + j].type != WALL && stage.grid[pos_x + i][pos_y + j - 1].type != WALL
        && stage.grid[pos_x + i + 1][pos_y + j].type == WALL && stage.grid[pos_x + i][pos_y + j + 1].type != WALL) 
        MLV_draw_partial_image(image, 153 * 2, 341 * 2, NB_PIXEL, NB_PIXEL, i * NB_PIXEL, j * NB_PIXEL);
    if (stage.grid[pos_x + i - 1][pos_y + j].type != WALL && stage.grid[pos_x + i][pos_y + j - 1].type == WALL
        && stage.grid[pos_x + i + 1][pos_y + j].type != WALL && stage.grid[pos_x + i][pos_y + j + 1].type != WALL) 
        MLV_draw_partial_image(image, 279 * 2, 288 * 2, NB_PIXEL, NB_PIXEL, i * NB_PIXEL, j * NB_PIXEL);
    if (stage.grid[pos_x + i - 1][pos_y + j].type != WALL && stage.grid[pos_x + i][pos_y + j - 1].type != WALL
        && stage.grid[pos_x + i + 1][pos_y + j].type != WALL && stage.grid[pos_x + i][pos_y + j + 1].type == WALL) 
        MLV_draw_partial_image(image, 279 * 2, 241 * 2, NB_PIXEL, NB_PIXEL, i * NB_PIXEL, j * NB_PIXEL);
    if (stage.grid[pos_x + i + 1][pos_y + j + 1].type != WALL && stage.grid[pos_x + i + 1][pos_y + j].type == WALL
        && stage.grid[pos_x + i][pos_y + j + 1].type == WALL)
        MLV_draw_partial_image(image, 67 * 2, 243 * 2, NB_PIXEL, NB_PIXEL, i * NB_PIXEL, j * NB_PIXEL);        
    if (stage.grid[pos_x + i - 1][pos_y + j + 1].type != WALL && stage.grid[pos_x + i - 1][pos_y + j].type == WALL
        && stage.grid[pos_x + i][pos_y + j + 1].type == WALL)
        MLV_draw_partial_image(image, 34 * 2, 243 * 2, NB_PIXEL, NB_PIXEL, i * NB_PIXEL, j * NB_PIXEL);   
    if (stage.grid[pos_x + i + 1][pos_y + j - 1].type != WALL && stage.grid[pos_x + i + 1][pos_y + j].type == WALL
        && stage.grid[pos_x + i][pos_y + j - 1].type == WALL)
        MLV_draw_partial_image(image, 67 * 2, 310 * 2, NB_PIXEL, NB_PIXEL, i * NB_PIXEL, j * NB_PIXEL);        
    if (stage.grid[pos_x + i - 1][pos_y + j - 1].type != WALL && stage.grid[pos_x + i - 1][pos_y + j].type == WALL
        && stage.grid[pos_x + i][pos_y + j - 1].type == WALL)
        MLV_draw_partial_image(image, 34 * 2, 310 * 2, NB_PIXEL, NB_PIXEL, i * NB_PIXEL, j * NB_PIXEL);
}

void draw_stage(Stage stage, MLV_Image **images, int pos_x, int pos_y){
    int i, j;
    Cell cell;
    MLV_Image *image;
    image = images[(stage.floor - 1) % 4];
    for (i = 0; i < NB_CELL_COL; i++){
        for (j = 0; j < NB_CELL_LIG; j++){
            cell = stage.grid[pos_x + i][pos_y + j];
            if (cell.type == ROOM || cell.type == TREASURE || cell.type == STAIR_UP || cell.type == STAIR_DOWN || cell.type == MONSTER)
                draw_room(i, j, image);         
            if (cell.type == STAIR_UP)
                draw_stair_up(i, j, image);
            if (cell.type == STAIR_DOWN)
                draw_stair_down(i, j, image);
            if (cell.type == TREASURE)
                draw_treasure(cell.entity.treasure, i, j, image); 
            if (cell.type == MONSTER)
                draw_monster(cell.entity.monster, i, j, images);
            if (cell.type == WALL){
                draw_wall_standard(stage, pos_x, pos_y, i, j, image); 
                draw_wall_corner(stage, pos_x, pos_y, i, j, image);      
         }
      }
   }
}

/* ------------------------------------------------------------------------------------------------------------------------------- */
/*                                                            Interface                                                            */
/* ------------------------------------------------------------------------------------------------------------------------------- */


void draw_equipment(Equipment equipment, MLV_Image *image, int pos_x, int pos_y){
    char text[20];
    sprintf(text, "%d", equipment.quality);
    if (equipment.type == ARMOR)
        MLV_draw_partial_image(image, 0, 249, 68, 68, pos_x, pos_y); 
    if (equipment.type == WEAPON)
        MLV_draw_partial_image(image, 71, 249, 68, 68, pos_x, pos_y); 
    if (equipment.type == WAND)
        MLV_draw_partial_image(image, 144, 249, 68, 68, pos_x, pos_y);   
    if (equipment.equip){
        MLV_draw_partial_image(image, 214, 247, 72, 72, pos_x - 2, pos_y - 2);
        MLV_draw_text(pos_x + 10, pos_y + 5, text, MLV_COLOR_YELLOW);  
    }
    else
        MLV_draw_text(pos_x + 10, pos_y + 5, text, MLV_COLOR_WHITE);  
}

void draw_potion(Potiontype type, MLV_Image *image, int pos_x, int pos_y){     
    if (type == HEAL)
        MLV_draw_partial_image(image, 216, 321, 68, 68, pos_x, pos_y ); 
    if (type == MAGIC)
        MLV_draw_partial_image(image, 0, 321, 68, 68, pos_x, pos_y); 
    if (type == REGENERATION)
        MLV_draw_partial_image(image, 144, 321, 68, 68, pos_x, pos_y);  
    if (type == ACCURACY)
        MLV_draw_partial_image(image, 288, 321, 68, 68, pos_x, pos_y); 
    if (type == LEARNING)
        MLV_draw_partial_image(image, 72, 321, 68, 68, pos_x, pos_y );    
}

void draw_select(MLV_Image *image, int i, int j){
    int pos_x = (NB_CELL_COL * NB_PIXEL / 2) - 316 / 2;
    int pos_y = (NB_CELL_LIG * NB_PIXEL / 2) - 244 / 2;  
    MLV_draw_partial_image(image, 286, 247, 72, 72, pos_x + 14 + (72 * (i % 4)), pos_y + 14 + 72 * j);   
}

void draw_inventory(Inventory * inventory, MLV_Image **images){
    int pos_x = (NB_CELL_COL * NB_PIXEL / 2) - 316 / 2;
    int pos_y = (NB_CELL_LIG * NB_PIXEL / 2) - 244 / 2;   
    MLV_draw_partial_image(images[7], 0, 0, 316, 243, pos_x, pos_y); 
    int i, j = -1;
    for (i = 0; i < NB_OBJECT; i++){
        if(i % 4 == 0)j++;
        if (inventory->grid[i].type == EQUIPMENT)
            draw_equipment(inventory->grid[i].entity.equipment, images[7], pos_x + 16 + (72 * (i % 4)), pos_y + 16 + 72 * j);         
        else if (inventory->grid[i].type == POTION)
            draw_potion(inventory->grid[i].entity.potion.type, images[7], pos_x + 16 + (72 * (i % 4)), pos_y + 16 + 72 * j); 
        if(i == inventory->select)
            draw_select(images[7], i, j);                               
    }
    MLV_draw_partial_image(images[7], 256, 389, 64, 64, pos_x + 332, pos_y + 244  - 80); 
    MLV_draw_partial_image(images[7], 256, 453, 64, 64, pos_x + 332, pos_y + 80 - 64);   
}

void draw_skill(Character character, MLV_Image *image){
    char text[20];
    int pos_x = (NB_CELL_COL * NB_PIXEL / 2) - 256 / 2;
    int pos_y = (NB_CELL_LIG * NB_PIXEL / 2) - 161 / 2;   
    MLV_draw_partial_image(image, 0, 389, 256, 161, pos_x, pos_y);
    sprintf(text, "Skill Point : %d", character.point);
    MLV_draw_text(pos_x + 16, pos_y + 161 - 32, text, MLV_COLOR_WHITE);    
}

void draw_map(Stage stage, Character character, int taille){
    int i, j;
    int dist = NB_PIXEL * NB_CELL_COL - STAGE_WIDTH * taille;
    for (i = 0; i < STAGE_WIDTH; i++){
        for (j = 0; j < STAGE_HEIGHT; j++){
            if (stage.grid[i][j].type == ROOM)
                MLV_draw_filled_rectangle(dist + i * taille,  j * taille, taille, taille, MLV_COLOR_BLACK);
            else if (stage.grid[i][j].type == STAIR_UP)
                MLV_draw_filled_rectangle(dist + i * taille, j * taille, taille, taille, MLV_COLOR_GREEN);        
            else if (stage.grid[i][j].type == STAIR_DOWN)
                MLV_draw_filled_rectangle(dist + i * taille, j * taille, taille, taille, MLV_COLOR_PURPLE);
            else if (stage.grid[i][j].type == TREASURE)
                MLV_draw_filled_rectangle(dist + i * taille, j * taille, taille, taille, MLV_COLOR_YELLOW); 
            else if (stage.grid[i][j].type == MONSTER)
                MLV_draw_filled_rectangle(dist + i * taille, j * taille, taille, taille, MLV_COLOR_RED);                               

        }
    }
    MLV_draw_filled_rectangle(dist + character.pos_x * taille, character.pos_y * taille, taille, taille, MLV_COLOR_BLUE); 
}

void draw_button(MLV_Image * image){
    MLV_draw_partial_image(image, 458, 314, 33, 33, 10, 64 * 6);  
    MLV_draw_partial_image(image, 316, 104, 64 * 3, 32, 64 * 2, WINDOW_HEIGHT - 32);  
    MLV_draw_partial_image(image, 316, 137, 64 * 3, 32, 64 * 2 + 64 * 3, WINDOW_HEIGHT - 32);  
    MLV_draw_partial_image(image, 316, 170, 64 * 3, 32, 64 * 2 + 64 * 3 * 2, WINDOW_HEIGHT - 32);  
}

void draw_stats(Character character, MLV_Image * image){
    char text[20];
    MLV_draw_partial_image(image, 316, 203, 32, 32, 10, WINDOW_HEIGHT/2 + 40);  
    MLV_draw_partial_image(image, 348, 203, 32, 32, 10, WINDOW_HEIGHT/2 - 10);  
    MLV_draw_partial_image(image, 380, 203, 32, 32, 10, WINDOW_HEIGHT/2 - 60);
    sprintf(text, "%d", character.stuff.weapon.quality + character.Atk);
    MLV_draw_text(40, WINDOW_HEIGHT/2 - 40, text, MLV_COLOR_YELLOW); 
    sprintf(text, "%d", character.stuff.wand.quality + character.Int);   
    MLV_draw_text(40, WINDOW_HEIGHT/2 + 10, text, MLV_COLOR_YELLOW); 
    sprintf(text, "%d", character.stuff.armor.quality + character.Def);      
    MLV_draw_text(40, WINDOW_HEIGHT/2 + 60, text, MLV_COLOR_YELLOW);    
}

void draw_effect(Effect effect, MLV_Image * image){
    char text[20];
    int dist = 0; 
    if (effect.regeneration.nb_round != 0){
        MLV_draw_partial_image(image, 412, 203, 32, 32, 115 + dist, 80);  
        sprintf(text, "%d", effect.regeneration.nb_round);
        MLV_draw_text(145 + dist, 100, text, MLV_COLOR_YELLOW); 
        dist += 60;
    }
    if (effect.accuracy.nb_round != 0){
        MLV_draw_partial_image(image, 444, 203, 32, 32, 115 + dist, 80);  
        sprintf(text, "%d", effect.accuracy.nb_round);   
        MLV_draw_text(145 + dist, 100, text, MLV_COLOR_YELLOW); 
        dist += 60;
    }
    if (effect.learning.nb_round != 0){
        MLV_draw_partial_image(image, 476, 203, 32, 32, 115 + dist, 80);
        sprintf(text, "%d", effect.learning.nb_round);      
        MLV_draw_text(145 + dist, 100, text, MLV_COLOR_YELLOW);  
        dist += 60;
    }
}

void draw_chest_menu(MLV_Image *image, Object object){
    MLV_draw_partial_image(image, 320, 389, 132, 118, 675, 230); 
    if (object.type == EQUIPMENT)
        draw_equipment(object.entity.equipment, image, 691, 264);         
    else if (object.type == POTION)
        draw_potion(object.entity.potion.type, image, 691, 264);        
}

void draw_interface(Character character, Dungeon dungeon, MLV_Image **images){
    int size;
    char text[20];
    Object object;
    MLV_draw_partial_image(images[7], 457, 280, 32, 32, WINDOW_WIDTH - 42, 10); 


    MLV_draw_partial_image(images[7], 362, 280, 96, 104, 10, 10); 

    sprintf(text, "Lv : %d", character.Lv);      
    MLV_draw_text(20, 89, text, MLV_COLOR_YELLOW);

    /* HP bar */     
    size = character.hp * (300.0 / character.hp_max);
    MLV_draw_partial_image(images[7], 316, 26, 316, 26, 106, 10);  
    MLV_draw_partial_image(images[7], 316, 0, 8 + size, 26, 106, 10); 
    sprintf(text, "%d / %d", character.hp, character.hp_max);   
    MLV_draw_text(106 + 158 - 30, 15, text, MLV_COLOR_WHITE);   

    /* MP bar */
    size = character.mp * (150.0 / character.mp_max);
    MLV_draw_partial_image(images[7], 316, 78, 166, 26, 106, 36);  
    MLV_draw_partial_image(images[7], 316, 52, 8 + size, 26, 106, 36); 
    sprintf(text, "%d / %d", character.mp, character.mp_max);   
    MLV_draw_text(106 + 83 - 20, 41, text, MLV_COLOR_WHITE);   
    /* Exp */
    size = character.Exp * (150.0 / (350 + 50 * character.Lv));
    MLV_draw_partial_image(images[7], 363, 260, 166, 14, 106, 62);  
    MLV_draw_partial_image(images[7], 363, 246, 8 + size, 14, 106, 62); 

    /* If inventory is open */ 
    if (character.inventory.state)
        draw_inventory(&character.inventory, images);

    /* If map is open */
    if (character.state_map)
        draw_map(dungeon.stage[dungeon.current_floor - 1], character, 6);

    /* If skill window is open */
    if (character.state_skill)      
        draw_skill(character, images[7]); 

    /* If a chest is open */
    if (is_open_chest(character, dungeon.stage[dungeon.current_floor - 1], &object)) {
        if (character.chest.state){
            draw_chest_menu(images[7], object);
            draw_inventory(&character.inventory, images);
        }
    }
    draw_button(images[7]);  
    draw_stats(character, images[7]);
    draw_effect(character.effect, images[7]);
}

void draw_gameover_screen(Character character, Dungeon dungeon, MLV_Image *image){
    char text[20];
    MLV_draw_image(image, 0, 0);
    if (character.job == TRAVELER) sprintf(text, "CLASS : %s", "TRAVELER");      
    if (character.job == WARRIOR) sprintf(text, "CLASS : %s", "WARRIOR");   
    if (character.job == MAGE) sprintf(text, "CLASS : %s", "MAGE");         
    MLV_draw_text(350, 155, text, MLV_COLOR_WHITE);    

    sprintf(text, "Level : %d", character.Lv);      
    MLV_draw_text(100, 205, text, MLV_COLOR_WHITE); 
    sprintf(text, "Hit Point : %d", character.hp_max);      
    MLV_draw_text(100, 255, text, MLV_COLOR_WHITE);   
    sprintf(text, "Mana Point : %d", character.mp_max);      
    MLV_draw_text(100, 305, text, MLV_COLOR_WHITE); 

    sprintf(text, "Attack : %d", character.Atk + character.stuff.weapon.quality);      
    MLV_draw_text(350, 205, text, MLV_COLOR_WHITE);     
    sprintf(text, "Defense : %d", character.Def + character.stuff.armor.quality);      
    MLV_draw_text(350, 255, text, MLV_COLOR_WHITE);
    sprintf(text, "Inteligence : %d", character.Int + character.stuff.wand.quality);      
    MLV_draw_text(350, 305, text, MLV_COLOR_WHITE); 

    sprintf(text, "Mob Kill : %d", character.nb_mob);      
    MLV_draw_text(600, 205, text, MLV_COLOR_WHITE);    
    sprintf(text, "Lowest Floor : %d", dungeon.nb_floor);      
    MLV_draw_text(600, 255, text, MLV_COLOR_WHITE); 
    sprintf(text, "Current Floor : %d", dungeon.current_floor);      
    MLV_draw_text(600, 305, text, MLV_COLOR_WHITE);        
}

void draw_menu_screen(MLV_Image *image){
    MLV_draw_image(image, 0, 0);        
}
void map_ascii(Stage stage, Character character){
    int i, j;
    printf("\n");
    for (j = 0; j < STAGE_HEIGHT; j++){
        for (i = 0; i < STAGE_WIDTH; i++){
         if (i == character.pos_x && j == character.pos_y) printf("P");   
         else if (stage.grid[i][j].type == ROOM) printf(" ");
         else if (stage.grid[i][j].type == STAIR_UP) printf("^");     
         else if (stage.grid[i][j].type == STAIR_DOWN) printf("v");     
         else if (stage.grid[i][j].type == TREASURE) printf("T");  
         else if (stage.grid[i][j].type == MONSTER) printf("M"); 
         else printf("#");                       
        }
      printf("\n");
   }
    printf("\nP = PLAYER | # = WALL | ^ = UP STAIR | v = DOWN STAIR | T = TREASURE | M = MONSTER\n");
}