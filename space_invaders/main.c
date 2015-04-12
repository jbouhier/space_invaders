//
//  main.c
//  space_invaders
//
//  Created by SynxS on 27/03/15.
//  Copyright (c) 2015 ETNA. All rights reserved.
//

#include "main.h"


int main(int argc, const char * argv[])
{
    S_Game game;
    int nbr_bullet;
    int tempsActuel;
    int tempsPrecedent;
    int terminer;
    
    terminer = 0;
    tempsActuel = 0;
    tempsPrecedent = 0;

    game.Gplayer.position = init_position(760, 560, 35, 35);
    game.Gplayer.bullet = malloc(sizeof(S_Bullet) * 100);
    game.Gwindow = init(game.Gwindow);
    game.Grenderer = SDL_CreateRenderer( game.Gwindow, -1, SDL_RENDERER_ACCELERATED );
    game.Gscreen = init_screen( game );

    if ( game.Gwindow != NULL) {
        game.Gplayer.player = loadPlayer(game);
        nbr_bullet = 0;
        while(!terminer)
        {
            SDL_PollEvent(&(game.Gevenements));
            SDL_SetRenderDrawColor( game.Grenderer, 0, 0, 0, 0 );
            
            if(game.Gevenements.window.event == SDL_WINDOWEVENT_CLOSE)
                terminer = 1;
            else {
                if (game.Gevenements.type == SDL_KEYDOWN) {
                    game.Gplayer = movePlayer(game);
                    
                    if(game.Gevenements.key.keysym.sym == SDLK_SPACE) {
                        game.Gplayer.bullet[nbr_bullet].bullet = loadBullet(game);
                        game.Gplayer.bullet[nbr_bullet].position = init_bulletPos(game.Gplayer);
                        nbr_bullet++;
                    }
                }
                tempsActuel = SDL_GetTicks();
                if (tempsActuel - tempsPrecedent > 18) /* Si 18 ms se sont écoulées depuis le dernier tour de boucle */
                {
                    launch_bullet(game);
                }
                tempsPrecedent = tempsActuel; /* Le temps "actuel" devient le temps "precedent" pour nos futurs calculs */
            }

            renderAll(game);
        }
    }

    end(game);
    return 0;
}