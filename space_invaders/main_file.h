//
//  main_file.h
//  space_invaders
//
//  Created by Gatien MOUAFO on 28/03/15.
//  Copyright (c) 2015 ETNA. All rights reserved.
//

#ifndef space_invaders_main_file_h
#define space_invaders_main_file_h


/*
 #   /$$$$$$ /$$   /$$  /$$$$$$  /$$       /$$   /$$  /$$$$$$  /$$$$$$  /$$$$$$  /$$   /$$  /$$$$$$
 #  |_  $$_/| $$$ | $$ /$$__  $$| $$      | $$  | $$ /$$__  $$|_  $$_/ /$$__  $$| $$$ | $$ /$$__  $$
 #    | $$  | $$$$| $$| $$  \__/| $$      | $$  | $$| $$  \__/  | $$  | $$  \ $$| $$$$| $$| $$  \__/
 #    | $$  | $$ $$ $$| $$      | $$      | $$  | $$|  $$$$$$   | $$  | $$  | $$| $$ $$ $$|  $$$$$$
 #    | $$  | $$  $$$$| $$      | $$      | $$  | $$ \____  $$  | $$  | $$  | $$| $$  $$$$ \____  $$
 #    | $$  | $$\  $$$| $$    $$| $$      | $$  | $$ /$$  \ $$  | $$  | $$  | $$| $$\  $$$ /$$  \ $$
 #   /$$$$$$| $$ \  $$|  $$$$$$/| $$$$$$$$|  $$$$$$/|  $$$$$$/ /$$$$$$|  $$$$$$/| $$ \  $$|  $$$$$$/
 #  |______/|__/  \__/ \______/ |________/ \______/  \______/ |______/ \______/ |__/  \__/ \______/
 #
 */
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <SDL2_mixer/SDL_mixer.h>

#define ROOT_DIR getenv("PWD")


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
    Mix_Chunk       *playerMove_sound;
    Mix_Chunk       *playerExplode_sound;
    int             nbr_bullet;
    
} typedef           S_Player;

struct              monster_struct
{
    SDL_Texture     *monster;
    SDL_Rect        position;
    S_Bullet        *bullet;
    Mix_Chunk       *monsterExplode_sound;
    int             nbr_bullet;
} typedef           S_Monster;

struct              game_struct
{
    SDL_Window      *Gwindow;
    SDL_Texture     *Gscreen;
    SDL_Renderer    *Grenderer;
    SDL_Event       Gevenements;
    S_Player        Gplayer;
    S_Monster       Gmonster;
    int             Gscore;
    int             Glifes;
} typedef           S_Game;


SDL_Rect        init_position(int x, int y, int h, int w);
SDL_Window      *init(SDL_Window *gWindow);
S_Game          init_screen(S_Game game);
SDL_Texture     *loadPlayer(S_Game game);
S_Player        movePlayer(S_Game game);
SDL_Texture     *loadBullet(S_Game game);
SDL_Rect        init_bulletPos(S_Player player);
S_Game          launch_bullet(S_Game game);
void            renderAll(S_Game game);
S_Game          deleteBullets(S_Game game, int index);
void            end(S_Game game);
bool            checkCollision( SDL_Rect a, SDL_Rect b );
S_Game          loadSounds(S_Game game);

#endif
