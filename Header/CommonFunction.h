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

static SDL_Window* g_window = NULL;
//static SDL_Surface* g_ScreenSurface = NULL;
//static SDL_Surface* g_background = NULL;
static SDL_Renderer* g_renderer = NULL;
//static SDL_Texture* g_texture = NULL;
static SDL_Event g_event;

const string WINDOW_TITLE = "DINOUSAUR TRAVEL";

const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 640;
const int SCREEN_BPP = 32;

const int step = 26;

const int COLOR_KEY_R = 167;
const int COLOR_KEY_G = 175;
const int COLOR_KEY_B = 180;
#endif /* CommonFunction_h */
