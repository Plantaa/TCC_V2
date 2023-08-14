#include <stdio.h>
#include <stdlib.h>

#include "result.h"

result result_create (int max_timesteps) {
	result r;
	r.succeptibles = 0;
	r.convergence = 0;
	r.deceased = 0;
	r.peak_infected = 0;
	r.infection_rate = rt_create(max_timesteps);
	return r;
}

void result_fill (result *r, double succeptibles, double peak_infected, double deceased, double convergence, rt infection_rate) {
	r->convergence = convergence;
	r->deceased = deceased;
	r->infection_rate = infection_rate;
	r->peak_infected = peak_infected;
	r->succeptibles = succeptibles;
}

void result_free (result* r) {
	rt_free(&r->infection_rate);
	free(r);
}

void result_calculate (result *r, int samples, int lines, int columns) {
	int population = lines*columns;
	r->convergence /= samples;
	r->deceased /= samples*population*0.01;
	r->peak_infected /= samples*population*0.01;
	r->succeptibles /= samples*population*0.01;
	rt_calculate(&r->infection_rate);
}

void result_print (result r) {
	printf("Succeptibles: %f%%; Peak Infected: %f%%; Deceased: %f%%; Convergence: %f\n", r.succeptibles, r.peak_infected, r.deceased, r.convergence);
//	rt_print(r.infection_rate);
}

void result_save (int initial_imunity, result *r, FILE *fp_pop_dynamics, FILE *fp_infection_rate) {
    fprintf(fp_pop_dynamics, "%d,%f,%f,%f,%f\n",
            initial_imunity,
            r->succeptibles,
            r->peak_infected,
            r->deceased,
            r->convergence);
    for(int i = 0; i < r->infection_rate.furthest_timestep; i++)
        fprintf(fp_infection_rate, "%f,", r->infection_rate.infected[i]);
    fprintf(fp_infection_rate, "\n");
}

void result_zero (result* r) {
	r->convergence = 0;
	r->succeptibles = 0;
	r->deceased = 0;
	r->peak_infected = 0;
	r->succeptibles = 0;
	rt_zero(r->infection_rate);
}

