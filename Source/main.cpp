#include <bits/stdc++.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <thread>
#include <chrono>
using namespace std;
#include "Dis.h"
#include "SDL_InitWindow.h"

SDL_Window* g_window = NULL;
SDL_Surface* g_ScreenSurface = NULL;
SDL_Surface* g_background = NULL;
SDL_Renderer* g_renderer = NULL;
SDL_Texture* g_texture = NULL;

const string WINDOW_TITLE = "DINOUSAUR TRAVEL";
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const int RSIZE = 25;
int x = SCREEN_WIDTH/2;
int y = SCREEN_HEIGHT/2;
const int step = 16;

SDL_Texture* loadTexture(string path )
{
    SDL_Texture* newTexture = NULL;
    SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
    if ( loadedSurface == NULL )
        logSDLError("Unable to load image " + path + " SDL_image Error: ", IMG_GetError());
    else
    {
        newTexture = SDL_CreateTextureFromSurface( g_renderer, loadedSurface );
        if( newTexture == NULL )
            logSDLError("Unable to create texture from " + path + " SDL Error: ", SDL_GetError());
        SDL_FreeSurface( loadedSurface );
    }
    return newTexture;
}

void draw(SDL_Renderer* g_renderer, int x,int y)
{
    SDL_Rect rect;
    rect.x = x;
    rect.y = y;
    rect.w = RSIZE;
    rect.h = RSIZE;
    SDL_SetRenderDrawColor(g_renderer, 0, 0 , 0, 0);
    SDL_RenderClear(g_renderer);
    SDL_SetRenderDrawColor(g_renderer, 255, 0 , 0, 0);
    SDL_RenderDrawRect(g_renderer,&rect);
    SDL_RenderPresent(g_renderer);
}
void process(SDL_Event e)
{
    draw(g_renderer,x,y);
    
    if(e.type == SDL_KEYDOWN)
    {
        //            cout << SDL_GetKeyName(e.key.keysym.sym) << "\n";
        switch(e.key.keysym.sym)
        {
            case SDLK_DOWN:
            {
                if(y + step <= SCREEN_HEIGHT - RSIZE) y+=step;
                    break;
            }
            case SDLK_UP:
            {
                if(y - step >= 0) y-=step;
                    break;
            }
            case SDLK_LEFT:
            {
                if(x - step >= 0) x-=step;
                    break;
            }
            case SDLK_RIGHT:
            {
                if(x + step <= SCREEN_WIDTH - RSIZE) x+=step;
                    break;
            }
        }
        draw(g_renderer,x,y);
    }
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
            // process game logic
            // (nothing to process)
            process(event);
            // draw & display
        }
    }
    
    quitSDL(g_window, g_renderer);
    
    return 0;
}
