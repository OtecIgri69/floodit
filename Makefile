CC = gcc
SRCS = src/main.c src/game.c src/utils.c
CFLAGS = -I./include/
LDFLAGS = -lSDL2 -lSDL2_ttf
TARGET = game

all:
	${CC} ${SRCS} ${CFLAGS} -o ${TARGET} ${LDFLAGS}