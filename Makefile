
PROGS:= main.o maze.o

CFLAGS = -Wall -std=c99 -g

Maze: $(PROGS)
	cc -o Maze $(PROGS) $(CFLAGS)

.PHONY: clean

clean:
	-rm maze $(PROGS)
