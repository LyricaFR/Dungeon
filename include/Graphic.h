/* Auteur: QUACH Kevin, PEREZ LEFEUVRE Vincent
   Date de création: 21-11-2021
   Date de modification: 13-01-2022
*/

/* Module that will handle the graphic display of the game */

#ifndef __GRAPHIC__
#define __GRAPHIC__

#define NB_PIXEL 64
#define WINDOW_WIDTH NB_CELL_COL * NB_PIXEL
#define WINDOW_HEIGHT NB_CELL_LIG * NB_PIXEL
#define NB_IMAGES 10

#include "Character.h"

/* Allocate a MLV_Image table where all the images used in the game will be stored, return that table */
MLV_Image **load_all_images();

/* Free the memory used for the image table images given as parameter */
void free_all_images(MLV_Image **images);

/* Draw the user interface on when in game , also manage what window to display depending on if it should be open or not */
void draw_interface(Character character, Dungeon dungeon, MLV_Image **images);

/* Draw the inventory window with all the item in it */
void draw_inventory(Inventory * inventory, MLV_Image **images);

/* Draw the character depending on the direction it is facing */
void draw_character(Character character, MLV_Image **images);

/* Draw a room type cell at the coordinates pos_x, pos_y */
void draw_room(int pos_x, int pos_y, MLV_Image *image);

/* Draw a chest at the coordinates pos_x, pos_y */
void draw_treasure(Treasure treasure, int pos_x, int pos_y, MLV_Image *image);

/* Draw stairs going up at the coordinates pos_x, pos_y */
void draw_stair_up(int pos_x, int pos_y, MLV_Image *image);

/* Draw stairs going down at the coordinates pos_x, pos_y */
void draw_stair_down(int pos_x, int pos_y, MLV_Image *image);

/* Function that will draw the stage given to it */
void draw_stage(Stage stage, MLV_Image **images, int pos_x, int pos_y);

/* Draw a map of the stage */
void draw_map(Stage stage, Character character, int taille);

/* Draw the skill upgrade window */
void draw_skill(Character character, MLV_Image *image) ;

MLV_Animation_player * draw_character_animation(Character character, MLV_Image **images); 

/* Draw the game over screen displaying game info */
void draw_gameover_screen(Character character, Dungeon dungeon, MLV_Image *image);

/* Draw the menu screen */
void draw_menu_screen(MLV_Image *image);

/* Draw the chest menu */
void draw_chest_menu(MLV_Image *image, Object object);

void map_ascii(Stage stage, Character character);

#endif