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
                game.Gplayer.position.x -= 2;
            }
            break;
            
        case SDLK_RIGHT:
            if ( game.Gplayer.position.x < 761 ) {
                game.Gplayer.position.x += 2;
            }
            break;
        default:
            break;
    }

    return game.Gplayer;
}



S_Game launch_bullet(S_Game game) {
    int i;
    int j;

    for (i = 0; game.Gplayer.bullet[i].bullet != NULL; i++) {
        if (game.Gplayer.bullet[i].position.y >= 0) {
            game.Gplayer.bullet[i].position.y -= 5;
            for (j = 0; game.Gmonster[j].monster != NULL; j++) {
                if (game.Gmonster[j].monster != NULL) {
                    if (checkCollision( game.Gmonster[j].position, game.Gplayer.bullet[i].position )) {
                        Mix_PlayChannel( -1, game.Gmonster[j].monsterExplode_sound, 0 );
                        SDL_DestroyTexture(game.Gmonster[j].monster);
                        game = deleteBullets(game, i);
                        game = showExposion(game, j);
                        renderAll(game);
                        SDL_Delay(100);
                        for (i = j; game.Gmonster[i].monster != NULL; i++) {
                            game.Gmonster[i] = game.Gmonster[i + 1];
                        }
                    }
                }
            }
        }
        else{
            game = deleteBullets(game, i);
        }
    }
    return game;
}

S_Game deleteBullets(S_Game game, int index) {
    int i;

    SDL_DestroyTexture(game.Gplayer.bullet[index].bullet);

    for (i = index; game.Gplayer.bullet[i].bullet != NULL; i++) {
        game.Gplayer.bullet[i] = game.Gplayer.bullet[i + 1];
    }
    if (i > 0) {
        game.Gplayer.nbr_bullet = i - 1;
    }

    return game;
}

bool checkCollision( SDL_Rect a, SDL_Rect b )
{
    //The sides of the rectangles
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;

    //Calculate the sides of rect A
    leftA = a.x;
    rightA = a.x + a.w;
    topA = a.y;
    bottomA = a.y + a.h;

    //Calculate the sides of rect B
    leftB = b.x;
    rightB = b.x + b.w;
    topB = b.y;
    bottomB = b.y + b.h;
    //If any of the sides from A are outside of B
    if ( bottomA <= topB ) {
        return false;
    }
    
    if ( topA >= bottomB ) {
        return false;
    }

    if ( rightA <= leftB ) {
        return false;
    }

    if ( leftA >= rightB ) {
        return false;
    }

    //If none of the sides from A are outside B
    return true;
}