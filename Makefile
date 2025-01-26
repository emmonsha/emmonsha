CC=gcc

CFLAGS= -Wall -Wextra -Werror -std=c11
SANFLAGS= -fsanitize=address,leak 

SRC=tetris.c

all:

	$(CC) -g $(CFLAGS) $(SRC) -o tetris  -lncurses