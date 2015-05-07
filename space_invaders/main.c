 //
//  main.c
//  space_invaders
//
//  Created by SynxS on 27/03/15.
//  Copyright (c) 2015 ETNA. All rights reserved.
//

#include "main_file.h"


int main(int argc, const char * argv[])
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
    if ( game.Gwindow != NULL) {
        game = showBegin(game);
        while(!terminer)
        {
            tempsActuel = SDL_GetTicks();
            SDL_PollEvent(&(game.Gevenements));
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
                
		if (tempsActuel - tempsPrecedent > 15) { /* Si 15 ms se sont écoulées depuis le dernier tour de boucle */
                    game = launch_bullet(game);
                    game = launch_bulletMonster(game);
                    game = moveMonster(game);
                }
                tempsPrecedent = tempsActuel; /* Le temps "actuel" devient le temps "precedent" pour nos futurs calculs */
            }
            tempsPrecedent = tempsActuel; /* Le temps "actuel" devient le temps "precedent" pour nos futurs calculs */
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
