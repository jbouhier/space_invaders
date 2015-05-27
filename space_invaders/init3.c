//
//  init3.c
//  space_invaders
//
//  Created by Jean-Baptiste Bouhier on 27/05/15.
//  Copyright (c) 2015 ETNA. All rights reserved.
//

#include "prototypes.h"


t_game  showGameOver(t_game game)
{
    game.Gscreen = loadTexture( "/../../../images/background/main_menu.png", game.Grenderer );
    game.begin.surface_play = TTF_RenderText_Solid(game.text.font, "GAME    OVER", game.text.color);
    game.begin.play_with_2 = SDL_CreateTextureFromSurface(game.Grenderer, game.begin.surface_play);
    game.begin.play_with_2_position = init_position(135, 180, 180, 500);
    
    SDL_Delay(50);
    game.begin.state = 1;
    
    if (game.Gplayer1.lives == -1)
    {
        write_score(game, game.Gplayer1);
        game = init_player(game);
    }
    
    renderEnd(game);
    
    return (game);
}


void    renderEnd(t_game game)
{
    int checkResult;
    
    checkResult = checkBeginTexture(game.begin);
    
    if (checkResult == 1) {
        SDL_RenderClear( game.Grenderer );
        SDL_RenderCopy( game.Grenderer, game.Gscreen, NULL, NULL );
        SDL_RenderCopy( game.Grenderer, game.begin.play_with_2, NULL, &(game.begin.play_with_2_position) );
        SDL_RenderPresent( game.Grenderer );
        SDL_UpdateWindowSurface( game.Gwindow );
    }
}


// Display game interface to be able to play
t_game    showGame(t_game game, int tempsActuel, int tempsPrecedent)
{
    if (game.Gevenements.type == SDL_KEYDOWN)
    {
        game.Gplayer1 = movePlayer(game);
        if (game.Gevenements.key.keysym.sym == SDLK_SPACE && game.Gplayer1.nbr_bullet < 2)
        {
            Mix_PlayChannel(-1, game.Gplayer1.bulletGo_sound, 0);
            game.Gplayer1.bullet[game.Gplayer1.nbr_bullet].bullet = loadBullet(game);
            game.Gplayer1.bullet[game.Gplayer1.nbr_bullet].position = init_bulletPos(game.Gplayer1);
            game.Gplayer1.nbr_bullet++;
        }
    }
    // Si 15 ms se sont écoulées depuis le dernier tour de boucle
    if (tempsActuel - tempsPrecedent > 15) {
        game = launch_bullet(game);
        game = launch_bulletMonster(game);
        game = moveMonster(game);
    }
    
    renderAll(game);
    return (game);
}