#include "App.h"

int main(int argc, char* argv[]) {
	srand(time(NULL));
	RunApp(argc, argv);
	glutMainLoop();
	g_fFileIn.close();
	g_fFileOu.close();
	return 0;
}