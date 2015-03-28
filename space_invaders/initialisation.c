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

bool init(SDL_Window *gWindow, SDL_Surface *gScreenSurface) {
    //Initialize PNG loading
    int imgFlags = IMG_INIT_PNG;
    
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
    
    if( !( IMG_Init( imgFlags ) & imgFlags ) )
    {
        printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
    }
    
    //Get window surface
    gScreenSurface = SDL_GetWindowSurface( gWindow );
    
    //Fill the surface black (color corresponding to the last 3 parameters : 0,0,0 for black & 255,255,255 for white)
    SDL_FillRect( gScreenSurface, NULL, SDL_MapRGB( gScreenSurface->format, 255, 255, 255 ) );

    
    //Wait two seconds
    //SDL_Delay( 5000 );
    if (gScreenSurface != NULL ) {
        // Use absolute path to get image.
        loadSurface( "/Users/mouafo/bitbucket/space_invaders/space_invaders/space-ship-md.png", gWindow, gScreenSurface );
    }
    
    //Update the surface
    SDL_UpdateWindowSurface( gWindow );
    return true;
    
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

