#include "glm.h"
using namespace std;

#include <gl/freeglut.h>
#define PI 3.14159265358
#define W 640
#define H 640

const GLfloat factor = 2;

GLMmodel *pmodel;

void DrawAxis() {
	glBegin(GL_LINES);
	{
		glColor3f(1, 0, 0);
		glVertex3f(0, 0, 0);
		glVertex3f(factor, 0, 0);
		glColor3f(0, 1, 0);
		glVertex3f(0, 0, 0);
		glVertex3f(0, factor, 0);
		glColor3f(0, 0, 1);
		glVertex3f(0, 0, 0);
		glVertex3f(0, 0, factor);
	}
	glEnd();
}

void display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0.7, 0.5, 0.3, 0, 0, 0, 0, 1, 0);

	DrawAxis();
	glScalef(0.25, 0.25, 0.25);
	glmDraw(pmodel, GLM_SMOOTH | GLM_MATERIAL);

	glutSwapBuffers();
}

void init() {
	glClearColor(1, 1, 1, 1);
	glColor3f(0, 0, 0);

	glEnable(GL_DEPTH_TEST);
	glFrontFace(GL_CW);
	// glEnable(GL_CULL_FACE);

	
}

//void idle(){}
//void special(int key, int x, int y) {}
//void key(unsigned char ch, int x, int y) {}
//void mouse(int button, int state, int x, int y) {}

int main(int argc, char* agrv[]) {
	glutInit(&argc, agrv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(W, H);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("window");

	glutDisplayFunc(display);
	// glutSpecialFunc(special);
	// glutKeyboardFunc(key);
	// glutMouseFunc(mouse);
	// glutIdleFunc(idle);
	pmodel = glmReadOBJ("data/cube.obj");


	init();

	glutMainLoop();
}