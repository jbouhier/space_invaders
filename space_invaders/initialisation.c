//
//  initialisation.c
//  space_invaders
//
//  Created by Gatien MOUAFO on 27/03/15.
//  Copyright (c) 2015 ETNA. All rights reserved.
//

/*
 #    /$$$$$$   /$$$$$$  /$$   /$$  /$$$$$$  /$$$$$$$$  /$$$$$$  /$$   /$$ /$$$$$$$$  /$$$$$$
 #   /$$__  $$ /$$__  $$| $$$ | $$ /$$__  $$|__  $$__/ /$$__  $$| $$$ | $$|__  $$__/ /$$__  $$
 #  | $$  \__/| $$  \ $$| $$$$| $$| $$  \__/   | $$   | $$  \ $$| $$$$| $$   | $$   | $$  \__/
 #  | $$      | $$  | $$| $$ $$ $$|  $$$$$$    | $$   | $$$$$$$$| $$ $$ $$   | $$   |  $$$$$$
 #  | $$      | $$  | $$| $$  $$$$ \____  $$   | $$   | $$__  $$| $$  $$$$   | $$    \____  $$
 #  | $$    $$| $$  | $$| $$\  $$$ /$$  \ $$   | $$   | $$  | $$| $$\  $$$   | $$    /$$  \ $$
 #  |  $$$$$$/|  $$$$$$/| $$ \  $$|  $$$$$$/   | $$   | $$  | $$| $$ \  $$   | $$   |  $$$$$$/
 #   \______/  \______/ |__/  \__/ \______/    |__/   |__/  |__/|__/  \__/   |__/    \______/
 #
 */
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;



#include "main_file.h"

SDL_Window* init(SDL_Window *gWindow) {
    
    if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER | SDL_INIT_EVENTS) != 0)
    {
        fprintf(stderr, "Erreur d'initialisation de la SDL : %s\n", SDL_GetError());
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


SDL_Texture* init_screen(S_Game game) {
    SDL_Texture* screenTexture;
    SDL_Surface *screenSurface;
    
    //Get window surface
    screenSurface = SDL_GetWindowSurface( game.Gwindow );
    screenTexture = SDL_CreateTextureFromSurface(game.Grenderer, screenSurface);
    
    
    return screenTexture;
}


void end(S_Game game)
{
    //Deallocate surface
    
    //Destroy window
    SDL_DestroyWindow( game.Gwindow );
    game.Gwindow = NULL;
    
    //Quit SDL subsystems
    SDL_Quit();
}

SDL_Rect init_position(int x, int y, int h, int w) {
    SDL_Rect DestR;
    
    DestR.x = x;
    DestR.y = y;
    DestR.h = h;
    DestR.w = w;
    
    return DestR;
}

SDL_Rect init_bulletPos(S_Player player) {
    SDL_Rect DestR;
    
    DestR.y =  player.position.y - 10;
    DestR.x =  player.position.x + 12;
    DestR.w = 10;
    DestR.h = 25;
    
    return DestR;
}

void    renderAll(S_Game game) {
    int i;
    
    SDL_RenderClear( game.Grenderer );
    SDL_RenderCopy( game.Grenderer, game.Gscreen, NULL, NULL );
    SDL_RenderCopy( game.Grenderer, game.Gplayer.player, NULL, &(game.Gplayer.position) );
    
    for (i = 0; game.Gplayer.bullet[i].bullet != NULL; i++) {
        SDL_RenderCopy( game.Grenderer, game.Gplayer.bullet[i].bullet, NULL, &(game.Gplayer.bullet[i].position) );
    }
    
    SDL_RenderPresent( game.Grenderer );
    SDL_UpdateWindowSurface( game.Gwindow );
}
