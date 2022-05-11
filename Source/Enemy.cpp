//
//  Enemy.cpp
//  Dino Journey
//
//  Created by Nguyễn Tiến Dũng on 4/24/22.
//  Copyright © 2022 Nguyễn Tiến Dũng. All rights reserved.
//

#include "Enemy.h"

Enemy::Enemy(int type)
{
    e_type = type; id_enemy = cnt_num;
    cnt_num++;
}

void Enemy::generateEnemy()
{
    d_object.x = rand() % ENEMY_RANGE + SCREEN_WIDTH;
    
    if(e_type == IN_AIR_ENEMY)
    {
        id_frame = 0;
        d_object.y = rand() % (MAX_HEIGHT - MIN_HEIGHT + 1) + MIN_HEIGHT;
    }
    else if(e_type == ON_GROUND_ENEMY)
    {
        d_object.y = GROUND - GRASS_HEIGHT;
    }
    
    if(id_enemy != 0)
        d_object.x = (d_object.x - enemy_pos[id_enemy-1].second >= ENEMY_RANGE) ? d_object.x : enemy_pos[id_enemy-1].second + ENEMY_RANGE;
    
    enemy_pos[id_enemy] = ii(e_type, d_object.x);
}

bool Enemy::loadImg(SDL_Renderer* &renderer)
{
    bool success = false;
    if(e_type == IN_AIR_ENEMY)
    {
        e_timer.start();
        success = BaseObject::loadIMG("Resource/Enemy/Bat.png", renderer);
        d_object = {d_object.x, d_object.y, d_object.w/TOTAL_FRAMES_OF_ENEMY, d_object.h };
        for(int i = 0; i < TOTAL_FRAMES_OF_ENEMY; i++)
        {
            frame_clip[i].x = d_object.w * i;
            frame_clip[i].y = 0;
            frame_clip[i].w = d_object.w;
            frame_clip[i].h = d_object.h;
        }
    }
    else if(e_type == ON_GROUND_ENEMY)
    {
        string path = ground_path[rand()%2];
        success = BaseObject::loadIMG(path, renderer);
        d_object = {d_object.x, d_object.y, d_object.w, d_object.h };
        
    }
    return success;
}

void Enemy::move(int &speed)
{
    int max_pos = 0;
    d_object.x = enemy_pos[id_enemy].second;
    d_object.x = d_object.x - (ENEMY_SPEED + speed);
    enemy_pos[id_enemy] = ii(e_type, d_object.x);
    
    if(d_object.x + d_object.w <= 0)
    {
        for(int i = 0; i < TOTAL_ENEMY; i++)
        {
            ii s = enemy_pos[i];
            if(i == id_enemy) continue;
            max_pos = max(s.second, max_pos);
        }
        d_object.x = rand() % ENEMY_RANGE + max(SCREEN_WIDTH + rand()%GOOD_RANGE , max_pos + ENEMY_RANGE);
        enemy_pos[id_enemy] = ii(e_type, d_object.x);
        
        for(int i = 0; i < TOTAL_ENEMY; i++)
        {
            if(i == id_enemy) continue;
            if(enemy_pos[i].second > SCREEN_WIDTH)
            {
                swap(enemy_pos[i].second, enemy_pos[id_enemy].second);
                
                break;
            }
        }
        
        if(e_type == IN_AIR_ENEMY)
        {
            id_frame = 0;
            d_object.y = rand() % (MAX_HEIGHT - MIN_HEIGHT + 1) + MIN_HEIGHT;
        }
        else if(e_type == ON_GROUND_ENEMY)
        {
            d_object.y = GROUND - GRASS_HEIGHT;
        }
        if(e_type == ON_GROUND_ENEMY)
        {
            rand_a_new_cactus = true;
        }
    }
}

void Enemy::Render(SDL_Renderer* &renderer)
{
    if(e_type == IN_AIR_ENEMY)
    {
        SDL_RenderCopy(renderer, p_object, &frame_clip[id_frame], &d_object);
        int real_enemy_time = e_timer.get_Ticks();
        
        if(real_enemy_time >= 1000/ENEMY_FPS)
        {
            id_frame++;
            if(id_frame == TOTAL_FRAMES_OF_ENEMY) id_frame = 0;
            e_timer.start();
        }
    }
    else if(e_type == ON_GROUND_ENEMY)
    {
        if(rand_a_new_cactus == true)
        {
            rand_a_new_cactus = false;
            SDL_DestroyTexture(p_object);
            string path = ground_path[rand()%2];
            BaseObject::loadIMG(path, renderer);
        }
        SDL_RenderCopy(renderer, p_object, &r_object, &d_object);
    }
}

void Enemy::RenderLose(SDL_Renderer* &renderer)
{
    if(e_type == IN_AIR_ENEMY)
    {
        SDL_RenderCopy(renderer, p_object, &frame_clip[id_frame], &d_object);
        int real_enemy_time = e_timer.get_Ticks();
    }
    else if(e_type == ON_GROUND_ENEMY)
    {
        if(rand_a_new_cactus == true)
        {
            rand_a_new_cactus = false;
            SDL_DestroyTexture(p_object);
            string path = ground_path[rand()%2];
            BaseObject::loadIMG(path, renderer);
        }
        SDL_RenderCopy(renderer, p_object, &r_object, &d_object);
    }
}

void Enemy::Free()
{
    BaseObject::Free();
    cnt_num = 0;
}
