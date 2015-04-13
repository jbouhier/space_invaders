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
    int tempsActuel;
    int tempsPrecedent;
    int terminer;
    
    terminer = 0;
    tempsActuel = 0;
    tempsPrecedent = 0;
    
    game.Gplayer.bullet = malloc(sizeof(S_Bullet) * 100);
    game.Gplayer.position = init_position(760, 560, 35, 35);
    game.Gmonster.position = init_position(360, 60, 55, 55);
    game.Gwindow = init(game.Gwindow);
    game.Grenderer = SDL_CreateRenderer( game.Gwindow, -1, SDL_RENDERER_ACCELERATED );
    game.Gscreen = init_screen( game );

    if ( game.Gwindow != NULL) {
        game.Gplayer.player = loadPlayer(game);
        game.Gmonster.monster = loadPlayer(game);
        game.Gplayer.nbr_bullet = 0;
        while(!terminer)
        {
            SDL_PollEvent(&(game.Gevenements));
            SDL_SetRenderDrawColor( game.Grenderer, 0, 0, 0, 0 );
            
            if(game.Gevenements.window.event == SDL_WINDOWEVENT_CLOSE)
                terminer = 1;
            else {
                if (game.Gevenements.type == SDL_KEYDOWN) {
                    game.Gplayer = movePlayer(game);
                    
                    if(game.Gevenements.key.keysym.sym == SDLK_SPACE && game.Gplayer.nbr_bullet < 2) {
                        game.Gplayer.bullet[game.Gplayer.nbr_bullet].bullet = loadBullet(game);
                        game.Gplayer.bullet[game.Gplayer.nbr_bullet].position = init_bulletPos(game.Gplayer);
                        game.Gplayer.nbr_bullet++;
                    }
                }
                tempsActuel = SDL_GetTicks();
                if (tempsActuel - tempsPrecedent > 5) /* Si 5 ms se sont écoulées depuis le dernier tour de boucle */
                {
                    game = launch_bullet(game);
                }
                tempsPrecedent = tempsActuel; /* Le temps "actuel" devient le temps "precedent" pour nos futurs calculs */
            }

            renderAll(game);
        }
    }

    end(game);
    return 0;
}