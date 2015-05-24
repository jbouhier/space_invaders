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
        fprintf(stderr, "Erreur d'initialisation de la SDL : %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    if (TTF_Init() != 0) {
        fprintf(stderr, "Error of text initialization of SDL : %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    if ( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
        fprintf(stderr, "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );

    gWindow = SDL_CreateWindow("Space Invaders", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
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
    game.Grenderer = SDL_CreateRenderer( game.Gwindow, -1, SDL_RENDERER_ACCELERATED );

    game.Gplayer1.player = loadPlayer(game);
    game = loadMonsters(game);
    game = loadSounds(game);

    screenSurface = SDL_GetWindowSurface( game.Gwindow );
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

    return game;
}

t_game  init_text(t_game game)
{
    game.text.font = TTF_OpenFont("/../../../fonts/uni05_53.ttf", FONT_SIZE);
    
    // Engine text size and position -  (x,    y,  h,   w)
    game.text.pos_stitle = init_position(180, 5, 25, 460);
    game.text.pos_hscore = init_position(365, 32, 25, 80);
    game.Gplayer1.score_pos = init_position(200, 32, 25, 80);
    game.Gplayer2.score_pos = init_position(540, 32, 25, 80);
    game.Gplayer1.lives_pos = init_position(20, 570, 25, 25);
    game.Gplayer2.lives_pos = init_position(760, 570, 25, 25);
    
    render_title(&(game.text), game.Grenderer);
    render_hscore(&(game.text), game.Grenderer);
    render_score(&(game.Gplayer1), game.text, game.Grenderer);
    render_lives(&(game.Gplayer1), game.text, game.Grenderer);
    render_score(&(game.Gplayer2), game.text, game.Grenderer);
    render_lives(&(game.Gplayer2), game.text, game.Grenderer);
    
    return (game);
}


t_game  init_player(t_game game)
{
    game.Gplayer1.position = init_position(SCREEN_WIDTH / 2, SCREEN_HEIGHT - 100, 35, 35);

    game.Gplayer1.nbr_bullet = 0;
    game.Gplayer1.score = 0;
    game.Gplayer1.lives = 3;

    game.Gplayer2.nbr_bullet = 0;
    game.Gplayer2.score = 0;
    game.Gplayer2.lives = 3;
    
    return (game);
}


void end(t_game game)
{
    freeBegin(game);
    freeMonster(game);
    freePlayer(game.Gplayer1);
    freePlayer(game.Gplayer2);
    freeInfos(game);

    SDL_DestroyTexture(game.Gscreen);
    SDL_DestroyRenderer( game.Grenderer );
    SDL_DestroyWindow( game.Gwindow );
    game.Grenderer = NULL;
    game.Gscreen = NULL;
    game.Gwindow = NULL;
    
    IMG_Quit();
    Mix_Quit();
    TTF_Quit();
    SDL_Quit();
}

SDL_Rect init_position(int x, int y, int h, int w)
{
    SDL_Rect DestR;

    DestR.x = x;
    DestR.y = y;
    DestR.h = h;
    DestR.w = w;
    
    return (DestR);
}

SDL_Rect init_bulletPos(t_player player)
{
    SDL_Rect DestR;

    DestR.y =  player.position.y - 10;
    DestR.x =  player.position.x + 12;
    DestR.w = 10;
    DestR.h = 25;

    return (DestR);
}

SDL_Rect init_bulletMonsterPos(t_monster monster) {
    SDL_Rect DestR;
    
    DestR.y =  monster.position.y + 4;
    DestR.x =  monster.position.x + 8;
    DestR.w = 4;
    DestR.h = 30;

    return (DestR);
}


// Show Game Over screen when all players are dead
t_game    showEnd(t_game game)
{
    int write_error;
    
    write_error = -1;
    write_error = write_score(game, game.Gplayer1);

    printf("GAME OVER\n");
    
    return (game);
}


// Display game interface to be able to play
t_game    showGame(t_game game, int tempsActuel, int tempsPrecedent)
{
    if (game.Gevenements.type == SDL_KEYDOWN) {
        game.Gplayer1 = movePlayer(game);
        if(game.Gevenements.key.keysym.sym == SDLK_SPACE && game.Gplayer1.nbr_bullet < 2) {
            Mix_PlayChannel( -1, game.Gplayer1.bulletGo_sound, 0 );
            game.Gplayer1.bullet[game.Gplayer1.nbr_bullet].bullet = loadBullet(game);
            game.Gplayer1.bullet[game.Gplayer1.nbr_bullet].position = init_bulletPos(game.Gplayer1);
            game.Gplayer1.nbr_bullet++;
        }
    }
    if (tempsActuel - tempsPrecedent > 15) { /* Si 15 ms se sont écoulées depuis le dernier tour de boucle */
        game = launch_bullet(game);
        game = launch_bulletMonster(game);
        game = moveMonster(game);
    }

    renderAll(game);
    return (game);
}