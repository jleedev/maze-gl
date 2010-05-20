#ifndef MAZE_H
#define MAZE_H

typedef struct _cell cell;
typedef struct _maze maze;

cell *maze_get_cell(maze *, unsigned row, unsigned col);
maze *maze_new(unsigned rows, unsigned cols);
void maze_free(maze *);

#endif
