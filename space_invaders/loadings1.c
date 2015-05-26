//
//  loadings1.c
//  space_invaders
//
//  Created by Gatien MOUAFO on 27/03/15.
//  Copyright (c) 2015 ETNA. All rights reserved.
//

#include "prototypes.h"

int i;
int j;
int x;
int y;


t_game  loadMonsters(t_game game)
{
    SDL_Surface *surf;
    x = 10;
    y = 100;
    
    surf = IMG_Load("/../../../images/monster1.png");
    
    if (surf == NULL)
    {
        printf( "Unable to load image %s! SDL_image Error: %s\n",
               "/../../../images/monster1.png", IMG_GetError() );
    }
    else
    {
        for (i = 0; i < MONSTER_NBR; i++)
        {
            game.Gmonster[i].monster = SDL_CreateTextureFromSurface(game.Grenderer, surf);
            if (game.Gmonster[i].monster == NULL)
            {
                printf( "Failed to load texture image %s for the monsters! SDL Error: %s\n",
                       "/../../../images/monster1.png", SDL_GetError() );
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



/*
 **  Fonction qui affiche l'interface qui permet de debuter le jeux.
 **  L'utilisateur doit cliquer sur commencer le jeux pour passer a l'interface du jeux et jouer
 */
t_game    showBegin(t_game game, t_text *t)
{
    game.Gscreen = loadTexture( "/../../../images/background/main_menu.png", game.Grenderer );
    game.begin.logo = loadTexture( "/../../../images/background/logo.png", game.Grenderer );
    game.begin.selected_option = loadTexture( "/../../../images/background/selection.png", game.Grenderer );
    game.begin.logo_position = init_position(120, 100, 150, 500);
    game.begin.state = 1;
    game.begin.surface_play = TTF_RenderText_Solid(game.text.font, "     Play      ", t->color);
    game.begin.play_with_1 = SDL_CreateTextureFromSurface(game.Grenderer, game.begin.surface_play);
    game.begin.play_with_1_position = init_position(265, game.begin.logo_position.y + 200, 50, 250);
    game.begin.surface_play = TTF_RenderText_Solid(game.text.font, "    Quit    ", t->color);
    game.begin.quit = SDL_CreateTextureFromSurface(game.Grenderer, game.begin.surface_play);
    game.begin.surface_play = TTF_RenderText_Solid(game.text.font, "  High Score   ", t->color);
    game.begin.high_score = SDL_CreateTextureFromSurface(game.Grenderer, game.begin.surface_play);
    game.quit = 0;
    game.begin.high_score_position = init_position(game.begin.play_with_1_position.x, game.begin.play_with_1_position.y + 50,
                                                   game.begin.play_with_1_position.h, game.begin.play_with_1_position.w);
    game.begin.quit_position = init_position(game.begin.high_score_position.x, game.begin.high_score_position.y + 50,
                                             game.begin.high_score_position.h, game.begin.high_score_position.w);
    game.begin.selected_option_position = init_position(game.begin.play_with_1_position.x - 100,
                                                        game.begin.play_with_1_position.y + 10, 30, 100);
    game.begin.play_with_2 = NULL;
    renderBegin(game);
    
    return (game);
}


int     checkBeginTexture(t_begin beginGame) {
    if (beginGame.high_score == NULL)
        printf("High score Text's Texture is NULL. Will not render the game\n");

    if (beginGame.logo == NULL)
        printf("logo Texture is NULL. Will not render the game\n");

    if (beginGame.play_with_1 == NULL)
        printf("the Play Text's Texture is NULL. Will not render the game\n");

    if (beginGame.quit == NULL)
        printf("the quit Text's Texture is NULL. Will not render the game\n");

    if (beginGame.selected_option == NULL)
        printf("the arrow Texture is NULL. Will not render the game\n");

    if (beginGame.high_score != NULL && beginGame.logo != NULL && beginGame.quit != NULL &&
        beginGame.play_with_1 != NULL && beginGame.selected_option != NULL) {
        return 1;
    }
    return 0;
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

t_game  selectionBeginHandler(t_game game) {
    SDL_Cursor* cursor;
    cursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_ARROW);
    if( game.Gevenements.motion.x >= game.begin.play_with_1_position.x &&
       game.Gevenements.motion.x <= game.begin.play_with_1_position.x + game.begin.play_with_1_position.w) {
        if ( game.Gevenements.motion.y >= game.begin.play_with_1_position.y &&
            game.Gevenements.motion.y <= game.begin.play_with_1_position.y + game.begin.play_with_1_position.h) {
            game.begin.selected_option_position.y = game.begin.play_with_1_position.y + 10;
            cursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_HAND);
        }
        else if (game.Gevenements.motion.y >= game.begin.high_score_position.y &&
                 game.Gevenements.motion.y <= game.begin.high_score_position.y + game.begin.high_score_position.h) {
            game.begin.selected_option_position.y = game.begin.high_score_position.y + 10;
            cursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_HAND);
        }
        else {
            game.begin.selected_option_position.y = game.begin.quit_position.y + 10;
            cursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_HAND);
        }
    }

    SDL_SetCursor(cursor);
    return game;
}
