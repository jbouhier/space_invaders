//
//  mouvements.c
//  space_invaders
//
//  Created by Gatien MOUAFO on 01/04/15.
//  Copyright (c) 2015 ETNA. All rights reserved.
//

#include "prototypes.h"


t_player movePlayer(t_game game) {
    switch( game.Gevenements.key.keysym.sym )
    {
        case SDLK_LEFT:
            if ( game.Gplayer1.position.x > 0 ) {
                game.Gplayer1.position.x -= 5;
            }
            break;
            
        case SDLK_RIGHT:
            if ( game.Gplayer1.position.x < 761 ) {
                game.Gplayer1.position.x += 5;
            }
            break;
        default:
            break;
    }

    return game.Gplayer1;
}

t_game moveMonster(t_game game)
{
    int i;

    for (i = 0; game.Gmonster[i].monster != NULL; i++) {
        if(game.Gmonster[i].flagpositon == 1)        //check si l'objet doit se déplacer vers la gauche
        {
            if(game.Gmonster[i].position.x > 0)
                game.Gmonster[i].position.x -= game.monster_speed;
            else{
                game.Gmonster[i].flagpositon = 0;
                game.Gmonster[i].position.y += 20;
            }
            
        }
        else   //Check si l'objet doit se déplacer vers la droite
        {
            if(game.Gmonster[i].position.x < 760)
                game.Gmonster[i].position.x += game.monster_speed;
            else{
                game.Gmonster[i].flagpositon = 1;
                game.Gmonster[i].position.y += 20;
            }
        }
    }

    return game;
}




t_game launch_bullet(t_game game) {
    int i;
    int j;

    for (i = 0; game.Gplayer1.bullet[i].bullet != NULL; i++) {
        if (game.Gplayer1.bullet[i].position.y >= 0) {
            game.Gplayer1.bullet[i].position.y -= 10;
            for (j = 0; game.Gmonster[j].monster != NULL; j++) {
                if (game.Gmonster[j].monster != NULL) {
                    if (checkCollision( game.Gmonster[j].position, game.Gplayer1.bullet[i].position )) {
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


t_game launch_bulletMonster(t_game game) {
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

    if (i == 0) {
        // No monsters. The player won
        SDL_Delay(5000);
        game = loadMonsters(game);
        if (game.monster_speed < 3)
            game.monster_speed += 1;
        i = 50;
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
            if (checkCollision( game.Gplayer1.position, game.Gmonster[MonsterToLaunch].bullet.position )) {
                Mix_PlayChannel( -1, game.Gplayer1.playerExplode_sound, 0 );
                printf("A monster has hit the player!\n");
                printf("Lifes %d\n", game.Gplayer1.lives);
                SDL_DestroyTexture(game.Gplayer1.player);
                game.Gplayer1.player = NULL;
                
                if (game.Gplayer1.lives == -1)
                {
                    printf("GAME OVER\n");
                }
                
                game.Gplayer1.lives--;
                renderAll(game);
                SDL_Delay(1500);
                game.Gplayer1.player = loadPlayer(game);
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


t_game deleteBullets(t_game game, int index) {
    int i;

    SDL_DestroyTexture(game.Gplayer1.bullet[index].bullet); // Error !

    for (i = index; game.Gplayer1.bullet[i].bullet != NULL; i++) {
        game.Gplayer1.bullet[i] = game.Gplayer1.bullet[i + 1];
    }
    if (i > 0) {
        game.Gplayer1.nbr_bullet = i - 1;
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
