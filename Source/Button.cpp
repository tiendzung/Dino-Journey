//
//  Button.cpp
//  Dino Journey
//
//  Created by Nguyễn Tiến Dũng on 5/7/22.
//  Copyright © 2022 Nguyễn Tiến Dũng. All rights reserved.
//

#include "Button.h"
Button::Button(int x, int y)
{
    d_object.x = x;
    d_object.y = y;
}
void Button:: setXY(int x,int y)
{
    d_object.x = x;
    d_object.y = y;
}
bool Button:: loadImg(string path, SDL_Renderer* &renderer)
{
    bool success = false;
    success = BaseObject::loadIMG(path.c_str(), renderer);
    d_object = {d_object.x, d_object.y, d_object.w/TOTAL_FRAMES_BUTTON, d_object.h };
    for(int i = 0; i < TOTAL_FRAMES_BUTTON; i++)
    {
        frame_clip[i].x = d_object.w * i;
        frame_clip[i].y = 0;
        frame_clip[i].w = d_object.w;
        frame_clip[i].h = d_object.w;
    }
    return success;
}
bool Button:: inSide()
{
    bool inside = false;
    SDL_GetMouseState(&curX, &curY);
    
    if(d_object.x + d_object.w > curX && curX > d_object.x && d_object.y + d_object.h > curY && curY > d_object.y)
        inside = true;
    
    if(inside == false) status = BUTTON_MOUSE_UP;
    else status = BUTTON_MOUSE_DOWN;
        
    return inside;
}

void Button::renderButton(SDL_Renderer* &renderer)
{
    SDL_RenderCopy(renderer, p_object, &frame_clip[status], &d_object);
    return;
}

