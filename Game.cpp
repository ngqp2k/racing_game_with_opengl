#define _CRT_SECURE_NO_WARNINGS
#include "Game.h"

#define WIDTH_ROAD 10
#define LENGTH_ROAD 1600
#define NUM_PICTURE_PER_ROAD 40
#define CONVERT_TEXTURE_TO_MODELVIEW (LENGTH_ROAD / NUM_PICTURE_PER_ROAD)
#define MAX_TRANSL WIDTH_ROAD / 2
#define MAX_ROTATE 12
#define MAX_CAM_ROTATE 50


enum eSTATUS_CAR {
	RIGHT_TO_LEFT = -1,
	STAND,
	LEFT_TO_RIGHT
};
enum eSTATUS_NPC {
	NPC_MOVE = 0,
	NPC_STAND
};
enum eSTATUS_GAME {
	RUNNING = 0,
	PAUSE,
	OVER
};

const int MAX_LEVEL = 37;
const GLfloat g_pSpeedLevel[MAX_LEVEL] = {0, 0.0f, 0, 0, 0, 
										  0, 0.5f, 0, 0, 0, 
										  0, 0.5f, 0, 0, 0, 
										  0, 0.5f, 0, 0, 0, 
										  0, 0.5f, 0, 0, 0, 
										  0, 0.5f, 0, 0, 0, 
										  0, 0.5f, 0, 0, 0, 
										  0.5f, 0};
GLint g_nLevelCurrent = 0;
GLint g_nStatusGame = RUNNING;
bool g_bRightKeyDown, g_bLeftKeyDown;

void KeyboardGame(unsigned char key, int x, int y);
void SpecialKeyGame(int key, int x, int y);

class ModelCar3D {
public:
	GLfloat m_nX, m_nZ;
	GLfloat m_nSpeed;
	GLfloat m_nCarRotate, m_nTyreRotate;

	// Rotate duong - quay nguoc chieu kim dong ho
	// Rotate am	- quay cung chieu kim dong ho

	GLint m_nColor;
	GLint m_nStatusMove;
	GLint m_nStatusMoveNPC;

	bool m_bFlag;

	ModelCar3D() {
		m_nX = m_nZ = m_nSpeed = m_nCarRotate = m_nTyreRotate = 0.0f;
		m_nColor = 0, m_nStatusMove = STAND;
		m_bFlag = false;
	}
	void Render() {
		GLfloat x, y, z;
		GLuint tex_2d = 0;
		x = 0.72f, y = 0.28f, z = 1.21f;
   		glEnable(GL_TEXTURE_2D);
		glPushMatrix();
			glMatrixMode(GL_MODELVIEW);
			glColor3f(1, 1, 1);
			// glRotatef(car_crash_angle, 1.0f, 0.0f, 0.0f);
			glTranslatef(m_nX, 0.59f, m_nZ);
			glRotatef(m_nCarRotate, 0.0f, 1.0f, 0.0f);
			switch (m_nColor)
			{
			case 0:
				tex_2d = g_pTexture[TEXTURE_CAR_0];
				break;
			case 1:
				tex_2d = g_pTexture[TEXTURE_CAR_1];
				break;
			case 2:
				tex_2d = g_pTexture[TEXTURE_CAR_2];
				break;
			case 3:
				tex_2d = g_pTexture[TEXTURE_CAR_3];
				break;
			case 4:
				tex_2d = g_pTexture[TEXTURE_CAR_4];
				break;
			case 5:
				tex_2d = g_pTexture[TEXTURE_CAR_5];
				break;
			case 6:
				tex_2d = g_pTexture[TEXTURE_CAR_6];
				break;
			default:
				break;
			}
			glBindTexture(GL_TEXTURE_2D, tex_2d);
			glmDraw(g_modCar, GLM_SMOOTH | GLM_TEXTURE);

			/*
				- Xe quay -> banh xe quay theo 
				- Xe quay 1 do, banh xe quay 1 * 1.5; 
			*/
			glBindTexture(GL_TEXTURE_2D, g_pTexture[TEXTURE_TYRE]);

			// top left
			glPushMatrix();
				glTranslatef(-0.05f, 0, -0.00f);;
				glTranslatef(-x, -y, -z);
				glRotatef(m_nCarRotate * 1.5f, 0, 1, 0);
				glRotatef(m_nTyreRotate, 1, 0, 0);
				glTranslatef(x, y, z); // tinh tien ve tam toa do
				glmDraw(g_modTyre, GLM_SMOOTH | GLM_TEXTURE);
			glPopMatrix();

			// top right
			glPushMatrix();
				glTranslatef(+0.05f, 0, -0.00f);
				glTranslatef(+x, -y, -z);
				glRotatef(m_nCarRotate * 1.5f+ 180, 0, 1, 0);
				glRotatef(m_nTyreRotate, 1, 0, 0);
				glTranslatef(x, y, z); // tinh tien ve tam toa do
				glmDraw(g_modTyre, GLM_SMOOTH | GLM_TEXTURE);
			glPopMatrix();

			// bot left
			glPushMatrix();
				glTranslatef(-0.05f, 0, -0.05f);
				glTranslatef(-x, -y, +z);
				glRotatef(m_nTyreRotate, 1, 0, 0);
				glTranslatef(x, y, z); // tinh tien ve tam toa do
				glmDraw(g_modTyre, GLM_SMOOTH | GLM_TEXTURE);
			glPopMatrix();

			// bot right
			glPushMatrix();
				glTranslatef(0.05f, 0, -0.05f);
				glTranslatef(+x, -y, +z);
				glRotatef(180, 0, 1, 0);
				glRotatef(m_nTyreRotate, 1, 0, 0);
				glTranslatef(x, y, z); // tinh tien ve tam toa do
				glmDraw(g_modTyre, GLM_SMOOTH | GLM_TEXTURE);
			glPopMatrix();

		glPopMatrix();
		glDisable(GL_TEXTURE_2D);
	}
};

class ModelTree2D {
public:
	GLfloat m_nX, m_nZ; // Vi tri cua cay
	GLint m_nType; // Loai cay 1 -> 3
	ModelTree2D() {
		m_nX = 0.0f, m_nZ = 0.0f;
		m_nType = 1;
	};
	void Render() {
		glPushMatrix();//for the current object
			glTranslatef(m_nX, -1.0, -m_nZ);//Object translate
			glEnable(GL_DEPTH_TEST);
			glEnable(GL_BLEND);     // Turn Blending On
			glDisable(GL_DEPTH_TEST);
			glBlendFunc(GL_SRC_ALPHA,GL_ONE);
			glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
			glEnable(GL_TEXTURE_2D);
			glRotatef(45.0f, 0.0f, 1.0f, 0.0f);

			GLuint tex2d;
			switch (m_nType)
			{
			case 1:
				tex2d = g_pTexture[TEXTURE_TREE01];
				break;
			case 2:
				tex2d = g_pTexture[TEXTURE_TREE02];
				break;
			case 3:
				tex2d = g_pTexture[TEXTURE_TREE03];
				break;
			default:
				break;
			}
			glBindTexture(GL_TEXTURE_2D, tex2d);
			GLfloat angle = 0.0f;
			for (int i = 0; i < 4; ++i) {
				glPushMatrix();
					glRotatef(angle, 0, 1, 0);
					glBegin(GL_POLYGON);
						GLfloat size = 6.0f;
						glTexCoord2d(0.0,0.0); glVertex3f(-size, -size, 0.0f);
						glTexCoord2d(0.0,1.0); glVertex3f(-size,  size, 0.0f);
						glTexCoord2d(1.0,1.0); glVertex3f(size,   size, 0.0f);
						glTexCoord2d(1.0,0.0); glVertex3f(size,  -size, 0.0f);
					glEnd();
				glPopMatrix();
				angle += 45.0f;
			}

			glDisable(GL_TEXTURE_2D);
			// DEBUG_drwCord();
			glEnable(GL_DEPTH_TEST);
			glDisable(GL_BLEND);     // Turn Blending On
		glPopMatrix();
	}
};

ModelCar3D g_mdPlayerCar;
GLfloat g_nTextureOffset;
LinkedList g_lNPC, g_lObjects; // Non-player character

long long g_nScore = 0;
GLint g_nCarColorPlayer = 0;
GLint g_nTotalTime;
GLint g_nMemoryStepTimeCreateCar, g_nMemoryStepTimeCreateObject, g_nMemoryStepTimeSpeedLevel;
GLfloat g_nMemoryStepDistCreateCar;
GLfloat g_nMemoryStepDistCreateObject;
GLfloat g_nCamPosition;
bool g_bStatusChangeCamera;

void InitGame(void) {
	//printf("init game\n");
	///// Khoi tao xe nguoi choi /////
	g_nLevelCurrent = 0;
	g_mdPlayerCar.m_nSpeed = 1 + g_pSpeedLevel[g_nLevelCurrent];
	g_mdPlayerCar.m_nColor = g_nCarColorPlayer;
	g_mdPlayerCar.m_nX = 0.0f;
	g_mdPlayerCar.m_nStatusMove = STAND;
	///// Khoi tao thoi gian /////
	g_nTotalTime = 0;
	g_nMemoryStepTimeCreateCar = 0;
	g_nMemoryStepTimeCreateObject = 0;
	g_nMemoryStepTimeSpeedLevel = 0;
	g_nMemoryStepDistCreateCar = 0.0f;
	g_nMemoryStepDistCreateObject = 0.0f;
	////////////////////////////////
	g_bRightKeyDown = false, g_bLeftKeyDown = false;
	g_nTextureOffset = 0;
	g_nStatusGame = RUNNING;
	g_nScore = 0;
	///////////////////////////////
	g_bStatusChangeCamera = false;
	g_nCamPosition = 0.0f;
}
void InitLinkedListNPC() {
	ModelCar3D *c1 = new ModelCar3D();
	ModelCar3D *c2 = new ModelCar3D();
	ModelCar3D *c3 = new ModelCar3D();

	c1->m_nX = (GLfloat) (rand() % WIDTH_ROAD - MAX_TRANSL);
	c1->m_nZ = -100;
	c2->m_nX = (GLfloat) (rand() % WIDTH_ROAD - MAX_TRANSL);
	c2->m_nZ = -200;
	c3->m_nX = (GLfloat) (rand() % WIDTH_ROAD - MAX_TRANSL);
	c3->m_nZ = -300;

	g_lNPC.insert(c1);
	g_lNPC.insert(c2);
	g_lNPC.insert(c3);
}
void InitLinkedListObjects() {
	for (int i = 0; i < 900; i += 20) {
		ModelTree2D* new_tree = new ModelTree2D;
		new_tree->m_nType = rand() % 3 + 1;
		new_tree->m_nX = (GLfloat) (rand() % 60 + 25);
		if (rand() % 2 == 0)
			new_tree->m_nX = -new_tree->m_nX;
		new_tree->m_nZ = (GLfloat) i;
		g_lObjects.insert(new_tree);
	}
}
void KeyboardGame(unsigned char key, int x, int y) {
	if (g_nStatusGame != OVER)
		switch (key)
		{
		case 'p':
			if (g_nStatusGame == RUNNING)
				g_nStatusGame = PAUSE;
			else
				g_nStatusGame = RUNNING;
			break;
		case 'a':
			glutIgnoreKeyRepeat(0);
			g_nCamPosition -= 1;
			g_nCamPosition = std::max((int)g_nCamPosition, -MAX_CAM_ROTATE);
			g_bStatusChangeCamera = true;
			break;
		case 'd':
			glutIgnoreKeyRepeat(0);
			g_nCamPosition += 1;
			g_nCamPosition = std::min((int)g_nCamPosition, MAX_CAM_ROTATE);
			g_bStatusChangeCamera = true;
			break;
		default:
			break;
		}
	else {
		switch (key)
		{
		case 13:
			glutKeyboardFunc(NULL);
			EnterMenu();
			break;
		default:
			break;
		}
	}
}
void KeyboardGameUp(unsigned char key, int x, int y) {
	switch (key)
	{
	case 'a':
		glutIgnoreKeyRepeat(1);
		g_bStatusChangeCamera = false;
		break;
	case 'd':
		glutIgnoreKeyRepeat(1);
		g_bStatusChangeCamera = false;
		break;
	default:
		break;
	}
}
void SpecialKeyGame(int key, int x, int y) {
	if (g_bStatusChangeCamera)
		return;
	switch (key)
	{
	case GLUT_KEY_UP:
		g_mdPlayerCar.m_nSpeed += 1.85f;
		break;
	case GLUT_KEY_DOWN:
		g_mdPlayerCar.m_nSpeed -= 0.5f;
		break;
	case GLUT_KEY_LEFT:
		g_mdPlayerCar.m_nStatusMove = RIGHT_TO_LEFT;
		g_bLeftKeyDown = true;
		//printf("key left down\n");
		break;
	case GLUT_KEY_RIGHT:
		g_mdPlayerCar.m_nStatusMove = LEFT_TO_RIGHT;
		g_bRightKeyDown = true;
		//printf("key right down\n");
		break;
	}
}
void SpecialKeyUpGame(int key, int x, int y) {
	if (g_bStatusChangeCamera)
		return;
	switch (key)
	{
	case GLUT_KEY_UP:
		g_mdPlayerCar.m_nSpeed -= 1.85f;
		break;
	case GLUT_KEY_DOWN:
		g_mdPlayerCar.m_nSpeed += 0.5f;
		break;
	case GLUT_KEY_LEFT:
		if (!g_bRightKeyDown)
			g_mdPlayerCar.m_nStatusMove = STAND;
		g_bLeftKeyDown = false;
		//printf("key left up\n");
		break;
	case GLUT_KEY_RIGHT:
		if (!g_bLeftKeyDown)
			g_mdPlayerCar.m_nStatusMove = STAND;
		g_bRightKeyDown = false;

		//printf("key right up\n");
		break;
	}
}

void EnterGame(void) {
	InitGame();
	g_lNPC.clearList();
	g_lObjects.clearList();
	g_lNPC.m_pHead = g_lNPC.m_pTail = NULL;
	g_lNPC.m_nCountElements = 0;
	g_lObjects.m_pHead = g_lObjects.m_pTail = NULL;
	g_lObjects.m_nCountElements = 0;
	InitLinkedListNPC();
	InitLinkedListObjects();
	glEnable(GL_DEPTH_TEST);
	glutDisplayFunc(RenderGame);
	glutSpecialFunc(SpecialKeyGame);
	glutSpecialUpFunc(SpecialKeyUpGame);
	glutKeyboardFunc(KeyboardGame);
	glutKeyboardUpFunc(KeyboardGameUp);
	glutIgnoreKeyRepeat(1);
	GameLoop(0);
}
void LeaveGame() {
	glutSpecialFunc(NULL);
	glutSpecialUpFunc(NULL);
	//glutKeyboardFunc(NULL);
	glutIgnoreKeyRepeat(1);
}
void DrawAxis() {
	GLfloat factor = 2.0f;
	//factor = 2.0f;
	glBegin(GL_LINES);
		glColor3f(1, 0, 0);
		glVertex3f(0, 0, 0);
		glVertex3f(factor, 0, 0);
		glColor3f(0, 1, 0);
		glVertex3f(0, 0, 0);
		glVertex3f(0, factor, 0);
		glColor3f(0, 0, 1);
		glVertex3f(0, 0, 0);
		glVertex3f(0, 0, factor);
	glEnd();
}
void RenderRoadAndLand(void) {
	glPushMatrix();
		glMatrixMode(GL_TEXTURE);
		/////////////////////Draw road/////////////////////
		glEnable(GL_TEXTURE_2D);

		glTranslatef(0.0f, g_nTextureOffset, 0.0f);
		//printf("texture offset =  %f\n", g_nTextureOffset);
		glBindTexture(GL_TEXTURE_2D, g_pTexture[TEXTURE_ROAD]);

		glBegin(GL_QUADS);
			glColor3f(1, 1, 1);
			glTexCoord2f(0.0, 0.0); glVertex3d(-WIDTH_ROAD / 2, 0, LENGTH_ROAD / 2);
			glTexCoord2f(1.0, 0.0); glVertex3d(WIDTH_ROAD / 2, 0, LENGTH_ROAD / 2);
			glTexCoord2f(1.0, 10.0); glVertex3d(WIDTH_ROAD / 2, 0, -LENGTH_ROAD / 2);
			glTexCoord2f(0.0, 10.0); glVertex3d(-WIDTH_ROAD / 2, 0, -LENGTH_ROAD / 2);
		glEnd();

		glDisable(GL_TEXTURE_2D);

		///////////////////////////////////////////////////

		/////////////////////Draw sand/////////////////////

		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, g_pTexture[TEXTURE_LAND]);
		glBegin(GL_QUADS);
			//glColor3f(0.4f, 0.0f, 0.0f);
			GLfloat ttt = 100.0f;
			GLfloat marginLand = -0.01f;
			glTexCoord2d(0.0f,  0.0f);  glVertex3f(-100.0f, marginLand,  1000.0f);
			glTexCoord2d(10.0f, 0.0f);  glVertex3f(100.0f,  marginLand,  1000.0f);
			glTexCoord2d(10.0f, ttt);   glVertex3f(100.0f,  marginLand, -1000.0f);
			glTexCoord2d(0.0f,  ttt);   glVertex3f(-100.0f, marginLand, -1000.0f);
			//glTranslatef(0.0,0.0,a);
		glEnd();
		glDisable(GL_TEXTURE_2D);

		///////////////////////////////////////////////////

	glPopMatrix();
}
void RenderNPC(void) {
	if (g_lNPC.m_nCountElements == 0) {
		printf("Khong co Car de render\n");
		return;
	}
	Node *tmp = g_lNPC.m_pHead;
	for (int i = 0; i < g_lNPC.m_nCountElements; ++i) {
		((ModelCar3D*)tmp->data)->Render();
		tmp = tmp->next;
	}
	//delete tmp;
}
void RenderObjects(void) {
	// Ve cay tu gan nhat roi moi den cay xa nhat
	if (g_lObjects.m_nCountElements == 0) {
		printf("Khong co Object de render\n");
		return;
	}
	Node* tmp = g_lObjects.m_pTail;
	for (int i = 0; i < g_lObjects.m_nCountElements; ++i) {
		((ModelTree2D*)tmp->data)->Render();
		tmp = tmp->prev;
	}
}
void RenderGameOver(void) {
	glPushMatrix();
		glDisable(GL_DEPTH_TEST);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA,GL_ONE);
		glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_TEXTURE_2D);
		glTranslatef(0, 0, -20);	
		glBindTexture(GL_TEXTURE_2D, g_pTexture[TEXTURE_GAMEOVER]);
		glBegin(GL_POLYGON);
			GLfloat size = 6.0f;
			glTexCoord2f(0.0f, 0.0f); glVertex3f(-size, -size, 0.0f);
			glTexCoord2f(1.0f, 0.0f); glVertex3f(size,  -size, 0.0f);
			glTexCoord2f(1.0f, 1.0f); glVertex3f(size,   size, 0.0f);
			glTexCoord2f(0.0f, 1.0f); glVertex3f(-size,  size, 0.0f);
		glEnd();
		glEnable(GL_DEPTH_TEST);
		glDisable(GL_TEXTURE_2D);
		glDisable(GL_BLEND);
	glPopMatrix();

	glPushMatrix();
		glEnable(GL_DEPTH_TEST);
		glDisable(GL_DEPTH_TEST);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA,GL_ONE);
		glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_TEXTURE_2D);
		glTranslatef(0, -2, 0);	
		glBindTexture(GL_TEXTURE_2D, g_pTexture[TEXTURE_TEXTBOX02]);
		glBegin(GL_POLYGON);
			GLfloat w = 6, h = 1.5f;
			glTexCoord2f(0.0f, 0.0f); glVertex3f(-w, -h, 0.0f);
			glTexCoord2f(1.0f, 0.0f); glVertex3f(w,  -h, 0.0f);
			glTexCoord2f(1.0f, 1.0f); glVertex3f(w,   h, 0.0f);
			glTexCoord2f(0.0f, 1.0f); glVertex3f(-w,  h, 0.0f);
		glEnd();
		glEnable(GL_DEPTH_TEST);
		glDisable(GL_TEXTURE_2D);
		glDisable(GL_BLEND);
	glPopMatrix();
	glDisable(GL_DEPTH_TEST);
	if (g_nScore > g_nHighScore) {
		// new high score
		PrintText1(-1, -1, 1, 0, 0, 1, GLUT_BITMAP_HELVETICA_18, "New high score");
	}
	PrintText2(-1.4f, -2, 1, 1, 0, 1, GLUT_BITMAP_HELVETICA_18, "Your score: ", g_nScore);
	glEnable(GL_DEPTH_TEST);
}
void RenderSky(void) {
	glPushMatrix();
		glDisable(GL_TEXTURE_2D);
		glDisable(GL_LIGHTING);
		glDisable(GL_CULL_FACE);
		glColor3f(79.0f / 255.0f, 155.0f / 255.0f, 217.0f / 255.0f);
		//glColor3f(1, 1, 1);
		glutSolidSphere(LENGTH_ROAD / 2.0f, 50, 50);
		glEnable(GL_CULL_FACE);
	glPopMatrix();
}
void RenderGame(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0, 5, 15, 0, 0, 0, 0, 1, 0);
	
	//DrawAxis();
	glPushMatrix();
		glRotatef(g_nCamPosition, 0, 1, 0);
		RenderRoadAndLand();
		RenderSky();
		g_mdPlayerCar.Render();
		RenderNPC();
		RenderObjects();
	glPopMatrix();
	glPushMatrix();
		if (g_nStatusGame == OVER) {
				printf("render gameover\n");
				RenderGameOver();
			}
		else PrintText(5.0f, 5.5f, 1, 1, 0, 1, GLUT_BITMAP_HELVETICA_18, g_nScore);
	glPopMatrix();
	glutSwapBuffers();
}

void UpdatePlayer(void) {
	//	Cap nhat speed player
	if ((g_mdPlayerCar.m_nStatusMove != 0) && (abs(g_mdPlayerCar.m_nX) <= MAX_TRANSL)) {
		// temp = g_mdPlayerCar.m_nStatusMove
		// temp = -1 => right to left -> xe quay nguoc chieu kim dong ho -> rotate duong
		g_mdPlayerCar.m_nX += g_mdPlayerCar.m_nStatusMove * TIME_STEP / 75.0f;
		g_mdPlayerCar.m_nCarRotate += -(g_mdPlayerCar.m_nStatusMove);
		//printf("car rotate = %f    status = %d\n", g_mdPlayerCar.m_nCarRotate, g_mdPlayerCar.m_nStatusMove);

		g_mdPlayerCar.m_nX = std::max(g_mdPlayerCar.m_nX, (GLfloat)-MAX_TRANSL);
		g_mdPlayerCar.m_nX = std::min(g_mdPlayerCar.m_nX, (GLfloat)+MAX_TRANSL);
		g_mdPlayerCar.m_nCarRotate = std::max(g_mdPlayerCar.m_nCarRotate, (GLfloat)-MAX_ROTATE);
		g_mdPlayerCar.m_nCarRotate = std::min(g_mdPlayerCar.m_nCarRotate, (GLfloat)+MAX_ROTATE);
	}

	if ((g_mdPlayerCar.m_nStatusMove == 0) && (g_mdPlayerCar.m_nCarRotate != 0)) {
		// Quay xe ve huong ban dau
		//printf("car rotate = %f\n", g_mdPlayerCar.m_nCarRotate);
		if (g_mdPlayerCar.m_nCarRotate < 0)
			g_mdPlayerCar.m_nCarRotate += 2;
		else
			g_mdPlayerCar.m_nCarRotate -= 2;
		if (abs(g_mdPlayerCar.m_nCarRotate) <= 1)
			g_mdPlayerCar.m_nCarRotate = 0;
	}
	g_mdPlayerCar.m_nTyreRotate += 25 * g_mdPlayerCar.m_nSpeed;
	if (g_mdPlayerCar.m_nTyreRotate > 360.0f)
		g_mdPlayerCar.m_nTyreRotate -= 360.0f;
}
void UpdateNPC(GLfloat texOffset) {
	if (g_nTextureOffset - g_nMemoryStepDistCreateCar >= 3) // 1000ms = 1s
	{
		//printf("create new car\n");
		srand(time(NULL));
		g_nMemoryStepDistCreateCar = g_nTextureOffset;
		ModelCar3D *new_car = new ModelCar3D();
		new_car->m_nX = (GLfloat) (rand() % (WIDTH_ROAD - 2) - (MAX_TRANSL - 1));
		new_car->m_nZ = -400.0f;
		new_car->m_bFlag = false;
		int tmp_color = rand() % 7;
		while (tmp_color == g_nCarColorPlayer) {
			//printf("rand color: %d\n", tmp_color);
			tmp_color = rand() % 7;
		}
		new_car->m_nStatusMoveNPC = rand() % 2;
		new_car->m_nColor = tmp_color;

		g_lNPC.insert(new_car);
	}
	// Cap nhat vi tri theo g_nTextureOffset (CONVERT_TEXTURE_TO_MODELVIEW)
	GLfloat distModelview = texOffset * CONVERT_TEXTURE_TO_MODELVIEW * 1.0f;
	Node* tmp = g_lNPC.m_pHead;
	for (int i = 0; i < g_lNPC.m_nCountElements; ++i) {
		//printf("Update npc!\n");
		((ModelCar3D*)tmp->data)->m_nZ += distModelview;
		((ModelCar3D*)tmp->data)->m_nTyreRotate += 25 * g_mdPlayerCar.m_nSpeed;
		if (((ModelCar3D*)tmp->data)->m_nTyreRotate > 360.0f)
			((ModelCar3D*)tmp->data)->m_nTyreRotate -= 360.0f;
		if (((ModelCar3D*)tmp->data)->m_nStatusMoveNPC == NPC_MOVE) {
			if (((ModelCar3D*)tmp->data)->m_bFlag == false) // NPC di chuyen tu trai qua phai
            {
                ((ModelCar3D*)tmp->data)->m_nX -= TIME_STEP / 100.0f;
                if (((ModelCar3D*)tmp->data)->m_nX < -(MAX_TRANSL - 1.0f))
                    ((ModelCar3D*)tmp->data)->m_bFlag = true;
            }
            else
            {
                ((ModelCar3D*)tmp->data)->m_nX += TIME_STEP / 100.0f;
                if (((ModelCar3D*)tmp->data)->m_nX > (MAX_TRANSL - 1.0f))
                    ((ModelCar3D*)tmp->data)->m_bFlag = false;			
			}
		}
		tmp = tmp->next;
	}
	//delete tmp;
	while (g_lNPC.m_nCountElements > 0)
		if (((ModelCar3D*)g_lNPC.m_pHead->data)->m_nZ > 100)
			void* p = g_lNPC.pop();
		else
			break;
}
void UpdateObjects(GLfloat texOffset) {
	if (g_nTextureOffset - g_nMemoryStepDistCreateObject >= 0.5f) // 1000ms = 1s
	{
		//printf("create new object\n");
		//srand(time(&g_nTotalTime));
		g_nMemoryStepDistCreateObject = g_nTextureOffset;
		ModelTree2D* new_tree = new ModelTree2D();
		new_tree->m_nType = rand() % 3 + 1;
		new_tree->m_nX = (GLfloat) (rand() % 60 + 25);
		if (rand() % 2 == 0)
			new_tree->m_nX = -new_tree->m_nX;
		new_tree->m_nZ = (GLfloat) 1200;
		g_lObjects.insert(new_tree);
	}
	// Cap nhat vi tri theo g_nTextureOffset (CONVERT_TEXTURE_TO_MODELVIEW)


	
	GLfloat distModelview = texOffset * CONVERT_TEXTURE_TO_MODELVIEW * 1.0f;
	Node* tmp = g_lObjects.m_pHead;
	for (int i = 0; i < g_lObjects.m_nCountElements; ++i) {
		((ModelTree2D*)tmp->data)->m_nZ -= distModelview;
		tmp = tmp->next;
	}
	//delete tmp;
	while (g_lObjects.m_nCountElements > 0)	
	{
		if (((ModelTree2D*)g_lObjects.m_pHead->data)->m_nZ < -100)
			void* p = g_lObjects.pop();
		else
			break;
		if (g_lObjects.m_nCountElements == 0)
			int ttt = 1;
	}
};
bool CheckGameOver(void) {
	/////////////////// check game over ///////////////////
	Node* tmp = g_lNPC.m_pHead;
	for (int i = 0; i < g_lNPC.m_nCountElements; ++i) {
		if (abs(((ModelCar3D*)tmp->data)->m_nX - g_mdPlayerCar.m_nX) < 2 &&
			abs(((ModelCar3D*)tmp->data)->m_nZ - g_mdPlayerCar.m_nZ) < 3) {
			// game over;
			return true;
		}
		tmp = tmp->next;
	}
	return false;
}

void UpdateGame(void) {
	//g_nTextureOffset += 0.01;
	// update player
	// update NPC - non player character
	// sau moi 3 giay tang speed level len mot bac
	g_nTotalTime += TIME_STEP;
	if (g_nTotalTime - g_nMemoryStepTimeSpeedLevel >= 1500.0f) {
		g_nMemoryStepTimeSpeedLevel = g_nTotalTime;
		g_nLevelCurrent++;
		g_nLevelCurrent = std::min(g_nLevelCurrent, MAX_LEVEL - 1);
		g_mdPlayerCar.m_nSpeed += g_pSpeedLevel[g_nLevelCurrent];
	}
	
	GLfloat texOffsetInFrame = g_mdPlayerCar.m_nSpeed * (TIME_STEP * 1.0f / 1000.0f);
	//printf("g_nTextureOffset  = %f\n", g_nTextureOffset);
	g_nTextureOffset += texOffsetInFrame;
	g_nScore = (long long) 100 * g_nTextureOffset;
	UpdatePlayer();
	UpdateNPC(texOffsetInFrame);
	UpdateObjects(texOffsetInFrame);
	if (CheckGameOver()) {
		RenderGameOver();
		printf("game over!!!!!!!!\n");
		//std::cout << g_USER.first << "'s score: " << g_nScore << "\n";
		//std::cout << g_pData[g_pData.size() - 1].first << "'s score: " << g_nScore << "\n";
		//g_pData[g_pData.size() - 1].second = std::max(g_pData[g_pData.size() - 1].second, g_nScore);
		g_mapData[g_USER.first] = std::max(g_mapData[g_USER.first], g_nScore);
		if (g_nScore > g_nHighScore) {
			printf("this is new highest score!!!!\n");
			printf("%d > %d\n",g_nScore, g_nHighScore);
			std::cout << g_nScore << " " << g_nHighScore << "\n";
			g_nHighScore = g_nScore;
		}
		g_fFileOu.open("data.txt");
		for(auto i: g_mapData)
			g_fFileOu << i.first << '#' << i.second << "\n";
		g_fFileOu.close();
		LeaveGame();
		g_nStatusGame = OVER;
	}
}

void DebugGame(void) {
	//printf("cnt car = %d   cnt tree = %d\n", g_lNPC.m_nCountElements, g_lObjects.m_nCountElements);
	//if (g_lObjects.m_nCountElements > 0)
	//	printf("cay xa nhat d = %f\n", ((ModelTree2D*)g_lObjects.m_pHead->data)->m_nZ);
	//else
	//	printf("khong con cay\n");
	printf("level current: %d   speed current = %f\n", g_nLevelCurrent, g_mdPlayerCar.m_nSpeed);
}

void GameLoop(int ttt) {
	if (g_nStatusGame == RUNNING) {
		UpdateGame();
		//DebugGame();
		printf("g_nleft = %f\n", g_nCamPosition);
		glutPostRedisplay();
		glutTimerFunc(TIME_STEP, GameLoop, 0);
	}
	else if (g_nStatusGame == PAUSE) {
		glutPostRedisplay();
		glutTimerFunc(TIME_STEP, GameLoop, 0);
	}
	else {
		;
	}

}