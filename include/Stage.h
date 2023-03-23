/* Auteur: PEREZ LEFEUVRE Vincent - QUACH Kevin
 * Date de création: 21-11-2021
 * Date de modification: 13-01-2022 */

#ifndef __STAGE__
#define __STAGE__

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <MLV/MLV_all.h>
#include "Treasure.h"
#include "Monster.h"

#define STAGE_WIDTH 63   
#define STAGE_HEIGHT 43
#define manhattan_distance(x1, y1, x2, y2) ((x1 > x2) ? (x1 - x2) : (x2 - x1)) + ((y1 > y2) ? (y1 - y2) : (y2 - y1))

typedef enum {
    WALL,
    ROOM, 
    MONSTER,
    TREASURE, 
    STAIR_UP, 
    STAIR_DOWN
} Celltype;

typedef union entity {
    Monster monster;
    Treasure treasure;
} Entity;

typedef struct {
    int pos_x;
    int pos_y;
    Celltype type;
    Entity entity;
} Cell;

/* Struct that represent the stage */
typedef struct {
    int floor;
    Cell grid[STAGE_WIDTH][STAGE_HEIGHT];
} Stage;

typedef struct {
    int nb_floor;
    int current_floor;
    Stage * stage;
}Dungeon;

/* Function that generate a cell of type given in the parameter */
Cell generate_cell(Celltype type, int pos_x, int pos_y);

/* Function that will generate a stage completely made of walls */
Stage generate_initial_stage(int floor);
     
/* Returns a table of the adjacent cells of the one at pos_x, pos_y */
Cell * generate_adjacent(Stage stage, int pos_x, int pos_y);

/* Choose randomly a cell and returns the table toexpand without this cell */
Cell * alea_cell(Cell * toexpand, Cell * cell, int *size);

/* Returns 1 if the cell can be a room */
int is_allowable(Stage stage, Cell cell);

/* Returns 1 if the cell is on the edge of the stage, if not, returns 0 */
int is_not_at_edge(Cell cell);

/* Add to the table toexpand the cell given in the parameter */
Cell * add_toexpand(Cell * toexpand, Cell cell, int * size);

/* Change in wall room with three adjacent wall */
void three_cell_wall(Stage *stage);

int generate_maze(Stage * stage);

/* Change a room into a treasure */
void room_to_treasure(Stage * stage, int pos_x, int pos_y, int x, int y);

/* Generate the starting treasure */
void start_treasure(Stage * stage);

/* Change a room into a monster */
void room_to_monster(Stage * stage, int pos_x, int pos_y);

/* Add all entity (monster and treasure) on the stage */
void add_all_entity(Stage * stage);

/* Generate the down stair on a floor */
void generate_stair_down(Stage * stage);

/* Function that generate a dungeon with 1 floor */
Dungeon generate_dungeon();

/* Add to the dungeon a floor */
void add_floor(Dungeon * dungeon);

#endif