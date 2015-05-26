//
//  loadings1.c
//  space_invaders
//
//  Created by Gatien MOUAFO on 27/03/15.
//  Copyright (c) 2015 ETNA. All rights reserved.
//

#include "prototypes.h"


t_game  loadMonsters(t_game game)
{
    SDL_Surface *surf;
    int i;
    int x;
    int y;
    
    x = 10;
    y = 100;
    
    surf = IMG_Load("/../../../images/monster1.png");
    
    if (surf == NULL)
    {
        printf( "Unable to load image %s! SDL_image Error: %s\n",
               "/../../../images/monster1.png", IMG_GetError() );
        SDL_Quit();
        exit(EXIT_FAILURE);
    }
    else
    {

        for (i = 0; i < MONSTER_NBR; i++)
        {
            game.Gmonster[i].monster = SDL_CreateTextureFromSurface(game.Grenderer, surf);
            if (game.Gmonster[i].monster == NULL)
            {
                printf( "Load texture error %s for the monsters! SDL Error: %s\n",
                       "/../../../images/monster1.png", SDL_GetError() );
                SDL_Quit();
                exit(EXIT_FAILURE);
            }
            game.Gmonster[i].position = init_position(x, y, 20, 20);
            if (y < 110)
                game.Gmonster[i].score = 30;
            else if (y > 110 && y < 180)
                game.Gmonster[i].score = 20;
            else
                game.Gmonster[i].score = 10;

            if ((i + 1) % 10 != 0 || i == 0)
                x += 30;
            else
            {
                x = 10;
                y += 30;
            }
        }
        SDL_FreeSurface(surf);
    }

    return (game);
}


t_game  handleBegin(t_game game) {
    while (SDL_WaitEvent(&game.Gevenements)) {
        if(game.Gevenements.type == SDL_MOUSEMOTION)
            game = selectionBeginHandler(game);

        if (game.Gevenements.type == SDL_KEYDOWN)
            game = KeyBeginHandler(game);

        renderBegin(game);
        if(game.Gevenements.type == SDL_MOUSEBUTTONDOWN && game.Gevenements.button.button == SDL_BUTTON_LEFT) {
            if( game.Gevenements.button.x >= game.begin.play_with_1_position.x &&
               game.Gevenements.button.x <= game.begin.play_with_1_position.x + game.begin.play_with_1_position.w &&
               game.Gevenements.button.y >= game.begin.play_with_1_position.y &&
               game.Gevenements.button.y <= game.begin.play_with_1_position.y + game.begin.play_with_1_position.h)
            {
                game.begin.state = 0;
            }

            if( game.Gevenements.button.x >= game.begin.quit_position.x &&
               game.Gevenements.button.x <= game.begin.quit_position.x + game.begin.quit_position.w &&
               game.Gevenements.button.y >= game.begin.quit_position.y &&
               game.Gevenements.button.y <= game.begin.quit_position.y + game.begin.quit_position.h)
            {
                game.quit = 1;
            }
        }
        if (game.begin.state == 0 || game.quit == 1) {
            return game;
        }
    }
    return game;
}

t_game  KeyBeginHandler(t_game game) {
    if( game.Gevenements.key.keysym.sym == SDLK_UP) {
        if ( game.begin.selected_option_position.y == game.begin.high_score_position.y + 10)
            game.begin.selected_option_position.y = game.begin.play_with_1_position.y + 10;
        else if (game.begin.selected_option_position.y == game.begin.quit_position.y + 10)
            game.begin.selected_option_position.y = game.begin.high_score_position.y + 10;
    }
    else if( game.Gevenements.key.keysym.sym == SDLK_DOWN) {
        if ( game.begin.selected_option_position.y == game.begin.play_with_1_position.y + 10)
            game.begin.selected_option_position.y = game.begin.high_score_position.y + 10;
        else if (game.begin.selected_option_position.y == game.begin.high_score_position.y + 10)
            game.begin.selected_option_position.y = game.begin.quit_position.y + 10;
    }

    if (game.Gevenements.key.keysym.sym == SDLK_RETURN || game.Gevenements.key.keysym.sym == SDLK_RETURN2) {
        if ( game.begin.selected_option_position.y == game.begin.play_with_1_position.y + 10)
            game.begin.state = 0;
        //else if (game.begin.selected_option_position.y == game.begin.high_score_position.y + 10)
            // TODO Script pour l'affichage des highscores
        else
            game.quit = 1;
    }

    return game;
}