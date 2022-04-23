
#include "CommonFunction.h"
#include "Display.h"
#include "SDL_InitWindow.h"
#include "GameStatus.h"
#include "Object.h"
#include "Map.h"
int x = SCREEN_WIDTH/2;
int y = SCREEN_HEIGHT/2;
const int RSIZE = 25;
class BaseObject ball;
class BaseObject g_background;
class Map Map_data;

bool loadBackGround()
{
    return (Map_data.loadGround("Resource/BackGround/ground.png", g_renderer)&&Map_data.loadBackGround(g_renderer, BACKGROUND_LAYER_1));
//    return g_background.loadIMG("Resource/BackGround.png", g_renderer);
}
void draw(SDL_Renderer* g_renderer, int x,int y)
{
    ball.setDesRect(x, y, -1, -1);
    ball.loadIMG("Resource/Ball.png", g_renderer);
    ball.Render(g_renderer);
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
    }
}
int main()
{
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
            Map_data.renderScrollingBackground(g_renderer, BACKGROUND_LAYER_1);
            Map_data.renderScrollingGround(/*speed, acceleration,*/g_renderer);
            // process game logic
            process(event);
            // (nothing to process)
            // draw & display
        }
    }
    
    quitSDL(g_window, g_renderer);
    
    return 0;
}
