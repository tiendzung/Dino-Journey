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
    const static int TOTAL_TYPE_OF_BACKGOUND = 3;
    const static int BACKGROUND_TOTAL_LAYERS = 9;
    int type_id;
    string bg_layer[TOTAL_TYPE_OF_BACKGOUND][BACKGROUND_TOTAL_LAYERS];
    string bg_ground[TOTAL_TYPE_OF_BACKGOUND];
    string grass_ground[TOTAL_TYPE_OF_BACKGOUND];
    BaseObject backGround[BACKGROUND_TOTAL_LAYERS];
    BaseObject Ground;
    BaseObject GrassGround;
public:
    void update_id(int type_id)
    {
        this->type_id = type_id;
    }
    Map()
    {
        grass_ground[0] = "Resource/BackGround/grass_ground.png";
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
        
        grass_ground[1] = "Resource/BackGround2/grass_ground.png";
        bg_ground[1] = "Resource/BackGround2/ground.png";
        bg_layer[1][0] = "Resource/BackGround2/Hills Layer 01.png";
        bg_layer[1][1] = "Resource/BackGround2/Hills Layer 02.png";
        bg_layer[1][2] = "Resource/BackGround2/Hills Layer 03.png";
        bg_layer[1][3] = "Resource/BackGround2/Hills Layer 04.png";
        bg_layer[1][4] = "Resource/BackGround2/Hills Layer 05.png";
        bg_layer[1][5] = "Resource/BackGround2/Hills Layer 06.png";
    
        grass_ground[2] = "Resource/BackGround3/grass_ground.png";
        bg_ground[2] = "Resource/BackGround3/ground_test.png";
        bg_layer[2][0] = "Resource/BackGround3/layer1.png";
        bg_layer[2][1] = "Resource/BackGround3/layer2.png";
        bg_layer[2][2] = "Resource/BackGround3/layer3.png";
        bg_layer[2][3] = "Resource/BackGround3/layer4.png";
        bg_layer[2][4] = "Resource/BackGround3/clouds_mg_1.png";
        bg_layer[2][5] = "Resource/BackGround3/clouds_mg_2.png";
        bg_layer[2][6] = "Resource/BackGround3/clouds_mg_3.png";

    };
    ~Map(){};
    
    bool loadBackGround(SDL_Renderer* renderer, int TOTAL, int type);
    bool loadGround(SDL_Renderer* renderer, int type);
    bool loadGrassGround(SDL_Renderer* renderer, int type);
    
    void renderScrollingBackground(/*vector <double> &offSetSpeed,*/ SDL_Renderer* renderer, int TOTAL, vector <double> & bg_speed);
    void renderScrollingGround(int &speed, int& acceleration, SDL_Renderer* renderer);
    void renderScrollingGrass(int &speed, int& acceleration, SDL_Renderer* renderer);
    void Free(int type);
};

#endif /* Map_h */
