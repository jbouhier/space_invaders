//
//  score2.c
//  space_invaders
//
//  Created by SynxS on 07/05/15.
//  Copyright (c) 2015 ETNA. All rights reserved.
//

#include "prototypes.h"

char  *score_str(long hscore, char *score_str)
{
    size_t  len;
    size_t  i;
    char    *tmp;
    
    sprintf(score_str, "%ld", hscore);
    len = strlen(score_str);
    tmp = malloc(sizeof(*tmp) * SCORE_LENGTH + 1);
    
    for (i = 0; i < SCORE_LENGTH - len; i++)
        strcat(tmp, "0");
    
    strcat(tmp, score_str);
    return (tmp);
}


char  *lives_str(long lives, char *lives_str)
{
    size_t  len;
    size_t  i;
    char    *tmp;
    
    sprintf(lives_str, "%ld", lives);
    len = strlen(lives_str);
    tmp = malloc(sizeof(*tmp) * LIVES_LENGTH + 1);
    
    for (i = 0; i < LIVES_LENGTH - len; i++)
        strcat(tmp, "0");
    
    strcat(tmp, lives_str);
    return (tmp);
}


//t_game    refresh_score(t_game game)
//{
//    SDL_Colour text_color = {255, 255, 255, 0};
//    
//    SDL_RenderClear( game.Grenderer );
//    
//    game.Gplayer1.surface_score = TTF_RenderText_Solid( game.infos.font, game.Gplayer1.score_str, text_color );
//    game.Gplayer1.texture_score = SDL_CreateTextureFromSurface( game.Grenderer, game.Gplayer1.surface_score );
//    
//    SDL_RenderCopy( game.Grenderer, game.Gplayer1.texture_score, NULL, &(game.Gplayer1.score_pos) );
//    SDL_RenderCopy( game.Grenderer, game.Gplayer1.texture_lives, NULL, &(game.Gplayer1.lives_pos) );
//    SDL_RenderCopy( game.Grenderer, game.Gplayer2.texture_score, NULL, &(game.Gplayer2.score_pos) );
//    SDL_RenderCopy( game.Grenderer, game.Gplayer2.texture_lives, NULL, &(game.Gplayer2.lives_pos) );
//
////    SDL_RenderPresent( game.Grenderer );
////    SDL_UpdateWindowSurface( game.Gwindow );
//    
//    return (game);
//}