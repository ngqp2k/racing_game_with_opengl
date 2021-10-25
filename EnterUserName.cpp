#include "EnterUserName.h"

enum eSTATUS_USERNAME {
	TYPING = 0,
	ACCEPT,
	ERROR_LENGTH,
	ERROR_CHARAC,
	ERROR_ALREADY_EXITS,
};

GLint g_nStatus = TYPING;

std::string g_sUsername;
std::pair<std::string, long long> g_USER;
bool g_bWarnningLengthUsername = false;
bool g_bStatus;

void PrintText(GLfloat x, GLfloat y, int r, int g, int b, int a, void* font, std::string s) {
	glColor3f((GLfloat)r, (GLfloat)g, (GLfloat)b);
	glRasterPos3f(x, y, 0);
	//sprintf(ch, "Score: %d", num);
	//len = (int)strlen(ch);
	for (int i = 0; i < (int)s.length(); ++i)
		glutBitmapCharacter(font, s[i]);
}
void InitUserName(void) {
	g_bStatus = true;
	g_sUsername = "";
	g_USER.first = "";
	g_USER.second = 0;
	g_bStatusEnterUsername = true;
}
bool CheckAlreadyExitsUsername(std::string s) {
	//for (int i = 0; i < (int)g_pData.size(); ++i) {
	//	//std::cout << g_pData[i].first << " --- " << g_pData[i].second << "\n";
	//	if (g_pData[i].first == s)
	//		return false;
	//}
	if (g_mapData[s])
		return false;
	return true;
}
bool CheckSpecialCharacterUsername(std::string s) {
	for (int i = 0; i < (int)s.length(); ++i)
		if (!((48 <= s[i] && s[i] <= 57) || (65 <= s[i] && s[i] <= 90) || (97 <= s[i] && s[i] <= 122)))
			return false;
	return true;
}
void LeaveEnterUserName(void) {
	g_bStatus = false;
	glutKeyboardFunc(NULL);
	glutIgnoreKeyRepeat(1);
}
void KeyboardEnterUserName(unsigned char key, int x, int y) {
	//printf("%d\n", (int)key);
	switch (key)
	{
	case 13:
		if (g_sUsername.length() == 0 || g_sUsername.length() > 15) {
			g_nStatus = ERROR_LENGTH;
		}
		else if (!CheckAlreadyExitsUsername(g_sUsername)){
			g_nStatus = ERROR_ALREADY_EXITS;
		}
		else if (!CheckSpecialCharacterUsername(g_sUsername)) {
			g_nStatus = ERROR_CHARAC;
		}
		else {
			// Accept
			g_USER.first = g_sUsername;
			LeaveEnterUserName();
			std::cout << "Accept username " << g_sUsername << " ! ---> EnterGame\n";
			//g_pData.push_back(g_USER);
			g_mapData[g_sUsername] = 0; // push map
			EnterGame();
		}
		break;
	case 8:
		if (g_sUsername.length() > 0) {
			g_sUsername.pop_back();
		}
		break;
	default:
		if (g_sUsername.length() <= 20)
			g_sUsername = g_sUsername + char(key);
		break;
	}
}
void RenderTextbox(void) {
	glPushMatrix();
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_BLEND);     // Turn Blending On
		glDisable(GL_DEPTH_TEST);
		glBlendFunc(GL_SRC_ALPHA,GL_ONE);
		glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, g_pTexture[TEXTURE_TEXTBOX01]);
		glBegin(GL_POLYGON);
			glTexCoord2f(0, 0); glVertex3f(-5, -0.5, 0);
			glTexCoord2f(1, 0); glVertex3f(5, -0.5, 0);
			glTexCoord2f(1, 1); glVertex3f(5, 0.5, 0);
			glTexCoord2f(0, 1); glVertex3f(-5, 0.5, 0);
		glEnd();
		glDisable(GL_TEXTURE_2D);
		glEnable(GL_DEPTH_TEST);
		glDisable(GL_BLEND);  
	glPopMatrix();
}
void RenderEnterUserName(void) {
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0, 0, 10, 0, 0, 0, 0, 1, 0);

	glPushMatrix();
		RenderTextbox();
		if (g_bWarnningLengthUsername) {
			
			g_bWarnningLengthUsername = false;
		}
		switch (g_nStatus)
		{
		case ERROR_LENGTH:
			PrintText(0.5f, -0.7f, 1, 0, 0, 1, GLUT_BITMAP_HELVETICA_18, "Username length between 1 - 15!");
			break;
		case ERROR_CHARAC:
			PrintText(0.5f, -0.7f, 1, 0, 0, 1, GLUT_BITMAP_HELVETICA_18, "Space and special character not allowed!");
			break;
		case ERROR_ALREADY_EXITS:
			PrintText(0.5f, -0.7f, 1, 0, 0, 1, GLUT_BITMAP_HELVETICA_18, "Username has already been taken!");
			break;
		default:
			break;
		}
		PrintText(0.5, 0, 1, 1, 1, 1, GLUT_BITMAP_HELVETICA_18, g_sUsername);
	glPopMatrix();


	glutSwapBuffers();
}
void EnterUsernameLoop(int t) {
	if (g_bStatus) {
		glutPostRedisplay();
		glutTimerFunc(TIME_STEP, EnterUsernameLoop, 0);
	}
	else;
}
void EnterEnterUserName(void) {
	InitUserName();
	glutDisplayFunc(RenderEnterUserName);
	glutKeyboardFunc(KeyboardEnterUserName);
	glutIgnoreKeyRepeat(0);
	EnterUsernameLoop(0);
}