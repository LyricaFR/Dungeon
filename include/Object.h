/* Auteur: PEREZ LEFEUVRE Vincent - QUACH Kevin
 * Date de création: 21-11-2021
 * Date de modification: 13-01-2022 */

#ifndef __OBJECT__
#define __OBJECT__
 
#include <stdio.h>
#include <stdlib.h>  
#include <MLV/MLV_all.h>

#define NB_POTION 5
#define NB_EQUIPMENT 3

#define HEAL_PERCENT 10 /* % de vie en plus */
#define MAGIC_PERCENT 10 /* % de magie en plus */

typedef enum {ARMOR, WEAPON, WAND} Equipmenttype;
typedef enum {HEAL, MAGIC, REGENERATION, ACCURACY, LEARNING} Potiontype;
typedef enum {EQUIPMENT, POTION, EMPTY} Objecttype;

typedef struct {
    Potiontype type;
    int nb_round;
} Potion;             

typedef struct {
    int quality;
    Equipmenttype type;
    int equip;
} Equipment; 

typedef union entityobject {
    Potion potion;
    Equipment equipment;
}Objectentity;

typedef struct {
    Objecttype type;
    Objectentity entity;
} Object;

typedef struct {
    Equipment armor;
    Equipment weapon;
    Equipment wand;
}Stuff;

typedef struct {
    Potion regeneration;
    Potion accuracy;
    Potion learning;
}Effect;

/* Create and returns a potion of type type given in the parameter */
Potion generate_potion(Potiontype type);

/* Create a piece of equiment of type and quality given as parameter and return it */
Equipment generate_equipment(int quality, Equipmenttype type);

/* Generate a random object and returns it. If the object is an equipment, its quality can go from 0 to nb_floor */
Object generate_object(int nb_floor);

/* Restores either health or mana based on a percentage given as parameter */
void restaure_potion(int * val, int val_max, int percent);

/* Initiate a Stuff struct with no equipment equipped and returns it */
Stuff init_stuff();

/* Automatically equip an equipment if it is of higher quality than the one equipped */
void equip(Stuff * stuff, Equipment * equipment);

/* Initiate an Effect struct */
Effect init_effect();    
    
void round_potion(Effect * effect, Potion potion, int nb_round);

/* Count down the number of turn of a potion that has effect over time */ 
void round_count_down(Potion *potion);

/* Turn effect of a regeneration potion, restore both health and mana by a fixed amount */
void regeneration_potion(int * hp, int * mp, int hp_max, int mp_max);

/* Turn effect of an accuracy potion, increase critical hit rate by a fixed amount */
void accuracy_potion(int * critical_hit); 

/* Turn effect of a learning potion, increase Exp gain by 30% */
void learning_potion(float * coef_exp);
    
#endif