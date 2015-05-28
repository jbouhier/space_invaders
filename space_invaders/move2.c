//
//  move2.c
//  space_invaders
//
//  Created by Jean-Baptiste Bouhier on 28/05/15.
//  Copyright (c) 2015 ETNA. All rights reserved.
//

#include "prototypes.h"


bool    checkCollision(SDL_Rect a, SDL_Rect b)
{
    //The sides of the rectangles
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;
    
    //Calculate the sides of rect A
    leftA = a.x;
    rightA = a.x + a.w;
    topA = a.y;
    bottomA = a.y + a.h;
    
    //Calculate the sides of rect B
    leftB = b.x;
    rightB = b.x + b.w;
    topB = b.y;
    bottomB = b.y + b.h;
    //If any of the sides from A are outside of B
    if ( bottomA <= topB )
        return (false);
    
    if ( topA >= bottomB )
        return (false);
    
    if ( rightA <= leftB )
        return (false);
    
    if ( leftA >= rightB )
        return (false);
    
    //If none of the sides from A are outside B
    return (true);
}


t_game  handleEvent(t_game game)
{
    switch (game.Gevenements.key.keysym.sym)
    {
        case SDLK_q:
            if (game.begin.state != 2)
                game.quit = 1;
            break;
        case SDLK_p:
            if (game.begin.state != 2)
                game.quit = 2;
            break;
        case SDLK_l:
            if (game.begin.state != 2)
                game.quit = 0;
            break;
        case SDLK_ESCAPE:
            game.begin.state = 1;
            game.quit = 0;
            break;
        default:
            switch (game.Gevenements.window.event)
            {
                case SDL_WINDOWEVENT_CLOSE:
                    game.quit = 1;
                    break;
                case SDL_WINDOWEVENT_HIDDEN:
                    if (game.begin.state != 2)
                        game.quit = 2;
                    break;
            }
            break;
    }
    return (game);
}


t_game  show_pause(t_game game)
{
    SDL_Rect pos = {(SCREEN_WIDTH / 2) - 100, (SCREEN_HEIGHT / 2) - 50, 200, 100};
    
    SDL_RenderCopy( game.Grenderer, game.begin.pause, NULL, &pos );
    SDL_RenderPresent(game.Grenderer);
    
    return (game);
}


t_game  showInstruction(t_game game)
{
    SDL_Colour text_color = { 255, 255, 255, 0 };
    SDL_Rect pos;
    int i;
    SDL_Texture *instruction[6];
    
    pos = init_position(120, 100, 50, 600);
    game.begin.surface_play = TTF_RenderText_Solid(game.text.font, "<-      :  Player moves left                  ", text_color);
    instruction[0] = SDL_CreateTextureFromSurface(game.Grenderer, game.begin.surface_play);
    game.begin.surface_play = TTF_RenderText_Solid(game.text.font, "->      :  Player moves right                 ", text_color);
    instruction[1] = SDL_CreateTextureFromSurface(game.Grenderer, game.begin.surface_play);
    game.begin.surface_play = TTF_RenderText_Solid(game.text.font, "Space  :  Player shoots (2 bullets at a time)", text_color);
    instruction[2] = SDL_CreateTextureFromSurface(game.Grenderer, game.begin.surface_play);
    game.begin.surface_play = TTF_RenderText_Solid(game.text.font, "p       :  Pause Game                         ", text_color);
    instruction[3] = SDL_CreateTextureFromSurface(game.Grenderer, game.begin.surface_play);
    game.begin.surface_play = TTF_RenderText_Solid(game.text.font, "l         :  Remove game from pause          ", text_color);
    instruction[4] = SDL_CreateTextureFromSurface(game.Grenderer, game.begin.surface_play);
    game.begin.surface_play = TTF_RenderText_Solid(game.text.font, "ESC    :  returns to main menu               ", text_color);
    instruction[5] = SDL_CreateTextureFromSurface(game.Grenderer, game.begin.surface_play);
    
    SDL_RenderClear(game.Grenderer);
    SDL_RenderCopy( game.Grenderer, game.Gscreen, NULL, NULL );
    for (i = 0; i < 6; i++) {
        pos.y += 50;
        if (instruction[i] != NULL) {
            SDL_RenderCopy( game.Grenderer, instruction[i], NULL, &pos );
        }
    }
    SDL_RenderPresent(game.Grenderer);
    
    return (game);
}