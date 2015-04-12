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

struct bullet_struct
{
    SDL_Texture  *bullet;
    SDL_Rect position;
} typedef S_Bullet;

struct player_struct
{
    SDL_Texture  *player;
    SDL_Rect position;
    S_Bullet *bullet;
} typedef S_Player;

struct monster_struct
{
    SDL_Texture  *monster;
    SDL_Rect position;
    S_Bullet *bullet;
} typedef S_Monster;

struct game_struct
{
    SDL_Window *Gwindow;
    SDL_Texture *Gscreen;
    SDL_Renderer *Grenderer;
    SDL_Event Gevenements;
    S_Player  Gplayer;
    S_Monster Gmonster;
    int Gscore;
    int Glifes;
} typedef S_Game;


SDL_Rect        init_position(int x, int y, int h, int w);
SDL_Window      *init(SDL_Window *gWindow);
SDL_Texture     *init_screen(S_Game game);
SDL_Texture     *loadPlayer(S_Game game);
S_Player        movePlayer(S_Game game);
SDL_Texture     *loadBullet(S_Game game);
SDL_Rect        init_bulletPos(S_Player player);
S_Game          launch_bullet(S_Game game);
void            renderAll(S_Game game);

void end(S_Game game);
SDL_Texture *loadTexture( char* path, SDL_Window *gWindow, SDL_Renderer* gRenderer);


/* 
**
** IN FILE MOUVEMENT.C
** FUNCTIONS THAT DEALS WITH ANY KIND OF MOUVEMENT IN THE WINDOW
**
*/

//SDL_Rect launch_bullet(SDL_Event evenements,SDL_Texture *bullet, SDL_Renderer* gRenderer,  SDL_Rect DestR);
SDL_Rect autoMoveBulletPlayer(SDL_Texture *bullet, SDL_Renderer* gRenderer, SDL_Rect DestR);


#endif
