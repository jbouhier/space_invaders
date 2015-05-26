//
//  events.c
//  space_invaders
//
//  Created by Jean-Baptiste Bouhier on 26/05/15.
//  Copyright (c) 2015 ETNA. All rights reserved.
//

#include "prototypes.h"



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


t_game  selectionBeginHandler(t_game game)
{
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
    return (game);
}