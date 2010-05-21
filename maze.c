#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "malloc.h"

#include "maze.h"

struct _cell {
	walls walls;
};

void cell_init(cell *c) {
	c->walls = NORTH | EAST | SOUTH | WEST;
}

walls cell_get_walls(cell *c) {
	return c->walls;
}

struct _maze {
	cell *cells;
	unsigned rows;
	unsigned cols;
};

cell *maze_get_cell(maze *m, unsigned row, unsigned col) {
	return m->cells + m->cols*row + col;
}

unsigned maze_get_rows(maze *m) {
	return m->rows;
}

unsigned maze_get_cols(maze *m) {
	return m->cols;
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
	// However, it still removes two walls each.
	for (unsigned row = 0; row < m->rows; row++) {
		for (unsigned col = 0; col < m->cols; col++) {
			int x = random() % 4;
			int y = (x + 1) % 4;
			maze_get_cell(m, row, col)->walls &= ~(1 << x);
			maze_get_cell(m, row, col)->walls &= ~(1 << y);
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
