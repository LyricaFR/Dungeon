/* Auteur: PEREZ LEFEUVRE Vincent - QUACH Kevin
 * Date de création: 21-11-2021
 * Date de modification: 07-01-2022 */

#include "../include/Stage.h"

Cell generate_cell(Celltype type, int pos_x, int pos_y){
    Cell c;
    c.type = type;
    c.pos_x = pos_x;
    c.pos_y = pos_y;
    return c;
}

Stage generate_initial_stage(int floor){
    int i, j;
    Stage stage;
    for (i = 0; i < STAGE_WIDTH; i++){
        for (j = 0; j < STAGE_HEIGHT; j++)
            stage.grid[i][j] = generate_cell(WALL, i, j);
    }
    stage.grid[STAGE_WIDTH / 2][STAGE_HEIGHT / 2] = 
    generate_cell(STAIR_UP, STAGE_WIDTH / 2, STAGE_HEIGHT / 2);
    stage.floor = floor;
    return stage;
}
 
Cell * generate_adjacent(Stage stage, int pos_x, int pos_y){
    Cell * adjacent = (Cell*)malloc(sizeof(Cell) * 4);
    if (adjacent == NULL){
        fprintf(stderr, "%s\n", "adjacent is null");
        return NULL;
    }
    adjacent[0] = stage.grid[pos_x + 1][pos_y];
    adjacent[1] = stage.grid[pos_x][pos_y + 1];    
    adjacent[2] = stage.grid[pos_x - 1][pos_y];
    adjacent[3] = stage.grid[pos_x][pos_y - 1];  
    return adjacent; 
}

Cell * alea_cell(Cell * toexpand, Cell * cell, int *size){
    int i, random, indice;
    Cell * toexpand2;
    if ((*size) <=  0)
        return NULL;
    toexpand2 = (Cell*)malloc(sizeof(Cell) * ((*size) - 1));
    if (toexpand2 == NULL){
        fprintf(stderr, "%s\n", "toexpand2 is null");
        return NULL;
    }
    random = rand() % (*size);
    indice = 0;
    for (i = 0; i < (*size); i++){
        if (i != random){
            toexpand2[indice] = toexpand[i];
            indice++;
        }
    }
    (*cell) = toexpand[random];
    (*size)--;
    free(toexpand);
    return toexpand2;
}

int is_allowable(Stage stage, Cell cell){
    int i, j, cmpt_1 = 0, cmpt_2 = 0;
    if (cell.type != WALL)
        return 0;
    for(i = cell.pos_x - 2; i < cell.pos_x + 3; i++){
        for(j = cell.pos_y - 2; j < cell.pos_y + 3; j++){
            if (manhattan_distance(cell.pos_x, cell.pos_y, i, j) == 1 && (stage.grid[i][j].type == ROOM || stage.grid[i][j].type == STAIR_UP))
                cmpt_1++;
            if (manhattan_distance(cell.pos_x, cell.pos_y, i, j) == 2 && (stage.grid[i][j].type == ROOM || stage.grid[i][j].type == STAIR_UP))
                cmpt_2++;           
        }
    }   
    if (cmpt_1 == 1 && cmpt_2 <= 2)
        return 1;
    return 0;
}

int is_not_at_edge(Cell cell){
    if (cell.pos_x < 1 || cell.pos_x > STAGE_WIDTH - 2)
        return 0;
    if (cell.pos_y < 1 || cell.pos_y > STAGE_HEIGHT - 2)
        return 0;  
    return 1;
}

Cell * add_toexpand(Cell * toexpand, Cell cell, int * size){
    int i;
    Cell * toexpand2 = (Cell*)malloc(sizeof(Cell) * ((*size) + 1));
    if(toexpand2 == NULL){
        fprintf(stderr, "%s\n", "toexpand2 is null");
        return NULL;
    }
    for (i = 0; i < (*size); i++){
        toexpand2[i] = toexpand[i];
    }
    toexpand2[i] = cell;
    (*size)++;
    free(toexpand);
    return toexpand2;
}

void three_cell_wall(Stage *stage){
    int i, j, cmpt, indice = 0;
    Cell tmp[STAGE_WIDTH * STAGE_HEIGHT];
    for (i = 1; i < STAGE_WIDTH - 1; i++){
        for (j = 1; j < STAGE_HEIGHT - 1; j++){
            if (stage->grid[i][j].type == ROOM){
                cmpt = 0;
                if (stage->grid[i + 1][j].type == WALL)
                    cmpt++;
                if (stage->grid[i - 1][j].type == WALL)
                    cmpt++;
                if (stage->grid[i][j + 1].type == WALL)
                    cmpt++;
                if (stage->grid[i][j - 1].type == WALL) 
                    cmpt++;  
                if (cmpt == 3){
                    tmp[indice] = stage->grid[i][j];  
                    indice++;                                   
                }
            }
        }
    }
    for (i = 0; i < indice; i++)
        stage->grid[tmp[i].pos_x][tmp[i].pos_y].type = WALL;
}

int generate_maze(Stage * stage){
    int pos_x = STAGE_WIDTH / 2;
    int pos_y = STAGE_HEIGHT / 2;
    int i, size = 4;
    Cell c;
    Cell *c_adjacent, *toexpand;

    /* 1. Initialisation de toexpand */
    toexpand = generate_adjacent(*stage, pos_x, pos_y);
    do {
        do {
            /* 2. Case aleatoire c */
            toexpand = alea_cell(toexpand, &c, &size);

        /* 3. Si ce n'est pas admissible on retourne a 2 */
        } while(!is_allowable(*stage, c) && toexpand != NULL);
        if (is_allowable(*stage, c)){
            /* Convertir c en room */
            (*stage).grid[c.pos_x][c.pos_y].type = ROOM;

            /* 4. case adjacentes a c */
            c_adjacent = generate_adjacent(*stage, c.pos_x, c.pos_y);

            for (i = 0; i < 4; i++){
                if (is_allowable(*stage, c_adjacent[i]) && is_not_at_edge(c_adjacent[i]))
                    toexpand = add_toexpand(toexpand, c_adjacent[i], &size);
            }
            free(c_adjacent);
        }

    /* 5. si toexpand est pas vide on retourne a 2 */
    }while(size != 0);

    /* 6. case de salle adjacentes a trois cases de mur */
    three_cell_wall(stage);
    free(toexpand);
    return 0;
}

void room_to_treasure(Stage * stage, int pos_x, int pos_y, int x, int y){
    stage->grid[pos_x + x][pos_y + y].type = TREASURE;
    stage->grid[pos_x + x][pos_y + y].entity.treasure = generate_treasure(stage->floor, pos_x + x, pos_y + y);
}

void room_to_monster(Stage * stage, int pos_x, int pos_y){
    stage->grid[pos_x][pos_y].type = MONSTER;
    stage->grid[pos_x][pos_y].entity.monster = generate_monster(((stage->floor + 1) / 2) * 30, ((stage->floor + 1) / 2) * 20);
}

void start_treasure(Stage * stage){
    int pos_x = STAGE_WIDTH / 2;
    int pos_y = STAGE_HEIGHT / 2;
    if (stage->grid[pos_x + 1][pos_y].type == ROOM)
        room_to_treasure(stage, pos_x, pos_y, 1, 0);
    else if (stage->grid[pos_x - 1][pos_y].type == ROOM)
        room_to_treasure(stage, pos_x, pos_y, -1, 0);
    else if (stage->grid[pos_x][pos_y + 1].type == ROOM)
        room_to_treasure(stage, pos_x, pos_y, 0, 1);
    else if (stage->grid[pos_x][pos_y - 1].type == ROOM)
        room_to_treasure(stage, pos_x, pos_y, 0, -1);    
}

void add_all_entity(Stage * stage){
    int i, j, k, cmpt;
    Cell *adjacent, tmp;
    if (stage->floor == 1)
        start_treasure(stage);
    for (i = 0; i < STAGE_WIDTH ; i++){
        for (j = 0; j < STAGE_HEIGHT; j++){
            if (stage->grid[i][j].type == ROOM){
                cmpt = 0;
                adjacent = generate_adjacent(*stage, i,  j);
                for (k = 0; k < 4; k++){
                    if (adjacent[k].type == WALL) cmpt++;
                    if (adjacent[k].type == ROOM) tmp = adjacent[k];
                }
                if (cmpt == 3){
                    room_to_treasure(stage, i, j, 0, 0); 
                    room_to_monster(stage, tmp.pos_x, tmp.pos_y);
                }

            }
        }
    }
}

void generate_stair_down(Stage * stage){
    int pos_x = STAGE_WIDTH / 2;
    int pos_y = STAGE_HEIGHT / 2;    
    int i, j, random, index = 0;
    Cell tmp[STAGE_WIDTH * STAGE_HEIGHT];
    for(i = 0; i < STAGE_WIDTH; i++){
        for(j = 0; j < STAGE_HEIGHT; j++){
            if (stage->grid[i][j].type == ROOM){
                if (manhattan_distance(pos_x, pos_y, i, j) >= 25){
                    tmp[index] = generate_cell(STAIR_DOWN, i, j);
                    index++; 
                }
            }      
        }
    }
    random = rand() % index;
    stage->grid[tmp[random].pos_x][tmp[random].pos_y] = tmp[random];  
}

Dungeon generate_dungeon(){
    Dungeon dungeon;
    dungeon.nb_floor = 1;
    dungeon.current_floor = 1;
    dungeon.stage = (Stage*)malloc(sizeof(Stage) * dungeon.nb_floor);
    if (dungeon.stage == NULL){
        fprintf(stderr, "%s\n", "stage is null");
        return dungeon;
    }
    /* first floor */
    dungeon.stage[0] = generate_initial_stage(1);    
    generate_maze(&dungeon.stage[0]);
    add_all_entity(&dungeon.stage[0]);
    generate_stair_down(&dungeon.stage[0]);
    return dungeon;
}

void add_floor(Dungeon * dungeon){
    dungeon->nb_floor++;
    dungeon->stage = (Stage*)realloc(dungeon->stage, sizeof(Stage) * dungeon->nb_floor);
    if (dungeon->stage == NULL){
        fprintf(stderr, "%s\n", "stage is null");
        return;
    }
    dungeon->stage[dungeon->nb_floor - 1] = generate_initial_stage(dungeon->nb_floor);
    generate_maze(&dungeon->stage[dungeon->nb_floor - 1]);
    add_all_entity(&dungeon->stage[dungeon->nb_floor - 1]);
    generate_stair_down(&dungeon->stage[dungeon->nb_floor - 1]);    
}