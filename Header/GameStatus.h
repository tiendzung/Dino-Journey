//
//  GameStatus.h
//  Dino Journey
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
#include "Button.h"
void controlFPS(class ImpTimer &Timer, int FPS);

bool checkCollision (class Dino& dino, class Enemy& enemy);

void drawEndGame(SDL_Renderer* &renderer, bool& play_again, bool& quit_menu, bool& quit_game, int type_map, bool &lose_game);

void HandlePlayButton(SDL_Event e, BaseObject& gMenu,
                      Button& Play_button,
                      bool& quit_menu,
                      bool& play_again, SDL_Renderer* &renderer,
                      Mix_Chunk *gClickMusic);

void HandleExitButton(SDL_Event e, BaseObject& gMenu,
                      Button& Play_button,
                      bool& quit_game, bool& quit_menu,
                      bool& play_again,
                      SDL_Renderer* &renderer,
                      Mix_Chunk *gClickMusic);

#endif /* GameStatus_h */
