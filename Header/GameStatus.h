//
//  GameStatus.h
//  Project Game
//
//  Created by Nguyễn Tiến Dũng on 4/22/22.
//  Copyright © 2022 Nguyễn Tiến Dũng. All rights reserved.
//

#ifndef GameStatus_h
#define GameStatus_h
#include "CommonFunction.h"
#include "Dino.h"
#include "Enemy.h"
#include "Map.h"
bool checkCollision (class Dino& dino, class Enemy& enemy);

void drawEndGame(SDL_Renderer* renderer, bool& play_again, bool &quit_menu, int type_map);

#endif /* GameStatus_h */
