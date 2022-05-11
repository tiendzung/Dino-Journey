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

#define BUTTON_MOUSE_UP  0
#define BUTTON_MOUSE_DOWN  1
#define ONE_SPRITE 1
#define TWO_SPRITES 2
#define MAX_FRAMES 2
class Button: public BaseObject
{
protected:
    int TOTAL_FRAMES_BUTTON = ONE_SPRITE;
    int curX, curY;
    bool is_map = false;
    SDL_Rect frame_clip[MAX_FRAMES];
    
public:
    int status = BUTTON_MOUSE_UP;
    Button(){};
    Button(int x,int y, int sprite);
    ~Button(){};
    bool loadImg(string path, SDL_Renderer* &renderer);
    bool inSide();
    void setDes(int x,int y, int w, int h);
    void renderButton(SDL_Renderer* &renderer);
};

#endif /* Button_h */
