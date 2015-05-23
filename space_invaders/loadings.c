//
//  loadings.c
//  space_invaders
//
//  Created by Gatien MOUAFO on 27/03/15.
//  Copyright (c) 2015 ETNA. All rights reserved.
//

#include "prototypes.h"
int i;
int j;
int x;
int y;

SDL_Texture *loadTexture(char* path, SDL_Renderer* gRenderer)
{
    SDL_Texture* newTexture;
    //Load image at specified path
    SDL_Surface* loadedSurface;
    
    newTexture = NULL;

    loadedSurface = IMG_Load( path );
    if( loadedSurface == NULL )
    {
        printf( "Unable to load image %s! SDL_image Error: %s\n", path, IMG_GetError() );
    }
    else
    {
        //Create texture from surface pixels

        newTexture = SDL_CreateTextureFromSurface( gRenderer, loadedSurface );
        if( newTexture == NULL )
        {
            printf( "Unable to create texture from %s! SDL Error: %s\n", path, SDL_GetError() );
        }

        //Get rid of old loaded surface
        SDL_FreeSurface( loadedSurface );
    }

    return newTexture;
}

SDL_Texture *loadPlayer(t_game game)
{
    //Loading success flag
    SDL_Texture* player;
    char        *ship_rel_path = "/../../../images/ship.png";
    char        *ship;
    
    // Create and malloc ship full path string
    ship = malloc ((sizeof(char) * strlen(PWD) + strlen(ship_rel_path)) + 1);
    strcpy(ship, PWD);
    strcat(ship, ship_rel_path);
    
    //Load ship PNG texture
    player = loadTexture("/../../../images/ship.png", game.Grenderer);
    if( player == NULL )
        printf( "Failed to load texture image!\n" );

    return player;
}


SDL_Texture *loadBullet(t_game game)
{
    //Loading success flag
    bool success = true;
    SDL_Texture* bullet;
    

    //Load PNG texture
    bullet = loadTexture("/../../../images/bullet.png", game.Grenderer);

    if( bullet == NULL )
    {
        printf( "Failed to load texture image!\n" );
        success = false;
    }
    

    return bullet;
}

t_game loadMonsters(t_game game)
{
    
    SDL_Surface *loadedSurface;

    x = 10;
    y = 100;

    loadedSurface = IMG_Load( "/../../../images/monster1.png" );
    if( loadedSurface == NULL )
        printf( "Unable to load image %s! SDL_image Error: %s\n", "/../../../images/monster1.png", IMG_GetError() );
    else {
        for (i = 0; i < MONSTER_NBR; i++) {
            game.Gmonster[i].monster = SDL_CreateTextureFromSurface ( game.Grenderer, loadedSurface);
            if( game.Gmonster[i].monster == NULL ) {
                printf( "Failed to load texture image %s for the monsters! SDL Error: %s\n", "/../../../images/monster1.png", SDL_GetError()  );
            }
            game.Gmonster[i].position = init_position(x, y, 20, 20);
            if (y < 110)
                game.Gmonster[i].score = 30;
            else if (y > 110 && y < 180)
                game.Gmonster[i].score = 20;
            else
                game.Gmonster[i].score = 10;

            if ((i + 1) % 10 != 0 || i == 0) {
                x += 30;
            }
            else {
                x = 10;
                y += 30;
            }
        }
        SDL_FreeSurface( loadedSurface );
    }

    return game;
}

t_game loadSounds(t_game game)
{
    char **paths;
    
    paths = malloc (sizeof(*paths) * LOAD_SOUND_MAX);
    paths = AllocateSoundPath(paths);

    game.Gplayer1.playerExplode_sound = Mix_LoadWAV( "/../../../sounds/explosion.wav" );
    game.Gplayer1.bulletGo_sound = Mix_LoadWAV( "/../../../sounds/invaderkilled.wav" );

    for (i = 0; game.Gmonster[i].monster != NULL; i++) {
        game.Gmonster[i].monsterExplode_sound = Mix_LoadWAV( "/../../../sounds/shoot.wav" );
        game.Gmonster[i].monsterMove_sound = Mix_LoadWAV( "/../../../sounds/MoveMonster.wav" );
    }

    if(game.Gplayer1.playerExplode_sound == NULL)
        fprintf(stderr,"Could not load %s\n", paths[0]);

    free(paths);

    return game;
}


char **AllocateSoundPath(char **paths)
{
    paths[0] = "/../../../sounds/explosion.wav";
    paths[1] = "/../../../sounds/invaderkilled.wav";
    paths[2] = "/../../../sounds/shoot.wav";
    paths[3] = "/../../../sounds/MoveMonster.wav";
    
    return paths;
}

t_game showExposion(t_game game, int index)
{
    
    game.Gmonster[index].explosion = loadTexture("/../../../images/explosion.png", game.Grenderer);
    game.Gmonster[index].timeShowExplosion = SDL_GetTicks();
    
    if (game.Gplayer1.player != NULL && game.Gplayer1.lives > -1)
    {
        game.Gplayer1.score += game.Gmonster[index].score;
        render_score(&(game.Gplayer1), game.text, game.Grenderer);
    }
    else
        game.Gplayer2.score += game.Gmonster[index].score;
    
    return (game);
}


SDL_Texture *loadMonster(SDL_Renderer* gRenderer)
{
    //Loading success flag
    bool success = true;
    SDL_Texture* monster;
    
    monster = loadTexture( "/../../../images/monster2.bmp", gRenderer);
    
    if (monster == NULL){
        printf( "Failed to load texture image!\n" );
        success = false;
    }
    return (monster);
}

/*
 **  Fonction qui affiche l'interface qui permet de debuter le jeux.
 **  L'utilisateur doit cliquer sur commencer le jeux pour passer a l'interface du jeux et jouer
 */
t_game    showBegin(t_game game)
{
    SDL_Colour text_color = { 255, 255, 255, 0 };
    game.Gscreen = loadTexture( "/../../../images/background/main_menu.png", game.Grenderer );
    game.begin.logo = loadTexture( "/../../../images/background/logo.png", game.Grenderer );
    game.begin.selected_option = loadTexture( "/../../../images/background/selection.png", game.Grenderer );
    game.begin.logo_position = init_position(120, 100, 150, 500);
    game.begin.state = 1;
    game.begin.surface_play = TTF_RenderText_Solid(game.text.font, "     Play      ", text_color);
    game.begin.play_with_1 = SDL_CreateTextureFromSurface(game.Grenderer, game.begin.surface_play);
    game.begin.play_with_1_position = init_position(265, game.begin.logo_position.y + 200, 50, 250);
    game.begin.surface_play = TTF_RenderText_Solid(game.text.font, "    Quit    ", text_color);
    game.begin.quit = SDL_CreateTextureFromSurface(game.Grenderer, game.begin.surface_play);
    game.begin.surface_play = TTF_RenderText_Solid(game.text.font, "  High Score   ", text_color);
    game.begin.high_score = SDL_CreateTextureFromSurface(game.Grenderer, game.begin.surface_play);
    game.quit = 0;
    game.begin.high_score_position = init_position(game.begin.play_with_1_position.x, game.begin.play_with_1_position.y + 50,
                                                   game.begin.play_with_1_position.h, game.begin.play_with_1_position.w);
    game.begin.quit_position = init_position(game.begin.high_score_position.x, game.begin.high_score_position.y + 50,
                                             game.begin.high_score_position.h, game.begin.high_score_position.w);
    game.begin.selected_option_position = init_position(game.begin.play_with_1_position.x - 100,
                                                        game.begin.play_with_1_position.y + 10, 30, 100);
    game.begin.play_with_2 = NULL;
    renderBegin(game);

    return game;
}


void    renderBegin(t_game game)
{
    int checkResult;

    checkResult = checkBeginTexture(game.begin);

    if (checkResult == 1) {
        SDL_RenderClear( game.Grenderer );
        SDL_RenderCopy( game.Grenderer, game.Gscreen, NULL, NULL );
        SDL_RenderCopy( game.Grenderer, game.begin.logo, NULL, &(game.begin.logo_position) );
        SDL_RenderCopy( game.Grenderer, game.begin.play_with_1, NULL, &(game.begin.play_with_1_position) );
        SDL_RenderCopy( game.Grenderer, game.begin.high_score, NULL, &(game.begin.high_score_position) );
        SDL_RenderCopy( game.Grenderer, game.begin.quit, NULL, &(game.begin.quit_position) );
        SDL_RenderCopy( game.Grenderer, game.begin.selected_option, NULL, &(game.begin.selected_option_position) );
        SDL_RenderPresent( game.Grenderer );
        SDL_UpdateWindowSurface( game.Gwindow );
    }
}

int     checkBeginTexture(t_begin beginGame) {
    if (beginGame.high_score == NULL)
        printf("High score Text's Texture is NULL. Will not render the game\n");

    if (beginGame.logo == NULL)
        printf("logo Texture is NULL. Will not render the game\n");

    if (beginGame.play_with_1 == NULL)
        printf("the Play Text's Texture is NULL. Will not render the game\n");

    if (beginGame.quit == NULL)
        printf("the quit Text's Texture is NULL. Will not render the game\n");

    if (beginGame.selected_option == NULL)
        printf("the arrow Texture is NULL. Will not render the game\n");

    if (beginGame.high_score != NULL && beginGame.logo != NULL && beginGame.quit != NULL &&
        beginGame.play_with_1 != NULL && beginGame.selected_option != NULL) {
        return 1;
    }
    return 0;
}

t_game  handleBegin(t_game game) {
    while (SDL_WaitEvent(&game.Gevenements)) {
        if(game.Gevenements.type == SDL_MOUSEMOTION)
            game = selectionBeginHandler(game);

        if (game.Gevenements.type == SDL_KEYDOWN)
            game = KeyBeginHandler(game);

        renderBegin(game);
        if(game.Gevenements.type == SDL_MOUSEBUTTONDOWN && game.Gevenements.button.button == SDL_BUTTON_LEFT) {
            if( game.Gevenements.button.x >= game.begin.play_with_1_position.x &&
               game.Gevenements.button.x <= game.begin.play_with_1_position.x + game.begin.play_with_1_position.w &&
               game.Gevenements.button.y >= game.begin.play_with_1_position.y &&
               game.Gevenements.button.y <= game.begin.play_with_1_position.y + game.begin.play_with_1_position.h)
            {
                game.begin.state = 0;
            }

            if( game.Gevenements.button.x >= game.begin.quit_position.x &&
               game.Gevenements.button.x <= game.begin.quit_position.x + game.begin.quit_position.w &&
               game.Gevenements.button.y >= game.begin.quit_position.y &&
               game.Gevenements.button.y <= game.begin.quit_position.y + game.begin.quit_position.h)
            {
                game.quit = 1;
            }
        }
        if (game.begin.state == 0 || game.quit == 1) {
            return game;
        }
    }
    return game;
}

t_game  KeyBeginHandler(t_game game) {
    if( game.Gevenements.key.keysym.sym == SDLK_UP) {
        if ( game.begin.selected_option_position.y == game.begin.high_score_position.y + 10)
            game.begin.selected_option_position.y = game.begin.play_with_1_position.y + 10;
        else if (game.begin.selected_option_position.y == game.begin.quit_position.y + 10)
            game.begin.selected_option_position.y = game.begin.high_score_position.y + 10;
    }
    else if( game.Gevenements.key.keysym.sym == SDLK_DOWN) {
        if ( game.begin.selected_option_position.y == game.begin.play_with_1_position.y + 10)
            game.begin.selected_option_position.y = game.begin.high_score_position.y + 10;
        else if (game.begin.selected_option_position.y == game.begin.high_score_position.y + 10)
            game.begin.selected_option_position.y = game.begin.quit_position.y + 10;
    }

    if (game.Gevenements.key.keysym.sym == SDLK_RETURN || game.Gevenements.key.keysym.sym == SDLK_RETURN2) {
        if ( game.begin.selected_option_position.y == game.begin.play_with_1_position.y + 10)
            game.begin.state = 0;
        //else if (game.begin.selected_option_position.y == game.begin.high_score_position.y + 10)
            // TODO Script pour l'affichage des highscores
        else
            game.quit = 1;
    }

    return game;
}

t_game  selectionBeginHandler(t_game game) {
    SDL_Cursor* cursor;
    cursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_ARROW);
    if( game.Gevenements.motion.x >= game.begin.play_with_1_position.x &&
       game.Gevenements.motion.x <= game.begin.play_with_1_position.x + game.begin.play_with_1_position.w) {
        if ( game.Gevenements.motion.y >= game.begin.play_with_1_position.y &&
            game.Gevenements.motion.y <= game.begin.play_with_1_position.y + game.begin.play_with_1_position.h) {
            game.begin.selected_option_position.y = game.begin.play_with_1_position.y + 10;
            cursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_HAND);
        }
        else if (game.Gevenements.motion.y >= game.begin.high_score_position.y &&
                 game.Gevenements.motion.y <= game.begin.high_score_position.y + game.begin.high_score_position.h) {
            game.begin.selected_option_position.y = game.begin.high_score_position.y + 10;
            cursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_HAND);
        }
        else {
            game.begin.selected_option_position.y = game.begin.quit_position.y + 10;
            cursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_HAND);
        }
    }

    SDL_SetCursor(cursor);
    return game;
}
