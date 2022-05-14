//
//  Dino.h
//  Dino Journey
//
//  Created by Nguyễn Tiến Dũng on 4/24/22.
//  Copyright © 2022 Nguyễn Tiến Dũng. All rights reserved.
//

#ifndef Dino_h
#define Dino_h

#include "CommonFunction.h"
#include "Timer.h"

#define RUN  0
#define JUMP 1
#define FALL 2

const double GRAVITY_FALL = 0.5 /*0.41*/;
static const int DINO_FPS = 15;
static const int DINO_HURT_FPS = 2;
static const int TOTAL_FRAMES_OF_DINO = 9;
static const int TOTAL_TYPE_OF_DINO = 4;
static const int FRAMES_OF_HURT = 6;
static const int SKIP_FRAME = 7;
const int DINO_POS_X = SCREEN_WIDTH - 700;
const string dino_type[TOTAL_TYPE_OF_DINO] =
{
    "Resource/MainDino/GreenTest.png",
    "Resource/MainDino/RedTest.png",
    "Resource/MainDino/GoldTest.png",
    "Resource/MainDino/BlueTest.png",
};

class Dino
{
protected:
    
    int id_frame = 0;
    class ImpTimer dino_timer;
    
    double vJump = 0;
    SDL_Texture* p_object;
    SDL_Rect r_object, d_object;
    SDL_Rect frame_clip[TOTAL_FRAMES_OF_DINO];
//    int status = FALL;
    
public:
    Dino();
    ~Dino() {};
    bool onGround();
    void HandleEvent(SDL_Event &e, bool &mute_volume, Mix_Chunk* gJumpMusic);
    void move();
    
    bool loadIMG(int type_dino, SDL_Renderer* &renderer);

    void Render(SDL_Renderer* &renderer, bool move);
    void RenderLose(SDL_Renderer* &renderer);
    int getPosX();
    int getPosY();
    
    int getWidth();
    int getHeight();
    
    void Free();
};

#endif /* Dino_h */
