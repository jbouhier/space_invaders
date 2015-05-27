//
//  loadings1.c
//  space_invaders
//
//  Created by Gatien MOUAFO on 27/03/15.
//  Copyright (c) 2015 ETNA. All rights reserved.
//

#include "prototypes.h"


SDL_Surface     *get_surface(char *path)
{
    SDL_Surface *surf;
    
    surf = IMG_Load(path);
    
    if (surf == NULL)
    {
        printf( "Unable to load image %s! SDL_image Error: %s\n",
               path, IMG_GetError() );
        SDL_Quit();
        exit(EXIT_FAILURE);
    }

    return (surf);
}


t_game  loadMonsters(t_game game)
{
    int i;
    int x;
    int y;
    
    x = 10;
    y = 100;
    SDL_Surface *surf;
    
    surf = get_surface("/../../../images/monster1.png");
    
    for (i = 0; i < MONSTER_NBR; i++)
        tex_monster(&game, i, &x, &y, surf);
        
    SDL_FreeSurface(surf);
    return (game);
}


void    tex_monster(t_game *game, int i, int *x, int *y, SDL_Surface *surf)
{
    game->Gmonster[i].monster = SDL_CreateTextureFromSurface(game->Grenderer, surf);
    if (game->Gmonster[i].monster == NULL)
    {
        printf( "Load texture error %s for the monsters! SDL Error: %s\n",
               "/../../../images/monster1.png", SDL_GetError() );
        SDL_Quit();
        exit(EXIT_FAILURE);
    }
    game->Gmonster[i].position = init_position(*x, *y, 20, 20);
    if (*y < 110)
        game->Gmonster[i].score = 30;
    else if (*y > 110 && *y < 180)
        game->Gmonster[i].score = 20;
    else
        game->Gmonster[i].score = 10;
    
    if ((i + 1) % 10 != 0 || i == 0)
        *x += 30;
    else
    {
        *x = 10;
        *y += 30;
    }
}


t_game  handleBegin(t_game game)
{
    while (SDL_WaitEvent(&game.Gevenements))
    {
        if (game.Gevenements.type == SDL_MOUSEMOTION)
            game = selectionBeginHandler(game);

        if (game.Gevenements.type == SDL_KEYDOWN)
            game = KeyBeginHandler(game);

        renderBegin(game);
        if (game.Gevenements.type == SDL_MOUSEBUTTONDOWN &&
            game.Gevenements.button.button == SDL_BUTTON_LEFT)
        {
            left_click(&game);
        }
        if (game.begin.state != 1 || game.quit == 1)
            return (game);
    }
    return (game);
}


void    left_click(t_game *game)
{
    if (game->Gevenements.button.x >= game->begin.play_with_1_position.x &&
        game->Gevenements.button.x <= game->begin.play_with_1_position.x +
        game->begin.play_with_1_position.w &&
        game->Gevenements.button.y >= game->begin.play_with_1_position.y &&
        game->Gevenements.button.y <= game->begin.play_with_1_position.y +
        game->begin.play_with_1_position.h)
    {
        game->begin.state = 0;
    }

    if( game->Gevenements.button.x >= game->begin.instruction_position.x &&
       game->Gevenements.button.x <= game->begin.instruction_position.x +
       game->begin.instruction_position.w &&
       game->Gevenements.button.y >= game->begin.instruction_position.y &&
       game->Gevenements.button.y <= game->begin.instruction_position.y +
       game->begin.instruction_position.h)
    {
        game->begin.state = 2;
    }

    if (game->Gevenements.button.x >= game->begin.quit_position.x &&
        game->Gevenements.button.x <= game->begin.quit_position.x +
        game->begin.quit_position.w &&
        game->Gevenements.button.y >= game->begin.quit_position.y &&
        game->Gevenements.button.y <= game->begin.quit_position.y +
        game->begin.quit_position.h)
    {
        game->quit = 1;
    }
}