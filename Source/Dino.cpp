//
//  Dino.cpp
//  Project Game
//
//  Created by Nguyễn Tiến Dũng on 4/24/22.
//  Copyright © 2022 Nguyễn Tiến Dũng. All rights reserved.
//

#include "Dino.h"
#include "CommonFunction.h"
#include "SDL_InitWindow.h"
Dino::Dino()
{
    d_object.x = SCREEN_WIDTH - 700;
    d_object.y = GROUND;
    d_object.w = d_object.h = 57;
    
    status = 0;
}

bool Dino::onGround()
{
    return d_object.y == GROUND;
}

void Dino::HandleEvent(SDL_Event& e)
{
    if (e.type == SDL_KEYDOWN)
    {
        switch (e.key.keysym.sym)
        {
            case SDLK_SPACE:
            case SDLK_UP:
            {
                if (onGround() == true&&e.key.repeat == 0)
                {
                    //                    Mix_PlayChannel(MIX_CHANNEL, gJump, NOT_REPEATITIVE);
                    status = JUMP;
                }
            }
        }
    }
}

void Dino::move()
{
    if (status == JUMP && d_object.y >= MAX_HEIGHT)
    {
        d_object.y += -JUMP_SPEED;
    }
    if (d_object.y <= MAX_HEIGHT)
    {
        status = FALL;
    }
    if (status == FALL && d_object.y < GROUND)
    {
        d_object.y += FALL_SPEED;
    }
}

bool Dino::loadIMG(string path, SDL_Renderer* renderer)
{
    SDL_Texture* new_texture = NULL;
    SDL_Surface* load_surface = IMG_Load( path.c_str() );
    
    if(load_surface != NULL)
    {
        SDL_SetColorKey(load_surface, SDL_TRUE, SDL_MapRGB( load_surface ->  format, COLOR_KEY_R, COLOR_KEY_G, COLOR_KEY_B) );
        new_texture = SDL_CreateTextureFromSurface(renderer, load_surface);
        if(new_texture != NULL)
        {
            r_object.w = load_surface -> w;
            r_object.h = load_surface -> h;
            p_object = new_texture;
            
            for(int i = 0; i < RUNNING_FRAMES; i++)
            {
                frame_clip[i].x = r_object.w/RUNNING_FRAMES * i;
                frame_clip[i].y = 0;
                frame_clip[i].w = r_object.w/RUNNING_FRAMES;
                frame_clip[i].h = r_object.w/RUNNING_FRAMES;
            }
            
            SDL_FreeSurface(load_surface);
            return true;
        }
        else  logSDLError("Unable to create texture from " + path + " SDL_Error: ", SDL_GetError());
    }
    else logSDLError("Unable to load image " + path + " SDL_image Error: ", IMG_GetError());
    
    return false;
}

void Dino::Render(SDL_Renderer *renderer, int id_frame)
{
    d_object.w = frame_clip[id_frame].w;
    d_object.h = frame_clip[id_frame].h;
    SDL_RenderCopy(renderer, p_object, &frame_clip[id_frame], &d_object);
}


int Dino::getPosX()
{
    return d_object.x;
}
int Dino::getPosY()
{
    return d_object.y;
}
