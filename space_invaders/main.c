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
    
    // Debug


    if ( game.Gwindow != NULL) {
        game.Gplayer1.nbr_bullet = 0;
        while(!terminer)
        {
            tempsActuel = SDL_GetTicks();
            SDL_PollEvent(&(game.Gevenements));
            SDL_SetRenderDrawColor( game.Grenderer, 0, 0, 0, 0 );
            
            if (gameover == 1) {
                exit(100);
            }
            if(game.Gevenements.window.event == SDL_WINDOWEVENT_CLOSE)
                terminer = 1;
            else {
                if (game.Gevenements.type == SDL_KEYDOWN) {
                    game.Gplayer1 = movePlayer(game);
                    
                    if(game.Gevenements.key.keysym.sym == SDLK_SPACE && game.Gplayer1.nbr_bullet < 2) {
                        Mix_PlayChannel( -1, game.Gplayer1.bulletGo_sound, 0 );
                        game.Gplayer1.bullet[game.Gplayer1.nbr_bullet].bullet = loadBullet(game);
                        game.Gplayer1.bullet[game.Gplayer1.nbr_bullet].position = init_bulletPos(game.Gplayer1);
                        game.Gplayer1.nbr_bullet++;
                    }
                }
                if (tempsActuel - tempsPrecedent > 15) { /* Si 15 ms se sont écoulées depuis le dernier tour de boucle */
                    game = launch_bullet(game);
                    game = launch_bulletMonster(game);
                    // game.Gmonster = moveMonster(game);

                }
                tempsPrecedent = tempsActuel; /* Le temps "actuel" devient le temps "precedent" pour nos futurs calculs */
            }
            
            if (game.Gplayer1.lives == -1 || game.Gplayer2.lives == -1 || game.Gmonster[0].monster == NULL)
                gameover = 1;
            
            toWait = SDL_GetTicks() - tempsActuel;
            if ( toWait < 16 )
                SDL_Delay(16 - toWait);
            renderAll(game);
        }
        /* This should never happen */
        printf("SDL_WaitEvent error: %s\n", SDL_GetError());
    }

    end(game);
    return 0;
}
