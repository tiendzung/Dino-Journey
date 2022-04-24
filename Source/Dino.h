//
//  Dino.h
//  Project Game
//
//  Created by Nguyễn Tiến Dũng on 4/24/22.
//  Copyright © 2022 Nguyễn Tiến Dũng. All rights reserved.
//

#ifndef Dino_h
#define Dino_h

#include "CommonFunction.h"
#include "Timer.h"

#define JUMP 1
#define FALL 2
#define RUN  0

class Dino
{
protected:
    static const int JUMP_SPEED = 6;
    static const int FALL_SPEED = 7;
    const string dino_type[4] =
    {
        "Resource/MainDino/DinoBlue.png",
        "Resource/MainDino/DinoRed.png",
        "Resource/MainDino/DinoGreen.png",
        "Resource/MainDino/DinoGold.png",
    };
    SDL_Texture* p_object;
    SDL_Rect r_object, d_object;
    SDL_Rect frame_clip[RUNNING_FRAMES];
    int status;
    
public:
    Dino();
    ~Dino() {};
    bool onGround();
    void HandleEvent(SDL_Event& e);
    void move();
    
    bool loadIMG(int type_dino, SDL_Renderer* renderer);

    void Render(SDL_Renderer* renderer, ImpTimer& Dino_Timer,int &id_frame);
//    void Show(SDL_Renderer* renderer);
    int getPosX();
    int getPosY();
};

#endif /* Dino_h */
