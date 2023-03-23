/* Auteur: PEREZ LEFEUVRE Vincent - QUACH Kevin
 * Date de création: 21-11-2021
 * Date de modification: 13-01-2022 */

#ifndef __CHARACTER__
#define __CHARACTER__

#include "Inventory.h"
#include "Stage.h"
#define NB_CELL_COL 13
#define NB_CELL_LIG 9

typedef enum {
    NORTH,
    SOUTH,
    EAST,
    WEST
} Direction;

typedef struct {
    int pos_x, pos_y;
}Camera;

typedef enum {
    TRAVELER,
    WARRIOR,
    MAGE
} Job;

typedef struct {
    int hp_max, mp_max;
    int hp, mp, Atk, Int, Def, Exp, Lv;
    int critical_hit, point;
    float coef_exp;
    Direction direction;
    int pos_x, pos_y;
    int state_map; /* 0 = close, 1 = open */
    int state_skill; /* 0 = close, 1 = open */
    int nb_mob;
    Camera camera;
    Inventory inventory;
    Stuff stuff;
    Effect effect;
    Chest chest;
    Job job;
} Character;

/* Initialise le character */
Character create_character(Job job);

/* Affiche l'écran de sélection de classe et retourne la classe choisis */
Job class_select();

/* Deplace le character et sa camera */
void move(Character * character, int x, int y);

/* Ouvre le coffre, place les items dans l'invetaire et enleve le coffre */
void open_treasure(Character * character, Stage * stage, int x, int y);

/* Descend d'un etage le donjon */
void go_down(Dungeon * dungeon, Character * character);

/* Monte d'un etage le donjon */
void go_up(Dungeon * dungeon, Character * character);

/* Lance une attaque */
int attack(Character * character, int atk, int accuracy);

/* Execute les attaques du joueur et des monste */
void fight(Character *character, Stage * stage, MLV_Keyboard_button touche, int clic_x, int clic_y);

/* Execute les interractions du personnage sur le dongeon et ses entités */
void interaction(Character *character, Dungeon * dungeon, Direction direction, MLV_Keyboard_button touche, int x, int y, int clic_x, int clic_y);

void move_interaction(Character * character, Dungeon * dungeon, MLV_Keyboard_button touche, int clic_x, int clic_y);

/* Permet de faire interargir le personnage dans le stage */
void character_interaction(Character * character, Dungeon * dungeon, MLV_Keyboard_button touche, int clic_x, int clic_y, int map);

/* Monte le niveau du joueur si il a assez d'experience */
void level_up(Character * character);

/* Verifie si le character est en vie */
int is_dead(Character character);

/* Retoune l'index du coffre ouvert */
int is_open_chest(Character character, Stage stage, Object * object);

#endif