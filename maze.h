#ifndef MAZE_H
#define MAZE_H

#define NORTH 1
#define EAST  2
#define SOUTH 4
#define WEST  8

typedef struct _cell cell;
typedef struct _maze maze;
typedef unsigned char walls;

cell *maze_get_cell(maze *, unsigned row, unsigned col);
walls cell_get_walls(cell *);
maze *maze_new(unsigned rows, unsigned cols);
unsigned maze_get_rows(maze *);
unsigned maze_get_cols(maze *);
void maze_generate(maze *);
void maze_free(maze *);
void maze_print(maze *);

#endif
