//
//  score2.c
//  space_invaders
//
//  Created by Jean-Baptiste Bouhier on 07/05/15.
//  Copyright (c) 2015 ETNA. All rights reserved.
//

#include "prototypes.h"

char  *score_str(long hscore, char *score_str)
{
    size_t  len;
    size_t  i;
    char    *tmp;
    
    score_str = malloc(sizeof(*tmp) * SCORE_LENGTH + 1);
    sprintf(score_str, "%ld", hscore);
    len = strlen(score_str);
    tmp = malloc(sizeof(*tmp) * SCORE_LENGTH + 1);
    
    for (i = 0; i < SCORE_LENGTH - len; i++)
        strcat(tmp, "0");
    
    strcat(tmp, score_str);
    return (tmp);
}


char  *lives_str(long lives, char *lives_str)
{
    lives_str = malloc(sizeof(*lives_str) * LIVES_LENGTH + 1);
    sprintf(lives_str, "%ld", lives);
    
    return (lives_str);
}