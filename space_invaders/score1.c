//
//  score1.c
//  space_invaders
//
//  Created by Jean-Baptiste Bouhier on 06/05/15.
//  Copyright (c) 2015 ETNA. All rights reserved.
//

#include "prototypes.h"

#define HSCORE_FILE_PATH "/../../../game/high_score.txt"
// Score is 4 numbers long + 1 for the NULL terminating string


char    *hscore_path()
{
    char    *path;
    
    path =  malloc (sizeof(*path) * strlen(PWD) + strlen(HSCORE_FILE_PATH) + 1);
    strcpy(path, PWD);
    strcat(path, HSCORE_FILE_PATH);
    
    return (path);
}


long    get_hscore(char *hscore_path)
{
    FILE    *fd;
    char    buffer[SCORE_LENGTH + 1];
    char    *end;
    long    score;
    
    score = 0;
    
    if ((fd = fopen(hscore_path, "r")))
    {
        if (fgets(buffer, SCORE_LENGTH + 1, fd))
            score = strtol(buffer, &end, 10);
        fclose(fd);
    }
    else
    {
        fprintf(stderr, "Could not open: %s -> Error: %s\n",
                hscore_path, strerror(errno));
        SDL_Quit();
        exit(EXIT_FAILURE);
    }
    
    return (score);
}


int     set_hscore(t_game *game, long score)
{
    int success;
    
    success = -1;
    game->text.hscore = score;
    
    if (game->text.hscore == score)
        return (0);
    return (1);
}

// score_str = long 4 + 1 for '\0'
void    overwrite_hscore(t_player player)
{
    FILE    *fd;
    char	score_str[5];
    
    if ((fd = fopen(hscore_path(), "w+")))
    {
        sprintf(score_str, "%ld", player.score);
        fwrite(score_str, 1, sizeof(score_str), fd);
        fclose(fd);
    }
    else
    {
        fprintf(stderr, "Could not open: %s -> Error: %s\n",
                hscore_path(), strerror(errno));
        SDL_Quit();
        exit(EXIT_FAILURE);
    }
}


int     write_score(t_game game, t_player player)
{
    if (player.lives < 0 && player.score > game.text.hscore)
    {
        overwrite_hscore(player);
        return (0);
    }
    else
        return (1);
}