
#include "CommonFunction.h"
#include "Display.h"
#include "SDL_InitWindow.h"
#include "GameStatus.h"
#include "Object.h"
#include "Map.h"
#include "Dino.h"
int x = SCREEN_WIDTH/2;
int y = SCREEN_HEIGHT/2;
//class BaseObject ball;
class BaseObject g_background;
class Map Map_data;
class Dino dino;
bool loadBackGround()
{
    return (Map_data.loadGround("Resource/BackGround/ground.png", g_renderer)&&Map_data.loadBackGround(g_renderer, BACKGROUND_LAYER_1));
//    return g_background.loadIMG("Resource/BackGround.png", g_renderer);
}
void draw(SDL_Renderer* g_renderer, int x,int y)
{
//    ball.setDesRect(SCREEN_WIDTH - 700, GROUND, -1, -1);
    dino.loadIMG("Resource/DinoRed.png", g_renderer);
    dino.Render(g_renderer);
//    SDL_RenderPresent(g_renderer);
}
void process(SDL_Event &e)
{
    dino.loadIMG("Resource/DinoRed.png", g_renderer);
    dino.move();
    dino.Render(g_renderer);
//    SDL_RenderPresent(g_renderer);
}
int main()
{
    int g_count = 0;
    initSDL(g_window, g_renderer, WINDOW_TITLE, SCREEN_WIDTH, SCREEN_HEIGHT);
    if(loadBackGround() == false) { cout<<"Can't not load Background!!!"; return 0; }
    g_background.setDesRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    bool is_running = true;
    SDL_Event event;
    while (is_running)
    {
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                is_running = false;
            }
            dino.HandleEvent(event);
        }
//        process(event);
//        dino.HandleEvent(event);
        Map_data.renderScrollingBackground(g_renderer, BACKGROUND_LAYER_1);
        Map_data.renderScrollingGround(/*speed, acceleration,*/g_renderer);
        // process game logic
        // draw(g_renderer,x,y);
        // (nothing to process)
        // draw & display
        process(event);
        SDL_RenderPresent(g_renderer);
    }
    
    quitSDL(g_window, g_renderer);
    
    return 0;
}
