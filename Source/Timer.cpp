//
//  Timer.cpp
//  Project Game
//
//  Created by Nguyễn Tiến Dũng on 4/24/22.
//  Copyright © 2022 Nguyễn Tiến Dũng. All rights reserved.
//

#include "CommonFunction.h"
#include "Timer.h"

ImpTimer::ImpTimer()
{
    start_tick = 0;
    paused_tick = 0;
    
    paused = started = false;
}

void ImpTimer::start()
{
    started = true;
    paused = false;
    start_tick = SDL_GetTicks();
}

void ImpTimer::stop()
{
    paused = true;
    started = false;
}

void ImpTimer::pause()
{
    if(started == true && paused == false)
    {
        paused = true;
        paused_tick = SDL_GetTicks() - start_tick;
    }
}

void ImpTimer::unpause()
{
    if (paused == true)
    {
        paused = false;
        start_tick = SDL_GetTicks();
        paused_tick = 0;
    }
}

int ImpTimer::get_Ticks()
{
    if (started == true)
    {
        if(paused == true)
        {
            return paused_tick;
        }
        else
        {
            return SDL_GetTicks() - start_tick;
        }
    }
    return 0;
}

bool ImpTimer::is_Started()
{
    return started;
}

bool ImpTimer::is_Paused()
{
    return paused;
}
