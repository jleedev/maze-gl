#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "maze.h"

#ifdef __APPLE__
#  include <GLUT/glut.h>
#else
#  include <GL/glut.h>
#endif

#define TIMERMSECS 17.0f

struct {
	GLuint maze;
} graphics;

struct {
	maze *maze;
	struct {
		unsigned row, col;
		unsigned angle;
	} player;
} game;

void render(void) {
	glClearColor(0.5f, 0.5f, 0.5f, 0.5f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glCallList(graphics.maze);
	glutSwapBuffers();
}

void update(int value) {
	(void) value;
	glutTimerFunc(TIMERMSECS, update, 0);
	glutPostRedisplay();
}

void renderWall(unsigned row, unsigned col, walls dir) {
	glBegin(GL_QUADS);
	switch (dir) {
		case NORTH:
			glVertex3f(col, 0, -row);
			glVertex3f(col+1, 0, -row);
			glVertex3f(col+1, 1, -row);
			glVertex3f(col, 1, -row);
			break;
		case EAST:
			glVertex3f(col+1, 0, -row);
			glVertex3f(col+1, 0, -row-1);
			glVertex3f(col+1, 1, -row-1);
			glVertex3f(col+1, 1, -row);
			break;
		case SOUTH:
			glVertex3f(col, 1, -row-1);
			glVertex3f(col+1, 1, -row-1);
			glVertex3f(col+1, 0, -row-1);
			glVertex3f(col, 0, -row-1);
			break;
		case WEST:
			glVertex3f(col, 1, -row);
			glVertex3f(col, 1, -row-1);
			glVertex3f(col, 0, -row-1);
			glVertex3f(col, 0, -row);
			break;
		default:
			fprintf(stderr, "renderWall: %d: not a wall\n",
			                dir);
			abort();
	}
	glEnd();
}

void renderMaze() {
	unsigned rows = maze_get_rows(game.maze);
	unsigned cols = maze_get_cols(game.maze);
	for (unsigned row = 0; row < rows; row++) {
		for (unsigned col = 0; col < cols; col++) {
			cell *c = maze_get_cell(game.maze, row, col);
			walls w = cell_get_walls(c);
			if (w & NORTH) renderWall(row, col, NORTH);
			if (w & EAST)  renderWall(row, col, EAST);
			if (w & SOUTH) renderWall(row, col, SOUTH);
			if (w & WEST)  renderWall(row, col, WEST);
		}
	}
}

void init(void) {
	game.maze = maze_new(4, 5);

	graphics.maze = glGenLists(1);
	glNewList(graphics.maze, GL_COMPILE);
	renderMaze();
	glEndList();

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60, 4./3, 60, 100);
	glMatrixMode(GL_MODELVIEW);
	glTranslatef(0, 0, -80);
}

int main(int argc, char **argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutInitWindowSize(400,300);
	glutCreateWindow("Hello World");
	glutDisplayFunc(render);
	glutTimerFunc(TIMERMSECS, update, 0);
	init();
	glutMainLoop();
	return 0;
}
