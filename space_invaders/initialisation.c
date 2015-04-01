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


SDL_Texture* init_screen(SDL_Window *gWindow, SDL_Renderer* gRenderer, SDL_Surface* screenSurface) {
    SDL_Texture* screenSurface2;
    //Get window surface
    screenSurface = SDL_GetWindowSurface( gWindow );
    
    screenSurface2 = SDL_CreateTextureFromSurface(gRenderer, screenSurface);
    
    
    return screenSurface2;
}


void end(SDL_Window *gWindow, SDL_Surface *gScreenSurface, SDL_Surface *gMonster)
{
    //Deallocate surface
    SDL_FreeSurface( gMonster );
    SDL_FreeSurface( gScreenSurface );
    gMonster = NULL;
    gScreenSurface = NULL;
    
    //Destroy window
    SDL_DestroyWindow( gWindow );
    gWindow = NULL;
    
    //Quit SDL subsystems
    SDL_Quit();
}

