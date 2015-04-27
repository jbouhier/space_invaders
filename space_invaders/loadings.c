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

    //Load PNG texture
    player = loadTexture( "/Users/mouafo/bitbucket/space_invaders/space_invaders/space-ship-md.png",
                         game.Gwindow, game.Grenderer);
    if( player == NULL )
    {
        player = loadTexture( "/Users/synxs/etna/0-bachelor/c/space/space_invaders/space_invaders/space-ship-md.png",
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
    char *paths;

<<<<<<< HEAD
    paths =  malloc (strlen(ROOT_DIR) + strlen("/../../../../space_invaders/1428113676_bullet_white.png") + 1);

    strcpy(paths, ROOT_DIR);
    strcat(paths,"/../../../../space_invaders/1428113676_bullet_white.png");

    //Load PNG texture
    bullet = loadTexture( "/Users/mouafo/bitbucket/space_invaders/space_invaders/1428113676_bullet_white.png",
                         game.Gwindow, game.Grenderer);
    if( bullet == NULL )
    {
        bullet = loadTexture( "/Users/synxs/etna/0-bachelor/c/space/space_invaders/space_invaders/1428113676_bullet_white.png",
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
    
=======
    paths =  malloc (strlen(ROOT_DIR) + strlen("/../../../space_invaders/1428113676_bullet_white.png") + 1);

    strcpy(paths, ROOT_DIR);
    strcat(paths,"/../../../space_invaders/1428113676_bullet_white.png");

    //Load PNG texture
    bullet = loadTexture( paths, game.Gwindow, game.Grenderer);

>>>>>>> dev
    if( bullet == NULL )
    {
        printf( "Failed to load texture image!\n" );
        success = false;
    }

    return bullet;
}


<<<<<<< HEAD
<<<<<<< Updated upstream
=======
=======
>>>>>>> dev
S_Game loadMonsters(S_Game game)
{
    char *paths;
    SDL_Surface *loadedSurface;

    x = 10;
    y = 10;
<<<<<<< HEAD
    paths =  malloc (strlen(ROOT_DIR) + strlen("/../../../../space_invaders/image/monster.png") + 1);

    strcpy(paths, ROOT_DIR);
    strcat(paths, "/../../../../space_invaders/image/monster.png");
=======
    paths =  malloc (strlen(ROOT_DIR) + strlen("/../../../space_invaders/image/monster.png") + 1);

    strcpy(paths, ROOT_DIR);
    strcat(paths, "/../../../space_invaders/image/monster.png");
>>>>>>> dev
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

    return game;
}

<<<<<<< HEAD
>>>>>>> Stashed changes
=======
>>>>>>> dev
S_Game loadSounds(S_Game game)
{
    char **paths;
    
    paths = AllocateSoundPath(paths);

    game.Gplayer.playerExplode_sound = Mix_LoadWAV( paths[0] );
    game.Gplayer.bulletGo_sound = Mix_LoadWAV( paths[2] );

    for (i = 0; game.Gmonster[i].monster != NULL; i++) {
        game.Gmonster[i].monsterExplode_sound = Mix_LoadWAV( paths[1] );
        game.Gmonster[i].monsterMove_sound = Mix_LoadWAV( paths[3] );
    }

    if(game.Gplayer.playerExplode_sound == NULL)
        fprintf(stderr,"Could not load %s\n", paths[0]);
    
    for (i = 0; i < LOAD_SOUND_MAX; i++) {
        free(paths[i]);
    }
    free(paths);

    return game;
}


char **AllocateSoundPath(char **paths) {
<<<<<<< HEAD

<<<<<<< Updated upstream
    paths = malloc (sizeof(char*) + LOAD_SOUND_MAX);
    paths[0] = malloc (strlen(ROOT_DIR) + strlen("/space_invaders/sounds/explosion.wav") + 1);
    paths[1] = malloc (strlen(ROOT_DIR) + strlen("/space_invaders/sounds/invaderkilled.wav") + 1);
    paths[2] = malloc (strlen(ROOT_DIR) + strlen("/space_invaders/sounds/shoot.wav") + 1);
    paths[3] = malloc (strlen(ROOT_DIR) + strlen("/space_invaders/sounds/MovePayer.wav") + 1);
=======
    paths[0] = malloc ((sizeof(char) * strlen(ROOT_DIR) + strlen("/../../../../space_invaders/sounds/explosion.wav")) + 1);
    paths[1] = malloc ((sizeof(char) * strlen(ROOT_DIR) + strlen("/../../../../space_invaders/sounds/invaderkilled.wav")) + 1);
    paths[2] = malloc ((sizeof(char) * strlen(ROOT_DIR) + strlen("/../../../../space_invaders/sounds/shoot.wav")) + 1);
    paths[3] = malloc ((sizeof(char) * strlen(ROOT_DIR) + strlen("/../../../../space_invaders/sounds/MoveMonster.wav")) + 1);
>>>>>>> Stashed changes
=======
    paths = malloc (sizeof(char*) + LOAD_SOUND_MAX);

    paths[0] = malloc ((sizeof(char) * strlen(ROOT_DIR) + strlen("/../../../space_invaders/sounds/explosion.wav")) + 1);
    paths[1] = malloc ((sizeof(char) * strlen(ROOT_DIR) + strlen("/../../../space_invaders/sounds/invaderkilled.wav")) + 1);
    paths[2] = malloc ((sizeof(char) * strlen(ROOT_DIR) + strlen("/../../../space_invaders/sounds/shoot.wav")) + 1);
    paths[3] = malloc ((sizeof(char) * strlen(ROOT_DIR) + strlen("/../../../space_invaders/sounds/MoveMonster.wav")) + 1);
>>>>>>> dev

    strcpy(paths[0], ROOT_DIR);
    strcpy(paths[1], ROOT_DIR);
    strcpy(paths[2], ROOT_DIR);
    strcpy(paths[3], ROOT_DIR);
<<<<<<< HEAD
<<<<<<< Updated upstream
=======
    
    strcat(paths[0],"/../../../../space_invaders/sounds/explosion.wav");
    strcat(paths[1],"/../../../../space_invaders/sounds/invaderkilled.wav");
    strcat(paths[2],"/../../../../space_invaders/sounds/shoot.wav");
    strcat(paths[3],"/../../../../space_invaders/sounds/MoveMonster.wav");
>>>>>>> Stashed changes
=======
    
    strcat(paths[0],"/../../../space_invaders/sounds/explosion.wav");
    strcat(paths[1],"/../../../space_invaders/sounds/invaderkilled.wav");
    strcat(paths[2],"/../../../space_invaders/sounds/shoot.wav");
    strcat(paths[3],"/../../../space_invaders/sounds/MoveMonster.wav");
>>>>>>> dev

    return paths;
}


<<<<<<< HEAD
<<<<<<< Updated upstream
=======
S_Game showExposion(S_Game game, int index) {
    char *paths;
    
    paths =  malloc (strlen(ROOT_DIR) + strlen("/../../../../space_invaders/image/explosion.png") + 1);
    
    strcpy(paths, ROOT_DIR);
    strcat(paths,"/../../../../space_invaders/image/explosion.png");
=======
S_Game showExposion(S_Game game, int index) {
    char *paths;
    
    paths =  malloc (strlen(ROOT_DIR) + strlen("/../../../space_invaders/image/explosion.png") + 1);
    
    strcpy(paths, ROOT_DIR);
    strcat(paths,"/../../../space_invaders/image/explosion.png");
>>>>>>> dev
    
    game.Gmonster[index].explosion = loadTexture( paths, game.Gwindow, game.Grenderer);

    return game;
}


<<<<<<< HEAD
>>>>>>> Stashed changes
=======
>>>>>>> dev
