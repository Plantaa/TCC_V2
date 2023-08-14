#include "experiment.h"
#include <stdlib.h>

experiment experiment_create (int lines, int columns, int max_timesteps) {
	experiment e;
	e.r = result_create(max_timesteps);
	e.boards[0] = board_create (lines, columns);
	e.boards[1] = board_create (lines, columns);
	return e;
}

void experiment_init (experiment* e, double imune, double infected) {
	board_init(e->boards[0], infected, imune);
	board_zero(e->boards[1]);
	e->imune = imune;
	e->infected = infected;
	result_zero(&e->r);
}

void experiment_free (experiment* e) {
	board_free(e->boards[0]);
	board_free(e->boards[1]);
	result_free(&e->r);
	free(e);
}

void experiment_print (experiment e) {
	board_print(e.boards[0]);
	printf("Initial imunity: %f\n", e.imune);
	printf("Initial infected: %f\n", e.infected);
	result_print(e.r);
}

void experiment_reset (experiment* e) {
	board_init(e->boards[0], e->infected, e->imune);
	board_zero(e->boards[1]);
}

