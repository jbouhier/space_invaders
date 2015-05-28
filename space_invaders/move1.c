//
//  move1.c
//  space_invaders
//
//  Created by Jean-Baptiste Bouhier on 28/05/15.
//  Copyright (c) 2015 ETNA. All rights reserved.
//

#include "prototypes.h"


t_player    movePlayer(t_game game)
{
    switch( game.Gevenements.key.keysym.sym )
    {
        case SDLK_LEFT:
            if ( game.Gplayer1.position.x > 0 )
                game.Gplayer1.position.x -= 5;
            break;
            
        case SDLK_RIGHT:
            if ( game.Gplayer1.position.x < 761 )
                game.Gplayer1.position.x += 5;
            break;
        default:
            break;
    }
    
    return (game.Gplayer1);
}


t_game  moveMonster(t_game game)
{
    int i;
    
    for (i = 0; game.Gmonster[i].monster != NULL; i++)
    {
        if(game.Gmonster[i].flagpositon == 1)        //check si l'objet doit se déplacer vers la gauche
            game = moveMonsterLeft(game, i);
        else   //Check si l'objet doit se déplacer vers la droite
            game = moveMonsterRight(game, i);
    }
    
    return (game);
}


t_game  moveMonsterLeft(t_game game, int i)
{
    
    if(game.Gmonster[i].position.x > 0)
        game.Gmonster[i].position.x -= game.monster_speed;
    else
    {
        game.Gmonster[i].flagpositon = 0;
        if (game.monster_speed < 3)
            game.Gmonster[i].position.y += (20 * game.monster_speed);
        else
            game.Gmonster[i].position.y += (20 * (game.monster_speed - 1));
    }
    
    return (game);
}


t_game  moveMonsterRight(t_game game, int i)
{
    if(game.Gmonster[i].position.x < 760)
        game.Gmonster[i].position.x += game.monster_speed;
    else
    {
        game.Gmonster[i].flagpositon = 1;
        if (game.monster_speed < 3)
            game.Gmonster[i].position.y += (20 * game.monster_speed);
        else
            game.Gmonster[i].position.y += (20 * (game.monster_speed - 1));
    }
    
    return (game);
}


t_game launch_bullet(t_game game)
{
    int i;
    int j;
    
    for (i = 0; game.Gplayer1.bullet[i].bullet != NULL; i++)
    {
        if (game.Gplayer1.bullet[i].position.y >= 0 && i < 2)
        {
            game.Gplayer1.bullet[i].position.y -= 10;
            for (j = 0; game.Gmonster[j].monster != NULL; j++)
            {
                if (game.Gmonster[j].monster != NULL)
                    game = collideAction(game, i, j);
            }
        }
        else if (i < 2)
            game = deleteBullets(game, i);
    }
    return (game);
}