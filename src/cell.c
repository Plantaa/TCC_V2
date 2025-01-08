#include <stdlib.h>
#include <stdio.h>

#include "cell.h"

cell* cell_create (void) {
	return (cell*) calloc(1, sizeof(cell));
}

void cell_fill (cell* c, int duration, int state, int time) {
	c->duration = duration;
	c->state = state;
	c->time = time;
}

void cell_print (cell c) {
	printf("Duration: %d\n", c.duration);
	printf("State: %d\n", c.state);
	printf("Time: %d\n\n", c.time);
}

void cell_zero (cell* c) {
	cell_fill(c, 0, 0, 0);
}

