#ifndef CELL_H_
#define CELL_H_

typedef struct Cell {
	int duration;
	int state;
	int time;
}cell;

cell* cell_create (void);
void cell_fill (cell* c, int duration, int state, int time);
void cell_print (cell c);
void cell_zero (cell* c);

#endif
