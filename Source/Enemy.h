//
//  Enemy.h
//  Project Game
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
#define ii pair<int, double>
static const int TOTAL_FRAMES_OF_ENEMY = 5;
static const int IN_AIR_ENEMY = 1;
static const int ON_GROUND_ENEMY = 2;
static const int ENEMY_RANGE = 150; /*240*/
static const int GOOD_RANGE = 350;
static const int ENEMY_FPS = 15;
static const double ENEMY_GROUND_WIDTH = 37;
static const int TOTAL_RAND_EG = 2;
static const string ground_path[2] = {"Resource/Enemy/Cactus.png", "Resource/Enemy/Double-Cactus.png"};

static ii enemy_pos[4];
static int cnt_num = 0;
class Enemy: BaseObject
{
protected:
    int e_type, x_back, id_frame = 0, id_enemy;
//    SDL_Rect r_object, d_object;
    SDL_Rect frame_clip[TOTAL_FRAMES_OF_ENEMY];
    BaseObject inAirEnemy, onGroundEnemy;
    class ImpTimer e_timer;
public:
    Enemy(int type);
    
    ~Enemy(){};
    
//    void Rebuild(int type);
    
    bool loadImg(SDL_Renderer* renderer);
    
    void move(int& acceleration);
    
    void Render(SDL_Renderer* renderer);
        
    int getX() { return d_object.x; }
    
    int getY() { return d_object.y; }

    int getW() {return d_object.w; }
    
    int getH() {return d_object.h; }
    
    int getType() {return e_type; }
    
    void Free();
};

#endif /* Enemy_h */
