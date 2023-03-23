/* Auteur: PEREZ LEFEUVRE Vincent - QUACH Kevin
 * Date de création: 21-11-2021
 * Date de modification: */

#include "../include/Graphic.h"
#include "../include/Save.h"
#include <getopt.h>

int main(int argc, char* argv[]){
    int floor, clic_x, clic_y, game = 1, menu = 1, exit = 0, map = 0;
    Dungeon dungeon;
    Character character;
    MLV_Image **images;
    MLV_Keyboard_button touche;
    MLV_init_audio();
    MLV_Music* bgm = MLV_load_music("Assets/Apocalypse_BGM_DOVA_SYNDROME.mp3");
    srand(time(NULL));
    char opt;
    static struct option long_options[] = {
        {"help", 0, NULL, 'h'},
        {"map", 0, NULL, 'm'}
    };

    /* Options */
    while((opt = getopt_long(argc, argv, "hm", long_options, NULL)) != -1){
        switch (opt){
            case 'h':
                printf("./dungeon : pour lancer le programme\n");
                printf("./dungeon -m ou --map : pour lancer le programme avec une map sur le terminal\n et avoir accès à la carte graphique (touche m)\n");
                printf("./dungeon -h ou --help : pour la liste des commandes\n");
                return 0;
            case 'm':
                map = 1;
                break;
        }
    }

    MLV_create_window("Dungeon", "Dungeon", WINDOW_WIDTH, WINDOW_HEIGHT);
    images = load_all_images();
    while (game){
        /* Menu Screen */
        while (menu){
            draw_menu_screen(images[6]);
            MLV_update_window();

            MLV_wait_keyboard_or_mouse(&touche, NULL, NULL, &clic_x, &clic_y);
            /* Exit */
            if (clic_x > 321 && clic_x < 510 && clic_y > 423 && clic_y < 453){
                game = 0;
                menu = 0;   
                exit = 1;   
            }
            /* New Game */
            if (clic_x > 321 && clic_x < 510 && clic_y > 347 && clic_y < 377){
                character = create_character(class_select(images[9]));
                dungeon = generate_dungeon();
                menu = 0;   
                MLV_play_music(bgm, 1.0, -1); /* 3e paramètre négatif pour que la musique joue loop à l'infin tant qu'on la stop pas */
            }
            /* Play */  
            if (clic_x > 321 && clic_x < 510 && clic_y > 271 && clic_y < 301){
                if (load(&dungeon, &character) == 0){
                    dungeon = generate_dungeon();
                    character = create_character(class_select(images[9]));
                }
                MLV_play_music(bgm, 1.0, -1); /* 3e paramètre négatif pour que la musique joue loop à l'infin tant qu'on la stop pas */
                menu = 0;       
            }                               
        }
        /* Game */
        while(!is_dead(character) && game){
            floor = dungeon.current_floor - 1;
            MLV_clear_window(MLV_COLOR_BLACK);
            draw_stage(dungeon.stage[floor], images, character.camera.pos_x, character.camera.pos_y);
            draw_character(character, images);
            draw_interface(character, dungeon, images); 
            if (map) map_ascii(dungeon.stage[floor], character);    
            MLV_update_window();
            MLV_wait_keyboard_or_mouse(&touche, NULL, NULL, &clic_x, &clic_y);
            MLV_draw_partial_image(images[7], 457, 280, 32, 32, WINDOW_WIDTH - 42, 10); 
            if (clic_x > WINDOW_WIDTH - 42 && clic_x < WINDOW_WIDTH - 10 && clic_y > 10 && clic_y < 42){
                save(dungeon, character);           
                game = 0;
            }

            character_interaction(&character, &dungeon, touche, clic_x, clic_y, map);
            touche = MLV_KEYBOARD_NONE;
            clic_x = -1;
            clic_y = -1;
        }
        /* Game Over Screen */
        if (game){
            draw_gameover_screen(character, dungeon, images[4]);
            MLV_stop_music();
            MLV_update_window();    
            MLV_wait_keyboard_or_mouse(&touche, NULL, NULL, &clic_x, &clic_y);
            if (clic_x > 321 && clic_x < 510 && clic_y > 458 && clic_y < 488) 
                game = 0;

            if (clic_x > 321 && clic_x < 510 && clic_y > 394 && clic_y < 424){
                menu = 1;
                clic_x = -1;
                clic_y = -1;            
            }
        }
    }
    MLV_free_music(bgm);
    if (!exit)
        free(dungeon.stage);
    free_all_images(images);
    MLV_free_window();
    return 0;
}