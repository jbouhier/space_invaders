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


t_game get_hscore(t_game game, char *hscore_path)
{
    FILE    *fd;
    long    score;
    char    buffer[BUFF_SIZE];
    char    *end;

    if ((fd = fopen(hscore_path, "r")))
    {
        if (fgets(buffer, BUFF_SIZE, fd))
        {
            score = strtol(buffer, &end, 10);
            game.high_score = score;
        }
        fclose(fd);
    }
    else
    {
        fprintf(stderr, "Could not open: %s -> Error: %s\n", hscore_path, strerror(errno));
        SDL_Quit();
        exit(EXIT_FAILURE);
    }
    
    return (game);
}

void    set_hscore(t_game game, char *hscore_path)
{
    FILE    *fd;
    char    score_string[BUFF_SIZE];

    // Create file if it doesn't exists, truncate, fd at pos 0
    if ( (fd = fopen(hscore_path, "w+")) )
    {
        // score_string = sprintf(score_string, "%ld", game.high_score)
        sprintf(score_string, "%ld", game.high_score);
        printf("score_string: %s\n", score_string);
        // fwrite(score_string, 1, sizeof(score_string), fd);
    }
    else
    {
        fprintf(stderr, "Could not open: %s -> Error: %s\n", hscore_path, strerror(errno));
        SDL_Quit();
        exit(EXIT_FAILURE);
    }
    
    fclose(fd);
}

t_game  init_hscore(t_game game)
{
    get_hscore(game, hscore_path());
    return (game);
}