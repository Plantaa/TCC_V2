#include <stdio.h>
#include <stdlib.h>

#include "output_f.h"

out_files create_output(const char* path_pop_dyn, const char* path_inf_rate) {
	out_files output;
	output.pop_dinamycs = fopen(path_pop_dyn, "w");
	if(output.pop_dinamycs == NULL) {
		perror("Unable to open population dynamics output file.\n");
		exit(1);
	}
	fprintf(output.pop_dinamycs, "Infected,Succeptible,Peak,Deceased,Timesteps\n");
	output.infection_rate = fopen(path_inf_rate, "w");
	if(output.infection_rate == NULL) {
		perror("Unable to open infection rate output file.\n");
		exit(1);
	}
	return output;
}

void close_output (out_files ofs) {
	fclose(ofs.infection_rate);
	fclose(ofs.pop_dinamycs);
}
