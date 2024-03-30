#include "experiment.h"
#include <stdlib.h>

typedef struct ThreadInfo {
	int rank;
	int start;
	int end;
	int samples;
	int max_timesteps;
	experiment* e;
}threadInfo;

experiment experiment_create (int lines, int columns, int max_timesteps) {
	experiment e;
	e.r = result_create(max_timesteps);
	e.boardps[0] = board_create(lines, columns);
	e.boardps[1] = board_create(lines, columns);
	return e;
}

void experiment_init (experiment* e, double imune, double infected) {
	board_init(e->boardps[0], infected, imune);
	// board_zero(e->boardps[1]);
	e->imune = imune;
	e->infected = infected;
	result_zero(&e->r);
}

// void experiment_free (experiment* e) {
// 	board_free(e->boardps[0]);
// 	board_free(e->boardps[1]);
// 	result_free(&e->r);
// 	free(e);
// }

void experiment_print (experiment e) {
	board_print(e.boardps[0]);
	printf("Initial imunity: %f\n", e.imune);
	printf("Initial infected: %f\n", e.infected);
	result_print(e.r);
}

void experiment_reset (experiment* e) {
	board_init(e->boardps[0], e->infected, e->imune);
//	board_zero(e->boards[1]);
}

// void* experiment_run (void* info) {
// 	threadInfo* t_info = (threadInfo*) info;
// 	double peak_infected;
// 	int i, s ,t;
// 	board *current_board, *future_board;
// 	for (i = t_info->start; i < t_info->end; i++) {
// 		srand(time(NULL));
// 		experiment_init(t_info->e, t_info->e->imune, t_info->e->infected);
// 		for (s = 0; s < t_info->samples; s++) {
// 			peak_infected = 0;
// 			for (t = 0; t < t_info->max_timesteps; t++) {
// 				current_board = t_info->e->boardps[t%2];
// 				future_board  = t_info->e->boardps[(t+1)%2];

// 			}
// 		}
// 	}
// }