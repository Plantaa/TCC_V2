#ifndef RESULT_H_
#define RESULT_H_

#include <stdio.h>

#include "rt.h"

typedef struct Result {
	double succeptibles;
	double peak_infected;
	double deceased;
	double convergence;
	rt infection_rate;
}result;

result result_create (int max_timesteps);
void result_calculate (result *r, int samples, int lines, int columns);
void result_fill (result* r, double succeptibles, double peak_infected, double deceased, double convergence, rt infection_rate);
void result_free (result* r);
void result_print (result r);
void result_save (int initial_imunity, result *res, FILE *fp_dinamica_populacional, FILE *fp_taxa_infeccao);
void result_zero (result* r);

#endif
