//
//  Button.h
//  Dino Journey
//
//  Created by Nguyễn Tiến Dũng on 5/7/22.
//  Copyright © 2022 Nguyễn Tiến Dũng. All rights reserved.
//

#ifndef Button_h
#define Button_h
#include "Object.h"
const int TOTAL_FRAMES_BUTTON = 2;

#define BUTTON_MOUSE_UP  0
#define BUTTON_MOUSE_DOWN  1

class Button: public BaseObject
{
protected:
    int curX, curY;
    int status = BUTTON_MOUSE_UP;
    SDL_Rect frame_clip[2];
public:
    Button(){};
    Button(int x,int y);
    ~Button(){};
    bool loadImg(string path, SDL_Renderer* &renderer);
    bool inSide(SDL_Event event);
    void setXY(int x,int y);
    void renderButton(SDL_Renderer* &renderer);
};

#endif /* Button_h */
