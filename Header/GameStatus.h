//
//  GameStatus.h
//  Dino Journey
//
//  Created by Nguyễn Tiến Dũng on 4/22/22.
//  Copyright © 2022 Nguyễn Tiến Dũng. All rights reserved.
//

#ifndef GameStatus_h
#define GameStatus_h
#include "CommonFunction.h"
#include "Dino.h"
#include "Enemy.h"
#include "Map.h"
#include "Button.h"
#include "Timer.h"
#include "SDL_InitWindow.h"
#include "Mouse.h"
void controlFPS(class ImpTimer &Timer, int FPS);

bool checkCollision (class Dino& dino, class Enemy& enemy);

void drawScore (class BaseObject &g_score, TTF_Font* g_font, SDL_Color text_color, SDL_Renderer* &renderer, class ImpTimer &game_timer, int &score, int &time, int &speed);

void drawHighScore(class BaseObject &g_highscore,TTF_Font* g_font, SDL_Color text_color, SDL_Renderer* &renderer,string path, int &score, int &time);

void drawEndGame(SDL_Renderer* &renderer, bool& play_again, bool& quit_menu, bool& quit_game, int type_map, bool &lose_game);

void HandleMuteButton(SDL_Event e, Button &Mute_button, SDL_Renderer* &renderer, bool &mute_volume, Mix_Chunk *gClickMusic);

void HandleUnmuteButton(SDL_Event e, Button &Unmute_button, SDL_Renderer* &renderer, bool &mute_volume, Mix_Chunk *gClickMusic);

bool HandleContinueButton(SDL_Event e, bool &paused, Button &Continue_button, SDL_Renderer* &renderer, bool &mute_volume, Mix_Chunk *gClickMusic);

void HandlePauseButton(SDL_Event e, bool &paused, Button &Pause_button, SDL_Renderer* &renderer, Mix_Chunk *gClickMusic);

bool HandleBackButton(SDL_Event e, Button& Back_button, Button &Continue_button ,SDL_Renderer* &renderer, Mix_Chunk *gClickMusic);

void HandlePlayButton(SDL_Event e, BaseObject& g_menu,
                      Button& Play_button,
                      bool& quit_game,
                      bool& quit_menu,
                      bool& play_again,
                      int& type_dino,
                      int& type_map,
                      SDL_Renderer* &renderer,
                      Mix_Chunk *gClickMusic);

void HandleHelpButton(SDL_Event e, BaseObject& g_menu, Mouse &mouse,
                      BaseObject& g_help_menu,
                      Button& Help_button,
                      Button& Back_button,
                      bool& quit_game, bool& quit_menu,
                      bool& play_again,
                      SDL_Renderer* &renderer,
                      Mix_Chunk *gClickMusic);

void HandleExitButton(SDL_Event e, BaseObject& g_menu,
                      Button& Play_button,
                      bool& quit_game, bool& quit_menu,
                      bool& play_again,
                      SDL_Renderer* &renderer,
                      Mix_Chunk *gClickMusic);

bool HandleCharacter(SDL_Event e, Button &Dino_button, Mix_Chunk* gClickMusic);

bool HandleMap(SDL_Event e, Button &Map_button, Mix_Chunk* gClickMusic);

void drawLoadDino(BaseObject g_menu, Mouse &mouse, Button &DinoGreen, Button &DinoRed, Button &DinoBLue, Button &DinoGold,int &type_dino, int &type_map, SDL_Renderer* &renderer, Mix_Chunk* gClickMusic);

void drawLoadMap(BaseObject g_menu, Mouse &mouse, Button* Map_butto,int &type_dino, int &type_map, SDL_Renderer* &renderer, Mix_Chunk* gClickMusic);

#endif /* GameStatus_h */
