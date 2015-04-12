//
//  loadings.c
//  space_invaders
//
//  Created by Gatien MOUAFO on 27/03/15.
//  Copyright (c) 2015 ETNA. All rights reserved.
//

#include "main_file.h"

SDL_Texture *loadTexture( char* path, SDL_Window *gWindow, SDL_Renderer* gRenderer)
{
    SDL_Texture* newTexture = NULL;
    //Load image at specified path
    SDL_Surface* loadedSurface = IMG_Load( path );
    
    if( loadedSurface == NULL )
    {
        //printf( "Unable to load image %s! SDL_image Error: %s\n", path, IMG_GetError() );
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

SDL_Texture *loadPlayer(S_Game game)
{
    //Loading success flag
    SDL_Texture* player;
    
    //Load PNG texture
    
    player = loadTexture( "/Users/mouafo/bitbucket/space_invaders/space_invaders/space-ship-md.png",
                         game.Gwindow, game.Grenderer);
    if( player == NULL )
    {
        player = loadTexture( "/Users/synxs/etna/c/space_invaders/space_invaders/space_invaders/space-ship-md.png",
                             game.Gwindow, game.Grenderer);
        if (player == NULL) {
            player  =  loadTexture (  "/Users/princetim/space_invaders/space_invaders/space_invaders/space-ship-md.png",
                                    game.Gwindow, game.Grenderer);
            if (player == NULL){
                player = loadTexture( "/Users/manelzrelli/Desktop/space_invaders/space_invaders/space-ship-md.png",
                                     game.Gwindow, game.Grenderer);
            }
        }
    }
    
    if( player == NULL)
    {
        printf( "Failed to load texture image!\n" );
    }
    
    return player;
}


SDL_Texture *loadBullet(S_Game game)
{
    //Loading success flag
    bool success = true;
    SDL_Texture* bullet;
    
    //Load PNG texture
    bullet = loadTexture( "/Users/mouafo/bitbucket/space_invaders/space_invaders/1428113676_bullet_white.png",
                         game.Gwindow, game.Grenderer);
    if( bullet == NULL )
    {
        bullet = loadTexture( "/Users/synxs/etna/c/space_invaders/space_invaders/space_invaders/1428113676_bullet_white.png",
                             game.Gwindow, game.Grenderer);
        if (bullet == NULL) {
            bullet  =  loadTexture (  "/Users/princetim/space_invaders/space_invaders/space_invaders/1428113676_bullet_white.png",
                                    game.Gwindow, game.Grenderer);
            if (bullet == NULL){
                bullet = loadTexture( "/Users/manelzrelli/Desktop/space_invaders/space_invaders/1428113676_bullet_white.png",
                                     game.Gwindow, game.Grenderer);
            }
        }
    }
    
    if( bullet == NULL )
    {
        printf( "Failed to load texture image!\n" );
        success = false;
    }
    
    return bullet;
}
