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
#include "Mouse.h"
bool play_again = false, lose_game = false;
int type_map = rand()%TOTAL_TYPE_OF_BACKGOUND, type_dino = rand()%TOTAL_TYPE_OF_DINO;

Mix_Music* gBackgroundMusic = NULL;
Mix_Music* gMenuMusic = NULL;
Mix_Chunk* gClickMusic = NULL;
Mix_Chunk* gJumpMusic = NULL;
Mix_Chunk* gLoseMusic = NULL;

class Mouse mouse;

class BaseObject g_menu, g_score, g_highscore, g_help_menu;
class Map Map_data;
class Dino dino;
class Enemy Air1(IN_AIR_ENEMY), Ground1(ON_GROUND_ENEMY), Air2(IN_AIR_ENEMY), Ground2(ON_GROUND_ENEMY);

class ImpTimer Event_Timer, program_timer, Menu_timer;

class Button Play_button(464 - 350/4, 220, TWO_SPRITES),
             Help_button(464 - 350/4, 305, TWO_SPRITES),
             Exit_button(464 - 350/4, 390, TWO_SPRITES),
             Back_button(75, 65, TWO_SPRITES),
             Pause_button(PAUSE_BUTTON_POSX, PAUSE_BUTTON_POSY, TWO_SPRITES),
             Continue_button(CONTINUE_BUTTON_POSX, CONTINUE_BUTTON_POSY, TWO_SPRITES);

class Button DinoGreen(GREEN_DINO_POSX, GREEN_DINO_POSY, ONE_SPRITE),
             DinoRed(RED_DINO_POSX,RED_DINO_POSY, ONE_SPRITE),
             DinoBlue(BLUE_DINO_POSX, BLUE_DINO_POSY, ONE_SPRITE),
             DinoGold(GOLD_DINO_POSX, GOLD_DINO_POSY, ONE_SPRITE);

class Button Map_button[TOTAL_TYPE_OF_BACKGOUND];

bool loadBackGround (int type);
bool loadMedia();

bool loadBackGround(int type)
{

    return (Map_data.loadGround(g_renderer, type) && Map_data.loadBackGround(g_renderer, TOTAL_BACKGROUND_LAYER[type], type)&&(Map_data.loadGrassGround(g_renderer, type))
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

    while(!quit_game)
    {
        Mix_PlayMusic(gMenuMusic, REPEATIVE);
        while(!quit_menu)
        {
            mouse.update();
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
                HandlePlayButton(event, g_menu, Play_button, quit_game, quit_menu, play_again, type_dino, type_map, g_renderer, gClickMusic);
                HandleHelpButton(event, g_menu, mouse, g_help_menu, Help_button, Back_button, quit_game, quit_menu, play_again, g_renderer, gClickMusic);
                HandleExitButton(event, g_menu, Exit_button, quit_game, quit_menu, play_again, g_renderer, gClickMusic);
            }
            
            g_menu.Render(g_renderer);
            Play_button.renderButton(g_renderer);
            Help_button.renderButton(g_renderer);
            Exit_button.renderButton(g_renderer);
            mouse.Render(g_renderer);
            SDL_RenderPresent(g_renderer);
            controlFPS(Menu_timer, MENU_FPS);
        }
        
        if(play_again == true)
        {
            drawLoadDino(g_menu, mouse, DinoGreen, DinoRed, DinoBlue, DinoGold, type_dino, type_map, g_renderer, gClickMusic);
            
            drawLoadMap(g_menu, mouse, Map_button, type_dino, type_map, g_renderer, gClickMusic);
        }
        
        while(play_again)
        {
            
            SDL_SetRenderDrawColor(g_renderer, 255, 255, 255, 255);
            SDL_RenderClear(g_renderer);
            
            class ImpTimer game_timer;
            game_timer.start();
            int score = 0, time = 0;
            int speed = 0, ground_pos = GROUND_SPEED, grass_ground_pos = GRASS_GROUND_SPEED;
            vector <double> bg_pos(BACKGROUND_TOTAL_LAYERS , BASE_POS);
            
            bool is_running = true; lose_game = false;
        
            Mix_PlayMusic(gBackgroundMusic, REPEATIVE);
           
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
            bool paused = false;
            while (is_running)
            {
                mouse.update();
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
                    if(!lose_game&&!paused)
                    {
                        HandlePauseButton(event, paused, Pause_button, g_renderer, gClickMusic);
                        dino.HandleEvent(event, gJumpMusic);
                    }
                    else if(paused)
                    {
                        game_timer.pause();
                        if(HandleContinueButton(event, paused, Continue_button, g_renderer, gClickMusic))
                            game_timer.start();
                    }
                }
                if(is_running == false) break;
                Map_data.renderScrollingBackground(g_renderer, TOTAL_BACKGROUND_LAYER[type_map], bg_pos, speed, !lose_game&&!paused);
                Map_data.renderScrollingGround(ground_pos, speed, g_renderer, !lose_game&&!paused);
                
                if(!lose_game&&!paused)
                {
                    dino.move();
                    Air1.move(speed, g_renderer);
                    Ground1.move(speed, g_renderer);
                    Air2.move(speed, g_renderer);
                    Ground2.move(speed, g_renderer);
                }
                
                Air1.Render(g_renderer, !lose_game&&!paused);
                Ground1.Render(g_renderer, !lose_game&&!paused);
                Air2.Render(g_renderer, !lose_game&&!paused);
                Ground2.Render(g_renderer, !lose_game&&!paused);
                
                if(checkCollision(dino, Air1)||checkCollision(dino, Air2)||checkCollision(dino, Ground1)||checkCollision(dino, Ground2))
                {
                    game_timer.pause();
                    if(!lose_game)
                    {
                        Mix_PauseMusic();
                        Mix_PlayChannel(MIX_CHANNEL, gLoseMusic, 0);
                    }
                    drawEndGame(g_renderer, play_again,quit_menu, quit_game, type_map, lose_game);
                }
                
                drawScore(g_score, g_font, text_color, g_renderer, game_timer, score, time, speed);
                drawHighScore(g_highscore, g_font, text_color, g_renderer, "Resource/database.txt", score, time);
                
                if(!lose_game) dino.Render(g_renderer, !lose_game&&!paused);
                
                else dino.RenderLose(g_renderer);
                
                Map_data.renderScrollingGrass(grass_ground_pos, speed, g_renderer, !lose_game&&!paused);
                
                if(!lose_game&&!paused) Pause_button.renderButton(g_renderer);
                
                if(paused) Continue_button.renderButton(g_renderer);
                mouse.Render(g_renderer);
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
    gMenuMusic = NULL;
    
    Mix_FreeChunk(gClickMusic);
    gClickMusic = NULL;
    
    Mix_FreeChunk(gJumpMusic);
    gJumpMusic = NULL;
    
    Mix_FreeChunk(gLoseMusic);
    gLoseMusic = NULL;
    
    g_menu.Free();
    Play_button.Free();
    Help_button.Free();
    Exit_button.Free();
    Back_button.Free();
    
    Pause_button.Free();
    Continue_button.Free();
    
    DinoGreen.Free();
    DinoRed.Free();
    DinoGold.Free();
    DinoBlue.Free();
    
    for(int i = 0; i < TOTAL_TYPE_OF_BACKGOUND; i++) Map_button[i].Free();
    
    quitSDL(g_window, g_renderer);
    return 0;
}

bool loadMedia()
{
    bool success = true;
    TTF_Init();
    //Load Mouse
    if(mouse.loadIMG("kira.png", g_renderer)==false) return 0;
    //
    //Load Menu
    if(g_menu.loadIMG("Resource/Menu/Menu1.png", g_renderer) == false) { cout<<"Fail to load Menu!"; return false; }
    
    if(g_help_menu.loadIMG("Resource/Menu/Help-menu.png", g_renderer) == false)
        { cout<<"Fail to load Help-menu!"; return false; }
    //--------------------------
    
    //Load Music
    gJumpMusic = Mix_LoadWAV("Resource/Sound/jump_sound.wav");
    
    if(gJumpMusic == NULL) {cout<<Mix_GetError<<1; success = false;}
    
    gMenuMusic = Mix_LoadMUS("Resource/Sound/background_sound.wav");
    
    if(gMenuMusic == NULL) {cout<<Mix_GetError<<2; success = false;}

    gBackgroundMusic =  Mix_LoadMUS("Resource/Sound/background_sound.wav");
    
    if(gBackgroundMusic == NULL) {cout<<Mix_GetError<<2; success = false;}
    
    gLoseMusic = Mix_LoadWAV("Resource/Sound/lose_sound.wav");
    
    if(gLoseMusic == NULL) {cout<<Mix_GetError<<3; success = false;}
    
    gClickMusic = Mix_LoadWAV("Resource/Sound/mouse_click_sound.wav");
    
    if(gClickMusic == NULL) {cout<<Mix_GetError<<4; success = false;}
    //--------------------------
    
    //Load Button
    if(Play_button.loadImg("Resource/Menu/Play-button.png", g_renderer) == false) return false;
    
    if(Exit_button.loadImg("Resource/Menu/Exit-button.png", g_renderer) == false) return false;
    
    if(Back_button.loadImg("Resource/Menu/back_button.png", g_renderer) == false) return false;
    
    if(Help_button.loadImg("Resource/Menu/Help-button.png", g_renderer) == false) return false;
    
    if(DinoGreen.loadImg("Resource/Menu/Button/Green1.png", g_renderer) == false) return false;
    
    if(DinoRed.loadImg("Resource/Menu/Button/Red1.png", g_renderer) == false) return false;
    
    if(DinoBlue.loadImg("Resource/Menu/Button/Blue1.png", g_renderer) == false) return false;
    
    if(DinoGold.loadImg("Resource/Menu/Button/Gold1.png", g_renderer) == false) return false;
    //--------------------------
    
    //Load Font, Text
    g_font = TTF_OpenFont("Resource/Font/mspc.ttf", 25);
    
    if(g_font == NULL) {  cout<<"Can't load Font!"<<Mix_GetError(); return false; }
    //--------------------------
    
    //Load Map Button
    Map_button[FOREST].loadImg("Resource/LoadMap/FOREST.png", g_renderer);
    Map_button[HILLS].loadImg("Resource/LoadMap/HILLS.png", g_renderer);
    Map_button[CLOUD_MOUTAIN].loadImg("Resource/LoadMap/CLOUD_MOUTAIN.png", g_renderer);
    Map_button[NIGHT_CITY].loadImg("Resource/LoadMap/NIGHT_CITY.png", g_renderer);
    Map_button[DESERT].loadImg("Resource/LoadMap/DESERT.png", g_renderer);
    Map_button[FAR_CITY].loadImg("Resource/LoadMap/FAR_CITY.png", g_renderer);
    
    Map_button[FOREST].setDesRect       (MAP_BUTTON_X_1, MAP_BUTTON_Y_1, MAP_BUTTON_W, MAP_BUTTON_H);
    Map_button[HILLS].setDesRect        (MAP_BUTTON_X_2, MAP_BUTTON_Y_1, MAP_BUTTON_W, MAP_BUTTON_H);
    Map_button[CLOUD_MOUTAIN].setDesRect(MAP_BUTTON_X_3, MAP_BUTTON_Y_1, MAP_BUTTON_W, MAP_BUTTON_H);
    Map_button[NIGHT_CITY].setDesRect   (MAP_BUTTON_X_1, MAP_BUTTON_Y_2, MAP_BUTTON_W, MAP_BUTTON_H);
    Map_button[DESERT].setDesRect       (MAP_BUTTON_X_2, MAP_BUTTON_Y_2, MAP_BUTTON_W, MAP_BUTTON_H);
    Map_button[FAR_CITY].setDesRect     (MAP_BUTTON_X_3, MAP_BUTTON_Y_2, MAP_BUTTON_W, MAP_BUTTON_H);
    
    Pause_button.loadImg("Resource/Menu/Button/pause_button.png", g_renderer);
    Continue_button.loadImg("Resource/Menu/Button/continue_button.png", g_renderer);
    //--------------------------
    
    return true;
}
