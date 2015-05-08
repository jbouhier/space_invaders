//
//  freeMemory.c
//  space_invaders
//
//  Created by Gatien MOUAFO on 08/05/15.
//  Copyright (c) 2015 ETNA. All rights reserved.
//

#include "main_file.h"


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

    player.player = NULL;
    player.texture_score = NULL;
    player.texture_lives = NULL;
    player.surface_score = NULL;
    player.surface_lives = NULL;
    player.bulletGo_sound = NULL;
    player.playerExplode_sound = NULL;

    free(player.bullet);
}

void freeInfos(t_game game)
{
    if (game.infos.surface_high_score)
        SDL_FreeSurface(game.infos.surface_high_score);
    if (game.infos.surface_score_title)
        SDL_FreeSurface(game.infos.surface_score_title);
    if (game.infos.texture_high_score)
        SDL_DestroyTexture(game.infos.texture_high_score);
    if (game.infos.texture_score_title)
        SDL_DestroyTexture(game.infos.texture_score_title);
    if (game.infos.font)
        TTF_CloseFont(game.infos.font);

    game.infos.surface_high_score = NULL;
    game.infos.surface_score_title = NULL;
    game.infos.texture_high_score = NULL;
    game.infos.texture_score_title = NULL;
    game.infos.font = NULL;
}