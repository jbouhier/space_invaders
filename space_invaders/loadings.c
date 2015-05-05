//
//  loadings.c
//  space_invaders
//
//  Created by Gatien MOUAFO on 27/03/15.
//  Copyright (c) 2015 ETNA. All rights reserved.
//

#include "main_file.h"
int i;
int j;
int x;
int y;

SDL_Texture *loadTexture( char* path, SDL_Window *gWindow, SDL_Renderer* gRenderer)
{
    SDL_Texture* newTexture;
    //Load image at specified path
    SDL_Surface* loadedSurface;

    loadedSurface = IMG_Load( path );
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

SDL_Texture *loadPlayer(S_Game game)
{
    //Loading success flag
    SDL_Texture* player;
    char        *ship_rel_path = "/../../../images/ship.png";
    char        *ship;
    
    // Create and malloc shipfull path string
    ship = malloc ((sizeof(char) * strlen(PWD) + strlen(ship_rel_path)) + 1);
    strcpy(ship, PWD);
    strcat(ship, ship_rel_path);
    
    //Load ship PNG texture
    player = loadTexture( ship, game.Gwindow, game.Grenderer);
    if( player == NULL )
        printf( "Failed to load texture image!\n" );

    return player;
}


SDL_Texture *loadBullet(S_Game game)
{
    //Loading success flag
    bool success = true;
    SDL_Texture* bullet;
    char *paths;
    
    paths =  malloc (strlen(PWD) + strlen("/../../../images/bullet.png") + 1);
    strcpy(paths, PWD);
    strcat(paths,"/../../../images/bullet.png");

    //Load PNG texture
    bullet = loadTexture( paths, game.Gwindow, game.Grenderer);

    if( bullet == NULL )
    {
        printf( "Failed to load texture image!\n" );
        success = false;
    }
    
    free(paths);

    return bullet;
}

S_Game loadMonsters(S_Game game)
{
    char *paths;
    SDL_Surface *loadedSurface;

    x = 10;
    y = 10;

    paths =  malloc (strlen(PWD) + strlen("/../../../images/monster1.png") + 1);
    strcpy(paths, PWD);
    strcat(paths, "/../../../images/monster1.png");

    loadedSurface = IMG_Load( paths );
    if( loadedSurface == NULL )
        printf( "Unable to load image %s! SDL_image Error: %s\n", paths, IMG_GetError() );
    else {
        for (i = 0; i < MONSTER_NBR; i++) {
            j = i;
            game.Gmonster[i].monster = SDL_CreateTextureFromSurface ( game.Grenderer, loadedSurface);
            if( game.Gmonster[i].monster == NULL ) {
                printf( "Failed to load texture image %s for the monsters! SDL Error: %s\n", paths, SDL_GetError()  );
            }
            game.Gmonster[i].position = init_position(x, y, 20, 20);
            if ((i + 1) % 6 != 0 || i == 0) {
                x += 50;
            }
            else {
                x = 10;
                y += 30;
            }
        }
        SDL_FreeSurface( loadedSurface );
    }
    
    free(paths);

    return game;
}

S_Game loadSounds(S_Game game)
{
    char **paths;
    
    paths = AllocateSoundPath(paths);

    game.Gplayer1.playerExplode_sound = Mix_LoadWAV( paths[0] );
    game.Gplayer1.bulletGo_sound = Mix_LoadWAV( paths[2] );

    for (i = 0; game.Gmonster[i].monster != NULL; i++) {
        game.Gmonster[i].monsterExplode_sound = Mix_LoadWAV( paths[1] );
        game.Gmonster[i].monsterMove_sound = Mix_LoadWAV( paths[3] );
    }

    if(game.Gplayer1.playerExplode_sound == NULL)
        fprintf(stderr,"Could not load %s\n", paths[0]);
    
    for (i = 0; i < LOAD_SOUND_MAX; i++) {
        free(paths[i]);
    }
    free(paths);

    return game;
}


char **AllocateSoundPath(char **paths)
{
    paths = malloc (sizeof(char*) + LOAD_SOUND_MAX);

    paths[0] = malloc ((sizeof(char) * strlen(PWD) + strlen("/../../../sounds/explosion.wav")) + 1);
    paths[1] = malloc ((sizeof(char) * strlen(PWD) + strlen("/../../../sounds/invaderkilled.wav")) + 1);
    paths[2] = malloc ((sizeof(char) * strlen(PWD) + strlen("/../../../sounds/shoot.wav")) + 1);
    paths[3] = malloc ((sizeof(char) * strlen(PWD) + strlen("/../../../sounds/MoveMonster.wav")) + 1);

    strcpy(paths[0], PWD);
    strcpy(paths[1], PWD);
    strcpy(paths[2], PWD);
    strcpy(paths[3], PWD);
    
    strcat(paths[0],"/../../../sounds/explosion.wav");
    strcat(paths[1],"/../../../sounds/invaderkilled.wav");
    strcat(paths[2],"/../../../sounds/shoot.wav");
    strcat(paths[3],"/../../../sounds/MoveMonster.wav");
    
    return paths;
}

S_Game showExposion(S_Game game, int index)
{
    char *paths;
    
    paths =  malloc (strlen(PWD) + strlen("/../../../images/explosion.png") + 1);
    
    strcpy(paths, PWD);
    strcat(paths,"/../../../images/explosion.png");
    
    game.Gmonster[index].explosion = loadTexture( paths, game.Gwindow, game.Grenderer);

    return game;
}