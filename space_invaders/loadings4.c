//
//  loadings4.c
//  space_invaders
//
//  Created by Jean-Baptiste Bouhier on 27/05/15.
//  Copyright (c) 2015 ETNA. All rights reserved.
//


#include "prototypes.h"


t_game  KeyBeginHandler(t_game game)
{
    if (game.Gevenements.key.keysym.sym == SDLK_UP)
    {
        if (game.begin.selected_option_position.y == game.begin.high_score_position.y + 10)
            game.begin.selected_option_position.y = game.begin.play_with_1_position.y + 10;
        else if (game.begin.selected_option_position.y == game.begin.quit_position.y + 10)
            game.begin.selected_option_position.y = game.begin.high_score_position.y + 10;
    }
    else if (game.Gevenements.key.keysym.sym == SDLK_DOWN)
    {
        if (game.begin.selected_option_position.y == game.begin.play_with_1_position.y + 10)
            game.begin.selected_option_position.y = game.begin.high_score_position.y + 10;
        else if (game.begin.selected_option_position.y == game.begin.high_score_position.y + 10)
            game.begin.selected_option_position.y = game.begin.quit_position.y + 10;
    }
    
    if (game.Gevenements.key.keysym.sym == SDLK_RETURN || game.Gevenements.key.keysym.sym == SDLK_RETURN2)
    {
        if (game.begin.selected_option_position.y == game.begin.play_with_1_position.y + 10)
            game.begin.state = 0;
        //else if (game.begin.selected_option_position.y == game.begin.high_score_position.y + 10)
        // TODO Script pour l'affichage des highscores
        else
            game.quit = 1;
    }
    
    return (game);
}