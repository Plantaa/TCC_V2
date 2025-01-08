#include <math.h>
#include <stdlib.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846

double randuniform(double min, double max){
    double rand_double = (double)rand() / ((double)RAND_MAX);
    double rand_uniform = rand_double * (max - min) + min;
    return rand_uniform;
}

double randnormal(double mu, double sigma){
    double u1, u2, z1, max, min, rand_normal;
    do
    {
        max = mu+(3*sigma);
        min = mu-(3*sigma);
        u1 = (double)rand() / (double)RAND_MAX;
        u2 = (double)rand() / (double)RAND_MAX;

        z1 = sqrt(-2.0 * log(u1)) * cos(2.0 * M_PI * u2);

        rand_normal = z1 * sigma + mu;

    } while (rand_normal < 0 || rand_normal < min || rand_normal > max);

    return rand_normal;
}

#endif
