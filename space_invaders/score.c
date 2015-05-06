//
//  get_hscore.c
//  space_invaders
//
//  Created by SynxS on 06/05/15.
//  Copyright (c) 2015 ETNA. All rights reserved.
//

#include "main_file.h"

#define HSCORE_FILE_PATH "/../../../game/high_score.txt"
// Score is 4 numbers long + 1 for the NULL terminating string
#define BUFF_SIZE 5

char    *hscore_path()
{
    char    *path;
    
    path =  malloc (strlen(PWD) + strlen(HSCORE_FILE_PATH) + 1);
    strcpy(path, PWD);
    strcat(path, HSCORE_FILE_PATH);
    
    return (path);
}


long get_hscore(char *hscore_path)
{
    FILE    *fd;
    long    score;
    char    buffer[BUFF_SIZE];
    char    *end;
    
    if ((fd = fopen(hscore_path, "r")))
    {
        if (fgets(buffer, BUFF_SIZE, fd))
            score = strtol(buffer, &end, 10);
        fclose(fd);
    }
    else
    {
        fprintf(stderr, "Could not open: %s -> Error: %s\n", hscore_path, strerror(errno));
        SDL_Quit();
        exit(EXIT_FAILURE);
    }
    
    return (score);
}


void    set_hscore(t_game *game, long score)
{
    game->high_score = score;
}


// Use: write_score(game, get_hscore(hscore_path()) );
void    write_score(t_game game, long hscore)
{
    if (game.Gplayer1.score > hscore)
        overwite_hscore(game.Gplayer1);
    else if (game.Gplayer2.score > hscore)
         overwite_hscore(game.Gplayer2);
}


void    overwrite_hscore(t_player player)
{
    FILE    *fd;
    char    buffer[BUFF_SIZE];
    char    *end;
    
    if ((fd = fopen(hscore_path(), "w+")))
    {
        if (fgets(buffer, BUFF_SIZE, fd))
            score = strtol(buffer, &end, 10);
        
        fclose(fd);
    }
    else
    {
        fprintf(stderr, "Could not open: %s -> Error: %s\n", hscore_path(), strerror(errno));
        SDL_Quit();
        exit(EXIT_FAILURE);
    }
}




 


















