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
                game.Gplayer.position.x -= 5;
            }
            break;
            
        case SDLK_RIGHT:
            if ( game.Gplayer.position.x < 761 ) {
                game.Gplayer.position.x += 5;
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
                        SDL_DestroyTexture(game.Gmonster[j].explosion);
                        if (game.Gmonster[j].bullet.bullet != NULL && game.Gmonster[j].bullet.position.y <= 560) {
                            if (game.Gmonster[j + 1].monster != NULL) {
                                game.Gmonster[j + 1].bullet = game.Gmonster[j].bullet;
                            }
                            else if (game.Gmonster[j - 1].monster != NULL) {
                                game.Gmonster[j - 1].bullet = game.Gmonster[j].bullet;
                            }
                        }
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


S_Game launch_bulletMonster(S_Game game) {
    int i;
    int bulletOn;
    int MonsterToLaunch;
    
    bulletOn = 0;
    MonsterToLaunch = 0;
    for (i = 0; game.Gmonster[i].monster != NULL; i++) {
        if (game.Gmonster[i].bullet.bullet != NULL) {
            bulletOn++;
            MonsterToLaunch = i;
        }
    }
    // Launch bullet of the monster when no other bullet have being launched by one of them
    if (bulletOn == 0) {
        MonsterToLaunch = rand() % i;
        for (i = 0; game.Gmonster[i].monster != NULL; i++) {
            if (game.Gmonster[i].position.x == game.Gmonster[MonsterToLaunch].position.x &&
                game.Gmonster[i].position.y > game.Gmonster[MonsterToLaunch].position.y) {
                MonsterToLaunch = i;
            }
        }
        game.Gmonster[MonsterToLaunch].bullet.bullet = loadBullet(game);
        game.Gmonster[MonsterToLaunch].bullet.position = init_bulletMonsterPos(game.Gmonster[MonsterToLaunch]);
    }
    else {
        if (game.Gmonster[MonsterToLaunch].bullet.position.y <= 560) {
            game.Gmonster[MonsterToLaunch].bullet.position.y += 5;
            if (checkCollision( game.Gplayer.position, game.Gmonster[MonsterToLaunch].bullet.position )) {
                Mix_PlayChannel( -1, game.Gplayer.playerExplode_sound, 0 );
                printf("A monster has hit the player!\n");
                printf("Lifes %d\n", game.lifes);
                SDL_DestroyTexture(game.Gplayer.player);
                game.Gplayer.player = NULL;
                
                if (game.lifes == -1)
                {
                    printf("GAME OVER\n");
                    end(game);
                }
                
                game.lifes--;
                renderAll(game);
                SDL_Delay(3000);
                game.Gplayer.player = loadPlayer(game);
                SDL_DestroyTexture(game.Gmonster[MonsterToLaunch].bullet.bullet);
                game.Gmonster[MonsterToLaunch].bullet.bullet = NULL;
            }
        }
        else {
            SDL_DestroyTexture(game.Gmonster[MonsterToLaunch].bullet.bullet);
            game.Gmonster[MonsterToLaunch].bullet.bullet = NULL;
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
