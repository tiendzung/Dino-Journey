//
//  CommonFunction.h
//  Dino Journey
//
//  Created by Nguyễn Tiến Dũng on 4/23/22.
//  Copyright © 2022 Nguyễn Tiến Dũng. All rights reserved.
//

#ifndef CommonFunction_h
#define CommonFunction_h
#define ii pair<int, double>
#include <bits/stdc++.h>
using namespace std;
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <thread>
#include <chrono>
#include <ctime>
#include <fstream>
static SDL_Window* g_window = NULL;
static SDL_Renderer* g_renderer = NULL;
static TTF_Font* g_font = NULL;
const int FONT_SIZE = 28;
const string WINDOW_TITLE = "DINO JOURNEY";

const int FRAME_PER_SECOND = 60;
const int MENU_FPS = 240;
const int SCREEN_WIDTH = 928;
const int SCREEN_HEIGHT = 522;
const int MAX_TIME = FRAME_PER_SECOND*60;

static SDL_Color text_color = { 0, 0, 0 };
const int COLOR_KEY_R = 167;
const int COLOR_KEY_G = 175;
const int COLOR_KEY_B = 180;

const int GROUND = 430;
const int GROUND_SPEED = 4 /* - 2 */ /* + 3*/ ; /*8.64*/
const int GRASS_GROUND_SPEED = 5 /*- 2*/ /* + 3*/;
const int ENEMY_SPEED = 4 /*- 2*/ /* + 3*/ ; /*8.64*/
const int JUMP_POW = 10;

const int GRASS_HEIGHT = 8; /*57*/

const int BASE_POS = 0;
const int MAX_SPEED = 2 /*3*/ ;
const int INCREASE_SPEED = 1;
const int MIX_CHANNEL = -1;
const int REPEATIVE = -1;
const int NOT_REPEATITIVE = 0;

const int GREEN_DINO_POSX = 145 - 60;
const int GREEN_DINO_POSY = 312 - 180;
const int RED_DINO_POSX = 318 - 25;
const int RED_DINO_POSY = 312 - 180;
const int GOLD_DINO_POSX = 520 - 25;
const int GOLD_DINO_POSY = 312 - 180;
const int BLUE_DINO_POSX = 725 - 30;
const int BLUE_DINO_POSY = 312 - 180;

const int MAP_BUTTON_W = 200;
const int MAP_BUTTON_H = 113;
const int MAP_BUTTON_Y_1 = 150;
const int MAP_BUTTON_Y_2 = 300;
const int MAP_BUTTON_X_1 = 266 - MAP_BUTTON_W;
const int MAP_BUTTON_X_2 = SCREEN_WIDTH/2 - MAP_BUTTON_W/2;
const int MAP_BUTTON_X_3 = SCREEN_WIDTH - 266;

const int SCORE_BUTTON_POSX = SCREEN_WIDTH - 300;
const int SCORE_BUTTON_POSY = 12;
const int HIGH_SCORE_BUTTON_POSX = SCREEN_WIDTH - 300;
const int HIGH_SCORE_BUTTON_POSY = 12 + 30;

const int PAUSE_BUTTON_POSX = 20;
const int PAUSE_BUTTON_POSY = 15;
const int CONTINUE_BUTTON_POSX = 20;
const int CONTINUE_BUTTON_POSY = 15;
enum TYPE_DINO
{
    DINO_GREEN,
    DINO_RED,
    DINO_GOLD,
    DINO_BLUE,
};
const string HighScoreFile = "database.txt";

#endif /* CommonFunction_h */
