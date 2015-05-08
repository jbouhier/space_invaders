//
//  main.c
//  space_invaders
//
//  Created by SynxS on 27/03/15.
//  Copyright (c) 2015 ETNA. All rights reserved.
//

#include "main_file.h"


int main(void)
{
    t_game  game;
    int     tempsActuel;
    int     tempsPrecedent;
    int     toWait;
    int     terminer;
    int     gameover;

    terminer = 0;
    gameover = 0;
    tempsActuel = 0;
    tempsPrecedent = 0;

    game = init_screen(game);
    set_hscore(&game, get_hscore(hscore_path()));
    game.hscore_str = score_str(game.high_score, game.hscore_str);
    
    game = showBegin(game);
    while(!terminer)
    {
        while( SDL_PollEvent(&game.Gevenements) >= 0 ) // Error !
        {
            tempsActuel = SDL_GetTicks();
            if(game.Gevenements.window.event == SDL_WINDOWEVENT_CLOSE || game.quit == 1)
                terminer = 1;
            else {
                if (game.begin.state == 1 && gameover == 0) {
                    game = handleBegin(game);
                }
                else {
                    if (game.begin.state == 0 && gameover == 0) {
                        game = showGame(game, tempsActuel, tempsPrecedent);
                    }
                    if (gameover == 1) {
                        game = showEnd(game);
                        exit(100);
                    }
                }
                tempsPrecedent = tempsActuel; /* Le temps "actuel" devient le temps "precedent" pour nos futurs calculs */
            }
            if (game.Gplayer1.lives == -1 || game.Gplayer2.lives == -1 || game.Gmonster[0].monster == NULL)
                gameover = 1;
            
            toWait = SDL_GetTicks() - tempsActuel;
            if ( toWait < 16 )
                SDL_Delay(16 - toWait);
        }
    }

    end(game);
    return 0;
}
