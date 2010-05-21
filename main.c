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

void renderAxes() {
	glLineWidth(2);
	glColor3f(1.0f, 0.0f, 0.0f);
	glBegin(GL_LINES);
	glVertex3f(0, 0, 0);
	glVertex3f(1, 0, 0);
	glEnd();

	glColor3f(0.0f, 1.0f, 0.0f);
	glBegin(GL_LINES);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 1, 0);
	glEnd();

	glColor3f(0.0f, 0.0f, 1.0f);
	glBegin(GL_LINES);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 0, 1);
	glEnd();

	glLineWidth(1);
}

void render(void) {
	glClearColor(0.5f, 0.5f, 0.5f, 0.5f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glCullFace(GL_BACK);
	glColor3f(1.0f, 1.0f, 1.0f);
	glPolygonMode(GL_FRONT, GL_FILL);
	glBegin(GL_QUADS);
	glVertex3f(0, 0, 0);
	glVertex3f(8, 0, 0);
	glVertex3f(8, 0, -10);
	glVertex3f(0, 0, -10);
	glEnd();

	renderAxes();

	glColor4f(1.0f, 0.0f, 0.0f, 0.25f);
	glCullFace(GL_BACK);
	glPolygonMode(GL_FRONT, GL_FILL);
	glCallList(graphics.maze);

	glColor4f(0.0f, 0.0f, 1.0f, 0.25f);
	glCullFace(GL_FRONT);
	glPolygonMode(GL_BACK, GL_FILL);
	glCallList(graphics.maze);

	glDisable(GL_CULL_FACE);
	glColor3f(0.0f, 0.0f, 0.0f);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glLineWidth(1);
	glCallList(graphics.maze);
	glEnable(GL_CULL_FACE);

	glutSwapBuffers();
}

void update(int value) {
	(void) value;
	glutTimerFunc(TIMERMSECS, update, 0);
	glutPostRedisplay();
}

void renderWall(int row, int col, walls dir) {
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
	game.maze = maze_new(8, 10);

	graphics.maze = glGenLists(1);
	glNewList(graphics.maze, GL_COMPILE);
	renderMaze();
	glEndList();

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60, 4./3, 0.1, 50);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(4, 6, 5, 4, 0, -5, 0, 1, 0);

	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);

	glEnable(GL_LINE_SMOOTH);
	glEnable(GL_POLYGON_SMOOTH);
	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
	glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

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
