//
//  GameStatus.cpp
//  Dino Journey
//
//  Created by Nguyễn Tiến Dũng on 4/22/22.
//  Copyright © 2022 Nguyễn Tiến Dũng. All rights reserved.
//

#include "GameStatus.h"
void controlFPS(class ImpTimer& Timer, int FPS)
{
    int real_imp_time = Timer.get_Ticks();
    int time_one_frame = 1000/FPS;
    if (real_imp_time < time_one_frame)
    {
        int delay_time = time_one_frame - real_imp_time;
        SDL_Delay(delay_time);
    }
}
bool checkCollision (class Dino& dino, class Enemy& enemy)
{
    int TRASH_PIXEL_X = 10, TRASH_PIXEL_Y = 10, TRASH_PIXEL_W = 25, TRASH_PIXEL_H = 20;
    
    SDL_Rect d_rect = {dino.getPosX() + TRASH_PIXEL_X, dino.getPosY() + TRASH_PIXEL_Y, dino.getWidth() - TRASH_PIXEL_W, dino.getHeight() - TRASH_PIXEL_H};
    if(enemy.getType() == ON_GROUND_ENEMY)
    {
        if(enemy.getGround_id()!=DOG)
        {
            TRASH_PIXEL_X = 15, TRASH_PIXEL_Y = 15, TRASH_PIXEL_W = 30, TRASH_PIXEL_H = 0;
        }
        else
        {
            TRASH_PIXEL_X = 23, TRASH_PIXEL_Y = 23, TRASH_PIXEL_W = 45, TRASH_PIXEL_H = 0;
        }
    }
    else
    {
        if(enemy.getAir_id() == HELICORPTER)
        {
             TRASH_PIXEL_X = 15, TRASH_PIXEL_Y = 4, TRASH_PIXEL_W = 55, TRASH_PIXEL_H = 15;
        }
        else
        {
            TRASH_PIXEL_X = 15, TRASH_PIXEL_Y = 4, TRASH_PIXEL_W = 15, TRASH_PIXEL_H = 15;
        }
    }
    SDL_Rect e_rect = {enemy.getPosX() + TRASH_PIXEL_X, enemy.getPosY() + TRASH_PIXEL_Y, enemy.getWidth() - TRASH_PIXEL_W, enemy.getHeight() - TRASH_PIXEL_H};

    return SDL_HasIntersection(&d_rect, &e_rect);
}
void drawScore(class BaseObject &g_score,TTF_Font* g_font, SDL_Color text_color, SDL_Renderer* &renderer,  class ImpTimer &game_timer, int &score, int &time, int &speed)
{
    if(time%7 == 0&&!game_timer.is_Paused()) score++;
    time++;
    if(time >= MAX_TIME) { speed += INCREASE_SPEED; time =0; }
    if(speed > MAX_SPEED) speed = 0;
    string new_score = to_string(score);
    new_score = "YOUR SCORE: " + new_score;
    g_score.loadText(new_score, g_font, text_color, renderer);
    g_score.RenderXY(SCORE_BUTTON_POSX, SCORE_BUTTON_POSY, renderer);
    g_score.Free();
}

void drawHighScore(class BaseObject &g_highscore,TTF_Font* g_font, SDL_Color text_color, SDL_Renderer* &renderer, string path, int &score, int &time)
{
    bool update = false;
    fstream HighScoreFile;
    int old_highscore;
    int new_highscore;

    HighScoreFile.open(path, ios::in);
    HighScoreFile >> old_highscore;

    if(score >= old_highscore)
    {
        update = true;
        new_highscore = score;
    } else new_highscore = old_highscore;
    fstream highScoreFile;
    highScoreFile.open(path, ios::out);
    highScoreFile << new_highscore;
    
    g_highscore.loadText("HIGH SCORE: "+to_string(new_highscore), g_font, text_color, renderer);
    if(update == false)
        g_highscore.RenderXY(HIGH_SCORE_BUTTON_POSX, HIGH_SCORE_BUTTON_POSY, renderer);
    g_highscore.Free();
}

void drawEndGame(SDL_Renderer* &renderer, bool& play_again, bool& quit_menu, bool& quit_game, int type_map, bool &lose_game)
{
    lose_game = true;
    string path;
    switch(type_map)
    {
        case FOREST: { path = "Resource/Menu/LooseScreenWhite.png"; break; }
        case HILLS: { path = "Resource/Menu/LooseScreenBlack.png"; break; }
        case CLOUD_MOUTAIN: { path = "Resource/Menu/LooseScreenBlack.png"; break; }
        case NIGHT_CITY: { path = "Resource/Menu/LooseScreenBlack.png"; break; }
        case DESERT: { path = "Resource/Menu/LooseScreenBlack.png"; break; }
        case FAR_CITY: { path = "Resource/Menu/LooseScreenBlack.png"; break; }
    }
    SDL_Surface* load_surface = IMG_Load(path.c_str());
    SDL_Texture* lose_texture = SDL_CreateTextureFromSurface(renderer, load_surface);
    
    SDL_RenderCopy(renderer, lose_texture, NULL, NULL);

    SDL_DestroyTexture(lose_texture);
    SDL_FreeSurface(load_surface);    
    return;
}
void HandleMuteButton(SDL_Event e, Button &Mute_button, SDL_Renderer* &renderer, bool &mute_volume, Mix_Chunk *gClickMusic)
{
    if(Mute_button.inSide() == true)
    {
        if(e.type == SDL_MOUSEBUTTONDOWN)
        {
            Mute_button.status = BUTTON_MOUSE_UP;
            Mix_PlayChannel(MIX_CHANNEL, gClickMusic, NOT_REPEATITIVE);
            Mix_PauseMusic();
            mute_volume = true;
        }
    }
}

void HandleUnmuteButton(SDL_Event e, Button &Unmute_button, SDL_Renderer* &renderer, bool &mute_volume, Mix_Chunk *gClickMusic)
{
    if(Unmute_button.inSide() == true)
    {
        if(e.type == SDL_MOUSEBUTTONDOWN)
        {
            Unmute_button.status = BUTTON_MOUSE_UP;
            Mix_PlayChannel(MIX_CHANNEL, gClickMusic, NOT_REPEATITIVE);
            Mix_ResumeMusic();
            mute_volume = false;
        }
    }
}

bool HandleContinueButton(SDL_Event e, bool &paused, Button &Continue_button, SDL_Renderer* &renderer, bool &mute_volume, Mix_Chunk *gClickMusic)
{
    if(Continue_button.inSide() == true)
    {
        if(e.type == SDL_MOUSEBUTTONDOWN)
        {
            Continue_button.status = BUTTON_MOUSE_UP;
            if(mute_volume == false)
            {
                Mix_ResumeMusic();
                Mix_PlayChannel(MIX_CHANNEL, gClickMusic, NOT_REPEATITIVE);
            }
            paused = false;
            return true;
        }
    }
    Continue_button.renderButton(renderer);
    return false;
}
void HandlePauseButton(SDL_Event e, bool &paused, Button &Pause_button, SDL_Renderer* &renderer, Mix_Chunk *gClickMusic)
{
    if(Pause_button.inSide() == true)
    {
        if(e.type == SDL_MOUSEBUTTONDOWN)
        {
            Pause_button.status = BUTTON_MOUSE_UP;
            Mix_PlayChannel(MIX_CHANNEL, gClickMusic, NOT_REPEATITIVE);
            Mix_PauseMusic();
            paused = true;
        }
    }
}

bool HandleBackButton(SDL_Event e, Button& Back_button, Mix_Chunk *gClickMusic)
{
    if(Back_button.inSide() == true)
    {
        if(e.type == SDL_MOUSEBUTTONDOWN)
        {
            Back_button.status = BUTTON_MOUSE_UP;
            Mix_PlayChannel(MIX_CHANNEL, gClickMusic, NOT_REPEATITIVE);
            return true;
        }
    }
    return false;
}

void HandlePlayButton(SDL_Event e, BaseObject& g_menu,
                      Button& Play_button,
                      bool& quit_game,
                      bool& quit_menu,
                      bool& play_again,
                      int& type_dino,
                      int& type_map,
                      SDL_Renderer* &renderer,
                      Mix_Chunk *gClickMusic)
{
    if(Play_button.inSide() == true)
    {
        if(e.type == SDL_MOUSEBUTTONDOWN)
        {
            Play_button.status = BUTTON_MOUSE_UP;
            play_again = true; quit_menu = true;
            Mix_PlayChannel(MIX_CHANNEL, gClickMusic, NOT_REPEATITIVE);
        }
    }
}

void HandleHelpButton(SDL_Event e, BaseObject& g_menu, Mouse &mouse,
                      BaseObject& g_help_menu,
                      Button& Help_button,
                      Button& Back_button,
                      bool& quit_game, bool& quit_menu,
                      bool& play_again,
                      SDL_Renderer* &renderer,
                      Mix_Chunk *gClickMusic)
{
    bool quit_help = false;
    if(Help_button.inSide() == true)
    {
        if(e.type == SDL_MOUSEBUTTONDOWN)
        {
            Help_button.status = BUTTON_MOUSE_UP;
            Mix_PlayChannel(MIX_CHANNEL, gClickMusic, NOT_REPEATITIVE);
            while(!quit_help)
            {
                mouse.update();
                ImpTimer Help_timer;
                Help_timer.start();
                while(SDL_PollEvent(&e))
                {
                    if(e.type == SDL_QUIT)
                    {
                        play_again = false; quit_game = true; quit_menu = true;
                        return;
                    }
                    if(HandleBackButton(e, Back_button, gClickMusic))
                        return;
                }
                g_menu.Render(renderer);
                g_help_menu.Render(renderer);
                Back_button.renderButton(renderer);
                controlFPS(Help_timer, MENU_FPS);
                mouse.Render(renderer);
                SDL_RenderPresent(renderer);
            }
        }
    }
    
}

void HandleExitButton(SDL_Event e, BaseObject& g_menu,
                      Button& Exit_button,
                      bool& quit_game, bool& quit_menu,
                      bool& play_again,
                      SDL_Renderer* &renderer,
                      Mix_Chunk *gClickMusic)
{
    if(Exit_button.inSide() == true)
    {
        if(e.type == SDL_MOUSEBUTTONDOWN)
        {
            Exit_button.status = BUTTON_MOUSE_UP;
            play_again = false; quit_game = true; quit_menu = true;
            Mix_PlayChannel(MIX_CHANNEL, gClickMusic, NOT_REPEATITIVE);
            SDL_Delay(200); //Wait 0.2sec
        }
    }
}
bool HandleCharacter(SDL_Event e, bool &running, Button &Dino_button, Mix_Chunk* gClickMusic)
{
    if(Dino_button.inSide() == true)
    {
        if(e.type == SDL_MOUSEBUTTONDOWN)
        {
            Dino_button.status = BUTTON_MOUSE_UP;
            running = false;
            Mix_PlayChannel(MIX_CHANNEL, gClickMusic, NOT_REPEATITIVE);
            return true;
        }
    }
    return false;
}

bool HandleMap(SDL_Event e, bool &running, Button &Map_button, Mix_Chunk* gClickMusic)
{
    if(Map_button.inSide() == true)
    {
        if(e.type == SDL_MOUSEBUTTONDOWN)
        {
            Map_button.status = BUTTON_MOUSE_UP;
            running = false;
            Mix_PlayChannel(MIX_CHANNEL, gClickMusic, NOT_REPEATITIVE);
            return true;
        }
    }
    return false;
}

void drawLoadDino(BaseObject g_menu, Mouse &mouse, Button &DinoGreen, Button &DinoRed, Button &DinoBlue, Button &DinoGold,int &type_dino, int &type_map, SDL_Renderer* &renderer, Mix_Chunk* gClickMusic)
{
    SDL_Event event;
    bool running = true;
    ImpTimer Timer;
    g_menu.loadIMG("Resource/Menu/LoadDino-menu.png", renderer);
    while(running)
    {
        mouse.update();
        Timer.start();
        while(SDL_PollEvent(&event))
        {
            if(HandleCharacter(event, running, DinoGreen, gClickMusic)) type_dino = DINO_GREEN;
            
            if(HandleCharacter(event, running, DinoRed, gClickMusic)) type_dino = DINO_RED;

            if(HandleCharacter(event, running, DinoBlue, gClickMusic)) type_dino = DINO_BLUE;

            if(HandleCharacter(event, running, DinoGold, gClickMusic)) type_dino = DINO_GOLD;
        }
        g_menu.Render(renderer);
        DinoGreen.renderButton(renderer);
        DinoRed.renderButton(renderer);
        DinoBlue.renderButton(renderer);
        DinoGold.renderButton(renderer);
        
        mouse.Render(renderer);
        SDL_RenderPresent(renderer);
        
        controlFPS(Timer, MENU_FPS);
    }
    g_menu.Free();
}

void drawLoadMap(BaseObject g_menu, Mouse &mouse, Button* Map_button, int &type_dino, int &type_map, SDL_Renderer* &renderer, Mix_Chunk* gClickMusic)
{
    SDL_Event event;
    bool running = true;
    ImpTimer Timer;
    g_menu.loadIMG("Resource/LoadMap/menu.png", renderer);
    while(running)
    {
        mouse.update();
        Timer.start();
        while(SDL_PollEvent(&event))
        {
            for(int i = 0; i < TOTAL_TYPE_OF_BACKGOUND; i++)
            {
                if(HandleMap(event, running, Map_button[i], gClickMusic)) type_map = i;
            }
        }
        g_menu.Render(renderer);
        for(int i = 0; i < TOTAL_TYPE_OF_BACKGOUND; i++)
        Map_button[i].renderButton(renderer);

        mouse.Render(renderer);
        SDL_RenderPresent(renderer);
        
        controlFPS(Timer, MENU_FPS);
    }
    g_menu.Free();
}

