#include <time.h>
#include <stdlib.h>

#include "maze.h"

int main(void) {
	srandom(time(NULL));
	maze *m = maze_new(4, 5);
	maze_print(m);
	maze_free(m);
}
