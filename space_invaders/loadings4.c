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
        ft_sdlk_up(&(game.begin));
    else if (game.Gevenements.key.keysym.sym == SDLK_DOWN)
        ft_sdlk_down(&(game.begin));
    
    if (game.Gevenements.key.keysym.sym == SDLK_RETURN ||
        game.Gevenements.key.keysym.sym == SDLK_RETURN2)
    {
        if (game.begin.selected_option_position.y ==
            game.begin.play_with_1_position.y + 10)
            game.begin.state = 0;
        else if (game.begin.selected_option_position.y ==
                 game.begin.instruction_position.y + 10)
            game.begin.state = 2;
        else
            game.quit = 1;
    }
    
    return (game);
}


void    ft_sdlk_up(t_begin *begin)
{
    if (begin->selected_option_position.y == begin->high_score_position.y + 10)
        begin->selected_option_position.y = begin->play_with_1_position.y + 10;
    else if (begin->selected_option_position.y == begin->quit_position.y + 10)
        begin->selected_option_position.y = begin->instruction_position.y + 10;
    else if (begin->selected_option_position.y == begin->instruction_position.y + 10)
        begin->selected_option_position.y = begin->high_score_position.y + 10;
}


void    ft_sdlk_down(t_begin *begin)
{
    if (begin->selected_option_position.y == begin->play_with_1_position.y + 10)
        begin->selected_option_position.y = begin->high_score_position.y + 10;
    else if (begin->selected_option_position.y ==
             begin->high_score_position.y + 10)
        begin->selected_option_position.y = begin->instruction_position.y + 10;
    else if (begin->selected_option_position.y == begin->instruction_position.y + 10)
        begin->selected_option_position.y = begin->quit_position.y + 10;
}