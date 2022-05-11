//
//  Object.cpp
//  Dino Journey
//
//  Created by Nguyễn Tiến Dũng on 4/23/22.
//  Copyright © 2022 Nguyễn Tiến Dũng. All rights reserved.
//

#include "SDL_InitWindow.h"
#include "Object.h"

BaseObject::BaseObject()
{
    p_object = NULL;
    r_object.x = 0;
    r_object.y = 0;
    r_object.w = 0;
    r_object.h = 0;
    d_object.x = 0;
    d_object.y = 0;
}

BaseObject::~BaseObject()
{
    
}

bool BaseObject::loadIMG(string path, SDL_Renderer* &renderer)
{
    SDL_Texture* new_texture = NULL;
    SDL_Surface* load_surface = IMG_Load( path.c_str() );
    
    if(load_surface != NULL)
    {
//        SDL_SetColorKey(load_surface, SDL_TRUE, SDL_MapRGB( load_surface ->  format, COLOR_KEY_R, COLOR_KEY_G, COLOR_KEY_B) );
        new_texture = SDL_CreateTextureFromSurface(renderer, load_surface);
        if(new_texture != NULL)
        {
            r_object.w = d_object.w = load_surface -> w;
            r_object.h = d_object.h = load_surface -> h;
            p_object = new_texture;
            SDL_FreeSurface(load_surface);
            return true;
        }
        else  logSDLError("Unable to create texture from " + path + " SDL_Error: ", SDL_GetError());
    }
    else logSDLError("Unable to load image " + path + " SDL_image Error: ", IMG_GetError());

    return false;
}
bool BaseObject::loadText(string text, TTF_Font *g_font, SDL_Color text_color, SDL_Renderer *renderer)
{
    SDL_Texture* new_texture = NULL;
    SDL_Surface* load_surface = TTF_RenderText_Solid(g_font, text.c_str(), text_color);
    if (load_surface == NULL) return 0;
    
    new_texture = SDL_CreateTextureFromSurface(renderer, load_surface);
    
    if (new_texture != NULL)
    {
        r_object.w = d_object.w = load_surface->w;
        r_object.h = d_object.h = load_surface->h;
    }
    
    SDL_FreeSurface(load_surface);
    p_object = new_texture ;
    
    return (p_object != NULL) ;
}
void BaseObject::Render(SDL_Renderer* &renderer)
{
//    SDL_Rect dest_rect = {d_object.x, d_object.y, d_object.w, d_object.h};
    SDL_RenderCopy(renderer, p_object, &r_object, &d_object);
}

void BaseObject::RenderXY(int x, int y, SDL_Renderer* &renderer)
{
    SDL_Rect desR = {x, y, d_object.w, d_object.h};
    SDL_RenderCopy(renderer, p_object, &r_object, &desR);
}
void BaseObject::Free()
{
    if(p_object != NULL)
    {
        SDL_DestroyTexture(p_object);
        p_object = NULL;
        r_object.x = 0;
        r_object.y = 0;
        r_object.w = 0;
        r_object.h = 0;
        d_object.x = 0;
        d_object.y = 0;
        d_object.w = 0;
        d_object.h = 0;
    }
}
