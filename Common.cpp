#include "Common.h"

GLuint g_pTexture[100];
GLMmodel* g_modCar;
GLMmodel* g_modTyre;

std::vector<std::pair<std::string, long long>> g_pData;
std::map<std::string, long long> g_mapData;

std::ifstream g_fFileIn("data.txt");
std::ofstream g_fFileOu;

long long g_nHighScore = 0;

void LoadMenuTexture(void) {
	g_pTexture[TEXTURE_MENU_BACKGROUND] = SOIL_load_OGL_texture (
			"res//menu//menu_background.jpg",
			SOIL_LOAD_AUTO,
			SOIL_CREATE_NEW_ID,
			SOIL_FLAG_TEXTURE_REPEATS | SOIL_FLAG_INVERT_Y
		);
	g_pTexture[TEXTURE_MENU1_NEWGAME] = SOIL_load_OGL_texture (
			"res//menu//menu1_1.png",
			SOIL_LOAD_AUTO,
			SOIL_CREATE_NEW_ID,
			SOIL_FLAG_TEXTURE_REPEATS | SOIL_FLAG_INVERT_Y
		);
	g_pTexture[TEXTURE_MENU1_HIGHSCORE] = SOIL_load_OGL_texture (
			"res//menu//menu1_2.png",
			SOIL_LOAD_AUTO,
			SOIL_CREATE_NEW_ID,
			SOIL_FLAG_TEXTURE_REPEATS | SOIL_FLAG_INVERT_Y
		);
	g_pTexture[TEXTURE_MENU1_QUIT] = SOIL_load_OGL_texture (
			"res//menu//menu1_3.png",
			SOIL_LOAD_AUTO,
			SOIL_CREATE_NEW_ID,
			SOIL_FLAG_TEXTURE_REPEATS | SOIL_FLAG_INVERT_Y
		);
	printf("Da load texture menu...\n");
}
void LoadGameTexture(void) {
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	g_pTexture[TEXTURE_CAR_0] = SOIL_load_OGL_texture(
		"res/skin/skin00/0000.BMP",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_TEXTURE_REPEATS | SOIL_FLAG_INVERT_Y
		);
	g_pTexture[TEXTURE_CAR_1] = SOIL_load_OGL_texture(
		"res/skin/skin01/0000.BMP",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_TEXTURE_REPEATS | SOIL_FLAG_INVERT_Y
		);
	g_pTexture[TEXTURE_CAR_2] = SOIL_load_OGL_texture(
		"res/skin/skin02/0000.BMP",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_TEXTURE_REPEATS | SOIL_FLAG_INVERT_Y
		);
	g_pTexture[TEXTURE_CAR_3] = SOIL_load_OGL_texture(
		"res/skin/skin03/0000.BMP",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_TEXTURE_REPEATS | SOIL_FLAG_INVERT_Y
		);
	g_pTexture[TEXTURE_CAR_4] = SOIL_load_OGL_texture(
		"res/skin/skin04/0000.BMP",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_TEXTURE_REPEATS | SOIL_FLAG_INVERT_Y
		);
	g_pTexture[TEXTURE_CAR_5] = SOIL_load_OGL_texture(
		"res/skin/skin05/0000.BMP",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_TEXTURE_REPEATS | SOIL_FLAG_INVERT_Y
		);
	g_pTexture[TEXTURE_CAR_6] = SOIL_load_OGL_texture(
		"res/skin/skin06/0000.BMP",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_TEXTURE_REPEATS | SOIL_FLAG_INVERT_Y
		);
	g_pTexture[TEXTURE_TYRE] = SOIL_load_OGL_texture(
		"res/tyre.jpg",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_TEXTURE_REPEATS | SOIL_FLAG_INVERT_Y
		);
	g_pTexture[TEXTURE_LAND]=SOIL_load_OGL_texture (
		"res/grass06.jpg",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_TEXTURE_REPEATS | SOIL_FLAG_INVERT_Y
		);
	g_pTexture[TEXTURE_SKY]=SOIL_load_OGL_texture (
		"res/sky.jpg",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_TEXTURE_REPEATS | SOIL_FLAG_INVERT_Y
		);
	g_pTexture[TEXTURE_ROAD]=SOIL_load_OGL_texture (
		"res/img_road1.jpg",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_TEXTURE_REPEATS | SOIL_FLAG_INVERT_Y
		);
	g_pTexture[TEXTURE_TREE01]=SOIL_load_OGL_texture (
		"res/tree/tree01.png",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_TEXTURE_REPEATS | SOIL_FLAG_INVERT_Y
		);
	g_pTexture[TEXTURE_TREE02]=SOIL_load_OGL_texture (
		"res/tree/tree02.png",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_TEXTURE_REPEATS | SOIL_FLAG_INVERT_Y
		);
	g_pTexture[TEXTURE_TREE03]=SOIL_load_OGL_texture (
		"res/tree/tree03.png",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_TEXTURE_REPEATS | SOIL_FLAG_INVERT_Y
		);
	g_pTexture[TEXTURE_GAMEOVER]=SOIL_load_OGL_texture (
		"res/gameover.png",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_TEXTURE_REPEATS | SOIL_FLAG_INVERT_Y
		);
	g_pTexture[TEXTURE_TEXTBOX02]=SOIL_load_OGL_texture (
		"res/textbox2.png",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_TEXTURE_REPEATS | SOIL_FLAG_INVERT_Y
		);
	printf("Da load texture game...\n");
}
void LoadModel3DGame(void) {
	if (!g_modCar) {
        g_modCar = glmReadOBJ("res/car.obj");
        if (!g_modCar) exit(0);
    }
    if (!g_modTyre) {
        g_modTyre = glmReadOBJ("res/tyre.obj");
        if (!g_modTyre) exit(0);
    }
	printf("Da load resource model 3D game...\n");
}
void LoadUsernameTexture(void) {
	g_pTexture[TEXTURE_TEXTBOX01] = SOIL_load_OGL_texture (
			"res//username//textbox1.png",
			SOIL_LOAD_AUTO,
			SOIL_CREATE_NEW_ID,
			SOIL_FLAG_TEXTURE_REPEATS | SOIL_FLAG_INVERT_Y
		);
	printf("Da load texture username...\n");
}
void LoadHighScoreTexture(void) {
	g_pTexture[TEXTURE_RANK01] = SOIL_load_OGL_texture (
			"res//rank//rank1.png",
			SOIL_LOAD_AUTO,
			SOIL_CREATE_NEW_ID,
			SOIL_FLAG_TEXTURE_REPEATS | SOIL_FLAG_INVERT_Y
		);
	g_pTexture[TEXTURE_RANK02] = SOIL_load_OGL_texture (
			"res//rank//rank2.png",
			SOIL_LOAD_AUTO,
			SOIL_CREATE_NEW_ID,
			SOIL_FLAG_TEXTURE_REPEATS | SOIL_FLAG_INVERT_Y
		);
	g_pTexture[TEXTURE_RANK03] = SOIL_load_OGL_texture (
			"res//rank//rank3.png",
			SOIL_LOAD_AUTO,
			SOIL_CREATE_NEW_ID,
			SOIL_FLAG_TEXTURE_REPEATS | SOIL_FLAG_INVERT_Y
		);
	g_pTexture[TEXTURE_RANK04] = SOIL_load_OGL_texture (
			"res//rank//rank4.png",
			SOIL_LOAD_AUTO,
			SOIL_CREATE_NEW_ID,
			SOIL_FLAG_TEXTURE_REPEATS | SOIL_FLAG_INVERT_Y
		);
	g_pTexture[TEXTURE_RANK05] = SOIL_load_OGL_texture (
			"res//rank//rank5.png",
			SOIL_LOAD_AUTO,
			SOIL_CREATE_NEW_ID,
			SOIL_FLAG_TEXTURE_REPEATS | SOIL_FLAG_INVERT_Y
		);
	printf("Da hoan thanh load texture high score...\n");
}
void LoadAllResouce(void) {
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	LoadMenuTexture();
	LoadGameTexture();
	LoadModel3DGame();
	LoadUsernameTexture();
	LoadHighScoreTexture();
	printf("Da hoan thanh load tat ca resouce!\n");
}

void PrintText(GLfloat x, GLfloat y, int r, int g, int b, int a, void* font, long long num) {
	glColor3f((GLfloat)r, (GLfloat)g, (GLfloat)b);
	glRasterPos3f(x, y, 0);
	std::string s = "score: " + std::to_string(num);
	for (int i = 0; i < (int)s.length(); ++i)
		glutBitmapCharacter(font, s[i]);
}
void PrintText1(GLfloat x, GLfloat y, int r, int g, int b, int a, void* font, std::string s) {
	glColor3f((GLfloat)r, (GLfloat)g, (GLfloat)b);
	glRasterPos3f(x, y, 0);
	for (int i = 0; i < (int)s.length(); ++i)
		glutBitmapCharacter(font, s[i]);
}
void PrintText2(GLfloat x, GLfloat y, int r, int g, int b, int a, void* font, std::string st, long long num) {
	glColor3f((GLfloat)r, (GLfloat)g, (GLfloat)b);
	glRasterPos3f(x, y, 0);
	std::string s = std::to_string(num);
	s = st + s;
	for (int i = 0; i < (int)s.length(); ++i)
		glutBitmapCharacter(font, s[i]);
}

//ifstream fi("score.dat");
//ofstream fo("score.dat", ios::app);

std::pair<std::string, long long> solve(std::string s) {
	std::pair<std::string, long long> res;
	std::string a = s.substr(0, s.find('#'));
	std::string b = s.substr(s.find('#') + 1, s.length() - a.length() - 1);
	long long c = atoi(&b[0]);
	//b = atoi(&s.substr(s.find('#'), s.length() - a.length() - 1)[0]);
	//std::cout << a << " - " << c << "\n";
	res.first = a, res.second = c;
	return res;
}

bool cmp(std::pair<std::string, long long> a, std::pair<std::string, long long> b){
	return a.second > b.second;
}

std::vector<std::pair<std::string, long long>> SortMap(std::map<std::string, long long> m) {
	std::vector<std::pair<std::string, long long>> v;
	for (auto &it: m)
		v.push_back(it);
	std::sort(v.begin(), v.end(), cmp);
	return v;
}

void ReadData(void) {
	std::string s;
	long long maxx = -1;
	while (!g_fFileIn.eof()) {
		std::getline(g_fFileIn, s);
		//std::cout << s << "\n";
		//auto a = solve(s);
		g_mapData[solve(s).first] = solve(s).second;
		maxx = std::max(maxx, solve(s).second);
		//g_pData.push_back(solve(s));
	}
	//std::sort(g_pData.begin(), g_pData.end(), cmp);
	/*for (int i = 0; i < (int)g_pData.size(); ++i) {
		std::cout << g_pData[i].first << " --- " << g_pData[i].second << "\n";
	}*/
	//g_fFileOu.close();
	g_nHighScore = maxx;
	printf("Da doc file thanh cong\n");
	printf("1st: %d\n", g_nHighScore);
}