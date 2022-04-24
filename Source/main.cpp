
#include "CommonFunction.h"
#include "Timer.h"
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

ImpTimer timer, Dino_Timer;
int id_frame = 0;
bool loadBackGround(int type)
{
//    if(Map_data.loadBackGround(g_renderer, BACKGROUND_LAYER_1, 0) == false) cout<< "CC!";
    return (Map_data.loadGround(g_renderer, type)
            &&Map_data.loadBackGround(g_renderer, BACKGROUND_LAYER[type], type)
            );
//    return g_background.loadIMG("Resource/BackGround.png", g_renderer);
}

void process()
{
    dino.move();
    if(id_frame == 6) id_frame = 0;
    dino.Render(g_renderer, Dino_Timer, id_frame);
//    id_frame %= RUNNING_FRAMES;
//    SDL_RenderPresent(g_renderer);
}
int main()
{
    Dino_Timer.start();
    srand((unsigned int)time(0));
    int type_map = rand()%2, type_dino = rand()%4;
    initSDL(g_window, g_renderer, WINDOW_TITLE, SCREEN_WIDTH, SCREEN_HEIGHT);
    if(loadBackGround(type_map) == false) { cout<<"Can't not load Background!!!"; return 0; }
    g_background.setDesRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    dino.loadIMG(type_dino, g_renderer);
    bool is_running = true;
    SDL_Event event;
    while (is_running)
    {
        timer.start();
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
        Map_data.renderScrollingBackground(g_renderer, BACKGROUND_LAYER[type_map]);
        Map_data.renderScrollingGround(/*speed, acceleration,*/g_renderer);
        // process game logic
        // (nothing to process)
        // draw & display
//        id_frame++;
        
        process();
        SDL_RenderPresent(g_renderer);
        
        int real_imp_time = timer.get_Ticks();
        int time_one_frame = 1000/FRAME_PER_SECOND;
        if (real_imp_time < time_one_frame)
        {
            int delay_time = time_one_frame - real_imp_time;
            SDL_Delay(delay_time);
        }
//        SDL_Delay(16);
    }
    
    quitSDL(g_window, g_renderer);
    
    return 0;
}
