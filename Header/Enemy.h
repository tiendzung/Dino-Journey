//
//  Enemy.h
//  Dino Journey
//
//  Created by Nguyễn Tiến Dũng on 4/24/22.
//  Copyright © 2022 Nguyễn Tiến Dũng. All rights reserved.
//

#ifndef Enemy_h
#define Enemy_h
#include "CommonFunction.h"
#include "SDL_InitWindow.h"
#include "Object.h"
#include "Timer.h"
#define ii pair<int, int>

static const int TOTAL_ENEMY = 4;
static const int TOTAL_FRAMES_OF_ENEMY = 5;
static const int IN_AIR_ENEMY = 1;
static const int ON_GROUND_ENEMY = 2;
static const int ENEMY_RANGE = 240; /*240*/
static const int GOOD_RANGE = 350;
static const int ENEMY_FPS = 15;
//static const double ENEMY_GROUND_WIDTH = 37;
static const int TOTAL_RAND_EG = 2;
static const string ground_path[2] = {"Resource/Enemy/Cactus.png", "Resource/Enemy/Double-Cactus.png"};
static ii enemy_pos[TOTAL_ENEMY];
static int cnt_num = 0;
class Enemy: public BaseObject
{
protected:
    bool rand_a_new_cactus = false;
    int e_type, id_frame = 0, id_enemy;
    SDL_Rect frame_clip[TOTAL_FRAMES_OF_ENEMY];
    class ImpTimer e_timer;
    
public:
    Enemy(int type);
    
    ~Enemy(){};
    
    void generateEnemy();
    
    bool loadImg(SDL_Renderer* &renderer);
    
    void move(int& speed);
    
    void Render(SDL_Renderer* &renderer);
    void RenderLose (SDL_Renderer* &renderer);
    int getType() {return e_type; }
    
    void Free();
};

#endif /* Enemy_h */
