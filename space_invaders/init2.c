//
//  init2.c
//  space_invaders
//
//  Created by Jean-Baptiste Bouhier on 27/05/15.
//  Copyright (c) 2015 ETNA. All rights reserved.
//

#include "prototypes.h"


t_game  init_player(t_game game)
{
    game.Gplayer1.position = init_position(SCREEN_WIDTH /
                                           2, SCREEN_HEIGHT - 100, 35, 35);
    
    game.Gplayer1.nbr_bullet = 0;
    game.Gplayer1.score = 0;
    game.Gplayer1.lives = 3;
    
    game.Gplayer2.nbr_bullet = 0;
    game.Gplayer2.score = 0;
    game.Gplayer2.lives = 3;
    
    return (game);
}


void end(t_game game)
{
    freeBegin(game);
    freeMonster(game);
    freePlayer(game.Gplayer1);
    freePlayer(game.Gplayer2);
    freeInfos(game);
    
    SDL_DestroyTexture(game.Gscreen);
    SDL_DestroyRenderer( game.Grenderer );
    SDL_DestroyWindow( game.Gwindow );
    game.Grenderer = NULL;
    game.Gscreen = NULL;
    game.Gwindow = NULL;
    
    IMG_Quit();
    Mix_Quit();
    TTF_Quit();
    SDL_Quit();
}


SDL_Rect init_position(int x, int y, int h, int w)
{
    SDL_Rect rect;
    
    rect.x = x;
    rect.y = y;
    rect.h = h;
    rect.w = w;
    
    return (rect);
}


SDL_Rect init_bulletPos(t_player player)
{
    SDL_Rect rectangle;
    
    rectangle.y =  player.position.y - 10;
    rectangle.x =  player.position.x + 12;
    rectangle.w = 10;
    rectangle.h = 25;
    
    return (rectangle);
}


SDL_Rect init_bulletMonsterPos(t_monster monster)
{
    SDL_Rect rectangle;
    
    rectangle.y =  monster.position.y + 4;
    rectangle.x =  monster.position.x + 8;
    rectangle.w = 4;
    rectangle.h = 30;
    
    return (rectangle);
}