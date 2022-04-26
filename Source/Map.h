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

const static int TOTAL_TYPE_OF_BACKGOUND = 6;
const static int BACKGROUND_TOTAL_LAYERS = 11;

class Map
{
private:
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
        grass_ground[0] = "Resource/BackGround1/grass_ground.png";
        bg_ground[0] = "Resource/BackGround1/ground.png";
        bg_layer[0][0] = "Resource/BackGround1/layer01.png";
        bg_layer[0][1] = "Resource/BackGround1/layer02.png";
        bg_layer[0][2] = "Resource/BackGround1/layer03.png";
        bg_layer[0][3] = "Resource/BackGround1/layer04.png";
        bg_layer[0][4] = "Resource/BackGround1/layer05.png";
        bg_layer[0][5] = "Resource/BackGround1/layer06.png";
        bg_layer[0][6] = "Resource/BackGround1/layer07.png";
        bg_layer[0][7] = "Resource/BackGround1/layer08.png";
        bg_layer[0][8] = "Resource/BackGround1/layer09.png";
        
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
        
        grass_ground[3] = "Resource/BackGround4/grass_ground.png";
        bg_ground[3] = "Resource/BackGround4/ground.png";
        bg_layer[3][0] = "Resource/BackGround4/layer1.png";
        bg_layer[3][1] = "Resource/BackGround4/layer2.png";
        bg_layer[3][2] = "Resource/BackGround4/layer3.png";

        grass_ground[4] = "Resource/BackGround5/grass_ground.png";
        bg_ground[4] = "Resource/BackGround5/1 Layer1.png";
        bg_layer[4][0] = "Resource/BackGround5/9 Background.png";
        bg_layer[4][1] = "Resource/BackGround5/8 Stars2.png";
        bg_layer[4][2] = "Resource/BackGround5/8 Stars.png";
        bg_layer[4][3] = "Resource/BackGround5/7 Clouds.png";
        bg_layer[4][4] = "Resource/BackGround5/7 Clouds.png";
        bg_layer[4][5] = "Resource/BackGround5/6 Sun.png";
        bg_layer[4][6] = "Resource/BackGround5/5 Mountains.png";
        bg_layer[4][7] = "Resource/BackGround5/4 Layer4.png";
        bg_layer[4][8] = "Resource/BackGround5/3 Layer3.png";
        bg_layer[4][9] = "Resource/BackGround5/2 Layer2.png";
        bg_layer[4][10] = "Resource/BackGround5/ground.png";
        
        grass_ground[5] = "Resource/BackGround6/grass_ground.png";
        bg_ground[5] = "Resource/BackGround6/ground.png";
        bg_layer[5][0] = "Resource/BackGround6/-6.png";
        bg_layer[5][1] = "Resource/BackGround6/-5.png";
        bg_layer[5][2] = "Resource/BackGround6/-4.png";
        bg_layer[5][3] = "Resource/BackGround6/-3.png";
        bg_layer[5][4] = "Resource/BackGround6/-2.png";
        bg_layer[5][5] = "Resource/BackGround6/-1.png";
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
