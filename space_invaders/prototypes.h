//
//  main_file.h
//  space_invaders
//
//  Created by Gatien MOUAFO on 28/03/15.
//  Copyright (c) 2015 ETNA. All rights reserved.
//

#ifndef __prototypes_h__
# define __prototypes_h__

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <SDL2_mixer/SDL_mixer.h>
#include <SDL2_ttf/SDL_ttf.h>

#define PWD getenv("PWD")
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#define LOAD_SOUND_MAX 4
#define MONSTER_NBR 50
#define LOAD_FONT_MAX 1
#define FONT_SIZE 20
#define SCORE_LENGTH 4
#define LIVES_LENGTH 1


typedef struct      s_bullet
{
    SDL_Texture     *bullet;
    SDL_Rect        position;
}                   t_bullet;

typedef struct      s_player
{
    SDL_Texture     *player;
    SDL_Rect        position;
    t_bullet        *bullet;
    Mix_Chunk       *bulletGo_sound;
    Mix_Chunk       *playerExplode_sound;
    int             nbr_bullet;
    long            score;
    char            *score_str;
    SDL_Rect        score_pos;
    SDL_Surface     *surface_score;
    SDL_Texture     *texture_score;
    long            lives;
    char            *lives_str;
    SDL_Rect        lives_pos;
    SDL_Surface     *surface_lives;
    SDL_Texture     *texture_lives;
}                   t_player;

typedef struct      s_monster
{
    SDL_Texture     *monster;
    SDL_Texture     *explosion;
    SDL_Rect        position;
    t_bullet        bullet;
    Mix_Chunk       *monsterExplode_sound;
    Mix_Chunk       *monsterMove_sound;
    int             timeShowExplosion;
    bool            flagpositon;
    int             nbr_bullet;
    int             score;
}                   t_monster;


typedef struct      s_text_game
{
    TTF_Font        *font;
    SDL_Surface     *surface_score_title;
    SDL_Texture     *texture_score_title;
    SDL_Rect        score_title_pos;
    SDL_Rect        high_score_pos;
    SDL_Surface     *surface_high_score;
    SDL_Texture     *texture_high_score;
}                   t_text_game;


typedef struct      s_begin
{
    SDL_Texture     *logo;
    SDL_Rect        logo_position;
    SDL_Texture     *play_with_1;
    SDL_Rect        play_with_1_position;
    SDL_Texture     *play_with_2;
    SDL_Rect        play_with_2_position;
    SDL_Texture     *high_score;
    SDL_Rect        high_score_position;
    SDL_Texture     *quit;
    SDL_Rect        quit_position;
    SDL_Surface     *surface_play;
    SDL_Texture     *selected_option;
    SDL_Rect        selected_option_position;
    int             state;
}                   t_begin;

typedef struct      s_game
{
    SDL_Window      *Gwindow;
    SDL_Texture     *Gscreen;
    SDL_Renderer    *Grenderer;
    SDL_Event       Gevenements;
    t_player        Gplayer1;
    t_player        Gplayer2;
    t_monster       *Gmonster;
    t_text_game     infos;
    t_begin         begin;
    int             monster_speed;
    int             quit;
    SDL_Rect        score_title_pos;
    long            high_score;
    char            *hscore_str;
    SDL_Rect        high_score_pos;
    SDL_Surface     *surface_high_score;
    SDL_Texture     *texture_high_score;
}                   t_game;

SDL_Rect        init_position(int x, int y, int h, int w);
void            renderBegin(t_game game);
t_game          showBegin(t_game game);
t_game          handleBegin(t_game game);
t_game          KeyBeginHandler(t_game game);
int             checkBeginTexture(t_begin beginGame);
t_game          selectionBeginHandler(t_game game);
t_game          showEnd(t_game game);
t_game          showGame(t_game game, int tempsActuel, int tempsPrecedent);
SDL_Window      *init(SDL_Window *gWindow);
t_game          init_screen(t_game game);
t_game          init_player(t_game game);
t_game          init_text(t_game game);
SDL_Texture     *loadPlayer(t_game game);
t_player        movePlayer(t_game game);
t_game          moveMonster(t_game game);
SDL_Texture     *loadBullet(t_game game);
SDL_Rect        init_bulletPos(t_player player);
SDL_Rect        init_bulletMonsterPos(t_monster monster);
t_game          launch_bullet(t_game game);
t_game          launch_bulletMonster(t_game game);
void            renderAll(t_game game);
t_game          deleteBullets(t_game game, int index);
void            end(t_game game);
bool            checkCollision( SDL_Rect a, SDL_Rect b );
t_game          loadSounds(t_game game);
char            **AllocateSoundPath(char **paths);
t_game          loadMonsters(t_game game);
t_game          showExposion(t_game game, int index);
char            *hscore_path();
long            get_hscore(char *hscore_path);
int             set_hscore(t_game *game, long score);
t_game          showExposion(t_game game, int index);
void            overwrite_hscore(t_player player);
int             write_score(t_game game, t_player player);
char            *score_str(long hscore, char *score_str);
void            freeBegin(t_game game);
void            freeMonster(t_game game);
void            freePlayer(t_player player);
void            freeInfos(t_game game);
t_game          init_monster_player(t_game game);
t_game          init_game(t_game game);
void            renderPlayer(t_game game);
char            *lives_str(long lives, char *lives_str);
t_game          handleEvent(t_game game);
t_game          refresh_score(t_game game);
t_game          refresh_lives(t_game game);
t_game          refresh_hscore(t_game game);


#endif /* __prototypes_h__ */
