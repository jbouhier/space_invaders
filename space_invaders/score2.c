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
    
    score_str = malloc(sizeof(*score_str) * SCORE_LENGTH + 1);
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
    lives_str = malloc(sizeof(*lives_str) * LIVES_LENGTH + 1);
    sprintf(lives_str, "%ld", lives);
    
    return (lives_str);
}


t_game  refresh_score(t_game game)
{
    SDL_Colour text_color = {255, 255, 255, 0};
    
    // Player 1
    // SDL_FreeSurface(game.Gplayer1.surface_score);
    game.Gplayer1.score_str = score_str(game.Gplayer1.score, game.Gplayer1.score_str);
    game.Gplayer1.surface_score = TTF_RenderText_Solid(game.infos.font, game.Gplayer1.score_str, text_color);
    game.Gplayer1.texture_score = SDL_CreateTextureFromSurface(game.Grenderer, game.Gplayer1.surface_score);

    // Player 2
    // SDL_FreeSurface(game.Gplayer2.surface_score);
    game.Gplayer2.score_str = score_str(game.Gplayer2.score, game.Gplayer2.score_str);
    game.Gplayer2.surface_score = TTF_RenderText_Solid(game.infos.font, game.Gplayer2.score_str, text_color);
    game.Gplayer2.texture_score = SDL_CreateTextureFromSurface(game.Grenderer, game.Gplayer2.surface_score);
    
    // Update Render
    SDL_RenderCopy( game.Grenderer, game.Gplayer1.texture_score, NULL, &(game.Gplayer1.score_pos) );
    SDL_RenderCopy( game.Grenderer, game.Gplayer2.texture_score, NULL, &(game.Gplayer2.score_pos) );
    
    return (game);
}

t_game  refresh_lives(t_game game)
{
    SDL_Colour text_color = {255, 255, 255, 0};
    
    // Player 1
    game.Gplayer1.lives_str = lives_str(game.Gplayer1.lives, game.Gplayer1.lives_str);
    game.Gplayer1.surface_lives = TTF_RenderText_Solid(game.infos.font, game.Gplayer1.lives_str, text_color);
    game.Gplayer1.texture_lives = SDL_CreateTextureFromSurface(game.Grenderer, game.Gplayer1.surface_lives);
    
    // Player 2
    game.Gplayer2.lives_str = lives_str(game.Gplayer2.lives, game.Gplayer2.lives_str);
    game.Gplayer2.surface_lives = TTF_RenderText_Solid(game.infos.font, game.Gplayer2.lives_str, text_color);
    game.Gplayer2.texture_lives = SDL_CreateTextureFromSurface(game.Grenderer, game.Gplayer2.surface_lives);
    
    // Update Render
    SDL_RenderCopy( game.Grenderer, game.Gplayer1.texture_lives, NULL, &(game.Gplayer1.lives_pos) );
    SDL_RenderCopy( game.Grenderer, game.Gplayer2.texture_lives, NULL, &(game.Gplayer2.lives_pos) );
    
    return (game);
}