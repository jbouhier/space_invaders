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
    
    if (init(gWindow, gScreenSurface)) {
        terminer = 0;
        //loadSurface( "/Users/mouafo/Pictures/space-ship-md.png", gScreenSurface );
        while(!terminer)
        {
            SDL_WaitEvent(&evenements);
            
            if(evenements.window.event == SDL_WINDOWEVENT_CLOSE)
                terminer = 1;
            else if (evenements.window.event != SDL_WINDOWEVENT_CLOSE) {
                
            }
            
        }
    }
    
    end(gWindow, gScreenSurface, gMonster);
    return 0;
}