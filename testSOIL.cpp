#include <GL/freeglut.h>
#include <stdio.h>
#include "SOIL.h"
#pragma comment(lib, "SOIL.lib")
#define PI 3.14159265358
#define W 640
#define H 640

const GLfloat factor = 2;

GLuint tex_2d;
GLuint g_box;
GLuint texture; 

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

GLuint MakeCube(GLfloat size)
{
  GLuint boxDisplay;
  boxDisplay=glGenLists(1);
  glNewList(boxDisplay,GL_COMPILE);
 
  glBegin(GL_QUADS);
  // Front Face
  glTexCoord2f(0.0f, 0.0f); glVertex3f(-size, -size, size);
  glTexCoord2f(1.0f, 0.0f); glVertex3f( size, -size, size);
  glTexCoord2f(1.0f, 1.0f); glVertex3f( size, size, size);
  glTexCoord2f(0.0f, 1.0f); glVertex3f(-size, size, size);
  // Back Face
  glTexCoord2f(1.0f, 0.0f); glVertex3f(-size, -size, -size);
  glVertex3f(-size, size, -size);
  glVertex3f( size, size, -size);
  glTexCoord2f(0.0f, 0.0f); glVertex3f( size, -size, -size);
  // Top Face
  glTexCoord2f(0.0f, 1.0f); glVertex3f(-size, size, -size);
  glTexCoord2f(0.0f, 0.0f); glVertex3f(-size, size, size);
  glTexCoord2f(1.0f, 0.0f); glVertex3f( size, size, size);
  glTexCoord2f(1.0f, 1.0f); glVertex3f( size, size, -size);
  // Bottom Face
  glTexCoord2f(1.0f, 1.0f); glVertex3f(-size, -size, -size);
  glTexCoord2f(0.0f, 1.0f); glVertex3f( size, -size, -size);
  glTexCoord2f(0.0f, 0.0f); glVertex3f( size, -size, size);
  glTexCoord2f(1.0f, 0.0f); glVertex3f(-size, -size, size);
  // Right face
  glTexCoord2f(1.0f, 0.0f); glVertex3f( size, -size, -size);
  glTexCoord2f(1.0f, 1.0f); glVertex3f( size, size, -size);
  glTexCoord2f(0.0f, 1.0f); glVertex3f( size, size, size);
  glTexCoord2f(0.0f, 0.0f); glVertex3f( size, -size, size);
  // Left Face
  glTexCoord2f(0.0f, 0.0f); glVertex3f(-size, -size, -size);
  glTexCoord2f(1.0f, 0.0f); glVertex3f(-size, -size, size);
  glTexCoord2f(1.0f, 1.0f); glVertex3f(-size, size, size);
  glTexCoord2f(0.0f, 1.0f); glVertex3f(-size, size, -size);
  glEnd();
 
  glEndList();
  return boxDisplay;
}

void display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	//glLoadIdentity();
	//gluLookAt(0.7, 0.5, 0.3, 0, 0, 0, 0, 1, 0);

	// DrawAxis();
	//glBindTexture(GL_TEXTURE_2D, tex_2d);
	//glCallList(g_box);

	glutSwapBuffers();
}

void init() {
	glClearColor(0, 0, 0, 1);

	//glEnable(GL_DEPTH_TEST);
	//glEnable(GL_TEXTURE_2D);

	//glFrontFace(GL_CW);

	// glEnable(GL_CULL_FACE);	
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	tex_2d = SOIL_load_OGL_texture
		(
			"res/car.jpg",
			SOIL_LOAD_AUTO,
			SOIL_CREATE_NEW_ID,
			SOIL_FLAG_TEXTURE_REPEATS | SOIL_FLAG_INVERT_Y
		);

	/* check for an error during the load process */
	if(0 == tex_2d)
	{
		printf( "SOIL loading error: '%s'\n", SOIL_last_result() );
	} else {
		printf( "Load thanh cong\n");
		printf("%d", tex_2d);
	}

	g_box = MakeCube(1.0);
	
}

void reshape(int w, int h) {
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (w <= h)
		glOrtho(-factor, factor, -factor * h / w, factor * h / w, -1000, 1000);
	else
		glOrtho(-factor * w / h, factor * w / h, -factor, factor, -1000, 1000);
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

	glutReshapeFunc(reshape);
	glutDisplayFunc(display);
	//system("pause");
	init();

	glutMainLoop();
}