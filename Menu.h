#ifndef MENU_H
#define MENU_H

#include "Common.h"
#include "Game.h"
#include "HighScore.h"
#include "EnterUserName.h"

extern bool g_bStatusEnterUsername;

void LeaveMenu(void);
void KeyboardMenu(unsigned char key, int x, int y);
void SpecialKeyMenu(int key, int x, int y);
void RenderMenu(void);
void MenuLoop(int ttt);
void EnterMenu(void);

#endif