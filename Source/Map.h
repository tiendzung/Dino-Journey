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
    string bg_layer[2][9];
    string bg_ground[2];
    BaseObject backGround[9];
    BaseObject Ground;
    
public:
    Map()
    {
        bg_ground[0] = "Resource/BackGround/ground.png";
        bg_layer[0][0] = "Resource/BackGround/layer01.png";
        bg_layer[0][1] = "Resource/BackGround/layer02.png";
        bg_layer[0][2] = "Resource/BackGround/layer03.png";
        bg_layer[0][3] = "Resource/BackGround/layer04.png";
        bg_layer[0][4] = "Resource/BackGround/layer05.png";
        bg_layer[0][5] = "Resource/BackGround/layer06.png";
        bg_layer[0][6] = "Resource/BackGround/layer07.png";
        bg_layer[0][7] = "Resource/BackGround/layer08.png";
        bg_layer[0][8] = "Resource/BackGround/layer09.png";
        
        bg_ground[1] = "Resource/BackGround2/ground.png";
        bg_layer[1][0] = "Resource/BackGround2/Hills Layer 01.png";
        bg_layer[1][1] = "Resource/BackGround2/Hills Layer 02.png";
        bg_layer[1][2] = "Resource/BackGround2/Hills Layer 03.png";
        bg_layer[1][3] = "Resource/BackGround2/Hills Layer 04.png";
        bg_layer[1][4] = "Resource/BackGround2/Hills Layer 05.png";
        bg_layer[1][5] = "Resource/BackGround2/Hills Layer 06.png";
    };
    ~Map(){};
    
    bool loadBackGround(SDL_Renderer* renderer, int TOTAL, int type);
    bool loadGround(SDL_Renderer* renderer, int type);
    
    void renderScrollingBackground(/*vector <double> &offSetSpeed,*/ SDL_Renderer* renderer, int TOTAL);
    void renderScrollingGround(/*int &speed, int& acceleration,*/ SDL_Renderer* screen);
    
    void Free(int type);
};

#endif /* Map_h */
