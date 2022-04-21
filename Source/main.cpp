//#include "stdafx.h"
#include <bits/stdc++.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <thread>
#include <chrono>
using namespace std;
#include "Dis.h"
#include "SDL_InitWindow.hpp"
SDL_Window* g_window = NULL;
SDL_Surface* g_ScreenSurface = NULL;
SDL_Surface* g_background = NULL;
SDL_Renderer* g_renderer = NULL;
SDL_Texture* g_texture = NULL;

const string WINDOW_TITLE = "DINOUSAUR TRAVEL";
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

SDL_Texture* loadTexture(string path )
{
    SDL_Texture* newTexture = NULL;
    SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
    if ( loadedSurface == NULL )
        logSDLError(std::cout, "Unable to load image " + path + " SDL_image Error: " + IMG_GetError());
    else
    {
        newTexture = SDL_CreateTextureFromSurface( g_renderer, loadedSurface );
        if( newTexture == NULL )
            logSDLError(std::cout, "Unable to create texture from " + path + " SDL Error: " + SDL_GetError());
        SDL_FreeSurface( loadedSurface );
    }
    return newTexture;
}

int main()
{
    initSDL(g_window, g_renderer, WINDOW_TITLE, SCREEN_WIDTH, SCREEN_HEIGHT);
    loadTexture("Resource/anhdep.jpeg");
    
    bool is_running = true;
    SDL_Event event;
    while (is_running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                is_running = false;
            }
            //Game Event
        }
        //                                SDL_Delay(16);
    }
    //            this_thread::sleep_for(chrono::milliseconds(2000));
    quitSDL(g_window, g_renderer);
    
    return 0;
}
