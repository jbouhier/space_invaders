//
//  loadings3.c
//  space_invaders
//
//  Created by Jean-Baptiste Bouhier on 26/05/15.
//  Copyright (c) 2015 ETNA. All rights reserved.
//

#include "prototypes.h"


char **AllocateSoundPath(char **paths)
{
    paths[0] = "/../../../sounds/explosion.wav";
    paths[1] = "/../../../sounds/invaderkilled.wav";
    paths[2] = "/../../../sounds/shoot.wav";
    paths[3] = "/../../../sounds/MoveMonster.wav";
    
    return (paths);
}


SDL_Texture *loadMonster(SDL_Renderer* gRenderer)
{
    //Loading success flag
    bool success = true;
    SDL_Texture* monster;
    
    monster = loadTexture( "/../../../images/monster2.bmp", gRenderer);
    
    if (monster == NULL){
        printf( "Failed to load texture image!\n" );
        success = false;
    }
    return (monster);
}


void    renderBegin(t_game game)
{
    int checkResult;
    
    checkResult = checkBeginTexture(game.begin);
    
    if (checkResult == 1)
    {
        SDL_RenderClear( game.Grenderer );
        SDL_RenderCopy( game.Grenderer, game.Gscreen, NULL, NULL );
        SDL_RenderCopy( game.Grenderer, game.begin.logo, NULL, &(game.begin.logo_position) );
        SDL_RenderCopy( game.Grenderer, game.begin.play_with_1, NULL, &(game.begin.play_with_1_position) );
        SDL_RenderCopy( game.Grenderer, game.begin.high_score, NULL, &(game.begin.high_score_position) );
        SDL_RenderCopy( game.Grenderer, game.begin.quit, NULL, &(game.begin.quit_position) );
        SDL_RenderCopy( game.Grenderer, game.begin.selected_option, NULL, &(game.begin.selected_option_position) );
        SDL_RenderPresent( game.Grenderer );
        SDL_UpdateWindowSurface( game.Gwindow );
    }
}
