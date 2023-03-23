/* Auteur: PEREZ LEFEUVRE Vincent - QUACH Kevin
 * Date de création: 21-11-2021
 * Date de modification: 13-01-2022 */

#ifndef __MONSTER__
#define __MONSTER__

typedef struct {
    int hp_max;
    int hp;
    int Atk;
}Monster;

/* Initiate a monster with hp and atk stats given as parameter */
Monster generate_monster(int Hp, int Atk);

/* Return 1 if the monster given as parameter is dead, else return 0 */
int monster_is_dead(Monster monster);

#endif