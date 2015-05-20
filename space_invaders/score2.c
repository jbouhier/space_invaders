//
//  score2.c
//  space_invaders
//
//  Created by Jean-Baptiste Bouhier on 07/05/15.
//  Copyright (c) 2015 ETNA. All rights reserved.
//

#include "prototypes.h"

char  *score_str(long hscore, char *score_str)
{
    size_t  len;
    size_t  i;
    char    *tmp;
    
    score_str = malloc(sizeof(*tmp) * SCORE_LENGTH + 1);
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
    
    game.Gplayer1.score_str = score_str(game.Gplayer1.score,
                                        game.Gplayer1.score_str);
    game.Gplayer1.surface_score = TTF_RenderText_Solid(game.text_game.font,
                                                       game.Gplayer1.score_str,
                                                       text_color);
    game.Gplayer1.texture_score = SDL_CreateTextureFromSurface(game.Grenderer,
                                                               game.Gplayer1.surface_score);
    
    game.Gplayer2.score_str = score_str(game.Gplayer2.score, game.Gplayer2.score_str);
    game.Gplayer2.surface_score = TTF_RenderText_Solid(game.text_game.font, game.Gplayer2.score_str, text_color);
    game.Gplayer2.texture_score = SDL_CreateTextureFromSurface(game.Grenderer, game.Gplayer2.surface_score);
    
    SDL_RenderCopy(game.Grenderer, game.Gplayer1.texture_score, NULL,
                   &(game.Gplayer1.score_pos));
    SDL_RenderCopy(game.Grenderer, game.Gplayer2.texture_score, NULL,
                   &(game.Gplayer2.score_pos) );
    
    return (game);
}


void  render_hscore(t_game *g, t_text_game text, SDL_Renderer *rend)
{
    SDL_Colour tcolor = {255, 255, 255, 0};
    
    g->hscore_str = malloc(sizeof(*(g->hscore_str)) * (SCORE_LENGTH + 1));
    g->hscore_str = score_str(g->high_score, g->hscore_str);
    g->surface_high_score = TTF_RenderText_Solid(text.font, g->hscore_str, tcolor);
    g->texture_high_score = SDL_CreateTextureFromSurface(rend, g->surface_high_score);
    SDL_RenderCopy(rend, g->texture_high_score, NULL, &(g->high_score_pos));
}


void  render_score(t_player *p, t_text_game text, SDL_Renderer *rend)
{
    SDL_Colour tcolor = {255, 255, 255, 0};
    
    p->score_str = malloc(sizeof(*(p->score_str)) * (SCORE_LENGTH) + 1);
    p->score_str = score_str(p->score, p->score_str);
    p->surface_score = TTF_RenderText_Solid(text.font, p->score_str, tcolor);
    p->texture_score = SDL_CreateTextureFromSurface(rend, p->surface_score);
    SDL_RenderCopy(rend, p->texture_score, NULL, &(p->score_pos));
}


void  render_lives(t_player *p, t_text_game text, SDL_Renderer *rend)
{
    SDL_Colour tcolor = {255, 255, 255, 0};
    
    p->lives_str = malloc(sizeof(*(p->lives_str)) * (LIVES_LENGTH) + 1);
    p->lives_str = lives_str(p->lives, p->lives_str);
    p->surface_lives = TTF_RenderText_Solid(text.font, p->lives_str, tcolor);
    p->texture_lives = SDL_CreateTextureFromSurface(rend, p->surface_lives);
    SDL_RenderCopy(rend, p->texture_lives, NULL, &(p->lives_pos));
}