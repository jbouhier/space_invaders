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
        game.Gplayer.bullet[i].position.y -= 20; /* On bouge la balle */
    }
    
    return game;
}


SDL_Rect autoMoveBulletPlayer(SDL_Texture *bullet, SDL_Renderer* gRenderer, SDL_Rect DestR) {
    
    SDL_Rect pos;
    pos = DestR;
    //Bullet = gRenderer;
    //printf("time : %d \n", SDL_GetTicks());
    

    
    pos.y -=  (SDL_GetTicks()/30.f) + 3;
    if (pos.y < 0) {
         pos.y =  DestR.y;
     }
    return pos;
    
}



