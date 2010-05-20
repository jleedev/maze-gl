#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#ifdef __APPLE__
#  include <GLUT/glut.h>
#else
#  include <GL/glut.h>
#endif

#define TIMERMSECS 17.0f

void render(void) {
}

void update(int value) {
	(void) value;
	glutTimerFunc(TIMERMSECS, update, 0);

	glutPostRedisplay();
}

int main(int argc, char **argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutInitWindowSize(400,300);
	glutCreateWindow("Hello World");
	glutDisplayFunc(render);
	glutTimerFunc(TIMERMSECS, update, 0);

	glutMainLoop();
	return 0;
}
