//
//  main.c
//  space_invaders
//
//  Created by SynxS on 27/03/15.
//  Copyright (c) 2015 ETNA. All rights reserved.
//

#include "prototypes.h"


int main(void)
{
    t_game  game;
    int     tempsActuel;
    int     tempsPrecedent;
    int     toWait;
    int     gameover;

    gameover = 0;
    tempsActuel = 0;
    tempsPrecedent = 0;

    game = init_screen(game);
    set_hscore(&game, get_hscore(hscore_path()));
    game.hscore_str = score_str(game.high_score, game.hscore_str);

    // Debug to save high score
    printf("game.high_score = %ld\n", game.high_score);
    printf("game.hscore_str: %s\n", game.hscore_str);
    
    game = showBegin(game);
    while(game.quit != 1)
    {
        while( SDL_PollEvent(&game.Gevenements) >= 0 && game.quit != 1 )
        {
            tempsActuel = SDL_GetTicks();
            game = handleEvent(game);

            if (game.begin.state == 1 && gameover == 0)
                game = handleBegin(game);
            else if (gameover == 1)
            {
                game = showEnd(game);
                exit(100);
            }
            else
            {
                if (game.begin.state == 0 && gameover == 0 && game.quit != 2) {
                    game = showGame(game, tempsActuel, tempsPrecedent);
                }
                tempsPrecedent = tempsActuel; /* Le temps "actuel" devient le temps "precedent" pour nos futurs calculs */
            }
            if (game.Gplayer1.lives == -1 || game.Gplayer2.lives == -1 || game.Gmonster[0].monster == NULL)
                gameover = 1;
            
            toWait = SDL_GetTicks() - tempsActuel;
            if ( toWait < 16 && game.quit != 1)
                SDL_Delay(16 - toWait);
        }
    }

    end(game);
    return 0;
}
