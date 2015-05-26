//
//  loadings2.c
//  space_invaders
//
//  Created by Jean-Baptiste Bouhier on 24/05/15.
//  Copyright (c) 2015 ETNA. All rights reserved.
//

#include "prototypes.h"


// Load image at specified path
SDL_Texture     *loadTexture(char *path, SDL_Renderer *gRenderer)
{
    SDL_Texture     *newTexture;
    SDL_Surface     *loadedSurface;

    newTexture = NULL;
    loadedSurface = IMG_Load(path);
    
    if (loadedSurface == NULL)
    {
        printf( "Unable to load image %s! SDL_image Error: %s\n",
               path, IMG_GetError() );
    }
    else
    {
        //Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface( gRenderer, loadedSurface );
        if (newTexture == NULL)
        {
            printf("Unable to create texture from %s! SDL Error: %s\n",
                   path, SDL_GetError() );
        }
        //Get rid of old loaded surface
        SDL_FreeSurface(loadedSurface);
    }
    
    return (newTexture);
}


SDL_Texture     *loadPlayer(t_game game)
{
    //Loading success flag
    SDL_Texture *player;
    char        *ship_rel_path = "/../../../images/ship.png";
    char        *ship;
    
    // Create and malloc ship full path string
    ship = malloc ((sizeof(char) * strlen(PWD) + strlen(ship_rel_path)) + 1);
    strcpy(ship, PWD);
    strcat(ship, ship_rel_path);
    
    //Load ship PNG texture
    player = loadTexture("/../../../images/ship.png", game.Grenderer);
    if (player == NULL)
        printf( "Failed to load texture image!\n" );
    
    return (player);
}


SDL_Texture     *loadBullet(t_game game)
{
    //Loading success flag
    bool success;
    SDL_Texture *bullet;
    
    //Load PNG texture
    bullet = loadTexture("/../../../images/bullet.png", game.Grenderer);
    success = true;
    
    if (bullet == NULL)
    {
        printf("Failed to load texture image!\n");
        success = false;
    }
    
    return (bullet);
}


t_game  loadSounds(t_game game)
{
    int     i;
    char    **paths;
    
    paths = malloc(sizeof(*paths) * LOAD_SOUND_MAX);
    paths = AllocateSoundPath(paths);
    
    game.Gplayer1.playerExplode_sound = Mix_LoadWAV( "/../../../sounds/explosion.wav" );
    game.Gplayer1.bulletGo_sound = Mix_LoadWAV( "/../../../sounds/invaderkilled.wav" );
    
    for (i = 0; game.Gmonster[i].monster != NULL; i++) {
        game.Gmonster[i].monsterExplode_sound = Mix_LoadWAV( "/../../../sounds/shoot.wav" );
        game.Gmonster[i].monsterMove_sound = Mix_LoadWAV( "/../../../sounds/MoveMonster.wav" );
    }
    
    if(game.Gplayer1.playerExplode_sound == NULL)
        fprintf(stderr,"Could not load %s\n", paths[0]);
    
    free(paths);
    
    return (game);
}

t_game  showExposion(t_game game, int i)
{
    char    *explo = "/../../../images/explosion.png";
    
    game.Gmonster[i].explosion = loadTexture(explo, game.Grenderer);
    game.Gmonster[i].timeShowExplosion = SDL_GetTicks();
    
    if (game.Gplayer1.player != NULL && game.Gplayer1.lives > -1)
    {
        game.Gplayer1.score += game.Gmonster[i].score;
        render_score(&(game.Gplayer1), game.text, game.Grenderer);
    }
    else
        game.Gplayer2.score += game.Gmonster[i].score;
    
    return (game);
}