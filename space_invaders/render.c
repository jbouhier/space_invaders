//
//  render.c
//  space_invaders
//
//  Created by Gatien MOUAFO on 09/05/15.
//  Copyright (c) 2015 ETNA. All rights reserved.
//

#include "prototypes.h"


void    renderAll(t_game game)
{
    int i;

    SDL_RenderClear( game.Grenderer );
    if (game.Gscreen != NULL)
        SDL_RenderCopy( game.Grenderer, game.Gscreen, NULL, NULL );

    renderPlayer(game);

    // Text
    SDL_RenderCopy( game.Grenderer, game.text_game.texture_score_title, NULL, &(game.text_game.score_title_pos) );
    SDL_RenderCopy( game.Grenderer, game.text_game.texture_high_score, NULL, &(game.text_game.high_score_pos) );
    SDL_RenderCopy( game.Grenderer, game.Gplayer1.texture_score, NULL, &(game.Gplayer1.score_pos) );
    SDL_RenderCopy( game.Grenderer, game.Gplayer1.texture_lives, NULL, &(game.Gplayer1.lives_pos) );
    SDL_RenderCopy( game.Grenderer, game.Gplayer2.texture_score, NULL, &(game.Gplayer2.score_pos) );
    SDL_RenderCopy( game.Grenderer, game.Gplayer2.texture_lives, NULL, &(game.Gplayer2.lives_pos) );

    for (i = 0; game.Gmonster[i].monster != NULL; i++) {
        SDL_RenderCopy( game.Grenderer, game.Gmonster[i].monster, NULL, &(game.Gmonster[i].position) ); // Error !
        if (game.Gmonster[i].explosion != NULL) {
            SDL_RenderCopy( game.Grenderer, game.Gmonster[i].explosion, NULL, &(game.Gmonster[i].position) );
        }
        if (game.Gmonster[i].bullet.bullet != NULL) {
            SDL_RenderCopy( game.Grenderer, game.Gmonster[i].bullet.bullet, NULL, &(game.Gmonster[i].bullet.position) );
        }
    }

    SDL_RenderPresent( game.Grenderer );
    SDL_UpdateWindowSurface( game.Gwindow );
}

void    renderPlayer(t_game game)
{
    int i;

    if (game.Gplayer1.player != NULL)
        SDL_RenderCopy( game.Grenderer, game.Gplayer1.player, NULL, &(game.Gplayer1.position) );
    if (game.Gplayer2.player != NULL)
        SDL_RenderCopy( game.Grenderer, game.Gplayer2.player, NULL, &(game.Gplayer1.position) );
    if (game.Gplayer1.texture_score != NULL)
        SDL_RenderCopy( game.Grenderer, game.Gplayer1.texture_score, NULL, &(game.Gplayer1.score_pos) );
    if (game.Gplayer2.texture_score != NULL)
        SDL_RenderCopy( game.Grenderer, game.Gplayer2.texture_score, NULL, &(game.Gplayer2.score_pos) );

    for (i = 0; i < 10; i++) {
        if (game.Gplayer1.bullet[i].bullet != NULL && game.Gplayer1.bullet[i].position.x <= SCREEN_WIDTH) {
            SDL_RenderCopy( game.Grenderer, game.Gplayer1.bullet[i].bullet, NULL, &(game.Gplayer1.bullet[i].position) ); // 2 balles = plantage !
        }
    }

    for (i = 0; game.Gplayer2.bullet[i].bullet != NULL; i++)
        SDL_RenderCopy( game.Grenderer, game.Gplayer2.bullet[i].bullet, NULL, &(game.Gplayer1.bullet[i].position) );
}