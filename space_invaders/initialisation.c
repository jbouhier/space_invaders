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


S_Game init_screen(S_Game game)
{
    SDL_Surface *screenSurface;

    game.Gplayer.bullet = malloc(sizeof(S_Bullet) * 50);
    game.Gmonster = malloc((sizeof(S_Monster) * MONSTER_NBR) + 1);
    game.Gplayer.position = init_position(60, 560, 35, 35);
    game.Gplayer.bullet = malloc(sizeof(S_Bullet) * 100);
    game.Gplayer.position = init_position(760, 560, 35, 35);
    game.Gmonster->position = init_position(360, 60, 55, 55);
    game.Gwindow = init(game.Gwindow);
    game.Grenderer = SDL_CreateRenderer( game.Gwindow, -1, SDL_RENDERER_ACCELERATED );
    
    //Initialize SDL_mixer
    if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
        printf( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );

    game.Gplayer.player = loadPlayer(game);
    game = loadMonsters( game );
    // Load sounds effects to the Game
    game = loadSounds( game );

    //Get window surface
    screenSurface = SDL_GetWindowSurface( game.Gwindow );
    game.Gscreen = SDL_CreateTextureFromSurface(game.Grenderer, screenSurface);
    
    SDL_FreeSurface(screenSurface);

    return game;
}


S_Game  init_text(S_Game game)
{
    //RGBA colors
    SDL_Colour text_color = { 255, 255, 255 };
    
    // Text size and position  -  (x,    y,  h,   w)
    game.score_title_pos = init_position(220, 10, 22, 345);
    game.high_score_pos = init_position(355, 35, 22, 80);
    
    
    // Attribute position values at player creation !
    // game.Gplayer.score_pos = init_position(240, 10, 22, 40);
    // game.Gplayer.position = init_position(400, 10, 22, 40);
    
    
    game.font = TTF_OpenFont("/../../../fonts/uni05_53.ttf", FONT_SIZE);
    
    // Score title
    game.surface_score_title = TTF_RenderText_Solid(game.font, "S C O R E < 1 >        H I - S C O R E        S C O R E < 2 >", text_color);
    game.texture_score_title = SDL_CreateTextureFromSurface(game.Grenderer, game.surface_score_title);
    
    // Hi-Score
    game.surface_high_score = TTF_RenderText_Solid(game.font, "0000", text_color); // Change "0000" with the correct variable
    game.texture_high_score = SDL_CreateTextureFromSurface(game.Grenderer, game.surface_high_score);

    // Player score
    game.Gplayer.surface_score = TTF_RenderText_Solid(game.font, "0000", text_color); // Change "0000" with the correct variable

    game.Gplayer.texture_score = SDL_CreateTextureFromSurface(game.Grenderer, game.Gplayer.surface_score);
    
    // Player lives
    game.Gplayer.surface_lives = TTF_RenderText_Solid(game.font, "0000", text_color); // Change "0000" with the correct variable
    game.Gplayer.texture_lives = SDL_CreateTextureFromSurface(game.Grenderer, game.Gplayer.surface_lives);

    
    // Next, look inside renderAll function !
    // Next, look inside renderAll function !
    // Next, look inside renderAll function !

    return (game);
}


S_Game  init_player(S_Game game)
{
    game.Gplayer.score = 0;
    game.Gplayer.lives = 3;
    
    return game;
}


void end(S_Game game)
{
    int i;
    //Deallocate textures
    for (i = 0; game.Gmonster[i].monster != NULL; i++) {
        SDL_DestroyTexture(game.Gmonster[i].monster);
        game.Gmonster[i].monster = NULL;
    }
    free(game.Gmonster);

    for (i = 0; game.Gplayer.bullet[i].bullet != NULL; i++) {
        SDL_DestroyTexture(game.Gplayer.bullet[i].bullet);
        game.Gplayer.bullet[i].bullet = NULL;
    }
    free(game.Gplayer.bullet);
    SDL_DestroyTexture(game.Gplayer.player);
    SDL_DestroyTexture(game.Gscreen);

    game.Gplayer.player =NULL;
    game.Gscreen = NULL;
    
    TTF_CloseFont(game.font);
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

SDL_Rect init_bulletPos(S_Player player)
{
    SDL_Rect DestR;

    DestR.y =  player.position.y - 10;
    DestR.x =  player.position.x + 12;
    DestR.w = 10;
    DestR.h = 25;

    return DestR;
}

SDL_Rect init_bulletMonsterPos(S_Monster monster) {
    SDL_Rect DestR;
    
    DestR.y =  monster.position.y + 4;
    DestR.x =  monster.position.x + 8;
    DestR.w = 4;
    DestR.h = 30;

    return DestR;
}


void    renderAll(S_Game game)
{
    int i;
    int x;
    int y;

    x = 10;
    y = 10;
    SDL_RenderClear( game.Grenderer );
    SDL_RenderCopy( game.Grenderer, game.Gscreen, NULL, NULL );
    SDL_RenderCopy( game.Grenderer, game.Gplayer.player, NULL, &(game.Gplayer.position) );
    
    // Text
    SDL_RenderCopy( game.Grenderer, game.texture_score_title, NULL, &(game.score_title_pos) );
    SDL_RenderCopy( game.Grenderer, game.texture_high_score, NULL, &(game.high_score_pos) );
    
    for (i = 0; game.Gmonster[i].monster != NULL; i++) {
        SDL_RenderCopy( game.Grenderer, game.Gmonster[i].monster, NULL, &(game.Gmonster[i].position) );
        if (game.Gmonster[i].explosion != NULL) {
            SDL_RenderCopy( game.Grenderer, game.Gmonster[i].explosion, NULL, &(game.Gmonster[i].position) );
        }
        if (game.Gmonster[i].bullet.bullet != NULL) {
            SDL_RenderCopy( game.Grenderer, game.Gmonster[i].bullet.bullet, NULL, &(game.Gmonster[i].bullet.position) );
        }
    }

    for (i = 0; game.Gplayer.bullet[i].bullet != NULL; i++) {
        SDL_RenderCopy( game.Grenderer, game.Gplayer.bullet[i].bullet, NULL, &(game.Gplayer.bullet[i].position) );
    }

    for (i = 0; game.Gplayer.bullet[i].bullet != NULL; i++)
        SDL_RenderCopy( game.Grenderer, game.Gplayer.bullet[i].bullet, NULL, &(game.Gplayer.bullet[i].position) );

    SDL_RenderPresent( game.Grenderer );
    SDL_UpdateWindowSurface( game.Gwindow );
}