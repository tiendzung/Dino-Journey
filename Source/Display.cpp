//
//  Display.cpp
//  Project Game
//
//  Created by Nguyễn Tiến Dũng on 4/22/22.
//  Copyright © 2022 Nguyễn Tiến Dũng. All rights reserved.
//

#include "Display.h"

SDL_Texture* loadTexture(string path, SDL_Renderer* &g_renderer )
{
    SDL_Texture* newTexture = NULL;
    SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
    if ( loadedSurface == NULL )
        logSDLError("Unable to load image " + path + " SDL_image Error: ", IMG_GetError());
    else
    {
//        SDL_RenderPresent(g_renderer);
        newTexture = SDL_CreateTextureFromSurface( g_renderer, loadedSurface );
        if( newTexture == NULL )
            logSDLError("Unable to create texture from " + path + " SDL Error: ", SDL_GetError());
        SDL_FreeSurface( loadedSurface );
    }
    return newTexture;
}
