CC=gcc
OBJS=main.o game.o move.o
EXEC=2048
DEBUG = -g
CFLAGS = -std=c99  -Wall -Werror $(DEBUG)

$(EXEC) : $(OBJS)
	$(CC) $(OBJS) -o $@
	
game.o: game.c move.h
main.o: main.c game.h move.h
move.o: move.c game.h

clean: 
	rm -f $(EXEC) $(OBJS)
	
