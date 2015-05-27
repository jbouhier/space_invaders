//
//  initialisation.c
//  space_invaders
//
//  Created by Gatien MOUAFO on 27/03/15.
//  Copyright (c) 2015 ETNA. All rights reserved.
//

#include "prototypes.h"


SDL_Window  *init(SDL_Window *gWindow)
{
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER | SDL_INIT_EVENTS) != 0) {
        fprintf(stderr, "Erreur d'initialisation de la SDL : %s\n",
                SDL_GetError());
        exit(EXIT_FAILURE);
    }
    
    if (TTF_Init() != 0) {
        fprintf(stderr, "Error of text initialization of SDL : %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    if (Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0)
        fprintf(stderr, "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );

    gWindow = SDL_CreateWindow("Space Invaders", SDL_WINDOWPOS_CENTERED,
                               SDL_WINDOWPOS_CENTERED,
                               SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

    if (gWindow == NULL) {
        fprintf(stderr, "Impossible de créer la fenêtre! Erreur SDL: %s\n", SDL_GetError() );
        SDL_Quit();
        exit(EXIT_FAILURE);
    }
    
    return (gWindow);
}


t_game init_screen(t_game game)
{
    SDL_Surface *screenSurface;

    game = init_game(game);
    game.Gwindow = init(game.Gwindow);
    game.Grenderer = SDL_CreateRenderer(game.Gwindow, -1,
                                        SDL_RENDERER_ACCELERATED);

    game.Gplayer1.player = loadPlayer(game);
    game = loadMonsters(game);
    game = loadSounds(game);

    screenSurface = SDL_GetWindowSurface(game.Gwindow);
    game.Gscreen = SDL_CreateTextureFromSurface(game.Grenderer, screenSurface);

    SDL_FreeSurface(screenSurface);

    game = init_player(game);
    game.text.hscore_str = score_str(game.text.hscore, game.text.hscore_str);
    game = init_text(game);

    return (game);
}


t_game init_game(t_game game)
{
    game.begin.high_score = NULL;
    game.begin.logo = NULL;
    game.begin.play_with_1 = NULL;
    game.begin.play_with_2 = NULL;
    game.begin.quit = NULL;
    game.begin.selected_option = NULL;
    game.begin.surface_play = NULL;
    game.Grenderer = NULL;
    game.Gscreen = NULL;
    game.Gwindow = NULL;
    game.text.font = NULL;
    game.text.sur_stitle = NULL;
    game.text.sur_hscore = NULL;
    game.text.tex_hscore = NULL;
    game.text.tex_stitle = NULL;
    game.monster_speed = 1;
    game.text.color.r = 255;
    game.text.color.g = 255;
    game.text.color.b = 255;
    game.text.color.a = 0;
    game = init_monster_player(game);
    set_hscore(&game, get_hscore(hscore_path()));

    return (game);
}


t_game init_monster_player(t_game game)
{
    int i;

    game.Gplayer1.bullet = malloc(sizeof(t_bullet) * 10);
    game.Gplayer2.bullet = malloc(sizeof(t_bullet) * 10);
    game.Gmonster = malloc((sizeof(t_monster) * MONSTER_NBR) + 1);
    game.Gplayer1.player = NULL;
    game.Gplayer1.bulletGo_sound = NULL;
    game.Gplayer1.playerExplode_sound = NULL;
    game.Gplayer2.player = NULL;
    game.Gplayer2.bulletGo_sound = NULL;
    game.Gplayer2.playerExplode_sound = NULL;
    for (i = 0; i < 10; i++) {
        game.Gplayer1.bullet[i].bullet = NULL;
        game.Gplayer2.bullet[i].bullet = NULL;
    }
    for (i = 0; i < MONSTER_NBR; i++) {
        game.Gmonster[i].bullet.bullet = NULL;
        game.Gmonster[i].explosion = NULL;
        game.Gmonster[i].monster = NULL;
        game.Gmonster[i].monsterExplode_sound = NULL;
        game.Gmonster[i].monsterMove_sound = NULL;
        game.Gmonster[i].nbr_bullet = 0;
    }

    return (game);
}


t_game  init_text(t_game game)
{
    game.text.font = TTF_OpenFont("/../../../fonts/uni05_53.ttf", FONT_SIZE);
    
    // Engine text size and position -  (x,    y,  h,   w)
    game.text.pos_stitle = init_position(180, 5, 25, 460);
    game.text.pos_hscore = init_position(365, 32, 25, 80);
    game.text.game_over = init_position(365, 32, 25, 80);
    game.Gplayer1.score_pos = init_position(200, 32, 25, 80);
    game.Gplayer2.score_pos = init_position(SCREEN_WIDTH - 260, 32, 25, 80);
    game.Gplayer1.lives_pos = init_position(20, SCREEN_HEIGHT - 30, 25, 25);
    game.Gplayer2.lives_pos = init_position( SCREEN_WIDTH - 20, SCREEN_HEIGHT - 30, 25, 25);
    
    render_title(&(game.text), game.Grenderer);
    render_hscore(&(game.text), game.Grenderer);
    render_score(&(game.Gplayer1), game.text, game.Grenderer);
    render_lives(&(game.Gplayer1), game.text, game.Grenderer);
    render_score(&(game.Gplayer2), game.text, game.Grenderer);
    render_lives(&(game.Gplayer2), game.text, game.Grenderer);
    
    return (game);
}