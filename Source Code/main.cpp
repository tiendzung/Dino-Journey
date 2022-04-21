//#include "stdafx.h"
#include <bits/stdc++.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <thread>
#include <chrono>
using namespace std;
SDL_Window* g_windows = NULL;
SDL_Surface* gScreenSurface = NULL;
SDL_Surface* g_background = NULL;

bool loadMedia()
{
    bool success = true;
    g_background = IMG_Load("Source Code/anhdep.jpeg");
    if( g_background == NULL )
    {
        success = false;
        cout << "Failed to load Image!!!\n";
    }
    
    return success;
}
void close()
{
    SDL_FreeSurface( g_background );
    g_background = NULL;
    SDL_DestroyWindow( g_windows );
    g_windows = NULL;
    SDL_Quit();
}

bool init()
{
    bool success = true;
    if( SDL_Init( SDL_INIT_VIDEO ) >= 0 )
    {
        g_windows = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, SDL_WINDOW_SHOWN );
        if( g_windows != NULL )
        {
            gScreenSurface = SDL_GetWindowSurface(g_windows);
        }
    }
    return success;
}

void waitUntilKeyPressed()
{
    SDL_Event e;
    while(true)
    {
        if( SDL_WaitEvent(&e)!=0 && (e.type == SDL_KEYDOWN || e.type == SDL_QUIT) ) //Xac dinh su kien ban phim
            return;
        SDL_Delay(100);
    }
}

int main()
{
    if(init() == true)
    {
        if(loadMedia())
        {
            SDL_BlitSurface( g_background, NULL, gScreenSurface, NULL );
            SDL_UpdateWindowSurface(g_windows);
            //                        waitUntilKeyPressed();
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
        }
    }
    
    close();
    return 0;
}
