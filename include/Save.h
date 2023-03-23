/* Auteur: PEREZ LEFEUVRE Vincent - QUACH Kevin
 * Date de création: 01-01-2022
 * Date de modification: 13-01-2022 */

#ifndef __SAVE__
#define __SAVE__

#include "Character.h"

/* Save the current state of the game in a bin file "save.bin". Returns 1 if successful, 0 if not. */
int save(Dungeon dungeon, Character character);

/* Load the save file "save.bin". Returns 1 if successful, 0 if not */
int load(Dungeon * dungeon, Character * character);

#endif