#include <stdio.h>
#include <stdlib.h>

#include "rt.h"

void rt_calculate (rt *infection_rate) {
	int i;
    for (i = 0; i < infection_rate->max_timesteps; i++) {
        if(infection_rate->quantity[i] < 1) {
            break;
        }
        infection_rate->infected[i] /= infection_rate->quantity[i];
    }
    for (int j = 0; j < i; j++) {
		infection_rate->infected[j] =
			(infection_rate->infected[j+1]/infection_rate->infected[j]);
	}
	infection_rate->furthest_timestep = i;
}

rt rt_create (int max_timesteps) {
	rt infection_rate;
	infection_rate.furthest_timestep = 0;
	infection_rate.max_timesteps = max_timesteps;
	infection_rate.infected = (double*) calloc(max_timesteps, sizeof(double));
	infection_rate.quantity = (int*) calloc(max_timesteps, sizeof(int));
	return infection_rate;
}

void rt_free (rt* infection_rate) {
		free(infection_rate->infected);
		free(infection_rate->quantity);
		free(infection_rate);
}

void rt_print (rt infection_rate) {
	printf("Infecction Rate: ");
	for (int i  = 0; i < infection_rate.max_timesteps; i++) {
		printf("%f:%d ", infection_rate.infected[i], infection_rate.quantity[i]);
	}
	printf("\n\n");
}

void rt_zero (rt infection_rate) {
	for (int i = 0; i < infection_rate.max_timesteps; i++)
		infection_rate.infected[i] = infection_rate.quantity[i] = infection_rate.furthest_timestep = 0;
}

