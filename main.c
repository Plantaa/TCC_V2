#include <string.h>
#include <stdlib.h>
#include <time.h>

#include "experiment.h"
#include "output_f.h"

#define INI_INF 10
#define SAMPLES 1000
#define LINES 1000
#define COLUMNS 1000
#define TIMESTEPS 16364
#define max(a,b) (((a) > (b)) ? (a) : (b))

int main (void) {
	int i, s, t, curr_infected;
	double peak_infected;
	char *dyn_pop_file_path, *inf_rate_file_path;
	dyn_pop_file_path  = (char*) malloc(64*sizeof(char));
	inf_rate_file_path = (char*) malloc(64*sizeof(char));
	sprintf(dyn_pop_file_path,  "Resultsd/%dx%dx%d_Population_dynamics.csv", LINES, COLUMNS, SAMPLES);
	sprintf(inf_rate_file_path, "Resultsd%dx%dx%d_Infection_rate.csv"     , LINES, COLUMNS, SAMPLES);
	out_files output = create_output(dyn_pop_file_path, inf_rate_file_path);
	free(dyn_pop_file_path);
	free(inf_rate_file_path);
	experiment e = experiment_create(LINES, COLUMNS, TIMESTEPS);
	board* current_board;
	board* future_board;
	for (i = 0; i <= 100-INI_INF; i++) {
		srand(time(0));
		experiment_init(&e, i, INI_INF);
		for (s = 0; s < SAMPLES; s++) {
			peak_infected = 0;
			for (t = 0; t < TIMESTEPS; t++) {
				current_board = &e.boards[t%2];
				future_board  = &e.boards[(t+1)%2];
				curr_infected = count_infected(*current_board);
				peak_infected = max(peak_infected, curr_infected);
				e.r.infection_rate.infected[t] += curr_infected;
				e.r.infection_rate.quantity[t] ++;
				timestep(current_board, future_board);
				if(convergent(*future_board)) break;
			}
			e.r.succeptibles  += count_succeptible(*future_board);
			e.r.deceased 	  += count_deceased   (*future_board);
			e.r.peak_infected += peak_infected;
			e.r.convergence   += t;
			srand(time(0));
			experiment_reset(&e);
		}
		result_calculate(&e.r, SAMPLES, LINES, COLUMNS);
		printf("\n\nInitial infected: %d\n", i);
		result_print(e.r);
		result_save(i, &e.r, output.pop_dinamycs, output.infection_rate);
	}
	close_output(output);
	return 0;
}
