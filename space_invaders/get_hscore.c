//
//  get_hscore.c
//  space_invaders
//
//  Created by SynxS on 06/05/15.
//  Copyright (c) 2015 ETNA. All rights reserved.
//

#include <stdio.h>
#include <errno.h>
#include "main_file.h"

#define HSCORE_FILE_PATH "/../../../game/high_score.txt"
#define BUFF_SIZE 5

t_game get_hscore(t_game game)
{
    FILE    *fd;
    char    buffer[BUFF_SIZE];
    
    
    if ((fd = fopen(HSCORE_FILE_PATH, "r")))
    {
        if (fgets(buffer, BUFF_SIZE, fd))
            printf("Debug: %s\n", buffer);
        fclose(fd);
    }
    else
    {
        fprintf(stderr, "Value of errno: %d\n", errno);
        fprintf(stderr, "Error opening file: %s\n", strerror(errno));
        SDL_Quit();
        exit(EXIT_FAILURE);
    }
    
    return (game);
}
