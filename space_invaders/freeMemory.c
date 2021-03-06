//
//  freeMemory.c
//  space_invaders
//
//  Created by Gatien MOUAFO on 08/05/15.
//  Copyright (c) 2015 ETNA. All rights reserved.
//

#include "prototypes.h"


void freeBegin(t_game game)
{
    if (game.begin.high_score != NULL)
        SDL_DestroyTexture(game.begin.high_score);
    if (game.begin.logo != NULL)
        SDL_DestroyTexture(game.begin.logo);
    if (game.begin.play_with_1 != NULL)
        SDL_DestroyTexture(game.begin.play_with_1);
    if (game.begin.play_with_2 != NULL)
        SDL_DestroyTexture(game.begin.play_with_2);
    if (game.begin.quit != NULL)
        SDL_DestroyTexture(game.begin.quit);

    game.begin.logo = NULL;
    game.begin.quit = NULL;
    game.begin.high_score = NULL;
    game.begin.play_with_1 = NULL;
    game.begin.play_with_2 = NULL;
}

void freeMonster(t_game game)
{
    int i;

    for (i = 0; i < MONSTER_NBR; i++) {
        if (game.Gmonster[i].monster != NULL)
            SDL_DestroyTexture(game.Gmonster[i].monster);
        if (game.Gmonster[i].explosion != NULL)
            SDL_DestroyTexture(game.Gmonster[i].explosion);
        if (game.Gmonster[i].bullet.bullet != NULL)
            SDL_DestroyTexture(game.Gmonster[i].bullet.bullet);
        if (game.Gmonster[i].monsterMove_sound != NULL)
            Mix_FreeChunk(game.Gmonster[i].monsterMove_sound);
        if (game.Gmonster[i].monsterExplode_sound != NULL)
            Mix_FreeChunk(game.Gmonster[i].monsterExplode_sound);

        game.Gmonster[i].score = 0;
        game.Gmonster[i].nbr_bullet = 0;
        game.Gmonster[i].monster = NULL;
        game.Gmonster[i].explosion = NULL;
        game.Gmonster[i].bullet.bullet = NULL;
        game.Gmonster[i].monsterMove_sound = NULL;
        game.Gmonster[i].monsterExplode_sound = NULL;
    }

    free(game.Gmonster);
}

void freePlayer(t_player player)
{
    int i;

    if (player.texture_score != NULL)
        SDL_DestroyTexture(player.texture_score);
    if (player.texture_lives != NULL)
        SDL_DestroyTexture(player.texture_lives);
    if (player.surface_score != NULL)
        SDL_FreeSurface(player.surface_score);
    if (player.surface_lives != NULL)
        SDL_FreeSurface(player.surface_lives);
    if (player.player != NULL)
        SDL_DestroyTexture(player.player);
    if (player.bulletGo_sound != NULL)
        Mix_FreeChunk(player.bulletGo_sound);
    if (player.playerExplode_sound != NULL)
        Mix_FreeChunk(player.playerExplode_sound);

    for (i = 0; player.bullet[i].bullet != NULL; i++) {
        SDL_DestroyTexture(player.bullet[i].bullet);
        player.bullet[i].bullet = NULL;
    }
    set_player(&player);
    free(player.bullet);
}

void    set_player(t_player *player)
{
    player->player = NULL;
    player->texture_score = NULL;
    player->texture_lives = NULL;
    player->surface_score = NULL;
    player->surface_lives = NULL;
    player->bulletGo_sound = NULL;
    player->playerExplode_sound = NULL;
}

void freeInfos(t_game game)
{
    if (game.text.sur_hscore)
        SDL_FreeSurface(game.text.sur_hscore);
    if (game.text.sur_stitle)
        SDL_FreeSurface(game.text.sur_stitle);
    if (game.text.tex_hscore)
        SDL_DestroyTexture(game.text.tex_hscore);
    if (game.text.tex_stitle)
        SDL_DestroyTexture(game.text.tex_stitle);
    if (game.text.font)
        TTF_CloseFont(game.text.font);

    game.text.sur_hscore = NULL;
    game.text.sur_stitle = NULL;
    game.text.tex_hscore = NULL;
    game.text.tex_stitle = NULL;
    game.text.font = NULL;
}