//
//  Timer.h
//  Dino Journey
//
//  Created by Nguyễn Tiến Dũng on 4/24/22.
//  Copyright © 2022 Nguyễn Tiến Dũng. All rights reserved.
//

#ifndef Timer_h
#define Timer_h
class ImpTimer
{
private:
    int start_tick;
    int paused_tick;
    
    bool paused;
    bool started;
    
public:
    ImpTimer();
    ~ImpTimer(){};
    
    void start();
    void stop();
    void pause();
    void unpause();
    
    bool is_Started();
    bool is_Paused();
    
    int get_Ticks();
};

#endif /* Timer_h */
