#ifndef USERNAME_H
#define USERNAME_H
#include "Common.h"
#include "Game.h"
#include "Menu.h"

extern std::pair<std::string, long long> g_USER;

void LeaveEnterUserName(void);
void KeyboardEnterUserName(unsigned char key, int x, int y);
void RenderEnterUserName(void);
void EnterEnterUserName(void);
#endif