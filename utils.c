#include "utils.h"

void normalize (double* arr, int size) {
	double sum = 0;
	for (int i = 0; i < size; i++) {
		sum += arr[i];
	}
	double normalizer = 100/sum;
	for (int i = 0; i < size; i++) {
		arr[i] *= normalizer;
	}
}
