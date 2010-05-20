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
	for (unsigned row = 0; row < rows; row++) {
		for (unsigned col = 0; col < cols; col++) {
			cell_init(maze_get_cell(m, row, col));
		}
	}
	return m;
}

void maze_free(maze *m) {
	free(m->cells);
	free(m);
}
