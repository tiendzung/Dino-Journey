//
//  Map.h
//  Dino Journey
//
//  Created by Nguyễn Tiến Dũng on 4/23/22.
//  Copyright © 2022 Nguyễn Tiến Dũng. All rights reserved.
//

#ifndef Map_h
#define Map_h

#include "CommonFunction.h"
#include "Object.h"
enum KIND_OF_MAP
{
    FOREST,
    HILLS,
    CLOUD_MOUTAIN,
    NIGHT_CITY,
    DESERT,
    FAR_CITY,
    TOTAL_TYPE_OF_BACKGOUND
};
const static int BACKGROUND_TOTAL_LAYERS = 11;

const int TOTAL_BACKGROUND_LAYER[TOTAL_TYPE_OF_BACKGOUND] = { 9, 6, 7, 3, 11, 6 };

const double LAYER_SPEED[BACKGROUND_TOTAL_LAYERS] =
{
    0.15, 0.25, 0.5, 0.75, 1, 1.25, 1.5, 1.75, 2.0, 2.25, 2.5
//    0.25, 0.75, 1.25, 1.5, 1.75, 2, 2.25, 2.5, 3, 3.25, 3.5
};
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
        grass_ground[FOREST] = "Resource/BackGround1/grass_ground.png";
        bg_ground[FOREST] = "Resource/BackGround1/ground.png";
        bg_layer[FOREST][0] = "Resource/BackGround1/layer01.png";
        bg_layer[FOREST][1] = "Resource/BackGround1/layer02.png";
        bg_layer[FOREST][2] = "Resource/BackGround1/layer03.png";
        bg_layer[FOREST][3] = "Resource/BackGround1/layer04.png";
        bg_layer[FOREST][4] = "Resource/BackGround1/layer05.png";
        bg_layer[FOREST][5] = "Resource/BackGround1/layer06.png";
        bg_layer[FOREST][6] = "Resource/BackGround1/layer07.png";
        bg_layer[FOREST][7] = "Resource/BackGround1/layer08.png";
        bg_layer[FOREST][8] = "Resource/BackGround1/layer09.png";
        
        grass_ground[HILLS] = "Resource/BackGround2/grass_ground.png";
        bg_ground[HILLS] = "Resource/BackGround2/ground.png";
        bg_layer[HILLS][0] = "Resource/BackGround2/Hills Layer 01.png";
        bg_layer[HILLS][1] = "Resource/BackGround2/Hills Layer 02.png";
        bg_layer[HILLS][2] = "Resource/BackGround2/Hills Layer 03.png";
        bg_layer[HILLS][3] = "Resource/BackGround2/Hills Layer 04.png";
        bg_layer[HILLS][4] = "Resource/BackGround2/Hills Layer 05.png";
        bg_layer[HILLS][5] = "Resource/BackGround2/Hills Layer 06.png";
    
        grass_ground[CLOUD_MOUTAIN] = "Resource/BackGround3/grass_ground.png";
        bg_ground[CLOUD_MOUTAIN] = "Resource/BackGround3/ground.png";
        bg_layer[CLOUD_MOUTAIN][0] = "Resource/BackGround3/layer1.png";
        bg_layer[CLOUD_MOUTAIN][1] = "Resource/BackGround3/layer2.png";
        bg_layer[CLOUD_MOUTAIN][2] = "Resource/BackGround3/layer3.png";
        bg_layer[CLOUD_MOUTAIN][3] = "Resource/BackGround3/layer4.png";
        bg_layer[CLOUD_MOUTAIN][4] = "Resource/BackGround3/clouds_mg_1.png";
        bg_layer[CLOUD_MOUTAIN][5] = "Resource/BackGround3/clouds_mg_2.png";
        bg_layer[CLOUD_MOUTAIN][6] = "Resource/BackGround3/clouds_mg_3.png";
        
        grass_ground[NIGHT_CITY] = "Resource/BackGround4/grass_ground.png";
        bg_ground[NIGHT_CITY] = "Resource/BackGround4/ground.png";
        bg_layer[NIGHT_CITY][0] = "Resource/BackGround4/layer1.png";
        bg_layer[NIGHT_CITY][1] = "Resource/BackGround4/layer2.png";
        bg_layer[NIGHT_CITY][2] = "Resource/BackGround4/layer3.png";

        grass_ground[DESERT] = "Resource/BackGround5/grass_ground.png";
        bg_ground[DESERT] = "Resource/BackGround5/1 Layer1.png";
        bg_layer[DESERT][0] = "Resource/BackGround5/9 Background.png";
        bg_layer[DESERT][1] = "Resource/BackGround5/8 Stars2.png";
        bg_layer[DESERT][2] = "Resource/BackGround5/8 Stars.png";
        bg_layer[DESERT][3] = "Resource/BackGround5/7 Clouds.png";
        bg_layer[DESERT][4] = "Resource/BackGround5/7 Clouds.png";
        bg_layer[DESERT][5] = "Resource/BackGround5/6 Sun.png";
        bg_layer[DESERT][6] = "Resource/BackGround5/5 Mountains.png";
        bg_layer[DESERT][7] = "Resource/BackGround5/4 Layer4.png";
        bg_layer[DESERT][8] = "Resource/BackGround5/3 Layer3.png";
        bg_layer[DESERT][9] = "Resource/BackGround5/2 Layer2.png";
        bg_layer[DESERT][10] = "Resource/BackGround5/ground.png";
        
        grass_ground[FAR_CITY] = "Resource/BackGround6/grass_ground.png";
        bg_ground[FAR_CITY] = "Resource/BackGround6/ground.png";
        bg_layer[FAR_CITY][0] = "Resource/BackGround6/-6.png";
        bg_layer[FAR_CITY][1] = "Resource/BackGround6/-5.png";
        bg_layer[FAR_CITY][2] = "Resource/BackGround6/-4.png";
        bg_layer[FAR_CITY][3] = "Resource/BackGround6/-3.png";
        bg_layer[FAR_CITY][4] = "Resource/BackGround6/-2.png";
        bg_layer[FAR_CITY][5] = "Resource/BackGround6/-1.png";
    };
    ~Map(){};
    
    bool loadBackGround(SDL_Renderer* &renderer, int TOTAL, int type);
    bool loadGround(SDL_Renderer* &renderer, int type);
    bool loadGrassGround(SDL_Renderer* &renderer, int type);
    
    void renderScrollingBackground(/*vector <double> &offSetSpeed,*/ SDL_Renderer* &renderer, int TOTAL, vector <double> & bg_pos, int speed, bool move);
    void renderScrollingGround(int &pos, int& speed, SDL_Renderer* &renderer, bool move);
    void renderScrollingGrass(int &pos, int& speed, SDL_Renderer* &renderer, bool move);
    void Free(int type);
};

#endif /* Map_h */
