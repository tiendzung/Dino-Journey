//
//  Mouse.cpp
//  Dino Journey
//
//  Created by Nguyễn Tiến Dũng on 5/13/22.
//  Copyright © 2022 Nguyễn Tiến Dũng. All rights reserved.
//

#include "Mouse.h"

void Mouse::update()
{
    SDL_ShowCursor(false);
    SDL_GetMouseState(&d_object.x, &d_object.y);
    d_object.x -= 20;
    d_object.y -= 20;
}

//void Mouse::Render(SDL_Renderer* &renderer)
//{
//    if(d_object.x >= 0 && d_object.x <= SCREEN_WIDTH && d_object.y >= 0 &&d_object.y <= SCREEN_HEIGHT)
//    {
//        SDL_RenderCopy(renderer, p_object, &r_object, &d_object);
//    }
//}

bool Mouse::loadIMG(string path, SDL_Renderer* &renderer)
{
    mouse_timer.start();
    SDL_Texture* new_texture = NULL;
    SDL_Surface* load_surface = IMG_Load( path.c_str() );
    
    if(load_surface != NULL)
    {
        new_texture = SDL_CreateTextureFromSurface(renderer, load_surface);
        if(new_texture != NULL)
        {
            r_object.w = load_surface -> w;
            r_object.h = load_surface -> h;
            d_object.h = r_object.h;
            d_object.w = r_object.w/TOTAL_FRAMES_OF_MOUSE;
            p_object = new_texture;
            
            for(int i = 0; i < TOTAL_FRAMES_OF_MOUSE; i++)
            {
                frame_clip[i].x = d_object.w * i;
                frame_clip[i].y = 0;
                frame_clip[i].w = d_object.w;
                frame_clip[i].h = d_object.w;
            }
            
            SDL_FreeSurface(load_surface);
            return true;
        }
        else  logSDLError("Unable to create texture from " + path + " SDL_Error: ", SDL_GetError());
    }
    else logSDLError("Unable to load image " + path + " SDL_image Error: ", IMG_GetError());
    
    return false;
}

void Mouse::Render(SDL_Renderer* &renderer)
{
    d_object.w = frame_clip[id_frame].w;
    d_object.h = frame_clip[id_frame].h;
    
    SDL_RenderCopy(renderer, p_object, &frame_clip[id_frame], &d_object);
    
    int real_mouse_time = mouse_timer.get_Ticks();
    if(real_mouse_time >= 1000/FPS_MOUSE)
    {
        id_frame++;
        if(id_frame >= TOTAL_FRAMES_OF_MOUSE) id_frame = 0;
        mouse_timer.start();
    }
}
