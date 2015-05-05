//
//  main_file.h
//  space_invaders
//
//  Created by Gatien MOUAFO on 28/03/15.
//  Copyright (c) 2015 ETNA. All rights reserved.
//

#ifndef space_invaders_main_file_h
#define space_invaders_main_file_h

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <SDL2_mixer/SDL_mixer.h>
#include <SDL2_ttf/SDL_ttf.h>

#define PWD getenv("PWD")
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#define LOAD_SOUND_MAX 4
#define MONSTER_NBR 30
#define LOAD_FONT_MAX 1
#define FONT_SIZE 20


struct              bullet_struct
{
    SDL_Texture     *bullet;
    SDL_Rect        position;
} typedef           S_Bullet;

struct              player_struct
{
    SDL_Texture     *player;
    SDL_Rect        position;
    S_Bullet        *bullet;
    Mix_Chunk       *bulletGo_sound;
    Mix_Chunk       *playerExplode_sound;
    int             nbr_bullet;
    int             score;
    SDL_Rect        score_pos;
    SDL_Surface     *surface_score;
    SDL_Texture     *texture_score;
    int             lives;
    SDL_Rect        lives_pos;
    SDL_Surface     *surface_lives;
    SDL_Texture     *texture_lives;
    
} typedef           S_Player;

struct              monster_struct
{
    SDL_Texture     *monster;
    SDL_Texture     *explosion;
    SDL_Rect        position;
    S_Bullet        bullet;
    Mix_Chunk       *monsterExplode_sound;
    Mix_Chunk       *monsterMove_sound;
    bool            flagdown;
    int             nbr_bullet;
} typedef           S_Monster;

struct              game_struct
{
    SDL_Window      *Gwindow;
    SDL_Texture     *Gscreen;
    TTF_Font        *font;
    SDL_Surface     *surface_score_title;
    SDL_Texture     *texture_score_title;
    SDL_Rect        lives_pos;
    SDL_Renderer    *Grenderer;
    SDL_Event       Gevenements;
    S_Player        Gplayer1;
    S_Player        Gplayer2;
    S_Monster       *Gmonster;
    SDL_Rect        score_title_pos;
    int             high_score;
    SDL_Rect        high_score_pos;
    SDL_Surface     *surface_high_score;
    SDL_Texture     *texture_high_score;
} typedef           S_Game;


SDL_Rect        init_position(int x, int y, int h, int w);
SDL_Window      *init(SDL_Window *gWindow);
S_Game          init_screen(S_Game game);
S_Game          init_player(S_Game game);
S_Game          init_text(S_Game game);
SDL_Texture     *loadPlayer(S_Game game);
S_Player        movePlayer(S_Game game);
SDL_Texture     *loadBullet(S_Game game);
SDL_Rect        init_bulletPos(S_Player player);
SDL_Rect        init_bulletMonsterPos(S_Monster monster);
S_Game          launch_bullet(S_Game game);
S_Game          launch_bulletMonster(S_Game game);
void            renderAll(S_Game game);
S_Game          deleteBullets(S_Game game, int index);
void            end(S_Game game);
bool            checkCollision( SDL_Rect a, SDL_Rect b );
S_Game          loadSounds(S_Game game);
char            **AllocateSoundPath(char **paths);
S_Game          loadMonsters(S_Game game);

S_Game showExposion(S_Game game, int index);

#endif
