/* Auteur: PEREZ LEFEUVRE Vincent - QUACH Kevin
 * Date de création: 21-11-2021
 * Date de modification: 07-01-2022 */

#include "../include/Object.h"

Potion generate_potion(Potiontype type){
    Potion potion;
    potion.type = type;
    potion.nb_round = 0;
    return potion;
}

Equipment generate_equipment(int quality, Equipmenttype type){
    Equipment equipment;
    equipment.quality = quality;
    equipment.type = type;
    equipment.equip = 0;
    return equipment;
}

Object generate_object(int nb_floor){
    Object object;
    int random = rand() % 3;
    if (random == 0 ||random == 1){
        object.type = POTION;
        object.entity.potion = generate_potion(rand() % NB_POTION);
    }
    else{
        object.type = EQUIPMENT;
        object.entity.equipment = generate_equipment((rand() % nb_floor) + 1, rand() % NB_EQUIPMENT);
    }
    return object;
}

/* Restaure une jauge (health or mana) en fonction d'un pourcentage mis en parametre */
void restaure_potion(int * val, int val_max, int percent){
    int rest = (percent * val_max) / 100;
    if (val_max - (*val) < rest)
        (*val) = val_max;
    else
        (*val) += rest;    
}

Stuff init_stuff(){
    Stuff stuff;
    stuff.armor.type = EMPTY;
    stuff.armor.quality = 0;
    stuff.weapon.type = EMPTY;
    stuff.weapon.quality = 0;   
    stuff.wand.type = EMPTY;   
    stuff.wand.quality = 0;    
    return stuff;     
}

void equip(Stuff * stuff, Equipment * equipment){
    if (equipment->type == ARMOR && equipment->quality > stuff->armor.quality){
        stuff->armor = (*equipment);
        equipment->equip = 1; 
    }
    else if (equipment->type == WEAPON && equipment->quality > stuff->weapon.quality){
        stuff->weapon = (*equipment);
        equipment->equip = 1; 
    }
    else if (equipment->type == WAND && equipment->quality > stuff->wand.quality){
        stuff->wand = (*equipment);        
        equipment->equip = 1; 
    }
}

Effect init_effect(){
    Effect effect;
    effect.regeneration.type = EMPTY;
    effect.regeneration.nb_round = 0;
    effect.accuracy.type = EMPTY;
    effect.accuracy.nb_round = 0;
    effect.learning.type = EMPTY;  
    effect.learning.nb_round = 0;    
    return effect;     
}

void round_potion(Effect * effect, Potion potion, int nb_round){
    potion.nb_round = nb_round;
    if (potion.type == REGENERATION)
        effect->regeneration = potion;
    else if (potion.type == ACCURACY)
        effect->accuracy = potion;
    else if (potion.type == LEARNING)
        effect->learning = potion;               
}

/* Decompte les tour pour une potion qui a une duration */
void round_count_down(Potion *potion){
    if (potion->nb_round != 0)
        potion->nb_round--;
    else{     
        potion->type = EMPTY;
    }
}

/* Regenere Vie et Mana */
void regeneration_potion(int * hp, int * mp, int hp_max, int mp_max){
    if (hp_max - (*hp) < 20) (*hp) = hp_max;
    else (*hp) += 20;    
    if (mp_max - (*mp) < 10) (*mp) = mp_max;
    else (*mp) += 10;
} 

/* Meilleur taux de coup critique */
void accuracy_potion(int * critical_hit){
    (*critical_hit) = 15;
} 

/* 2x plus d'experience */
void learning_potion(float * coef_exp){
    (*coef_exp) = 1.3;
} 