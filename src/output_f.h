#ifndef OUTPUT_F_
#define OUTPUT_F_

#include <stdio.h>

typedef struct Out_files {
	FILE *infection_rate;
	FILE *pop_dinamycs;
}out_files;

out_files create_output(const char* path_pop_dyn, const char* path_inf_rate);
void close_output (out_files ofs);

#endif
