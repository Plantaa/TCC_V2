#ifndef BOARD_H_
#define BOARD_H_

#include "cell.h"

typedef struct Board {
	cell** matrix;
	int lines;
	int columns;
}board;

board board_create (int lines, int columns);
void board_free (board b);
void board_init (board b, int infected, int imune);
void board_print (board b);
void board_zero (board b);
int convergent (board b);
int count_deceased (board b);
int count_infected (board b);
int count_state (board b, int state);
int count_succeptible (board b);
cell infect (board *current, board *future, int line, int column);
void timestep (board* current, board* future);
cell transition (cell expired_cell);

#endif
