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
//    d_object.w = d_object.h = 57;
    
//    status = 0;
}

bool Dino::onGround()
{
    return d_object.y == GROUND;
}

void Dino::HandleEvent(SDL_Event& e, Mix_Chunk* gJumpMusic)
{
    if (e.type == SDL_KEYDOWN)
    {
        switch (e.key.keysym.sym)
        {
            case SDLK_SPACE:
            case SDLK_UP:
            {
                if (onGround() == true/*&&e.key.repeat == 0*/)
                {
                    Mix_PlayChannel(-1, gJumpMusic, 0);
//                    status = JUMP;
                    vJump = 8.5;
//                    vFail = 0;
                }
            }
        }
    }
}

void Dino::move()
{
//    if (status == JUMP && d_object.y >= MAX_HEIGHT)
//    {
        vJump -= GRAVITY_FALL;
        d_object.y += -vJump;
        if(d_object.y >= GROUND) vJump = GRAVITY_FALL;
        d_object.y = min(GROUND, d_object.y);
//    }
//    if (d_object.y <= MAX_HEIGHT)
//    {
//        status = FALL;
//        vJump = 8;
//    }
//    if (status == FALL && d_object.y < GROUND)
//    {
//        vFail += GRAVITY_FALL;
//        d_object.y += vFail;
//        d_object.y = min(GROUND, d_object.y);
//    }
}

bool Dino::loadIMG(int type_dino, SDL_Renderer* renderer)
{
    dino_timer.start();
    string path = dino_type[type_dino];
    SDL_Texture* new_texture = NULL;
    SDL_Surface* load_surface = IMG_Load( path.c_str() );
    
    if(load_surface != NULL)
    {
//        SDL_SetColorKey(load_surface, SDL_TRUE, SDL_MapRGB( load_surface ->  format, COLOR_KEY_R, COLOR_KEY_G, COLOR_KEY_B) );
        new_texture = SDL_CreateTextureFromSurface(renderer, load_surface);
        if(new_texture != NULL)
        {
            r_object.w = load_surface -> w;
            r_object.h = load_surface -> h;
            d_object.h = r_object.h;
            d_object.w = r_object.w/TOTAL_FRAMES_OF_DINO;
            p_object = new_texture;
        
            for(int i = 0; i < TOTAL_FRAMES_OF_DINO; i++)
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

void Dino::Render(SDL_Renderer *renderer)
{
    d_object.w = frame_clip[id_frame].w;
    d_object.h = frame_clip[id_frame].h;
    
    SDL_RenderCopy(renderer, p_object, &frame_clip[id_frame], &d_object);
    
    int real_dino_time = dino_timer.get_Ticks();
    if(real_dino_time >= 1000/DINO_FPS && this->onGround())
    {
        id_frame++;
        if(id_frame == TOTAL_FRAMES_OF_DINO) id_frame = 0;
        dino_timer.start();
    }
}


int Dino::getPosX()
{
    return d_object.x;
}
int Dino::getPosY()
{
    return d_object.y;
}

int Dino::getWidth()
{
    return d_object.w;
}
int Dino::getHeight()
{
    return d_object.h;
}

void Dino::Free()
{
    SDL_DestroyTexture(p_object);
}
