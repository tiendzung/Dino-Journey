//
//  Enemy.cpp
//  Project Game
//
//  Created by Nguyễn Tiến Dũng on 4/24/22.
//  Copyright © 2022 Nguyễn Tiến Dũng. All rights reserved.
//

#include "Enemy.h"

//static vector<ii> enemy_pos;

Enemy::Enemy(int type)
{
    e_type = type; id_enemy = cnt_num;
    d_object.x = rand() % ENEMY_RANGE + SCREEN_WIDTH;
    
    if(type == IN_AIR_ENEMY)
    {
        id_frame = 0;
        d_object.y = rand() % (MAX_HEIGHT - MIN_HEIGHT + 1) + MIN_HEIGHT;
    }
    else if(type == ON_GROUND_ENEMY)
    {
        d_object.y = GROUND - GRASS_HEIGHT;
    }
    
    if(id_enemy != 0)
    d_object.x = (d_object.x - enemy_pos[id_enemy-1].second >= ENEMY_RANGE) ? d_object.x : enemy_pos[id_enemy-1].second + ENEMY_RANGE;
    
    enemy_pos[id_enemy] = ii(type, d_object.x);
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

bool Enemy::loadImg(SDL_Renderer *renderer)
{
    bool success = false;
    if(e_type == IN_AIR_ENEMY)
    {
        e_timer.start();
        BaseObject::loadIMG("Resource/Enemy/Bat.png", renderer);
        success = inAirEnemy.loadIMG("Resource/Enemy/Bat.png", renderer);
        d_object = {d_object.x, d_object.y, inAirEnemy.getWidth()/TOTAL_FRAMES_OF_ENEMY, inAirEnemy.getHeight() };
        for(int i = 0; i < TOTAL_FRAMES_OF_ENEMY; i++)
        {
            frame_clip[i].x = d_object.w * i;
            frame_clip[i].y = 0;
            frame_clip[i].w = d_object.w;
            frame_clip[i].h = d_object.w;
        }
    }
    else if(e_type == ON_GROUND_ENEMY)
    {
        string path = ground_path[rand()%2];
        BaseObject::loadIMG(path, renderer);
        success = onGroundEnemy.loadIMG(path, renderer);
        d_object = {d_object.x, d_object.y, onGroundEnemy.getWidth(), onGroundEnemy.getHeight() };
        
    }
    return success;
}

void Enemy::move(int &acceleration)
{
    double max_pos = 0;
    d_object.x = enemy_pos[id_enemy].second;
    d_object.x = d_object.x - (ENEMY_SPEED + acceleration);
    enemy_pos[id_enemy] = ii(e_type, d_object.x);
    if(d_object.x + d_object.w <= 0)
    {
        for(int i = 0; i < 4; i++)
        {
            ii s = enemy_pos[i];
            if(i == id_enemy) continue;
            max_pos = max(s.second, max_pos);
        }
        d_object.x = rand() % ENEMY_RANGE + max(double(SCREEN_WIDTH + rand()%GOOD_RANGE), max_pos + ENEMY_RANGE);
        enemy_pos[id_enemy] = ii(e_type, d_object.x);
        for(int i = 0; i < 4; i++)
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
    }
}

void Enemy::Render(SDL_Renderer* renderer)
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
        SDL_RenderCopy(renderer, p_object, &r_object, &d_object);
    }
}

void Enemy::Free()
{
    BaseObject::Free();
    cnt_num = 0;
    if(e_type == IN_AIR_ENEMY) inAirEnemy.Free();
    else onGroundEnemy.Free();
}
