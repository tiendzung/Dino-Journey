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

enum KIND_GROUND
{
    CACTUS,
    DOUBLE_CACTUS,
    DOG
};
enum KIND_AIR
{
    BAT,
    HELICORPTER
};
const int MIN_HEIGHT = 350;
const int MAX_HEIGHT = 330;

static const int MAX_FRAMES = 5;
static const int TOTAL_ENEMY = 4;

static const int IN_AIR_ENEMY = 1;
static const int ON_GROUND_ENEMY = 2;
static const int ENEMY_RANGE = 240; /*240*/
static const int GOOD_RANGE = 350;

static const int TOTAL_RAND_AG = 2;
static const int TOTAL_RAND_EG = 3;

static const int TOTAL_FRAMES_OF_AIR[TOTAL_RAND_AG] = {5, 4};
static const int TOTAL_FRAMES_OF_GROUND[TOTAL_RAND_EG] = {1, 1, 4};

static const int AIR_ENEMY_FPS[TOTAL_RAND_AG] = {15, 5};
static const int GROUND_ENEMY_FPS[TOTAL_RAND_EG] = {1, 1, 5};

static const string air_path[TOTAL_RAND_AG] = {
    "Resource/Enemy/Air1.png",
    "Resource/Enemy/Air2.png"
};

static const string ground_path[TOTAL_RAND_EG] = {
    "Resource/Enemy/Cactus.png",
    "Resource/Enemy/Double-Cactus.png",
    "Resource/Enemy/Ground1.png",
    
};
static ii enemy_pos[TOTAL_ENEMY];
static int cnt_num = 0;
class Enemy: public BaseObject
{
protected:
    int air_id, ground_id;
    bool rand_a_new_cactus = false;
    int e_type, id_frame = 0, id_enemy;
    SDL_Rect frame_clip[MAX_FRAMES];
    class ImpTimer e_timer;
    
public:
    Enemy(int type);
    
    ~Enemy(){};
    
    void generateEnemy();
    
    bool loadImg(SDL_Renderer* &renderer);
    
    void move(int& speed, SDL_Renderer* &renderer);
    
    void Render(SDL_Renderer* &renderer, bool move);
    void RenderLose (SDL_Renderer* &renderer);
    int getType() {return e_type; }
    int getGround_id() { return ground_id; }
    int getAir_id() { return air_id; }
    void Free();
};

#endif /* Enemy_h */
