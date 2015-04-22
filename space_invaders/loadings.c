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


S_Game loadSounds(S_Game game)
{
    char **paths;
    int i;
    
    paths = AllocateSoundPath(paths);
    
    strcat(paths[0],"/space_invaders/sounds/explosion.wav");
    strcat(paths[1],"/space_invaders/sounds/invaderkilled.wav");
    strcat(paths[2],"/space_invaders/sounds/shoot.wav");
    strcat(paths[3],"/space_invaders/sounds/MoveMonster.wav");
    
    game.Gplayer.playerExplode_sound = Mix_LoadWAV( paths[0] );
    game.Gmonster.monsterExplode_sound = Mix_LoadWAV( paths[1] );
    game.Gplayer.bulletGo_sound = Mix_LoadWAV( paths[2] );
    game.Gmonster.monsterMove_sound = Mix_LoadWAV( paths[3] );
    
    for (i = 0; i < LOAD_SOUND_MAX; i++) {
        free(paths[i]);
    }
    free(paths);
    
    return game;
}


char **AllocateSoundPath(char **paths) {

    paths = malloc (sizeof(char*) + LOAD_SOUND_MAX);
    paths[0] = malloc (strlen(ROOT_DIR) + strlen("/space_invaders/sounds/explosion.wav") + 1);
    paths[1] = malloc (strlen(ROOT_DIR) + strlen("/space_invaders/sounds/invaderkilled.wav") + 1);
    paths[2] = malloc (strlen(ROOT_DIR) + strlen("/space_invaders/sounds/shoot.wav") + 1);
    paths[3] = malloc (strlen(ROOT_DIR) + strlen("/space_invaders/sounds/MovePayer.wav") + 1);

    strcpy(paths[0], ROOT_DIR);
    strcpy(paths[1], ROOT_DIR);
    strcpy(paths[2], ROOT_DIR);
    strcpy(paths[3], ROOT_DIR);

    return paths;
}


SDL_Texture *loadMonster(SDL_Event evenements, SDL_Window *gWindow, SDL_Renderer* gRenderer)
{
    //Loading success flag
    bool success = true;
    SDL_Texture* monster;
    
    monster = loadTexture( "/Users/princetim/space_invaders/space_invaders/space_invaders/images.bmp", gWindow, gRenderer);
    
    if (monster == NULL){
        printf( "Failed to load texture image!\n" );
        success = false;
    }
    return monster;
}

SDL_Rect moveMonster(SDL_Rect DestR)
{
    
        
    return DestR;
}

