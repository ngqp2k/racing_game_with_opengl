#include "App.h"

void RunApp(int argc, char* argv[]) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
	glutInitWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("My game");

	glClearColor(0, 0, 0, 1);
	glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_LINEAR);//avs might well change to flat
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);//??

	glFrontFace(GL_CCW);
    glEnable(GL_CULL_FACE);//glFrontFace()for GL_CW or GL_CCW

	LoadAllResouce();
	ReadData();

	glutReshapeFunc(ReshapeApp);
	//glutDisplayFunc(DisplayApp);
	//glutIgnoreKeyRepeat(1);
	EnterMenu();
	//EnterEnterUserName();
	//EnterHighScore();
	//EnterGame();
}

void ReshapeApp(int w, int h) {
    if(h == 0)
		h = 1;
    GLfloat aspect = 1.0f * w / h * 1.0f;
    glViewport(0, 0, w, h);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluPerspective(45.0f, aspect, 1.0f, 10000.0f);
}