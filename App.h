#ifndef APP_H
#define APP_H
#include "Common.h"
#include "Menu.h"
#include "EnterUserName.h"
#include "HighScore.h"

void Init(void);
void ReshapeApp(int w, int h);
void DisplayApp(void);
void RunApp(int argc, char* argv[]);
#endif