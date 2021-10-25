#include "HighScore.h"

GLfloat g_pPossitionRank[5] = {-18, -16, -14 ,-12 ,-10};
bool g_bStatusHighScore;

void KeyboardHighScore(unsigned char key, int x, int y) {
	switch (key)
	{
	case 27:
		g_bStatusHighScore = false;
		LeaveHighScore();
		EnterMenu();
	default:
		break;
	}
}
void RenderRank(void) {
	//sort(g_pData.begin(), g_pData.end(), cmp);
	//g_mapData["quangphu"] = 123456;
	auto v = SortMap(g_mapData);
	glPushMatrix();
		glEnable(GL_TEXTURE_2D);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA,GL_ONE);
		glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);

		// 1200 300
		GLfloat size_w = 5.5f, size_h = size_w * 3.0f / 12.0f;
		glPushMatrix();
			//glTranslatef(g_pTranslateMenu[0], 3.0f, 0);
			glTranslatef(g_pPossitionRank[0], 3.0f, 0);
			glBindTexture(GL_TEXTURE_2D, g_pTexture[TEXTURE_RANK01]);
			glBegin(GL_POLYGON);
				glColor3f(1, 1, 1);
				glTexCoord2f(0, 0); glVertex3f(-size_w / 2.0f, -size_h / 2.0f, 0);
				glTexCoord2f(1, 0); glVertex3f(size_w / 2.0f, -size_h / 2.0f, 0);
				glTexCoord2f(1, 1); glVertex3f(size_w / 2.0f, size_h / 2.0f, 0);
				glTexCoord2f(0, 1); glVertex3f(-size_w / 2.0f, size_h / 2.0f, 0);
			glEnd();
			glDisable(GL_DEPTH_TEST);
			glDisable(GL_BLEND);
			glDisable(GL_TEXTURE_2D);
			PrintText1(-0.5f, 0.35f, 1, 1, 1, 1, GLUT_BITMAP_HELVETICA_18, v[0].first);
			PrintText2(0.3f, -0.2f, 1, 1, 1, 1, GLUT_BITMAP_HELVETICA_18, "", v[0].second);
			glEnable(GL_TEXTURE_2D);
			glEnable(GL_BLEND);
			glEnable(GL_DEPTH_TEST);
		glPopMatrix();

		glPushMatrix();
			//glTranslatef(g_pTranslateMenu[0], 3.0f, 0);
			glTranslatef(g_pPossitionRank[1], 1.5f, 0);
			glBindTexture(GL_TEXTURE_2D, g_pTexture[TEXTURE_RANK02]);
			glBegin(GL_POLYGON);
				glColor3f(1, 1, 1);
				glTexCoord2f(0, 0); glVertex3f(-size_w / 2.0f, -size_h / 2.0f, 0);
				glTexCoord2f(1, 0); glVertex3f(size_w / 2.0f, -size_h / 2.0f, 0);
				glTexCoord2f(1, 1); glVertex3f(size_w / 2.0f, size_h / 2.0f, 0);
				glTexCoord2f(0, 1); glVertex3f(-size_w / 2.0f, size_h / 2.0f, 0);
			glEnd();
			glDisable(GL_DEPTH_TEST);
			glDisable(GL_BLEND);
			glDisable(GL_TEXTURE_2D);
			PrintText1(-0.5f, 0.35f, 1, 1, 1, 1, GLUT_BITMAP_HELVETICA_18, v[1].first);
			PrintText2(0.3f, -0.2f, 1, 1, 1, 1, GLUT_BITMAP_HELVETICA_18, "", v[1].second);
			glEnable(GL_TEXTURE_2D);
			glEnable(GL_BLEND);
			glEnable(GL_DEPTH_TEST);
		glPopMatrix();

		glPushMatrix();
			//glTranslatef(g_pTranslateMenu[0], 3.0f, 0);
			glTranslatef(g_pPossitionRank[2], 0, 0);
			glBindTexture(GL_TEXTURE_2D, g_pTexture[TEXTURE_RANK03]);
			glBegin(GL_POLYGON);
				glColor3f(1, 1, 1);
				glTexCoord2f(0, 0); glVertex3f(-size_w / 2.0f, -size_h / 2.0f, 0);
				glTexCoord2f(1, 0); glVertex3f(size_w / 2.0f, -size_h / 2.0f, 0);
				glTexCoord2f(1, 1); glVertex3f(size_w / 2.0f, size_h / 2.0f, 0);
				glTexCoord2f(0, 1); glVertex3f(-size_w / 2.0f, size_h / 2.0f, 0);
			glEnd();
			glDisable(GL_DEPTH_TEST);
			glDisable(GL_BLEND);
			glDisable(GL_TEXTURE_2D);
			PrintText1(-0.5f, 0.35f, 1, 1, 1, 1, GLUT_BITMAP_HELVETICA_18, v[2].first);
			PrintText2(0.3f, -0.2f, 1, 1, 1, 1, GLUT_BITMAP_HELVETICA_18, "", v[2].second);
			glEnable(GL_TEXTURE_2D);
			glEnable(GL_BLEND);
			glEnable(GL_DEPTH_TEST);
		glPopMatrix();

		glPushMatrix();
			//glTranslatef(g_pTranslateMenu[0], 3.0f, 0);
			glTranslatef(g_pPossitionRank[3], -1.5f, 0);
			glBindTexture(GL_TEXTURE_2D, g_pTexture[TEXTURE_RANK04]);
			glBegin(GL_POLYGON);
				glColor3f(1, 1, 1);
				glTexCoord2f(0, 0); glVertex3f(-size_w / 2.0f, -size_h / 2.0f, 0);
				glTexCoord2f(1, 0); glVertex3f(size_w / 2.0f, -size_h / 2.0f, 0);
				glTexCoord2f(1, 1); glVertex3f(size_w / 2.0f, size_h / 2.0f, 0);
				glTexCoord2f(0, 1); glVertex3f(-size_w / 2.0f, size_h / 2.0f, 0);
			glEnd();
			glDisable(GL_DEPTH_TEST);
			glDisable(GL_BLEND);
			glDisable(GL_TEXTURE_2D);
			PrintText1(-0.5f, 0.35f, 1, 1, 1, 1, GLUT_BITMAP_HELVETICA_18, v[3].first);
			PrintText2(0.3f, -0.2f, 1, 1, 1, 1, GLUT_BITMAP_HELVETICA_18, "", v[3].second);
			glEnable(GL_TEXTURE_2D);
			glEnable(GL_BLEND);
			glEnable(GL_DEPTH_TEST);
		glPopMatrix();

		glPushMatrix();
			//glTranslatef(g_pTranslateMenu[0], 3.0f, 0);
			glTranslatef(g_pPossitionRank[4], -3.0f, 0);
			glBindTexture(GL_TEXTURE_2D, g_pTexture[TEXTURE_RANK05]);
			glBegin(GL_POLYGON);
				glColor3f(1, 1, 1);
				glTexCoord2f(0, 0); glVertex3f(-size_w / 2.0f, -size_h / 2.0f, 0);
				glTexCoord2f(1, 0); glVertex3f(size_w / 2.0f, -size_h / 2.0f, 0);
				glTexCoord2f(1, 1); glVertex3f(size_w / 2.0f, size_h / 2.0f, 0);
				glTexCoord2f(0, 1); glVertex3f(-size_w / 2.0f, size_h / 2.0f, 0);
			glEnd();
			glDisable(GL_DEPTH_TEST);
			glDisable(GL_BLEND);
			glDisable(GL_TEXTURE_2D);
			PrintText1(-0.5f, 0.35f, 1, 1, 1, 1, GLUT_BITMAP_HELVETICA_18, v[4].first);
			PrintText2(0.3f, -0.2f, 1, 1, 1, 1, GLUT_BITMAP_HELVETICA_18, "", v[4].second);
			glEnable(GL_TEXTURE_2D);
			glEnable(GL_BLEND);
			glEnable(GL_DEPTH_TEST);
		glPopMatrix();

		glDisable(GL_TEXTURE_2D);
		glDisable(GL_BLEND);
	glPopMatrix();

}
void RenderHightScoreBackground(void) {
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
void RenderHighScore(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0, 0, 10, 0, 0, 0, 0, 1, 0);

	glPushMatrix();
		RenderHightScoreBackground();
		RenderRank();
	glPopMatrix();

	glutSwapBuffers();
}
void LeaveHighScore(void) {
	glutKeyboardFunc(NULL);
}
void HighScoreLoop(int t) {
	if (g_bStatusHighScore) {
		for (int i = 0; i < 5; ++i) {
			g_pPossitionRank[i] += 0.2f;
			g_pPossitionRank[i] = std::min(g_pPossitionRank[i], 0.0f);
		}
		glutTimerFunc(TIME_STEP, HighScoreLoop, 10);
		glutPostRedisplay();
		//printf("high score loop,  t = %d\n", t);
	}
	else;
}
void EnterHighScore(void) {
	g_bStatusHighScore = true;
	g_pPossitionRank[0] = -18;
	g_pPossitionRank[1] = -16;
	g_pPossitionRank[2] = -14;
	g_pPossitionRank[3] = -12;
	g_pPossitionRank[4] = -10;
	glutDisplayFunc(RenderHighScore);
	glutKeyboardFunc(KeyboardHighScore);
	HighScoreLoop(0);
}

