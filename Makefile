CC = gcc
LIBS = -lncurses -lmenu -lform -lpanel

interface:
	${CC} game.c interface.c -o robot ${LIBS}

