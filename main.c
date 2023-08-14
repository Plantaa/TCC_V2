#include <string.h>
#include <stdlib.h>
#include <time.h>

#include "experiment.h"
#include "output_f.h"

#define INI_INF 10
#define SAMPLES 100
#define LINES 100
#define COLUMNS 100
#define TIMESTEPS 16364
#define max(a,b) (((a) > (b)) ? (a) : (b))

int main (void) {
	
	int i, t, s, curr_infected;
	double peak_infected;
	out_files output = create_output("din_pop_test.csv", "inf_rate_test.csv");
	experiment e = experiment_create(LINES, COLUMNS, TIMESTEPS);
	board* current_board;
	board* future_board;
	for (i = 0; i <= 100-INI_INF; i++) {
		peak_infected = 0;
		experiment_init(&e, i, INI_INF);
		for (s = 0; s < SAMPLES; s++) {
			srand(time(0));
			experiment_reset(&e);
			for (t = 0; t < TIMESTEPS; t++) {
				current_board = &e.boards[t%2];
				future_board = &e.boards[(t+1)%2];
				curr_infected = count_infected(*current_board);
				peak_infected = max(peak_infected, curr_infected);
				e.r.infection_rate.infected[t] += curr_infected;
				e.r.infection_rate.quantity[t]++;
//				board_print(*current_board);
//				getchar();
				timestep(current_board, future_board);
				if(convergent(*future_board)) break;
			}
			e.r.convergence += t;
			e.r.deceased += count_deceased(*future_board);
			e.r.peak_infected += peak_infected;
			e.r.succeptibles += count_succeptible(*future_board);
//			printf("Initial Imunity: %d; Sample: %d\n", i, s);
//			printf("Succeptibles: %f; Peak Infected: %f; Deceased: %f; Convergence: %f\n", e.r.succeptibles, e.r.peak_infected, e.r.deceased, e.r.convergence);
//			board_print(*future_board);
//			getchar();
		}
		result_calculate(&e.r, SAMPLES, LINES, COLUMNS);
		printf("\n\nInitial infected: %d\n", i);
		result_print(e.r);
		result_save(i, &e.r, output.pop_dinamycs, output.infection_rate);
	}
	close_output(output);
	return 0;
}
