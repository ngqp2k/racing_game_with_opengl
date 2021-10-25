#include "Menu.h"
#define MAX_TRANSLATE -1.5f
#define MIN_TRANSLATE -2.5f
#define STEP_TRANSLATE 0.075f

GLint g_nSelection = 0;
GLfloat g_pTranslateMenu[3] = {MIN_TRANSLATE, MIN_TRANSLATE, MIN_TRANSLATE};
bool g_bStatusEnterUsername = false;
bool g_bStatusMenu;

void SpecialKeyMenu(int key, int x, int y) {
	switch (key)
	{
	case GLUT_KEY_UP:
		if (g_nSelection == 0) {
			g_nSelection = 2;
		}
		else
			g_nSelection--;
		break;
	case GLUT_KEY_DOWN:
		if (g_nSelection == 2) {
			g_nSelection = 0;
		}
		else
			g_nSelection++;
		break;
	default:
		break;
	}
}

void LeaveMenu(void) {
	g_bStatusMenu = true;
	glutSpecialFunc(NULL);
	glutKeyboardFunc(NULL);
}

void KeyboardMenu(unsigned char key, int x, int y) {
	switch (key)
	{
	case 13:
		LeaveMenu();
		switch (g_nSelection)
		{
		case 0:
			printf("new game\n");
			if (!g_bStatusEnterUsername) {
				printf("enter username\n");
				EnterEnterUserName();
			}
			else
				EnterGame();
			break;
		case 1:
			printf("high score\n");
			EnterHighScore();
			break;
		case 2:
			printf("exit\n");
			exit(0);
			break;
		default:
			break;
		}
		break;
	default:
		break;
	}
}

void EnterMenu(void) {
	g_bStatusMenu = false;
	glutDisplayFunc(RenderMenu);
	glutSpecialFunc(SpecialKeyMenu);
	glutKeyboardFunc(KeyboardMenu);
	MenuLoop(0);
}

void RenderMenuBackground(void) {
	glPushMatrix();
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, g_pTexture[TEXTURE_MENU_BACKGROUND]);

		glScalef(2.2f, 2.2f, 1.0f);
		glTranslatef(0.0f, 0.0f, -5.75f);

		glBegin(GL_POLYGON);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(-4.5f, -3.0f, 0.0f);
			glTexCoord2f(1.0f, 0.0f); glVertex3f(4.5f, -3.0f, 0.0f);
			glTexCoord2f(1.0f, 1.0f); glVertex3f(4.5f, 3.0f, 0.0f);
			glTexCoord2f(0.0f, 1.0f); glVertex3f(-4.5f, 3.0f, 0.0f);
		glEnd();

		glDisable(GL_TEXTURE_2D);
	glPopMatrix();
}

void RenderMenuSelection(void) {
	GLfloat size_w = 5.0f;
	GLfloat size_h = size_w * 239.0f / 1000.0f;
	/// min x = -2.5, max x = -1.5
	switch (g_nSelection)
	{
	case 0:
		g_pTranslateMenu[0] = std::min(MAX_TRANSLATE, g_pTranslateMenu[0] + STEP_TRANSLATE);
		g_pTranslateMenu[1] = std::max(MIN_TRANSLATE, g_pTranslateMenu[1] - STEP_TRANSLATE);
		g_pTranslateMenu[2] = std::max(MIN_TRANSLATE, g_pTranslateMenu[2] - STEP_TRANSLATE);
		break;
	case 1:
		g_pTranslateMenu[0] = std::max(MIN_TRANSLATE, g_pTranslateMenu[0] - STEP_TRANSLATE);
		g_pTranslateMenu[1] = std::min(MAX_TRANSLATE, g_pTranslateMenu[1] + STEP_TRANSLATE);
		g_pTranslateMenu[2] = std::max(MIN_TRANSLATE, g_pTranslateMenu[2] - STEP_TRANSLATE);
		break;
	case 2:
		g_pTranslateMenu[0] = std::max(MIN_TRANSLATE, g_pTranslateMenu[0] - STEP_TRANSLATE);
		g_pTranslateMenu[1] = std::max(MIN_TRANSLATE, g_pTranslateMenu[1] - STEP_TRANSLATE);
		g_pTranslateMenu[2] = std::min(MAX_TRANSLATE, g_pTranslateMenu[2] + STEP_TRANSLATE);
		break;
	default:
		break;
	}
	glPushMatrix();
		glEnable(GL_TEXTURE_2D);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA,GL_ONE);
		glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);

		glPushMatrix();
			glTranslatef(g_pTranslateMenu[0], 3.0f, 0);
			glBindTexture(GL_TEXTURE_2D, g_pTexture[TEXTURE_MENU1_NEWGAME]);
			glBegin(GL_POLYGON);
				glColor3f(1, 1, 1);
				glTexCoord2f(0, 0); glVertex3f(-size_w / 2.0f, -size_h / 2.0f, 0);
				glTexCoord2f(1, 0); glVertex3f(size_w / 2.0f, -size_h / 2.0f, 0);
				glTexCoord2f(1, 1); glVertex3f(size_w / 2.0f, size_h / 2.0f, 0);
				glTexCoord2f(0, 1); glVertex3f(-size_w / 2.0f, size_h / 2.0f, 0);
			glEnd();
		glPopMatrix();

		glPushMatrix();
			glTranslatef(g_pTranslateMenu[1], 1.75f, 0);
			glBindTexture(GL_TEXTURE_2D, g_pTexture[TEXTURE_MENU1_HIGHSCORE]);
			glBegin(GL_POLYGON);
				glColor3f(1, 1, 1);
				glTexCoord2f(0, 0); glVertex3f(-size_w / 2.0f, -size_h / 2.0f, 0);
				glTexCoord2f(1, 0); glVertex3f(size_w / 2.0f, -size_h / 2.0f, 0);
				glTexCoord2f(1, 1); glVertex3f(size_w / 2.0f, size_h / 2.0f, 0);
				glTexCoord2f(0, 1); glVertex3f(-size_w / 2.0f, size_h / 2.0f, 0);
			glEnd();
		glPopMatrix();

		glPushMatrix();
			glTranslatef(g_pTranslateMenu[2], 0.5f, 0);
			glBindTexture(GL_TEXTURE_2D, g_pTexture[TEXTURE_MENU1_QUIT]);
			glBegin(GL_POLYGON);
				glColor3f(1, 1, 1);
				glTexCoord2f(0, 0); glVertex3f(-size_w / 2.0f, -size_h / 2.0f, 0);
					glTexCoord2f(1, 0); glVertex3f(size_w / 2.0f, -size_h / 2.0f, 0);
					glTexCoord2f(1, 1); glVertex3f(size_w / 2.0f, size_h / 2.0f, 0);
					glTexCoord2f(0, 1); glVertex3f(-size_w / 2.0f, size_h / 2.0f, 0);
			glEnd();
		glPopMatrix();

		glDisable(GL_TEXTURE_2D);
		glDisable(GL_BLEND);
	glPopMatrix();
}

void RenderMenu(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0, 0, 10, 0, 0, 0, 0, 1, 0);

	RenderMenuBackground();
	RenderMenuSelection();

	glutSwapBuffers();
}

void MenuLoop(int ttt) {
	if (!g_bStatusMenu) {
		//printf("selection: %d\n", g_nSelection);
		glutTimerFunc(TIME_STEP, MenuLoop, 0);
		glutPostRedisplay();
		//printf("menu loop\n");
	}
	else;
}