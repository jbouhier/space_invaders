//
//  main.c
//  space_invaders
//
//  Created by Jean-Baptiste Bouhier on 27/03/15.
//  Copyright (c) 2015 ETNA. All rights reserved.
//

#include "prototypes.h"


int     main(void)
{
    t_game  game;
    t_time  time;

    init_time(&time);
    game = init_screen(game);
    game = showBegin(game, &(game.text));
    
    while (game.quit != 1)
    {
        while (SDL_PollEvent(&game.Gevenements) >= 0 && game.quit != 1)
        {
            time.tempsActuel = SDL_GetTicks();
            game = handleEvent(game);

            if (game.begin.state == 1 && time.gameover == 0)
                game = handleBegin(game);
            else if (time.gameover == 1)
            {
                game = showGameOver(game);
                printf("GAME OVER\n");
                time.gameover = 0;
            }
            else
            {
                if (game.begin.state == 2)
                    game = showInstruction(game);
                else
                {
                    if (game.begin.state == 0 && time.gameover == 0 && game.quit != 2)
                        game = showGame(game, time.tempsActuel, time.tempsPrecedent);
                    if (game.quit == 2)
                        game = show_pause (game);
                }
                // Le temps "actuel" devient le temps "precedent" pour nos futurs calculs
                time.tempsPrecedent = time.tempsActuel;
            }
            
            if (game.Gplayer1.lives == -1 || game.Gplayer2.lives == -1 || game.Gmonster[0].monster == NULL)
                time.gameover = 1;
            
            time.toWait = SDL_GetTicks() - time.tempsActuel;
            
            if (time.toWait < 16 && game.quit != 1)
                SDL_Delay(16 - time.toWait);
        }
    }

    end(game);
    return (0);
}