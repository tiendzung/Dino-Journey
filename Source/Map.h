//
//  Map.h
//  Project Game
//
//  Created by Nguyễn Tiến Dũng on 4/23/22.
//  Copyright © 2022 Nguyễn Tiến Dũng. All rights reserved.
//

#ifndef Map_h
#define Map_h

#include "CommonFunction.h"
#include "Object.h"

class Map
{
private:
    BaseObject backGround[BACKGROUND_LAYER_1];
    BaseObject Ground;
    
public:
    Map(){};
    ~Map(){};
    
    bool loadBackGround(SDL_Renderer* renderer, int TOTAL);
    bool loadGround(string path, SDL_Renderer* renderer);
    
    void renderScrollingBackground(/*vector <double> &offSetSpeed,*/ SDL_Renderer* renderer, int TOTAL);
    void renderScrollingGround(/*int &speed, int& acceleration,*/ SDL_Renderer* screen);
    
    void Free();
};

#endif /* Map_h */
