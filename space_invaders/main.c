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
    int     tempsActuel;
    int     tempsPrecedent;
    int     toWait;
    int     gameover;

    init_time(&tempsActuel, &tempsPrecedent, &gameover);
    game = init_screen(game);
    game = showBegin(game, &(game.text));
    
    // Put init function inside it w/ pointer parameters
    // start_game();

    while (game.quit != 1)
    {
        while (SDL_PollEvent(&game.Gevenements) >= 0 && game.quit != 1)
        {
            tempsActuel = SDL_GetTicks();
            game = handleEvent(game);

            if (game.begin.state == 1 && gameover == 0)
                game = handleBegin(game);
            else if (gameover == 1)
            {
                game = showGameOver(game);
                printf("GAME OVER\n");
                gameover = 0;
            }
            else
            {
                if (game.begin.state == 2)
                    game = showInstruction(game);
                else
                {
                    if (game.begin.state == 0 && gameover == 0 && game.quit != 2)
                        game = showGame(game, tempsActuel, tempsPrecedent);
                    if (game.quit == 2)
                        game = show_pause (game);
                }
                // Le temps "actuel" devient le temps "precedent" pour nos futurs calculs
                tempsPrecedent = tempsActuel;
            }
            
            if (game.Gplayer1.lives == -1 || game.Gplayer2.lives == -1 || game.Gmonster[0].monster == NULL)
                gameover = 1;
            
            toWait = SDL_GetTicks() - tempsActuel;
            
            if (toWait < 16 && game.quit != 1)
                SDL_Delay(16 - toWait);
        }
    }

    end(game);
    return (0);
}