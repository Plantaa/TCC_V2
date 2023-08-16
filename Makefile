CC		 = gcc
BIN		 = TCC
OBJ      = cell.o main.o random.o result.o rt.o board.o output_f.o experiment.o utils.o transitions.o
LINKOBJ  = cell.o main.o random.o result.o rt.o board.o output_f.o experiment.o utils.o transitions.o
CFLAGS   = -g3 -std=c99 -Wall -Wextra -Wpedantic -O1
RM       = rm.exe -f

$(BIN): $(OBJ)
	$(CC) $(LINKOBJ) -o $(BIN) $(LIBS) -lm

cell.o: cell.c
	$(CC) -c cell.c -o cell.o $(CFLAGS)

main.o: main.c
	$(CC) -c main.c -o main.o $(CFLAGS)

random.o: random.c
	$(CC) -c random.c -o random.o $(CFLAGS)

result.o: result.c
	$(CC) -c result.c -o result.o $(CFLAGS)

rt.o: rt.c
	$(CC) -c rt.c -o rt.o $(CFLAGS)

board.o: board.c
	$(CC) -c board.c -o board.o $(CFLAGS)

output_f.o: output_f.c
	$(CC) -c output_f.c -o output_f.o $(CFLAGS)

experiment.o: experiment.c
	$(CC) -c experiment.c -o experiment.o $(CFLAGS)

utils.o: utils.c
	$(CC) -c utils.c -o utils.o $(CFLAGS)

transitions.o: transitions.c
	$(CC) -c transitions.c -o transitions.o $(CFLAGS)

clean:
	rm -f *.o