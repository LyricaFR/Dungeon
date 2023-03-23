/* Auteur: PEREZ LEFEUVRE Vincent - QUACH Kevin
 * Date de création: 21-11-2021
 * Date de modification: 03-01-2022 */

#include "../include/Monster.h"

Monster generate_monster(int hp, int Atk){
    Monster monster;
    monster.hp_max = hp;
    monster.hp = hp;
    monster.Atk = Atk;
    return monster;
}

int monster_is_dead(Monster monster){
    if (monster.hp <= 0)
       return 1;
    return 0;
}