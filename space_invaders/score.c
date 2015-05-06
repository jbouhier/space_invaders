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

t_game get_hscore(t_game game)
{
    FILE    *fd;
    long    score;
    char    buffer[BUFF_SIZE];
    char    *path;
    char    *end;

    path =  malloc (strlen(PWD) + strlen(HSCORE_FILE_PATH) + 1);
    strcpy(path, PWD);
    strcat(path, HSCORE_FILE_PATH);
    
    if ((fd = fopen(path, "r")))
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
        fprintf(stderr, "Could not open: %s -> Error: %s\n", path, strerror(errno));
        SDL_Quit();
        exit(EXIT_FAILURE);
    }
    
    return (game);
}
