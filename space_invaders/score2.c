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


void    render_title(t_text *t, SDL_Renderer *rend)
{
    char    *title;
    
    title = "S C O R E < 1 >        H I - S C O R E        S C O R E < 2 >";
    t->sur_stitle = malloc(sizeof(title) * strlen(title) + 1);
    t->sur_stitle = TTF_RenderText_Solid(t->font, title, t->color);
    t->tex_stitle = SDL_CreateTextureFromSurface(rend, t->sur_stitle);
    SDL_RenderCopy(rend, t->tex_stitle, NULL, &(t->pos_stitle));
}


void  render_hscore(t_text *t, SDL_Renderer *rend)
{
    t->hscore_str = malloc(sizeof(*(t->hscore_str)) * SCORE_LENGTH + 1);
    t->hscore_str = score_str(t->hscore, t->hscore_str);
    t->sur_hscore = TTF_RenderText_Solid(t->font, t->hscore_str, t->color);
    t->tex_hscore = SDL_CreateTextureFromSurface(rend, t->sur_hscore);
    SDL_RenderCopy(rend, t->tex_hscore, NULL, &(t->pos_hscore));
}


void  render_score(t_player *p, t_text t, SDL_Renderer *rend)
{
    p->score_str = malloc(sizeof(*(p->score_str)) * SCORE_LENGTH + 1);
    p->score_str = score_str(p->score, p->score_str);
    p->surface_score = TTF_RenderText_Solid(t.font, p->score_str, t.color);
    p->texture_score = SDL_CreateTextureFromSurface(rend, p->surface_score);
    SDL_RenderCopy(rend, p->texture_score, NULL, &(p->score_pos));
}


void  render_lives(t_player *p, t_text t, SDL_Renderer *rend)
{
    p->lives_str = malloc(sizeof(*(p->lives_str)) * LIVES_LENGTH + 1);
    p->lives_str = lives_str(p->lives, p->lives_str);
    p->surface_lives = TTF_RenderText_Solid(t.font, p->lives_str, t.color);
    p->texture_lives = SDL_CreateTextureFromSurface(rend, p->surface_lives);
    SDL_RenderCopy(rend, p->texture_lives, NULL, &(p->lives_pos));
}