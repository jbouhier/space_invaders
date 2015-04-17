//
//  initialisation.c
//  space_invaders
//
//  Created by Gatien MOUAFO on 27/03/15.
//  Copyright (c) 2015 ETNA. All rights reserved.
//


#include "main_file.h"

SDL_Window* init(SDL_Window *gWindow)
{
    
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
    
    //RGBA colors
    SDL_Colour text_color = { 255, 255, 255 };
    
    game.Gplayer.bullet = malloc(sizeof(S_Bullet) * 100);
    game.Gplayer.position = init_position(760, 560, 35, 35);
    game.Gmonster.position = init_position(360, 60, 55, 55);
    
    //Text positioning test
    game.textPosition = init_position(250, 30, 30, 300);
    
    game.Gwindow = init(game.Gwindow);
    game.Grenderer = SDL_CreateRenderer( game.Gwindow, -1, SDL_RENDERER_ACCELERATED );
    game.font = TTF_OpenFont("/Users/synxs/etna/c/space_invaders/space_invaders/space_invaders/fonts/04B_03__.TTF", FONT_SIZE);
    game.sText = TTF_RenderText_Solid(game.font, "SPACE    INVADERS", text_color);
    game.tText = SDL_CreateTextureFromSurface(game.Grenderer, game.sText);

    //Initialize SDL_mixer
    if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
    {
        printf( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );
    }

    // Load sounds effects to the Game
    game = loadSounds( game );

    //Get window surface
    screenSurface = SDL_GetWindowSurface( game.Gwindow );
    game.Gscreen = SDL_CreateTextureFromSurface(game.Grenderer, screenSurface);
    
    
    return game;
}


void end(S_Game game)
{
    int i;
    //Deallocate textures
    SDL_DestroyTexture(game.Gmonster.monster);
    SDL_DestroyTexture(game.Gplayer.player);
    SDL_DestroyTexture(game.Gscreen);
    
    for (i = 0; game.Gplayer.bullet[i].bullet != NULL; i++) {
        SDL_DestroyTexture(game.Gplayer.bullet[i].bullet);
    }
    
    TTF_CloseFont(game.font);
    TTF_Quit();
    
    SDL_RenderClear( game.Grenderer );

    //Destroy window
    SDL_DestroyWindow( game.Gwindow );
    game.Gwindow = NULL;
    
    //Quit SDL subsystems
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

void    renderAll(S_Game game)
{
    int i;
    
    SDL_RenderClear( game.Grenderer );
    SDL_RenderCopy( game.Grenderer, game.Gscreen, NULL, NULL );
    SDL_RenderCopy( game.Grenderer, game.Gplayer.player, NULL, &(game.Gplayer.position) );
    SDL_RenderCopy( game.Grenderer, game.Gmonster.monster, NULL, &(game.Gmonster.position) );
    SDL_RenderCopy( game.Grenderer, game.tText, NULL, &(game.textPosition) );
    
    for (i = 0; game.Gplayer.bullet[i].bullet != NULL; i++) {
        SDL_RenderCopy( game.Grenderer, game.Gplayer.bullet[i].bullet, NULL, &(game.Gplayer.bullet[i].position) );
    }
    
    SDL_RenderPresent( game.Grenderer );
    SDL_UpdateWindowSurface( game.Gwindow );
}
