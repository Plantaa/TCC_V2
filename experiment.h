#ifndef EXPERIMENT_H_
#define EXPERIMENT_H_

#include "board.h"
#include "result.h"

typedef struct Experiment {
	board* boardps[2];
	result r;
	double infected;
	double imune;
}experiment;

experiment experiment_create (int lines, int columns, int max_timesteps);
void experiment_init (experiment* e, double imune, double infected);
void experiment_free (experiment* e);
void experiment_print (experiment e);
void experiment_reset (experiment* e);

#endif
