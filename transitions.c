#include <math.h>
#include <stdlib.h>

#include "random.h"
#include "transitions.h"
#include "utils.h"

void transition_1(cell* c) {
	double r = roundf(randuniform(0, 100));
	double tps[4] = {randnormal(55, 33), randnormal(30, 3), randnormal(10, 3), randnormal(5, 3)};
	normalize(tps, 4);
	if (tps[0] >= r) {
		cell_fill(c, roundf(randnormal(5, 3)), 2, 0);
		return;
	}	
	r-=tps[0];
	if (tps[1] >= r) {
		cell_fill(c, roundf(randnormal(12, (5/3))), 7, 0);
		return;
	}
	r-=tps[1];
	if (tps[2] >= tps[3]) {
		if (tps[2] >= r) {
			cell_fill(c, roundf(randnormal(4, (2/3))), 3, 0);
			return;
		}
		cell_fill(c, roundf(randnormal(3, (1/3))), 4, 0);
		return;
	}
	else {
		if (tps[3] >= r) {
			cell_fill(c, roundf(randnormal(3, (1/3))), 4, 0);
			return;
		}	
		cell_fill(c, roundf(randnormal(4, (2/3))), 3, 0);
	}
}

void transition_5 (cell* c) {
	double pt11 = randnormal(15, (10/3));
	double r = roundf(randuniform(0, 100));
	if (pt11 > r) {
		cell_fill(c, INT_MAX, 11, 0);
		return;
	}
	cell_fill(c, roundf(randnormal(4, (2/3))), 9, 0);
}

void transition_6 (cell* c) {
	double pt11 = randnormal(50, (10/3));
	double r = roundf(randuniform(0, 100));
	if (pt11 > r) {
		cell_fill(c, INT_MAX, 11, 0);
		return;
	}	
	cell_fill(c, roundf(randnormal(4, (2/3))), 10, 0);
}
