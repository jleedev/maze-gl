#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "malloc.h"

#include "maze.h"

#define NORTH 1
#define EAST  2
#define SOUTH 4
#define WEST  8

struct _cell {
	unsigned char walls;
};

void cell_init(cell *c) {
	c->walls = NORTH | EAST | SOUTH | WEST;
}

struct _maze {
	cell *cells;
	unsigned rows;
	unsigned cols;
};

cell *maze_get_cell(maze *m, unsigned row, unsigned col) {
	return m->cells + m->cols*row + col;
}

maze *maze_new(unsigned rows, unsigned cols) {
	maze *m = snew(maze);
	m->cells = snewn(rows*cols, cell);
	m->rows = rows;
	m->cols = cols;
	for (unsigned row = 0; row < rows; row++) {
		for (unsigned col = 0; col < cols; col++) {
			cell_init(maze_get_cell(m, row, col));
		}
	}
	maze_generate(m);
	return m;
}

void maze_generate(maze *m) {
	// FIXME fake maze generation for now.
	for (unsigned row = 0; row < m->rows; row++) {
		for (unsigned col = 0; col < m->cols; col++) {
			maze_get_cell(m, row, col)->walls &=
				~(1 << (random() % 4));
		}
	}
}

void maze_print(maze *m) {
	for (unsigned row = 0; row < m->rows; row++) {
		for (unsigned col = 0; col < m->cols; col++) {
			printf("%x", maze_get_cell(m, row, col)->walls);
		}
		putchar('\n');
	}
}

void maze_free(maze *m) {
	if (m) sfree(m->cells);
	sfree(m);
}
