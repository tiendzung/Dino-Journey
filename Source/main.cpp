//
//  main.cpp
//  Dino Journey
//
//  Created by Nguyễn Tiến Dũng on 4/22/22.
//  Copyright © 2022 Nguyễn Tiến Dũng. All rights reserved.
//

#include "CommonFunction.h"
#include "Timer.h"
#include "SDL_InitWindow.h"
#include "GameStatus.h"
#include "Object.h"
#include "Map.h"
#include "Dino.h"
#include "Enemy.h"
#include "Button.h"

bool play_again = false, lose_game = false;
int type_map = rand()%TOTAL_TYPE_OF_BACKGOUND, type_dino = rand()%TOTAL_TYPE_OF_DINO;
int acceleration = 1, speedG = GROUND_SPEED, speedGG = GRASS_GROUND_SPEED;

Mix_Music* gBackgroundMusic = NULL;
Mix_Music* gMenuMusic = NULL;
Mix_Chunk* gClickMusic = NULL;
Mix_Chunk* gJumpMusic = NULL;
Mix_Chunk* gLoseMusic = NULL;

class BaseObject g_menu;
class Map Map_data;
class Dino dino;
class Enemy Air1(IN_AIR_ENEMY), Ground1(ON_GROUND_ENEMY), Air2(IN_AIR_ENEMY), Ground2(ON_GROUND_ENEMY);

class ImpTimer Event_Timer, program_timer, Menu_timer;
class Button Play_button(464 - 230/4,200), Exit_button(464 - 230/4,360), Back_button, Hscroce_button, Help_button(464 - 230/4,280);

bool loadBackGround (int type);
bool loadMedia();

bool loadBackGround(int type)
{

    return (Map_data.loadGround(g_renderer, type)
            &&Map_data.loadBackGround(g_renderer, TOTAL_BACKGROUND_LAYER[type], type)&&(Map_data.loadGrassGround(g_renderer, type))
            );
}

int main()
{
    SDL_Event event;
    bool quit_menu = false;
    bool quit_game = false;

    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
    srand((unsigned int)time(0));
    
    Map_data.update_id(type_map);
    initSDL(g_window, g_renderer, WINDOW_TITLE, SCREEN_WIDTH, SCREEN_HEIGHT);
    
    if(loadMedia() == false) { cout<<"Can't not load Media!!!"; return 0;}
    type_map = -1;
    
    while(!quit_game)
    {
        Mix_PlayMusic(gMenuMusic, REPEATIVE);
        while(!quit_menu)
        {
            SDL_SetRenderDrawColor(g_renderer, 255, 255, 255, 255);
            SDL_RenderClear(g_renderer);
            
            Menu_timer.start();
            Play_button.inSide();
            Help_button.inSide();
            play_again = false;
            SDL_Event event;
            while(SDL_PollEvent(&event))
            {
                if (event.type == SDL_QUIT)
                {
                    quit_menu = true; quit_game = true;
                    play_again = false;
                }
                HandlePlayButton(event, g_menu, Play_button, quit_menu, play_again, g_renderer, gClickMusic);
//                HandleHelpButton();
                HandleExitButton(event, g_menu, Exit_button, quit_game, quit_menu, play_again, g_renderer, gClickMusic);
            }
            
            g_menu.Render(g_renderer);
            Play_button.renderButton(g_renderer);
            Help_button.renderButton(g_renderer);
            Exit_button.renderButton(g_renderer);
            SDL_RenderPresent(g_renderer);
            controlFPS(Menu_timer, FRAME_PER_SECOND);
        }
        while(play_again)
        {
            lose_game = false;
            SDL_SetRenderDrawColor(g_renderer, 255, 255, 255, 255);
            SDL_RenderClear(g_renderer);
            
            Mix_PlayMusic(gBackgroundMusic, REPEATIVE);
            type_map++;
            type_map%=6;
            
            type_dino = rand()%TOTAL_TYPE_OF_DINO;
//            type_dino = 3;
           
            if(loadBackGround(type_map) == false) { cout<<"Can't not load Background!!!"; return 0; }
            
            Air1.generateEnemy();
            Ground1.generateEnemy();
            Air2.generateEnemy();
            Ground2.generateEnemy();

            dino.loadIMG(type_dino, g_renderer);
            Air1.loadImg(g_renderer);
            Ground1.loadImg(g_renderer);
            Air2.loadImg(g_renderer);
            Ground2.loadImg(g_renderer);
            
            program_timer.start();
            bool is_running = true;
            vector <double> bg_speed(BACKGROUND_TOTAL_LAYERS , BASE_OFFSET_SPEED);
            acceleration = 0; speedG = GROUND_SPEED; speedGG = GRASS_GROUND_SPEED;
            
            while (is_running)
            {
                Event_Timer.start();
                while (SDL_PollEvent(&event) != 0)
                {
                    if (event.type == SDL_QUIT)
                    {
                        is_running = false;
                        play_again = false;
                        quit_game = true;
                        quit_menu = true;
                    }
                    else if (event.type == SDL_KEYDOWN && lose_game)
                    {
                        switch (event.key.keysym.sym)
                        {
                            case SDLK_SPACE:
                            {
                                lose_game = false;
                                is_running = false;
                                break;
                                
                            }
                            case SDLK_ESCAPE:
                            {
                                quit_menu = false;
                                is_running = false;
                                play_again = false;
                                break;
                            }
                        }
                    }
                    dino.HandleEvent(event, gJumpMusic);
                }
                if(is_running == false) break;
                Map_data.renderScrollingBackground(g_renderer, TOTAL_BACKGROUND_LAYER[type_map], bg_speed, !lose_game);
                Map_data.renderScrollingGround(speedG, acceleration, g_renderer, !lose_game);
                if(!lose_game)
                {
                    dino.move();
                    Air1.move(acceleration);
                    Ground1.move(acceleration);
                    Air2.move(acceleration);
                    Ground2.move(acceleration);
                    
                    Air1.Render(g_renderer);
                    Ground1.Render(g_renderer);
                    Air2.Render(g_renderer);
                    Ground2.Render(g_renderer);
                }
                if(lose_game)
                {
                    Air1.RenderLose(g_renderer);
                    Ground1.RenderLose(g_renderer);
                    Air2.RenderLose(g_renderer);
                    Ground2.RenderLose(g_renderer);
                }
                if(checkCollision(dino, Air1)||checkCollision(dino, Air2)||checkCollision(dino, Ground1)||checkCollision(dino, Ground2))
                {
                    if(!lose_game)
                    {
                        Mix_PauseMusic();
                        Mix_PlayChannel(MIX_CHANNEL, gLoseMusic, 0);
                    }
                    drawEndGame(g_renderer, play_again,quit_menu, quit_game, type_map, lose_game);
                }
                
                if(!lose_game) dino.Render(g_renderer);
                else dino.RenderLose(g_renderer);
                
                Map_data.renderScrollingGrass(speedGG, acceleration, g_renderer, !lose_game);
                SDL_RenderPresent(g_renderer);
                
                controlFPS(Event_Timer, FRAME_PER_SECOND);
            }
            Map_data.Free(type_map);
            dino.Free();
            Air1.Free();
            Air2.Free();
            Ground1.Free();
            Ground2.Free();
        }
    }
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
    
    g_menu.Free();
    
    quitSDL(g_window, g_renderer);
    return 0;
}

bool loadMedia()
{
    bool success = true;
    if(g_menu.loadIMG("Resource/Menu/Menu1.png", g_renderer) == false) return false;

    gJumpMusic = Mix_LoadWAV("Resource/Sound/jump_sound.wav");
    
    if(gJumpMusic == NULL) {cout<<Mix_GetError<<1; success = false;}
    
    gMenuMusic = Mix_LoadMUS("Resource/Sound/menu_audio_sound.wav");
    
    if(gMenuMusic == NULL) {cout<<Mix_GetError<<2; success = false;}

    gBackgroundMusic =  Mix_LoadMUS("Resource/Sound/background_sound.wav");
    
    if(gBackgroundMusic == NULL) {cout<<Mix_GetError<<2; success = false;}
    
    gLoseMusic = Mix_LoadWAV("Resource/Sound/lose_sound.wav");
    
    if(gLoseMusic == NULL) {cout<<Mix_GetError<<3; success = false;}
    
    gClickMusic = Mix_LoadWAV("Resource/Sound/mouse_click_sound.wav");
    
    if(gClickMusic == NULL) {cout<<Mix_GetError<<4; success = false;}
    
    if(Play_button.loadImg("Resource/Menu/play_button.png", g_renderer) == false) return false;
    
    if(Exit_button.loadImg("Resource/Menu/exit_button.png", g_renderer) == false) return false;
    
    if(Back_button.loadImg("Resource/Menu/back_button.png", g_renderer) == false) return false;
    
    if(Help_button.loadImg("Resource/Menu/help_button.png", g_renderer) == false) return false;
    
    return true;
}
