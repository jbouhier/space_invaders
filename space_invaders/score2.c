//
//  score2.c
//  space_invaders
//
//  Created by SynxS on 07/05/15.
//  Copyright (c) 2015 ETNA. All rights reserved.
//

#include "main_file.h"

char  *score_str(long hscore, char *score_str)
{
    size_t  len;
    size_t  i;
    char    *tmp;
    
    sprintf(score_str, "%ld", hscore);
    len = strlen(score_str);
    tmp = malloc(sizeof(char) * 4 + 1);
    
    for (i = 0; i < SCORE_LENGTH - len; i++)
        strcat(tmp, "0");
    
    strcat(tmp, score_str);
    return (tmp);
}