#ifndef GAME_H
#define GAME_H

#include "Common.h"
#include "LinkedList.h"
#include <ctime>
#include "Menu.h"
#include "GameOver.h"
#include "EnterUserName.h"

void KeyboardGame(unsigned char key, int x, int y);
void SpecialKeyGame(int key, int x, int y);
void RenderGame(void);
void GameLoop(int ttt);
void EnterGame(void);

#endif