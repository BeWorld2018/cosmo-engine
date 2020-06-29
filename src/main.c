//
// Created by efry on 21/07/2017.
//

#include <SDL.h>
#include "sound/audio.h"
#include "sound/music.h"
#include "game.h"
#include "map.h"
#include "dialog.h"
#include "video.h"
#include "status.h"
#include "config.h"
#include "high_scores.h"
#include "demo.h"
#include "b800.h"
#include "input.h"

int cleanup_and_exit();

#ifdef __MORPHOS__
unsigned long __stack = 100000;
static const char *version __attribute__((used)) = "$VER: Cosmo Engine (29.06.2020) port by BeWorld";
#endif

int main(int argc, char *argv[]) {
    if ( SDL_Init(SDL_INIT_VIDEO  | SDL_INIT_GAMECONTROLLER) < 0 ) {
        printf("argh!!");
    }

    load_config_from_command_line(argc, argv);

    video_init();
	controller_init();
    audio_init();
    game_init();

    video_fill_screen_with_black();

    if(!is_quick_start())
    {
        a_game_by_dialog();
        game_play_mode = main_menu();
    }
    else
    {
        set_initial_game_state();
        game_play_mode = PLAY_GAME;
    }

    while(game_play_mode != QUIT_GAME)
    {
        load_level(current_level);

        if(game_play_mode == PLAY_DEMO)
        {
            load_demo();
        }

        game_loop();
        stop_music();
        if(game_play_mode == PLAY_GAME)
        {
            show_high_scores();
        }
        game_play_mode = main_menu();
    }

    stop_music();
    display_exit_text();

    return cleanup_and_exit();
}

int cleanup_and_exit()
{
    write_config_file();
    config_cleanup();
	controller_shutdown();
    video_shutdown();
    audio_shutdown();
    SDL_Quit();

    return 0;
}
