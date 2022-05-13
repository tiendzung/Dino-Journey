//
//  Mouse.h
//  Dino Journey
//
//  Created by Nguyễn Tiến Dũng on 5/13/22.
//  Copyright © 2022 Nguyễn Tiến Dũng. All rights reserved.
//

#ifndef Mouse_h
#define Mouse_h

#include "CommonFunction.h"
#include "Object.h"
#include "Timer.h"
#include "SDL_InitWindow.h"
const int TOTAL_FRAMES_OF_MOUSE = 47;
const int FPS_MOUSE = 6;
class Mouse: public BaseObject
{
protected:
    SDL_Rect point;
    SDL_Rect frame_clip[TOTAL_FRAMES_OF_MOUSE];
    ImpTimer mouse_timer;
    int id_frame;
public:
    Mouse()
    {
        d_object.w = 25;
        d_object.h = 25;
    }
    ~Mouse(){};
    bool loadIMG(string path, SDL_Renderer* &renderer);
    void update();
    void Render(SDL_Renderer* &renderer);
};


#endif /* Mouse_h */
