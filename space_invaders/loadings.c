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
    DestR.w = 1000;
    DestR.h = 1000;
    
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

        SDL_BlitSurface( loadedSurface, &DestR, gScreenSurface, NULL );

        SDL_FreeSurface( loadedSurface );
        SDL_FreeSurface( optimizedSurface );
    }
    
    return optimizedSurface;
}
