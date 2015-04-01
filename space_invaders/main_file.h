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


SDL_Window* init(SDL_Window *gWindow);
SDL_Texture* init_screen(SDL_Window *gWindow, SDL_Renderer* gRenderer,SDL_Surface* screenSurface);

SDL_Surface *loadSurface( char* path, SDL_Window *gWindow, SDL_Surface *gScreenSurface );


void end(SDL_Window *gWindow, SDL_Surface *gScreenSurface, SDL_Surface *gMonster );
SDL_Texture *loadTexture( char* path, SDL_Window *gWindow, SDL_Renderer* gRenderer);
SDL_Texture *loadPlayer(SDL_Event evenements, SDL_Window *gWindow, SDL_Renderer* gRenderer);
SDL_Rect movePlayer(SDL_Event evenements, SDL_Rect DestR);


#endif
