//
//  main.c
//  space_invaders
//
//  Created by SynxS on 27/03/15.
//  Copyright (c) 2015 ETNA. All rights reserved.
//

#include "main.h"


int main(int argc, const char * argv[])
{
    
    int terminer;
    SDL_Event evenements;
    SDL_Rect DestR;
    
    
    DestR.x = 760;
    DestR.y = 560;
    DestR.w = 35;
    DestR.h = 35;
    
    gWindow = init(gWindow);
    gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED );
    gTexture = init_screen( gWindow, gRenderer, gScreenSurface);
    
   
    if ( gWindow != NULL) {
        terminer = 0;
        gPlayer = loadPlayer(evenements, gWindow, gRenderer);
        while(!terminer)
        {
            SDL_WaitEvent(&evenements);
            
            if(evenements.window.event == SDL_WINDOWEVENT_CLOSE)
                terminer = 1;
            else {
                DestR = movePlayer(evenements, DestR);
            }
            //Clear screen
            SDL_RenderClear( gRenderer );
            //Render texture to screen
            SDL_RenderCopy( gRenderer, gPlayer, NULL, &DestR );
            //Update screen
            SDL_RenderPresent( gRenderer );
            
            SDL_UpdateWindowSurface( gWindow );
            
        }
    }
    
    end(gWindow, gScreenSurface, gMonster);
    return 0;
}