//
//  CommonFunction.h
//  Project Game
//
//  Created by Nguyễn Tiến Dũng on 4/23/22.
//  Copyright © 2022 Nguyễn Tiến Dũng. All rights reserved.
//

#ifndef CommonFunction_h
#define CommonFunction_h

#include <bits/stdc++.h>
using namespace std;
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <thread>
#include <chrono>
#include <ctime>

static SDL_Window* g_window = NULL;
//static SDL_Surface* g_ScreenSurface = NULL;
//static SDL_Surface* g_background = NULL;
static SDL_Renderer* g_renderer = NULL;
//static SDL_Texture* g_texture = NULL;
static SDL_Event g_event;

const string WINDOW_TITLE = "DINOUSAUR TRAVEL";
const int step = 16;

const int MIX_CHANNEL = -1;

const int FRAME_PER_SECOND = 60;
const int SCREEN_WIDTH = 928;
const int SCREEN_HEIGHT = 522;

const int COLOR_KEY_R = 167;
const int COLOR_KEY_G = 175;
const int COLOR_KEY_B = 180;

const int GROUND = 430;
const int SCREEN_BPP = 64;
const double GROUND_SPEED = 8; /*8.64*/
const double ENEMY_SPEED = 8 ; /*8.64*/
const int IN_AIR_ENEMY = 1;
const int ON_GROUND_ENEMY = 2;
const int ENEMY_RANGE = 240;
const int MIN_HEIGHT = 330;
const int MAX_HEIGHT = 100;
const int GRASS_HEIGHT = 8;
const int JUMP = 64;
const int FALL = 150;
const int MAX_JUMP = 240;

const int BASE_OFFSET_SPEED = 0;
const int JUMP_POW = 18;
const double GRAVITY_FALL = 0.41;
const int MAX_ACCELERATION = 9;

const int TOTAL_BACKGROUND_LAYER[2] = { 9, 6 };
const double LAYER_1_SPEED = 0;
const double LAYER_2_SPEED = 0.25;
const double LAYER_3_SPEED = 0.5;
const double LAYER_4_SPEED = 0.75;
const double LAYER_5_SPEED = 1.0;
const double LAYER_6_SPEED = 1.25;
const double LAYER_7_SPEED = 1.5;
const double LAYER_8_SPEED = 1.75;
const double LAYER_9_SPEED = 2.0;

const int RUNNING_FRAMES = 6;
static SDL_Rect dino_frame[RUNNING_FRAMES];


#endif /* CommonFunction_h */
