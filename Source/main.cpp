
#include "CommonFunction.h"
#include "Timer.h"
#include "Display.h"
#include "SDL_InitWindow.h"
#include "GameStatus.h"
#include "Object.h"
#include "Map.h"
#include "Dino.h"

#include "Enemy.h"
bool play_again = true;
int type_map = rand()%TOTAL_TYPE_OF_BACKGOUND, type_dino = rand()%TOTAL_TYPE_OF_DINO;
int acceleration = 1, speedG = GROUND_SPEED, speedGG = GRASS_GROUND_SPEED;

Mix_Music* gBackgroundMusic = NULL;
Mix_Music* gMenuMusic = NULL;
Mix_Chunk* gClickMusic = NULL;
Mix_Chunk* gJumpMusic = NULL;
Mix_Chunk* gLoseMusic = NULL;

class BaseObject g_background;
class Map Map_data;
class Dino dino;
class Enemy Air1(IN_AIR_ENEMY), Ground1(ON_GROUND_ENEMY), Air2(IN_AIR_ENEMY), Ground2(ON_GROUND_ENEMY);

ImpTimer Event_Timer, program_timer;

bool loadBackGround (int type);

void randomMap (int map_time)
{
    if(map_time > 5000)
    {
        Map_data.Free(type_map);
        dino.Free();
        program_timer.start();
        type_map = rand()%6; type_dino = rand()%4;
        
        Map_data.update_id(type_map);
        
        if(loadBackGround(type_map) == false) { cout<<"Can't not load Background!!!"; return; }
        
        dino.loadIMG(type_dino, g_renderer);
    }
}
bool loadBackGround(int type)
{

    gJumpMusic = Mix_LoadWAV("Resource/Sound/jump_sound.wav");
    
    if(gBackgroundMusic == NULL) cout<<Mix_GetError();

    gBackgroundMusic =  Mix_LoadMUS("Resource/Sound/background_sound.wav");
    
    if(gBackgroundMusic == NULL) cout<<Mix_GetError();

    gLoseMusic = Mix_LoadWAV("Resource/Sound/lose_sound.wav");
    
    return (Map_data.loadGround(g_renderer, type)
            &&Map_data.loadBackGround(g_renderer, TOTAL_BACKGROUND_LAYER[type], type)&&(Map_data.loadGrassGround(g_renderer, type))
            );
}

void process()
{
    Air1.move(acceleration);
    Ground1.move(acceleration);
    Air1.Render(g_renderer);
    Ground1.Render(g_renderer);
                 
    Air2.move(acceleration);
    Ground2.move(acceleration);
    Air2.Render(g_renderer);
    Ground2.Render(g_renderer);
    
    dino.move();
    dino.Render(g_renderer);
}
int main()
{
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
    srand((unsigned int)time(0));
//    type_map = 1;
    Map_data.update_id(type_map);
    initSDL(g_window, g_renderer, WINDOW_TITLE, SCREEN_WIDTH, SCREEN_HEIGHT);
    
    if(loadBackGround(type_map) == false) { cout<<"Can't not load Background!!!"; return 0; }
    while(play_again)
    {
        Mix_PlayMusic(gBackgroundMusic, -1);
        
        dino.loadIMG(type_dino, g_renderer);
        Air1.loadImg(g_renderer);
        Ground1.loadImg(g_renderer);
        Air2.loadImg(g_renderer);
        Ground2.loadImg(g_renderer);
        
        program_timer.start();
        bool is_running = true;
        SDL_Event event;
        vector <double> bg_speed(TOTAL_BACKGROUND_LAYER[0] , BASE_OFFSET_SPEED);
        acceleration = 0; speedG = GROUND_SPEED; speedGG = GRASS_GROUND_SPEED;
        
        while (is_running)
        {
            int map_time = program_timer.get_Ticks();
            randomMap(map_time);
            
            Event_Timer.start();

            while (SDL_PollEvent(&event))
            {
                if (event.type == SDL_QUIT)
                {
                    is_running = false;
                }
                dino.HandleEvent(event, gJumpMusic);
            }
            Map_data.renderScrollingBackground(g_renderer, TOTAL_BACKGROUND_LAYER[type_map], bg_speed);
            Map_data.renderScrollingGround(speedG, acceleration, g_renderer);
            
            process();
        
            Map_data.renderScrollingGrass(speedGG, acceleration, g_renderer);
            SDL_RenderPresent(g_renderer);
            
            if(checkCollision(dino, Air1)||checkCollision(dino, Air2)||checkCollision(dino, Ground1)||checkCollision(dino, Ground2))
            {
                Mix_PauseMusic();
                Mix_PlayChannel(MIX_CHANNEL, gLoseMusic, 0);
                is_running = false;
    //            waitUntilKeyPressed();
            }
            
            int real_imp_time = Event_Timer.get_Ticks();
            int time_one_frame = 1000/FRAME_PER_SECOND;
            if (real_imp_time < time_one_frame)
            {
                int delay_time = time_one_frame - real_imp_time;
                SDL_Delay(delay_time);
            }
        }
    }
    
    dino.Free();
    Map_data.Free(type_map);
    
    Mix_FreeMusic(gBackgroundMusic);
    gBackgroundMusic = NULL;

    Mix_FreeMusic(gMenuMusic);
    gMenuMusic = NULL ;
    
    Mix_FreeChunk(gClickMusic);
    gClickMusic = NULL ;
    
    Mix_FreeChunk(gJumpMusic);
    gJumpMusic = NULL ;
    
    Mix_FreeChunk(gLoseMusic);
    gLoseMusic = NULL;
    quitSDL(g_window, g_renderer);
    return 0;
}
