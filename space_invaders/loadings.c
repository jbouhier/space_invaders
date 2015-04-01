//
//  loadings.c
//  space_invaders
//
//  Created by Gatien MOUAFO on 27/03/15.
//  Copyright (c) 2015 ETNA. All rights reserved.
//

#include "main_file.h"
#define SHAPE_SIZE 160

SDL_Surface *loadSurface( char* path, SDL_Window *gWindow, SDL_Surface *gScreenSurface )
{
    SDL_Rect DestR;
    SDL_Surface *optimizedSurface = NULL;
    SDL_Surface *loadedSurface;
    
    loadedSurface = IMG_Load( path );
    // -630 la position de droite max
    DestR.x = -300;
    DestR.y = -300;
    if( loadedSurface == NULL )
    {
        printf( "Unable to load image %s! SDL_image Error: %s\n", path, IMG_GetError() );
        exit(EXIT_FAILURE);
    }
    else
    {
        //Convert surface to screen format
        optimizedSurface = SDL_ConvertSurface( loadedSurface, gScreenSurface->format, 0 );

        if( optimizedSurface == NULL )
        {
            printf( "Unable to optimize image %s! SDL Error: %s\n", path, SDL_GetError() );
            exit(EXIT_FAILURE);
        }
        
        SDL_BlitSurface( optimizedSurface, &DestR, gScreenSurface, NULL );
        SDL_FreeSurface( loadedSurface );
    }
    
    return optimizedSurface;
}

SDL_Texture *loadTexture( char* path, SDL_Window *gWindow, SDL_Renderer* gRenderer)
{
    SDL_Texture* newTexture = NULL;
    //Load image at specified path
    SDL_Surface* loadedSurface = IMG_Load( path );
    
    if( loadedSurface == NULL )
    {
        printf( "Unable to load image %s! SDL_image Error: %s\n", path, IMG_GetError() );
    }
    else
    {
        //Create texture from surface pixels
        
        newTexture = SDL_CreateTextureFromSurface( gRenderer, loadedSurface );
        if( newTexture == NULL )
        {
            printf( "Unable to create texture from %s! SDL Error: %s\n", path, SDL_GetError() );
        }
        
        //Get rid of old loaded surface
        SDL_FreeSurface( loadedSurface );
    }
    
    return newTexture;
}

SDL_Texture *loadPlayer(SDL_Event evenements, SDL_Window *gWindow, SDL_Renderer* gRenderer)
{
    //Loading success flag
    bool success = true;
    SDL_Texture* player;
    
    //Load PNG texture
    player = loadTexture( "/Users/mouafo/bitbucket/space_invaders/space_invaders/space-ship-md.png", gWindow, gRenderer);
    if( player == NULL )
    {
        printf( "Failed to load texture image!\n" );
        success = false;
    }
    
    return player;
}

SDL_Rect movePlayer(SDL_Event evenements, SDL_Rect DestR) {
    switch( evenements.key.keysym.sym )
    {
        case SDLK_LEFT:
            if ( DestR.x > 0 ) {
                DestR.x -= 10;
            }
            break;
            
        case SDLK_RIGHT:
            if ( DestR.x < 770 ) {
                DestR.x += 10;
            }
            break;
    }
    
    return DestR;
}
