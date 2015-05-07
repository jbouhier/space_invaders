//
//  initialisation.c
//  space_invaders
//
//  Created by Gatien MOUAFO on 27/03/15.
//  Copyright (c) 2015 ETNA. All rights reserved.
//


#include "main_file.h"

SDL_Window* init(SDL_Window *gWindow) {
    if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER | SDL_INIT_EVENTS) != 0)
    {
        fprintf(stderr, "Erreur d'initialisation de la SDL : %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }
    
    if(TTF_Init() != 0)
    {
        fprintf(stderr, "Error of text initialization of SDL : %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }
    
    gWindow = SDL_CreateWindow("Space Invaders",
                               SDL_WINDOWPOS_CENTERED,
                               SDL_WINDOWPOS_CENTERED,
                               SCREEN_WIDTH, SCREEN_HEIGHT,
                               SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);

    if ( gWindow == NULL )
    {
        fprintf(stderr,  "Impossible de créer la fenêtre! Erreur SDL: %s\n", SDL_GetError() );
        SDL_Quit();
        exit(EXIT_FAILURE);
    }

    return gWindow;
}


t_game init_screen(t_game game)
{
    SDL_Surface *screenSurface;

    game.Gmonster = malloc((sizeof(t_monster) * MONSTER_NBR) + 1);
    game.Gmonster->position = init_position(360, 60, 55, 55);
    game.Gwindow = init(game.Gwindow);
    game.Grenderer = SDL_CreateRenderer( game.Gwindow, -1, SDL_RENDERER_ACCELERATED );

    //Initialize SDL_mixer
    if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
        printf( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );

    game.Gplayer1.player = loadPlayer(game);
    game = loadMonsters( game );
    // Load sounds effects to the Game
    game = loadSounds( game );

    //Get window surface
    screenSurface = SDL_GetWindowSurface( game.Gwindow );
    game.Gscreen = SDL_CreateTextureFromSurface(game.Grenderer, screenSurface);
    
    SDL_FreeSurface(screenSurface);
    
    game = init_player(game);
    game = init_text(game);

    return game;
}


t_game  init_text(t_game game)
{
    game.infos.font = TTF_OpenFont("/../../../fonts/uni05_53.ttf", FONT_SIZE);
    SDL_Colour text_color = { 255, 255, 255 };
    
    // Engine text size and position -  (x,    y,  h,   w)
    game.infos.score_title_pos = init_position(200, 5, 25, 420);
    game.infos.high_score_pos = init_position(355, 40, 25, 80);
    game.Gplayer1.score_pos = init_position(200, 40, 25, 80);
    game.Gplayer2.score_pos = init_position(480, 40, 25, 80);
    
    // Score title
    game.infos.surface_score_title = TTF_RenderText_Solid(game.infos.font, "S C O R E < 1 >        H I - S C O R E        S C O R E < 2 >", text_color);
    game.infos.texture_score_title = SDL_CreateTextureFromSurface(game.Grenderer, game.infos.surface_score_title);
    
    // Hi-Score
    game.infos.surface_high_score = TTF_RenderText_Solid(game.infos.font, "0000", text_color); // Change "0000" with the correct variable
    game.infos.texture_high_score = SDL_CreateTextureFromSurface(game.Grenderer, game.infos.surface_high_score);

    // Player1 - Change "0000" with the correct variable !!!!!!!
    game.Gplayer1.surface_score = TTF_RenderText_Solid(game.infos.font, "0000", text_color);
    game.Gplayer1.texture_score = SDL_CreateTextureFromSurface(game.Grenderer, game.Gplayer1.surface_score);
    game.Gplayer1.surface_lives = TTF_RenderText_Solid(game.infos.font, "0000", text_color);
    game.Gplayer1.texture_lives = SDL_CreateTextureFromSurface(game.Grenderer, game.Gplayer1.surface_lives);

    
    // Player2 - Change "0000" with the correct variable !!!!!!!!!
    game.Gplayer2.surface_score = TTF_RenderText_Solid(game.infos.font, "0000", text_color);
    game.Gplayer2.texture_score = SDL_CreateTextureFromSurface(game.Grenderer, game.Gplayer2.surface_score);
    game.Gplayer2.surface_lives = TTF_RenderText_Solid(game.infos.font, "0000", text_color);
    game.Gplayer2.texture_lives = SDL_CreateTextureFromSurface(game.Grenderer, game.Gplayer2.surface_lives);
    
    // Next, look inside renderAll function !!!
    // Next, look inside renderAll function !!!
    // Next, look inside renderAll function !!!

    return (game);
}


t_game  init_player(t_game game)
{
    game.Gplayer1.position = init_position(SCREEN_WIDTH / 2, SCREEN_HEIGHT - 100, 35, 35);
    game.Gplayer1.bullet = malloc(sizeof(t_bullet) * 50);

    game.Gplayer1.nbr_bullet = 0;
    game.Gplayer1.score = 0;
    game.Gplayer1.lives = 3;

    game.Gplayer2.nbr_bullet = 0;
    game.Gplayer2.score = 0;
    game.Gplayer2.lives = 3;
    
    return game;
}


void end(t_game game)
{
    int i;
    //Deallocate textures
    for (i = 0; game.Gmonster[i].monster != NULL; i++) {
        SDL_DestroyTexture(game.Gmonster[i].monster);
        game.Gmonster[i].monster = NULL;
    }
    free(game.Gmonster);

    for (i = 0; game.Gplayer1.bullet[i].bullet != NULL; i++) {
        SDL_DestroyTexture(game.Gplayer1.bullet[i].bullet);
        game.Gplayer1.bullet[i].bullet = NULL;
    }
    free(game.Gplayer1.bullet);
    SDL_DestroyTexture(game.Gplayer1.player);
    SDL_DestroyTexture(game.Gscreen);

    game.Gplayer1.player =NULL;
    game.Gscreen = NULL;
    
    TTF_CloseFont(game.infos.font);
    TTF_Quit();
    
    SDL_RenderClear( game.Grenderer );

    SDL_DestroyRenderer( game.Grenderer );
    game.Grenderer = NULL;
    //Destroy window
    SDL_DestroyWindow( game.Gwindow );
    game.Gwindow = NULL;

    //Quit SDL subsystems
    IMG_Quit();
    SDL_Quit();
}

SDL_Rect init_position(int x, int y, int h, int w)
{
    SDL_Rect DestR;

    DestR.x = x;
    DestR.y = y;
    DestR.h = h;
    DestR.w = w;
    
    return DestR;
}

SDL_Rect init_bulletPos(t_player player)
{
    SDL_Rect DestR;

    DestR.y =  player.position.y - 10;
    DestR.x =  player.position.x + 12;
    DestR.w = 10;
    DestR.h = 25;

    return DestR;
}

SDL_Rect init_bulletMonsterPos(t_monster monster) {
    SDL_Rect DestR;
    
    DestR.y =  monster.position.y + 4;
    DestR.x =  monster.position.x + 8;
    DestR.w = 4;
    DestR.h = 30;

    return DestR;
}


void    renderAll(t_game game)
{
    int i;
    int x;
    int y;

    x = 10;
    y = 10;
    SDL_RenderClear( game.Grenderer );
    SDL_RenderCopy( game.Grenderer, game.Gscreen, NULL, NULL );
    SDL_RenderCopy( game.Grenderer, game.Gplayer1.player, NULL, &(game.Gplayer1.position) );
    
    // Text
    SDL_RenderCopy( game.Grenderer, game.infos.texture_score_title, NULL, &(game.infos.score_title_pos) );
    SDL_RenderCopy( game.Grenderer, game.infos.texture_high_score, NULL, &(game.infos.high_score_pos) );
    
    for (i = 0; game.Gmonster[i].monster != NULL; i++) {
        SDL_RenderCopy( game.Grenderer, game.Gmonster[i].monster, NULL, &(game.Gmonster[i].position) );
        if (game.Gmonster[i].explosion != NULL) {
            SDL_RenderCopy( game.Grenderer, game.Gmonster[i].explosion, NULL, &(game.Gmonster[i].position) );
        }
        if (game.Gmonster[i].bullet.bullet != NULL) {
            SDL_RenderCopy( game.Grenderer, game.Gmonster[i].bullet.bullet, NULL, &(game.Gmonster[i].bullet.position) );
        }
    }

    for (i = 0; game.Gplayer1.bullet[i].bullet != NULL; i++) {
        SDL_RenderCopy( game.Grenderer, game.Gplayer1.bullet[i].bullet, NULL, &(game.Gplayer1.bullet[i].position) );
    }

    for (i = 0; game.Gplayer1.bullet[i].bullet != NULL; i++)
        SDL_RenderCopy( game.Grenderer, game.Gplayer1.bullet[i].bullet, NULL, &(game.Gplayer1.bullet[i].position) );

    SDL_RenderPresent( game.Grenderer );
    SDL_UpdateWindowSurface( game.Gwindow );
}

/*
**  Fonction qui affiche l'interface du GameOver lorsque le Joueur se fait tuer
**
*/
t_game    showEnd(t_game game)
{
    return game;
}

/*
**  Fonction qui affiche l'interface du jeux et le permet de jouer.
**
*/
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
    return game;
}
