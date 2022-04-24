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
    const int DINO_FPS = 15;
    const int DINO_SPRITES = 6;
    
    int id_frame = 0;
    class ImpTimer Dino_Timer;
    
    double vJump = 0;
//    double vFail = 0;
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
//    int status = FALL;
    
public:
    Dino();
    ~Dino() {};
    bool onGround();
    void HandleEvent(SDL_Event& e, Mix_Chunk* gJumpMusic);
    void move();
    
    bool loadIMG(int type_dino, SDL_Renderer* renderer);

    void Render(SDL_Renderer* renderer);
//    void Show(SDL_Renderer* renderer);
    int getPosX();
    int getPosY();
    
    void Free();
};

#endif /* Dino_h */
