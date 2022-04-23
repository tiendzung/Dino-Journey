//
//  Object.h
//  Project Game
//
//  Created by Nguyễn Tiến Dũng on 4/23/22.
//  Copyright © 2022 Nguyễn Tiến Dũng. All rights reserved.
//

#ifndef Object_h
#define Object_h
#include "CommonFunction.h"

class BaseObject
{
protected:
    SDL_Texture* p_object;
    SDL_Rect r_object, d_object;
    
public:
    BaseObject();
    ~BaseObject();
    void setRect(const int& x, const int& y) { r_object.x = x; r_object.y = y; }
    void setDesRect(const int& x, const int& y, const int& w, const int& h)
    {
        d_object.x = x; d_object.y = y; d_object.w = w; d_object.h = h;
        if(w < 0 && h < 0)
        {
            d_object.w = r_object.w;
            d_object.h = r_object.h;
        }
    }
    SDL_Texture* getObject() const { return p_object; }
    SDL_Rect getRect() const { return r_object; }
    
    int getWidth() { return d_object.w; }
    int getHeight() { return d_object.h; }
    
    bool loadIMG(string, SDL_Renderer* renderer);
    void Render(SDL_Renderer* renderer);
    
    void Free();
};

#endif /* Object_h */
