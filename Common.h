#ifndef COMMON_H
#define COMMON_H

#include <GL\freeglut.h>
#include "SOIL.h"
#pragma comment(lib, "SOIL.lib")
#include "glm.h"

#include <stdio.h>
#include <map>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <string>
#include <vector>
#include <fstream>

#define SCREEN_WIDTH 1000
#define SCREEN_HEIGHT 800

enum eTEXTURE {
	TEXTURE_CAR_0 = 0,
	TEXTURE_CAR_1,
	TEXTURE_CAR_2,
	TEXTURE_CAR_3,
	TEXTURE_CAR_4,
	TEXTURE_CAR_5,
	TEXTURE_CAR_6,
	TEXTURE_TYRE,
	TEXTURE_ROAD,
	TEXTURE_INTRO,
	TEXTURE_MENU_BACKGROUND,
	TEXTURE_MENU1_NEWGAME,
	TEXTURE_MENU1_HIGHSCORE,
	TEXTURE_MENU1_QUIT,
	TEXTURE_MENU_OPTIONS,
	TEXTURE_LAND,
	TEXTURE_SKY,
	TEXTURE_SPEED,
	TEXTURE_PTR,
	TEXTURE_GO,
	TEXTURE_TREE01,
	TEXTURE_TREE02,
	TEXTURE_TREE03,
	TEXTURE_TEXTBOX01,
	TEXTURE_TEXTBOX02,
	TEXTURE_GAMEOVER,
	TEXTURE_RANK01,
	TEXTURE_RANK02,
	TEXTURE_RANK03,
	TEXTURE_RANK04,
	TEXTURE_RANK05,
};

enum eGAMEMODE {
	GAME_RUNNING = 0,
	GAME_PAUSE,
	GAME_OVER,
};

enum eCAR {
	CAR_1 = 0,
	CAR_2,
	CAR_3,
	CAR_4,
	CAR_5,
};

extern GLuint g_pTexture[100]; // mang luu cac texture
extern GLint g_nMode; // 0: menu, 1: tam dung, 2: on game, 3: over
extern GLuint g_nTexApp;
extern long long g_nHighScore;
extern long long g_nScore;

/// Model ///
extern GLMmodel* g_modCar;
extern GLMmodel* g_modTyre;

extern std::string g_sUsername;

extern std::vector<std::pair<std::string, long long>> g_pData;
extern std::map<std::string, long long> g_mapData;
extern std::ifstream g_fFileIn;
extern std::ofstream g_fFileOu;

void LoadAllResouce(void);
void LoadGameTexture(void);
void LoadMenuTexture(void);
void LoadModel3DGame(void);
void LoadUsernameTexture(void);
void ReadData(void);
void PrintText(GLfloat x, GLfloat y, int r, int g, int b, int a, void* font, long long num);
void PrintText1(GLfloat x, GLfloat y, int r, int g, int b, int a, void* font, std::string s);
void PrintText2(GLfloat x, GLfloat y, int r, int g, int b, int a, void* font, std::string st, long long num);

bool cmp(std::pair<std::string, long long> a, std::pair<std::string, long long> b);
std::vector<std::pair<std::string, long long>> SortMap(std::map<std::string, long long> m);

#define TIME_STEP 20 //fps - frame per second (moi khung anh ve cach nhau 20ms)

#endif