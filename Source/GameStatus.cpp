//
//  GameStatus.cpp
//  Project Game
//
//  Created by Nguyễn Tiến Dũng on 4/22/22.
//  Copyright © 2022 Nguyễn Tiến Dũng. All rights reserved.
//

#include "GameStatus.h"

bool checkCollision (class Dino& dino, class Enemy& enemy)
 {
    SDL_Rect d_rect = {dino.getPosX() + 15, dino.getPosY() + 15, dino.getWidth() - 25, dino.getHeight() - 35};

    SDL_Rect e_rect = {enemy.getX() + 10, enemy.getY() + 10, enemy.getW() - 15, enemy.getH() - 15};

    return SDL_HasIntersection(&d_rect, &e_rect);
}
