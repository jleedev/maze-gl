#include "maze.h"

int main(void) {
	maze *m = maze_new(4, 5);
	maze_free(m);
}
