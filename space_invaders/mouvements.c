//
//  mouvements.c
//  space_invaders
//
//  Created by Gatien MOUAFO on 01/04/15.
//  Copyright (c) 2015 ETNA. All rights reserved.
//

#include "main_file.h"



S_Player movePlayer(S_Game game) {
    switch( game.Gevenements.key.keysym.sym )
    {
        case SDLK_LEFT:
            if ( game.Gplayer.position.x > 0 ) {
                game.Gplayer.position.x -= 1;
            }
            break;
            
        case SDLK_RIGHT:
            if ( game.Gplayer.position.x < 761 ) {
                game.Gplayer.position.x += 1;
            }
            break;
        default:
            break;
    }
    
    return game.Gplayer;
   // SDL_RenderCopy( gRenderer, gPlayer, NULL, &DestR );    
}


S_Game launch_bullet(S_Game game) {
    
    int i;
    
    for (i = 0; game.Gplayer.bullet[i].bullet != NULL; i++) {
        if (game.Gplayer.bullet[i].position.y >= 0) {
            game.Gplayer.bullet[i].position.y -= 2; /* On bouge la balle */
        }
        else{
            game = deleteBullets(game, i);
        }
    }
    return game;
}

S_Game deleteBullets(S_Game game, int index) {
    int i;
    
    for (i = index; game.Gplayer.bullet[i].bullet != NULL; i++) {
        game.Gplayer.bullet[i] = game.Gplayer.bullet[i + 1];
       // if (game.Gplayer.bullet[i + 1].bullet == NULL) {
         //   SDL_DestroyTexture(game.Gplayer.bullet[i].bullet);
           // game.Gplayer.bullet[i].bullet = NULL;
        //}
    }
    if (i > 0) {
        game.Gplayer.nbr_bullet = i - 1;
    }
    
    
    return game;
}


