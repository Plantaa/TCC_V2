#include <limits.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

#include "board.h"
#include "random.h"
#include "transitions.h"

board* board_create (int lines, int columns) {
	board* b = malloc(sizeof(board));
	b->lines = lines;
	b->columns = columns;
	b->matrix = calloc(lines, sizeof(cell*));
	for (int c = 0; c < columns; c++)
		b->matrix[c] = calloc(columns, sizeof(cell));
	return b;
}

// void board_free (board* b) {
// 	for (int l = 0; l < b.lines; l++)
// 		free(b.matrix[l]);
// 	free(b.matrix);
// }

void board_init (board* b, int pc_infected, int pc_imune) {
	int population   = b->lines*b->columns;
	int abs_infected = pc_infected*(population/100);
	int abs_imune    = pc_imune*(population/100);
	board_zero(b);
	int l, c;
	for (int i = 0; i < abs_infected; i++) {
		l = roundf(randuniform(0, b->lines  -1));
		c = roundf(randuniform(0, b->columns-1));
		if (b->matrix[l][c].state == 0) 
			cell_fill(&b->matrix[l][c], roundf(randnormal(5, (2/3))), 1, 0);
		else i--;
	}
	for (int i = 0; i < abs_imune; i++) {
		l = roundf(randuniform(0, b->lines  -1));
		c = roundf(randuniform(0, b->columns-1));
		if (b->matrix[l][c].state == 0)
			cell_fill(&b->matrix[l][c], INT_MAX, 12, 0);
		else i--;
	}
}

void board_print (board* b) {
	for (int l = 0; l < b->lines; l++) {
		for (int c = 0; c < b->columns; c++)
			printf("%x   ", b->matrix[l][c].state);
		printf("\n\n");
	}
	printf("\n\n");
}

void board_zero (board* b) {
	for (int l = 0; l < b->lines; l++)
		for (int c = 0; c < b->columns; c++)
			b->matrix[l][c].state = b->matrix[l][c].duration = b->matrix[l][c].time = 0;
}

int count_deceased (board* b) {
	int deceased = 0;
	for (int l = 0; l < b->lines; l++)
		for (int c = 0; c < b->columns; c++)
			deceased += (b->matrix[l][c].state == 11);
	return deceased;
}

int count_infected (board* b) {
	int infected = 0;
	for (int l = 0; l < b->lines; l++)
		for (int c = 0; c < b->columns; c++)
			infected += (b->matrix[l][c].state > 0 && b->matrix[l][c].state < 11);
	return infected;
}

// int count_state (board* b, int state) {
// 	int count;
// 	for (int l = 0; l < b->lines; l++)
// 		for (int c = 0; c < b->columns; c++)
// 			count += (b->matrix[l][c].state == state);
// 	return count;
// }

int count_succeptible (board* b) {
	int succeptible = 0;
	for (int l = 0; l < b->lines; l++)
		for (int c = 0; c < b->columns; c++)
			succeptible += (b->matrix[l][c].state == 0);
	return succeptible;
}

int convergent (board* b) {
    for(int l = 0; l < b->lines; l++)
    	for(int c = 0; c < b->columns; c++)
        	if(b->matrix[l][c].state > 0 && b->matrix[l][c].state < 11)
            	return 0;    
    return 1;
}

cell infect (board *current, int line, int column) {
	cell new_cell;
	int neighbours = 8;
	float infection_chance = 0;
	for (int i = -1; i < 2; i++) {
		for (int j = -1; j < 2; j++) {
			cell* neighbour = &current->matrix[(line   + current->lines   + i) % current->lines  ]
									 		  [(column + current->columns + j) % current->columns];
			switch (neighbour->state) {
				case 1:
                    infection_chance += randnormal(80, (20/3));
                    break;
                case 2:
                    infection_chance += randnormal(80, (20/3));
                    break;
                case 3:
                    infection_chance += randnormal(80, (20/3));
                    break;
                case 4:
                    infection_chance += randnormal(80, (20/3));
                    break;
                case 5:
                    infection_chance += randnormal(20, (20/3));
                    break;
                case 6:
                    infection_chance += randnormal(20, (20/3));
                    break;
                case 7:
                    infection_chance += randnormal(80, (20/3));
                    break;
                case 8:
                    infection_chance += randnormal(80, (20/3));
                    break;
                case 9:
                    infection_chance += randnormal(80, (20/3));
                    break;
                case 10:
                    infection_chance += randnormal(80, (20/3));
                    break;
                default:
                    break;
			}
		}
	}
	infection_chance /= neighbours;
	float r = roundf(randuniform(0, 100));
	if (infection_chance > r)
		cell_fill(&new_cell, randnormal(5, (2/3)), 1, 0);
	else
		cell_fill(&new_cell, INT_MAX, 0, 0);
	return new_cell;
}

void timestep (board* current, board* future) {
	for (int l = 0; l < current->lines; l++)
		for (int c = 0; c < current->columns; c++) {
			if (current->matrix[l][c].state == 0)
				future->matrix[l][c] = infect(current, l, c);
			else if (++current->matrix[l][c].time > current->matrix[l][c].duration)
				future->matrix[l][c] = transition(current->matrix[l][c]);
			else
				future->matrix[l][c] = current->matrix[l][c];
		}
}

cell transition (cell expired_cell)  {
	cell new_cell;
	switch (expired_cell.state) {
		case 1:
			transitiond_1(&new_cell);
			break;
		case 2:
			cell_fill(&new_cell, roundf(randnormal(15, 2)), 8, 0);
			break;
		case 3:
			cell_fill(&new_cell, roundf(randnormal(14, 2)), 5, 0);
			break;
		case 4:
			cell_fill(&new_cell, roundf(randnormal(10, (4/3))), 6, 0);
			break;
		case 5:
			transition_5(&new_cell);
			break;
		case 6:
			transition_6(&new_cell);
			break;
		case 7:
			cell_fill(&new_cell, INT_MAX, 12, 0);
			break;
		case 8:
			cell_fill(&new_cell, INT_MAX, 12, 0);
			break;
		case 9:
			cell_fill(&new_cell, INT_MAX, 12, 0);
			break;
		case 10:
			cell_fill(&new_cell, INT_MAX, 12, 0);
			break;
		case 11: break;
		case 12: break;
	}
	return new_cell;
}

