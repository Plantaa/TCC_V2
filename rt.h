#ifndef RT_H_
#define RT_H_

typedef struct Rt {
	int furthest_timestep;
	int max_timesteps;
	double* infected;
	int* quantity;
}rt;

void rt_calculate (rt *infecction_rate);
rt rt_create (int max_timesteps);
void rt_free (rt* infection_rate);
void rt_print (rt infection_rate);
void rt_zero (rt infection_rate);

#endif
